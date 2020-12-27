#include <iostream>
#include <vector>

void testcase(){
    int n; std::cin >>n;
    std::vector<int> vals(n);
    std::vector<int> sums(n);
    int evens = 0;
    int odds = 0;
    for(int i = 0; i < n; ++i){
        int x; std::cin >>x;
        vals[i] = x;
        if(i>0) sums[i] = sums[i-1] + x;
        else sums[i] = x;
        if(sums[i]%2) odds++;
        else evens++;
    }
    int sol = (evens)*(evens-1)/2 + (odds)*(odds-1)/2 + evens;
    
    std::cout << sol << std::endl;
}


int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >>t;
    while(t--) testcase();
}