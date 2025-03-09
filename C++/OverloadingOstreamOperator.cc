#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <string>

class Person
{
private:
    std::string first_name_;
    std::string last_name_;
public:
    Person(std::string_view first_name, std::string_view last_name);
    ~Person();
    friend std::ostream &operator<<(std::ostream &lhs, const Person &person);
};

Person::Person(std::string_view first_name, std::string_view last_name)
    : first_name_{first_name}, last_name_{last_name}
{
}

Person::~Person()
{
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    std::string first_name;
    std::string last_name;
    std::string some_string_value;

    std::cin >> first_name;
    std::cin >> last_name;
    std::cin >> some_string_value;

    Person p(first_name, last_name);

    std::cout << p << " " << some_string_value << std::endl;

    return 0;
}

std::ostream &operator<<(std::ostream &lhs, const Person &person)
{
    lhs << "first_name=" << person.first_name_ << ",last_name=" << person.last_name_;
    return lhs;
}
