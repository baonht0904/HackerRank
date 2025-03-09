#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#include <stdexcept>

class Server {
public:
    static long long compute(long long A, long long B) {
        if(A < 0) {
			throw std::invalid_argument("A is negative");
		}
		std::vector<int> v(A, 0);
		int real = -1, cmplx = sqrt(-1);
		if(B == 0) throw 0;
		real = (A/B)*real;
		int ans = v.at(B);
		return real + A - B*ans;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
        long long server_load{0};
        std::cin >> server_load;
        std::vector<long long> As;
        std::vector<long long> Bs;
        for(auto i = 0; i < server_load; ++i){
            long long a{0};
            long long b{0};
            std::cin >> a >> b;
            As.push_back(a);
            Bs.push_back(b);
        }
        for(auto i = 0; i < server_load; ++i){
            try {
                std::cout << Server::compute(As.at(i), Bs.at(i)) << std::endl;
            } catch (const std::bad_alloc &){
                std::cout << "Not enough memory" << std::endl;
            } catch (const std::exception &ex) {
                std::cout << "Exception: " << ex.what()  << std::endl;
            } catch (...){
                std::cout << "Other Exception" << std::endl;
            }
        }
        
        std::cout << server_load << std::endl;
        
    
    return 0;
}
