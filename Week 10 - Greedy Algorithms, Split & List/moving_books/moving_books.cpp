#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

void testcase(){
    int n, m; std::cin >> n >> m;
    std::vector<int> strength(n);
    int strongest = 0;
    for(int i = 0; i < n; ++i){
        std::cin >> strength[i];
        if(strength[i] > strongest) strongest = strength[i];
    }
    std::sort(strength.begin(), strength.end());
    std::list<int> boxes;
    int heaviest = 0;
    for(int i = 0; i < m; ++i){
        int b; std::cin >> b;
        if(b > heaviest) heaviest = b;
        boxes.push_back(b);
    }
    boxes.sort();
    if(heaviest>strongest) {
        std::cout << "impossible" << std::endl;
        return;
    }
    std::vector<int> turns (n, 0);
    int count = m;
    int max_turns = 0;
    
    for(int i = 0; i < n && count > 0; ++i){
        while(strength[i] >= *boxes.begin() && count > 0){
            if(turns[i] == max_turns && count <= (n-i-1)*max_turns) break; // no need to overload this person anymore remaining can do the carrying
            boxes.pop_front();
            turns[i]++;
            count--;
            max_turns = std::max(max_turns, turns[i]);
        }  
    }
    std::cout << max_turns*3 -1 << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}