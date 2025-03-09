#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

void largest_proper_divisor(int n) {
    if(n < 2)
    {
        throw std::invalid_argument("largest proper divisor is not defined for n=" + std::to_string(n));
    }

    int lcp{1};

    for(int i = 2; i <= sqrt(n); ++i)
    {
        if(n % i == 0)
        {
            lcp = n/i;
            break;
        }
    }
    
    std::cout << "result=" << lcp << std::endl;
} 

void process_input(int n) {
    try {
        largest_proper_divisor(n);
    }
    catch(const std::invalid_argument &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "returning control flow to caller" << std::endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n{0};

    std::cin >> n;
    process_input(n);

    return 0;
}
