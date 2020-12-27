#include <iostream>
#include <vector>
#include <cmath>

int main(){
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++){
        int num, key;
        bool found = false;
        std::cin >> num >> key;
        std::vector<int> a(num);
        std::vector<int> sums(num);
        std::cin >> a[0];
        sums[0] = a[0];
        if(a[0] == key){
            std::cout << "0 0" << std::endl;
            found = true;
        }
        for(int j = 1; j < num; j++){
            std::cin >> a[j];
            sums[j] = a[j] + sums[j-1];
            if(sums[j] == key){
                std::cout << "0 " << j <<std::endl;
                found = true;
            }
        }
        
        if(found){
            continue;
        }
        int low = 0;
        int high = num-1;
        int min = abs(sums[num-1]-key);
        int curr;
        for(int j = 0; j < num; j++){
            for(int k = j; k < num; k++){
                if(j == 0){
                    curr = abs(key - sums[k]);
                }
                else{
                    curr = abs(key - sums[k] + sums[j-1]);
                }
                if(curr == key){
                    std::cout << j << " " << k << std::endl;
                    found = true;
                    break;
                }
                if(curr < min){
                    low = j;
                    high = k;
                    min = curr;
                }
            }
            if(found){
                break;
            }
        }
        if(found){
            continue;
        }
        std::cout << low << " " << high << std::endl;
    }
}