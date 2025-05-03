#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;

// Define specializations for the Traits class template here.
#include <map>
#include <string>

const map<Fruit, string> k_fruit_string{
    {Fruit::apple, "apple"},
    {Fruit::orange, "orange"},
    {Fruit::pear, "pear"},
};

const map<Color, string> k_color_string{
    {Color::red, "red"},
    {Color::green, "green"},
    {Color::orange, "orange"}
};

template <typename T> struct Traits {
    static string name(int index)
    {
        try
        {
            if (std::is_same<T, Fruit>::value) {
                if(index >= k_fruit_string.size()) {
                    throw std::out_of_range("Fruit out of range");
                }
                return k_fruit_string.at(static_cast<Fruit>(index));
            }
            else if (std::is_same<T, Color>::value) {
                if(index >= k_color_string.size()) {
                    throw std::out_of_range("Color out of range");
                }
                return k_color_string.at(static_cast<Color>(index));
            }
            else {
                throw std::out_of_range("Enum out of range");
            }
        }
        catch(const std::out_of_range&)
        {
            return "unknown";
        }
    }
};

int main()
{
	int t = 0; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}
