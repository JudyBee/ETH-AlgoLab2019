#include <iostream>
#include <vector>
#include <climits>

void testcase(){
    int n, m, k; std::cin >> n >> m >> k;
    std::vector<int> vals(n);
    for(int i = 0; i < n; ++i){
        int curr; std::cin >> curr;
        vals[i] = curr;
    }
    std::vector<std::vector<int>> dp(n, std::vector<int> (n, INT_MAX));
    
    int last_coin = (n-k)%m;
    if(!last_coin) last_coin+=m;

    for(int j = 0; j < n; ++j){ // front
        for(int i = j; i >= 0; --i){ // back
            if(j-i+1 < m+last_coin){ // we will get at most 1 more coin
                if(j-i+1 < last_coin) // no more coin
                    dp[i][j] = 0;
                else if(j-i+1 == last_coin) // this is your last coin pick higher value one
                     dp[i][j] = std::max(vals[i], vals[j]);
                else // opponent has some moves before I get to go
                    dp[i][j] = std::min(dp[i+1][j], dp[i][j-1]);
            } else { // we will get at least one more coin
                if((j-i+1-last_coin)%m == 0) // its currently our turn
                    dp[i][j] = std::max(vals[i] + dp[i+1][j], vals[j] + dp[i][j-1]);
                 else { // opponent gets to go before we go
                    dp[i][j] = std::min(dp[i+1][j], dp[i][j-1]);
                }
            }
        }
    }
    std::cout << dp[0][n-1] << std::endl; 
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}