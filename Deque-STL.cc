#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <deque>

auto findMax(const std::deque<int> &deque_){
    return std::max_element(deque_.begin(), deque_.end());
}


struct Input {
    std::vector<int> vec;
    size_t sub_array_size;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int total{0};
    std::cin >> total;

    std::vector<Input> vecs;
    for(auto i = 0; i < total; ++ i){
        int arr_size{0};
        Input input;
        std::cin >> arr_size >> input.sub_array_size;

        for(auto j = 0; j < arr_size; ++j)
        {
            int value{0};
            std::cin >> value;
            input.vec.push_back(value);
        }

        vecs.push_back(input);
    }
    
    for(const auto &input: vecs){
        std::deque<int> deque_{input.vec.begin(), input.vec.begin() + input.sub_array_size};
        auto current_max_it = std::max_element(deque_.begin(), deque_.end());
        auto total_loop = input.vec.size() - input.sub_array_size + 1;
        for(auto i = 0; i < total_loop - 1; ++ i){
            std::cout << *current_max_it << " ";
            if(current_max_it == deque_.begin()){
                current_max_it = std::max_element(deque_.begin() + 1, deque_.end());
            }
            deque_.pop_front();
            auto next_index = i + input.sub_array_size;
            auto next_value = input.vec.at(next_index);
            deque_.push_back(input.vec.at(
                next_index));
            if(next_value > *current_max_it){
                current_max_it = deque_.end() - 1;
            }
        }
        
        std::cout << *current_max_it << std::endl;
    }
    
    return 0;
}
