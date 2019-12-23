#include <iostream>
#include <queue>

typedef std::priority_queue<int> max_heap;
typedef std::priority_queue<int, std::vector<int>, std::greater<int> > min_heap;

int main(){
    int t; 
    std::cin >> t;
    for (int i = 0; i < t; i++){
        int n, curr;
        std::cin >> n;
        max_heap max;
        min_heap min;
        for(int j = 0; j < n; j++){
            std::cin >> curr;
            max.push(curr);
            min.push(curr);
        }
        int x; 
        std::cin >> x;
        if (x == 0){
            while(!min.empty()){
                std::cout << min.top() << " ";
                min.pop();
            }
        }
        else{
            while(!max.empty()){
                std::cout << max.top() << " ";
                max.pop();
            }
        }
        std::cout << std::endl;
    }
}