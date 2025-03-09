#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <array>
#include <memory>

class Person
{
public:
    enum class Type{
        Professor_t = 1,
        Student_t = 2
    };
    virtual ~Person() = default;
    virtual void getData(std::string_view input_string);
    virtual void putData();

protected:
    virtual int getCurrentId() = 0;
    virtual void getSpecificProperties(std::string_view input_string) = 0;
    virtual void putSpecificProperties() = 0;
    
private:
    int cur_id_;
    std::string name_;
    int age_;
};

class Professor : public Person
{
private:
    int publications_;
    
    inline static int id_count = 0;
    int getCurrentId() override;
    void getSpecificProperties(std::string_view input_string) override;
    void putSpecificProperties() override;
};
class Student : public Person
{
private:
    std::array<int, 6> marks_;
    
    inline static int id_count = 0;
    int getCurrentId() override;
    void getSpecificProperties(std::string_view input_string) override;
    void putSpecificProperties() override;
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    // Input 
    int number{0};
    std::cin >> number;
    
    std::vector<std::unique_ptr<Person>> people;
    for(auto i = 0; i < number; ++i){
        int type;
        std::string person_properties;
        std::cin >> type;
        std::cin.ignore();
        std::getline(std::cin, person_properties);
        std::unique_ptr<Person> person;
        if(static_cast<Person::Type>(type) == Person::Type::Professor_t){
            person = std::make_unique<Professor>();
            
        }
        else if(static_cast<Person::Type>(type) == Person::Type::Student_t){
            person = std::make_unique<Student>();
        }
        person->getData(person_properties);
        people.push_back(std::move(person));
    }
    
    // Output
    for(const auto &person: people){
        person->putData();
    }
    
    return 0;
}

void Person::getData(std::string_view input_string){
    // current id
    this->cur_id_ = this->getCurrentId();
    
    // name
    auto start_name_pos = 0;
    auto end_name_pos = input_string.find_first_of(" ");
    this->name_ = std::string(input_string.substr(start_name_pos, end_name_pos));
    
    // age
    auto start_age_pos = end_name_pos + 1;
    auto end_age_pos = input_string.find_first_of(" ", end_name_pos + 1);
    this->age_ = std::stoi(std::string(input_string.substr(start_age_pos, end_age_pos)));
    
    // remain
    auto remain = input_string.substr(end_age_pos + 1);
    this->getSpecificProperties(remain);
}

void Person::putData() {
    std::cout << this->name_ << " " << this->age_ << " ";
    this->putSpecificProperties();
    std::cout << " " << this->cur_id_ << std::endl;
}

int Professor::getCurrentId(){
    ++Professor::id_count;
    return Professor::id_count;
}

void Professor::getSpecificProperties(std::string_view input_string) {
    auto start_publications_pos = 0;
    auto end_publications_pos = input_string.find_first_of(" ");
    this->publications_ = std::stoi(std::string(input_string.substr(
        start_publications_pos, end_publications_pos)));
}

void Professor::putSpecificProperties() {
    std::cout << this->publications_;
}

int Student::getCurrentId(){
    ++Student::id_count;
    return Student::id_count;
}

void Student::getSpecificProperties(std::string_view input_string) {
    size_t start_current_mark = -1;
    size_t end_current_mark = -1;
    for(auto i = 0; i < marks_.size(); ++i){
        start_current_mark = end_current_mark + 1;
        end_current_mark = input_string.find_first_of(" ", start_current_mark + 1);
        auto current_mark = std::stoi(std::string(input_string.substr(
            start_current_mark, end_current_mark)));
        this->marks_.at(i) = current_mark;
    }
}

void Student::putSpecificProperties() {
    int sum{0};
    for(const auto &mark: this->marks_){
        sum += mark;
    }
    std::cout << sum;
}
