#include <iostream>
#include <string>

void testcase(){
    int a; std::cin >>a;
    long long b; std::cin >> b;
    std::string c; std::cin >> c;
    double d; std::cin >> d;
    std::cout << std::setprecision(2) << a << " " << b << " " << c << " " << d << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}