#include <iostream>
#include <vector>
#include <algorithm>

void testcase(){
    int n, m, k; std::cin >> n >> m >> k;
    std::vector<int> defense(n);
    for(int i = 0; i < n; ++i){
        std::cin >> defense[i];
    }
    std::vector<std::pair<int, int> > seg;
    int count = 0;

    int front = 0, back = 0;
    int curr = defense[front];

    while(front < n){
        if(curr == k){
            seg.push_back(std::make_pair(front+1,back+1)); // j: front, i: back
            count++;
        }
        if(curr < k){
            front++;
            curr+=defense[front];
        } else {
            curr-=defense[back];
            back++;
        }
    }

    std::vector<std::vector<int> > dp (m+1, std::vector<int> (n+1,-1)); // dp[i][j] max value with i attackers on line 0-j
    for(int i = 0; i < n+1; ++i) dp[0][i] = 0;
    
    int seg_start = 0;
    for(int i = 1; i < m+1; ++i){
        int build_to = 0;
        bool found = false;
        for(auto it = seg.begin(); it != seg.end(); ++it){
            std::pair<int, int> curr_seg = *it;
            int begin = curr_seg.second;
            int end = curr_seg.first;
            if(found){
                while(build_to+1 < end){
                    dp[i][build_to+1] = dp[i][build_to];
                    build_to++;
                }
            }
            if(dp[i-1][begin-1] ==-1) continue;
            found = true;
            dp[i][end] = std::max(dp[i][build_to], dp[i-1][begin-1] + (end-begin+1));
            build_to = end;
        }
        while(build_to < n){
            dp[i][build_to+1] = dp[i][build_to];
            build_to++;
        }
    }
    if(dp[m][n]>0) std::cout << dp[m][n] << std::endl;
    else std::cout << "fail" << std::endl;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}