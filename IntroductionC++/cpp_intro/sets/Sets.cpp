#include <iostream>
#include <set>

int main(){
    int t, q, a, b;
    std::cin >> t;
    for (int i = 0; i < t; i++){
        std::cin >> q;
        std::set<int> s;
        for (int l = 0; l < q; l++){
            std::cin >> a;
            std:: cin >> b;
            if (a == 0){
                s.insert(b);
            }
            else if (a == 1){
                s.erase(b);
            }
        }
        if (s.empty()){
                std::cout << "Empty\n";
            }
        else{
            std::set<int>::iterator it =s.begin();
            for(int j = 0; j < s.size(); j++){
                std::cout << *it;
                std::cout << " ";
                it++;
            }
            printf("\n");
        }
    }
}