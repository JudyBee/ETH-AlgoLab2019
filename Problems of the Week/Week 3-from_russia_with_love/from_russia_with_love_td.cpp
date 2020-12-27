#include <iostream>
#include <vector>
#include <climits> 

std::vector<std::vector<int> > dp;

int play(int i, int j, std::vector<int> & coins, int num, int m){
    if(j < i)  // not valid
        return 0; 
    if(dp[i][j]!= -1)  // already computed return knowledge
        return dp[i][j]; 
    if(j-i + 1 < num+1)  // i will not get another coin
        dp[i][j] = 0; 
    if(num == 0) { // my turn
        int left = coins[i] + play(i+1, j, coins, m-1, m);
        int right = coins[j] + play(i, j-1, coins, m-1, m);
        dp[i][j] = std::max(left, right);
        return dp[i][j];
    }
    dp[i][j] = std::min(play(i+1, j, coins, num-1, m), play(i, j-1, coins, num-1, m));
    return dp[i][j];
}

void testcase(){
    int n, m, k; std::cin >> n >> m >> k;
    std::vector<int> coin(n);
    for(int i = 0; i < n; ++i){
        int x; std::cin >> x;
        coin[i] = x;
    }
    dp.clear();
    dp = std::vector<std::vector<int> > (n, std::vector<int>(n, -1));

    int sol = INT_MAX;
    for(int i = 0; i <= k; ++i){
        int left = play(i+1, n-1-(k-i), coin, m-1, m);
        int right = play(i, n-1-(k-i) - 1, coin, m-1, m);
        dp[i][n-(k-i)] = std::max(coin[i] + left, coin[n-1-(k-i)] + right);
        sol = std::min(sol, dp[i][n-(k-i)]);
    }
    std::cout << sol << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}