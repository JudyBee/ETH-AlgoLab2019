#include <iostream>
#include <algorithm>
#include <vector>

void testcase(){
    int n; std::cin >> n;
    std::vector<int> dom(n);
    for(int i = 0; i < n; ++i){
        int d; std::cin >> d;
        dom[i] = d;
    }

    int curr = dom[0] -1;
    int count = 1;
    for(int i = 1; i < n; ++i){
        if(curr == 0) break;
        curr = std::max(curr-1, dom[i]-1);
        count++;
    }
    std::cout << count << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t; 
    while(t--) testcase();
}