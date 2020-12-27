#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> 
#include <cmath>

void testcase(int count){
    int n; std::cin >> n;
    std::vector<int> locations(n);
    for(int i = 0; i < n; ++i){
        int x; std::cin >> x;
        locations[i] = x;
    }
    std::sort(locations.begin(), locations.end());
    int i1 = 0;
    int i2 = 0;
    int curr_max = 0; // number parsols in reach
    int min_d = INT_MAX; // max distance person needs to walk
    std::vector<int> curr_best; // locations best is attained
   

    while(i2 < n && i1 < n){
        int back = locations[i2];
        int front = locations[i1];
        if(front - back <= 200){
            int count = i1 - i2+1;
            if(count>curr_max){ // more people reachable
                curr_max = count;
                curr_best.clear();
                min_d = std::max(std::abs(front - (back+front)/2), std::abs((back+front)/2 - back));
                curr_best.push_back(back+min_d);
                curr_best.push_back(front - min_d);
            } else if(count == curr_max){ // same number reachable
                int curr_d = std::max(std::abs(front - (back+front)/2), std::abs((back+front)/2 - back));
                if(min_d > curr_d){ // test if longest distance is shorter
                    min_d = curr_d;
                    curr_best.clear();
                    curr_best.push_back(back+min_d);
                    curr_best.push_back(front - min_d);
                } else if (min_d < curr_d){ 
                    i1++;
                    continue;
                } else {
                    curr_best.push_back(back+min_d);
                    curr_best.push_back(front - min_d);
                }
            }
            i1++;
        } else 
            i2++;
    }
    std::cout << curr_max << " " << min_d << std::endl;
    std::sort(curr_best.begin(), curr_best.end());
    auto last = std::unique(curr_best.begin(), curr_best.end());
    curr_best.erase(last, curr_best.end());
    std::sort(curr_best.begin(), curr_best.end());
    for(auto it = curr_best.begin(); it != curr_best.end();){
        std::cout << *it;
        if(++it != curr_best.end()) std::cout << " ";
    }
    std::cout << std::endl;

}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    int count = 1;
    while(t--) {
        testcase(count);
        count++;
    }
}