#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
// case 0: parent has paved roads -> curr city is already saved
// case 1: parent is save, but did not pave own roads -> need to take care of current city
// case 2: curr city needs to save parent

std::vector<std::vector<int>> tree;
std::vector<int> costs;
std::vector<std::vector<int>> dp;

int build(int curr, int case1){
    if(case1 == 0){ // can either pave myself to save children or children save themselves
        if (dp[0][curr] != INT_MAX) 
            return dp[0][curr];
        if(tree[curr].empty()){ // If i don't have children there is nothing to do
            dp[0][curr] = 0;
            return dp[0][curr];
        }
        int op1 = costs[curr]; // paving myself to save children
        for(auto it = tree[curr].begin(); it != tree[curr].end(); ++it)
            op1 += build(*it, 0);
        int op2 = 0; // children save themselves
        for(auto it = tree[curr].begin(); it != tree[curr].end(); ++it)
            op2 += build(*it, 1);
        dp[0][curr] = std::min(op1, op2);
        return dp[0][curr];
    } else if (case1 == 1){ // can either save myself, or force one of my children to save me
        if(dp[1][curr] != INT_MAX) 
            return dp[1][curr];
        int op1 = costs[curr]; // saving myself
        if(tree[curr].empty()){ // I don't have children which can save me
            dp[1][curr] = op1;
            return op1;
        }
        for(auto it = tree[curr].begin(); it != tree[curr].end(); ++it)
            op1 += build(*it, 0); 
        // determine best child to save parent
        int options = tree[curr].size();
        std::vector<int> v1 (options); // parent saved by other child
        std::vector<int> v2 (options); // parent saved by mes
        int sum = 0;
        for(int i = 0; i < options; ++i){
            v1[i] = build(tree[curr][i], 1);
            v2[i] = build(tree[curr][i], 2);
            sum+= std::min(v1[i], v2[i]);
        }
        int op2 = sum - v1[0] + v2[0]; // curr saved by tree[curr][0]
        for(int i = 1; i < options; ++i)
            op2 = std::min(op2, sum + v2[i] - v1[i]); // curr saved by tree[curr][i]
        dp[1][curr] = std::min(op1, op2);
        return dp[1][curr];
    } else if(case1 == 2){ // I have to pave myself, my children get to choose
        if(dp[2][curr] != INT_MAX) 
            return dp[2][curr];
        int op1 = costs[curr]; // have to pave myself
        for(auto it = tree[curr].begin(); it != tree[curr].end(); ++it)
            op1 += build(*it, 0);
        dp[2][curr] = op1;
        return dp[2][curr];
    } 
    return 0; // this should never trigger!
}

void testcase(){
    int n; std::cin >> n;
    tree.clear();
    tree = std::vector<std::vector<int> > (n);
    for(int i = 0; i < n-1; ++i){
        int a, b; std::cin >> a >> b;
        tree[a].push_back(b);
    }
    costs.clear();
    costs = std::vector<int> (n);
    for(int i = 0; i < n; ++i){
        int c; std::cin >> c;
        costs[i] = c;
    }
    dp.clear();
    dp = std::vector<std::vector<int> > (3, std::vector<int> (n, INT_MAX));
    int option1 = costs[0];
    for(auto it = tree[0].begin(); it!= tree[0].end(); ++it)
        option1 += build(*it, 0);
    // determine best child to save parent
    int options = tree[0].size();
    std::vector<int> v1(options); // parent saved by other child
    std::vector<int> v2(options); // v2[i] parent saved by tree[0][i]
    int sum = 0;
    for(int i = 0; i < options; ++i){
        v1[i] = build(tree[0][i], 1);
        v2[i] = build(tree[0][i], 2);
        sum+= std::min(v1[i], v2[i]);
    }
    int option2 = sum - v1[0] + v2[0];
    for(int i = 1; i < options; ++i)
        option2 = std::min(option2, sum + v2[i] - v1[i]);
    std::cout << std::min(option1, option2) << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}