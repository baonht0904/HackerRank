#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <map>
#include <stdexcept>

// ------------------------------------ Utilities ------------------------------------------
// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// ------------------------------------ Decleare ------------------------------------------
class HrmlNotFound : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class HrmlTag {
public:
    HrmlTag getTag(const std::string &name) const;
    std::string getValue(const std::string &key) const;
    void parseTag(std::vector<std::string> lines);
private:
    std::map<std::string, HrmlTag, std::less<>> children_tags_;
    std::map<std::string, std::string, std::less<>> attributes_;

    std::string extractTagName(std::string_view line) const;
    std::map<std::string, std::string, std::less<>> extractAttributes(std::string_view line) const;
    size_t findClosingTagInLines(std::string_view tag_name, const std::vector<std::string> &lines) const;
};

class HrmlQuery {
public:
    std::string executeQuery(const HrmlTag &tag) const;
    void parseQuery(std::string_view query_string);
    void display();
private:
    std::vector<std::string> tag_names_;
    std::string attributes_key_;
    
    void parseTags(std::string_view query_string);
    void parseAttribute(std::string_view query_string);
};


// ------------------------------------ Main ------------------------------------------
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int hrml_quantity{0};
    int query_quantity{0};
    
    std::vector<std::string> hrml_lines;
    std::vector<std::string> query_lines;
    
    std::cin >> hrml_quantity >> query_quantity;
    std::cin.ignore();

    // Read Hrml lines
    for(auto i = 0; i < hrml_quantity; ++i) {    
        std::string line;
        std::getline(std::cin, line);
        hrml_lines.push_back(line);
    }
    
    // Read query lines
    for(auto i = 0; i < query_quantity; ++i) {
        std::string line;
        std::getline(std::cin, line);
        query_lines.push_back(line);
    }
    
    // Parse
    HrmlTag hrml_doc;
    hrml_doc.parseTag(hrml_lines);
    
    for(const auto &line: query_lines) {
        HrmlQuery query;
        query.parseQuery(line);
        std::cout << query.executeQuery(hrml_doc) << std::endl;
    }
    
    return 0;
}


// ------------------------------------ Define ------------------------------------------
// HrmlTag
HrmlTag HrmlTag::getTag(const std::string &name) const {
    try {
    {
        return children_tags_.at(name);
    }
    } catch (const std::out_of_range &) {
        throw HrmlNotFound("Tag not found " + name);
    }
}

std::string HrmlTag::getValue(const std::string &key) const {
    try {
        return attributes_.at(key);
    } catch (const std::out_of_range &) {
        throw HrmlNotFound("Attribute not found " + key);
    }
}

void HrmlTag::parseTag(std::vector<std::string> lines) {
     // copy lines to prevent modify source value 
    while(!lines.empty()) {
        HrmlTag current_tag;
        auto line = lines.at(0);
        auto tag_name = extractTagName(line);
        auto closing_tag_index = findClosingTagInLines(tag_name, lines);
        
        current_tag.attributes_ = extractAttributes(line);
        current_tag.parseTag(std::vector<std::string>{lines.begin() + 1, lines.begin() + closing_tag_index});

        children_tags_.try_emplace(tag_name, current_tag);
        lines.erase(lines.begin(), lines.begin() + closing_tag_index + 1);
    }
}

std::string HrmlTag::extractTagName(std::string_view line)  const {
    auto start_pos = line.find("<") + 1;
    auto end_pos = line.find_first_of(" >");
    auto tag_name = line.substr(start_pos, end_pos - start_pos);
    return std::string{tag_name};
}

std::map<std::string, std::string, std::less<>> HrmlTag::extractAttributes(std::string_view line) const {
    if(line.find("=") == std::string::npos) {
        // No attributes.
        return std::map<std::string, std::string, std::less<>>();
    }

    auto attributes_start_pos = line.find_first_of(" ") + 1;
    auto attributes_end_pos = line.find(">");
    std::string attributes_string {line.substr(attributes_start_pos, attributes_end_pos - attributes_start_pos)};

    std::map<std::string, std::string, std::less<>> attributes_map;
    while(!attributes_string.empty()) {
        // Find key
        auto end_key_pos = attributes_string.find_first_of("=");
        std::string key{attributes_string.substr(0, end_key_pos)};
        trim(key);

        // Find value
        auto start_value_pos = attributes_string.find_first_of("\"") + 1;
        auto end_value_pos = attributes_string.find_first_of("\"", start_value_pos);
        std::string value {attributes_string.substr(start_value_pos, end_value_pos - start_value_pos)};
        trim(value);

        // append and increase
        attributes_map.try_emplace(key, value);
        attributes_string.erase(0, end_value_pos + 1);
    }

    return attributes_map;
}

size_t HrmlTag::findClosingTagInLines(std::string_view tag_name, const std::vector<std::string> &lines) const
{
    for(auto index = 0; index < lines.size(); ++index) {
        if(lines.at(index).find("</" + std::string{tag_name}) != std::string::npos) {
            return index;
        }
    }
    throw std::invalid_argument("Invalid input hrmls");
}

// HrmlQuery
std::string HrmlQuery::executeQuery(const HrmlTag &tag) const {
    try {
        HrmlTag target_tag = tag;
        for(const auto &name: tag_names_)
        {
            target_tag = target_tag.getTag(name);
        }
        return target_tag.getValue(attributes_key_);
    } catch (const HrmlNotFound &) {
        return "Not Found!";
    }
}

void HrmlQuery::parseQuery(std::string_view query_string) {
    this->parseTags(query_string);
    this->parseAttribute(query_string);
}

void HrmlQuery::parseTags(std::string_view query_string) {
    auto end_of_tag = query_string.find("~");
    std::string tag_strings {query_string.substr(0, end_of_tag)};
    
    std::string delimiter{"."};
    auto dot_index = tag_strings.find(delimiter);
    while(dot_index != std::string::npos)
    {
        std::string token = {tag_strings.substr(0, dot_index)};
        tag_names_.push_back(token);
        tag_strings.erase(0, dot_index + delimiter.length());
        dot_index = tag_strings.find(delimiter);
    }
    tag_names_.push_back(tag_strings);
}

void HrmlQuery::parseAttribute(std::string_view query_string) {
    auto start_of_attribute = query_string.find("~") + 1;
    attributes_key_ = query_string.substr(start_of_attribute,
                                          query_string.length() - start_of_attribute);
}

void HrmlQuery::display(){
    std::cout << "[";
    for(auto index = 0; index < tag_names_.size(); ++index)
    {
        if(index > 0)
        {
            std::cout << ", ";
        }
        std::cout << tag_names_.at(index);
    }
    std::cout << "]";
    
    std::cout << " -> " << attributes_key_ << std::endl;
}
