#include <iostream>
#include <map>
#include <string>
#include <set>

int main() {
    int t,q, a;
    std::string b, find;
    std::cin >> t;
    for (int i = 0; i < t; i++){
        std::multimap<std::string, int> m;
        std::multimap<std::string, int>::iterator it;
        std::cin >> q;
        for(int j = 0; j < q; j++){
            std::cin >> a;
            std::cin >> b;
            if (a == 0){
                m.erase(b);
            }
            else {
                m.insert(std::pair<std::string, int>(b.c_str(),a));
            }
        }
        std::cin >> find;
        if (m.count(find)> 0){
            std::set<int> s;
            for(it = m.begin(); it != m.end(); ++it ) {
                if(it->first.compare(find)==0){
                    s.insert(it->second);
                }
            }
            std::set<int>::iterator iter;
            for(iter = s.begin(); iter!= s.end(); iter++){
                std::cout << *iter;
                std::cout << " ";
            }
        }
        else{
            std::cout << "Empty";
        }
        std::cout << std::endl;
    }
}