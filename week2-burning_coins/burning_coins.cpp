#include <vector>
#include <iostream>

int play(int front, int back, std::vector<int> & vals, std::vector<std::vector<int> > & dp);
int opplay(int front, int back, std::vector<int> & vals, std::vector<std::vector<int> > & dp);
void testcase();

int play(int front, int back, std::vector<int> & vals, std::vector<std::vector<int> > & dp){
    if(front == back) return vals[front];
    else if (dp[front][back] != -1) return dp[front][back];
    int left = vals[front] + opplay(front + 1, back, vals, dp);
    int right = vals[back] + opplay(front, back -1, vals, dp);
    dp[front][back] = std::max(left, right);
    return dp[front][back];
}


int opplay(int front, int back, std::vector<int> & vals, std::vector<std::vector<int> > & dp){
    if(front >= back) return 0;
    if(dp[front][back] != -1) return dp[front][back];
    int left = play(front + 1, back, vals, dp);
    int right = play(front, back-1, vals, dp);
    dp[front][back] = std::min(left, right);
    
    return dp[front][back];
}

void testcase(){
    int n; std::cin >> n;
    std::vector<int> vals(n);
    for(int i = 0; i < n; ++i){
        int x; std::cin >> x;
        vals[i] = x;
    }
    std::vector<std::vector<int>> dp (n, std::vector<int>(n, -1));
    int left = vals[0] + opplay(1, n-1, vals, dp);
    int right = vals[n-1] + opplay(0, n-2, vals, dp);
    std::cout << std::max(left, right) << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}