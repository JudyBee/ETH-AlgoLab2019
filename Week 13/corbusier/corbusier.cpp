#include <iostream> 
#include <vector> 

void testcase(){
    int n,i,k; std::cin >> n >> i >> k;
    int goal = i%k;
    std::vector<int> height_mod_k (n);
    for(int j = 0; j < n; ++j){
        long h; std::cin >> h;
        height_mod_k[j] = h%k;
    }

    std::vector<std::vector<bool> > DP (n, std::vector<bool> (k, false));
    DP[0][0] = true;
    DP[0][height_mod_k[0]] = true;
    
    for(int j = 1; j < n; j++){
        for(int l = 0; l < k; ++l){
            int what_i_need = (k+l-height_mod_k[j])%k; 
            DP[j][l] = DP[j-1][l] || DP[j-1][what_i_need];
        }
    }
    
    for(int j = n-1; j >0; --j){
        if(DP[j-1][(k-height_mod_k[j] + goal)%k]){
            std::cout << "yes" << std::endl;
            return;
        }
    }
    std::cout << "no" << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t; 
    while(t--) testcase();
}