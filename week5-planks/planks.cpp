#include <iostream>
#include <vector>
#include <algorithm> 
#include <utility> 

void recursive (int curr, const std::vector<int> & plank, std::vector<std::vector<int> >  & split, int u, std::vector<std::vector<int> > & assignments){
    if(curr >= u){
        std::vector<int>  temp(4,0);
        for(int j = 0; j < 4; ++j){
            for(int i = 0; i < (int) split[j].size(); ++i){
                temp[j] += split[j][i];
            }
        }
        assignments.push_back(temp);
        return;
    }
    for(int i = 0; i < 4; ++i){
        split[i].push_back(plank[curr]);
        recursive(curr+1, plank, split, u, assignments);
        split[i].pop_back();
    }
}

void testcase(){
    int n; std::cin >> n;
    std::vector<int> planks (n);
    int sum = 0;
    for(int i=0; i < n; i++){
        std::cin >> planks[i];
        sum += planks[i];
    }
    if(sum%4) {
        std::cout << 0 << std::endl;
        return;
    }
    std::vector<std::vector<int> > split1 (4), split2 (4), assignments1, assignments2;
    recursive(0, planks, split1, n/2, assignments1);
    recursive(n/2, planks, split2, n, assignments2);
    std::sort(assignments2.begin(), assignments2.end());
    long result = 0;
    for(int i = 0; i< (int) assignments1.size(); ++i){
        std::vector<int> curr(4,sum/4);
        for(int j = 0; j < 4; ++j){
            curr[j]-=assignments1[i][j];
        }
        auto bounds = std::equal_range(assignments2.begin(), assignments2.end(), curr);
        long counter = std::distance(bounds.first, bounds.second);
        result+=counter;
        // if(std::find(assignments2.begin(), assignments2.end(), curr)!=assignments2.end()){
        // if(counter){
        //     std::cout << "1" << std::endl;
        //     return;
        // }
    }
    // std::cout << "0" << std::endl;
    std::cout << result/24 << std::endl;
}

int main(int argc, char const *argv[]) {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for(int i = 0; i < t; i++){
        testcase();
    }
}