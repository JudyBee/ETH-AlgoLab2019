#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

void compute_cost(int curr_a, int curr_b, std::vector<std::vector<int> > & costs, const std::vector<int> & a, const std::vector<int> & b){
    long curr_min = INT_MAX;
    if(costs[curr_a][curr_b]!= -1) return;

    // take 1 from a
    int f1 = a[curr_a-1] - a[curr_a] -1;
    for(int j = 1; j <=curr_b; ++j){
        if((curr_a-1>0 && curr_b-j>0) || (curr_a-1 == 0 && curr_b - j ==0)){
            int f2 = b[curr_b-j] - b[curr_b] - j;
            long cost_move = f1*f2;
            if(costs[curr_a-1][curr_b-j]== -1) compute_cost(curr_a-1, curr_b-j,costs,a,b);
            curr_min = std::min(cost_move+costs[curr_a-1][curr_b-j], curr_min);
        }
    }  

    // take 1 from b
    int f2 = b[curr_b-1] - b[curr_b] -1;
    for(int i = 1; i <= curr_a; ++i){
        if((curr_a-i>0 && curr_b-1>0) || (curr_a-i == 0 && curr_b - 1 ==0)){
            f1 = a[curr_a-i] - a[curr_a] -i;
            long cost_move = f1*f2;
            if(costs[curr_a-i][curr_b-1]== -1) compute_cost(curr_a-i, curr_b-1,costs,a,b);
            curr_min = std::min(curr_min, cost_move + costs[curr_a-i][curr_b-1]);
        }
    }
    costs[curr_a][curr_b] = curr_min;
}

void testcase(){
    int n; std::cin >>n;
    // read in values
    std::vector<int> a(n+1,0);
    std::vector<int> b(n+1,0);
    for(int i = 0; i <n; ++i){
        int ai; std::cin >> ai;
        a[i] = ai;
    }
    for(int i = 0; i < n; ++i){
        int bi; std::cin >> bi;
        b[i] = bi;
    }
    for(int i = n-1; i >= 0; --i){
        a[i] = a[i+1] + a[i];
        b[i] = b[i+1] + b[i];
    }
    long min_cost = INT_MAX;
    std::vector<std::vector<int> > costs (n+1, std::vector<int> (n+1, -1)); // costs[a][b]: min cost to go when stack a has height a and stack b has height b
    costs[0][0] = 0;
    compute_cost(n, n, costs, a, b);
    std::cout << costs[n][n] << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}