#include <iostream>
#include <vector>
#include <climits>

void testcase(){
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
                curr_best.push_back((front+back)/2);
                if((front + back)%2) curr_best.push_back(curr_best.back()+1);
                min_d = curr_best.back()-back;
            } else if(count == curr_max){ // same number reachable
                if(min_d > front - (front+back)/2){ // test if longest distance is shorter
                    min_d = (front+back)/2;
                    curr_best.clear();
                    curr_best.push_back((front+back)/2);
                    if((front + back)%2) curr_best.push_back(curr_best.back()+1);
                } else { // add new location
                    curr_best.push_back((front+back)/2);
                    if((front + back)%2) curr_best.push_back(curr_best.back()+1);
                }
            }
            i1++;
        } else 
            i2++;
    }
    std::cout << curr_max << " " << min_d << std::endl;
    for(auto it = curr_best.begin(); it != curr_best.end();){
        std::cout << *it;
        if(++it != curr_best.end()) std::cout << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}