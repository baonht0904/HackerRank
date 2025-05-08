#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <iomanip>

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin >> t;
    for(auto i = 0; i < t; ++i) {
        double a, b, c;
        cin >> a >> b >> c;
        auto defaultFlags = std::cout.flags();
        cout << nouppercase << setbase(16) << showbase << static_cast<long>(a) << endl;
        cout << setfill('_') << setw(15) << showpos
             << fixed << setprecision(2) << b << endl;
        cout << noshowpos << setprecision(9) << scientific << uppercase << c << endl;
        std::cout.flags(defaultFlags); 
    }
    return 0;
}
