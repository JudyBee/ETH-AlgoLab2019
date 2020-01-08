#include <iostream> 
#include <vector> 
#include <algorithm>

void recursive(int id, int u, int k, const std::vector<int> & heights,  std::vector<std::vector<int>> &assignment, std::vector<std::pair<int, int> >& F){
    if(id>=u){// generate a set
        int curr =0; 
        int count = 0;
        for(int i = 0; i < (int)assignment[0].size(); ++i){
            curr = (curr + assignment[0][i])%k;
            count++;
        }
        F.push_back(std::make_pair(curr, count));
        return;
    }
    for(int i = 0; i< 2; ++i){
        if(heights[id]){
            assignment[i].push_back(id);
            recursive(id+1, u, k, heights, assignment, F);
            assignment[i].pop_back();
        }
    }
}

void testcase(){
    int n, i ,k; std::cin >> n >> i >> k; // n: number of disks, i,k: parameters of modular (want to find non-empty set of disks of height congruent i modulo k)
    int goal = i%k;
    std::vector<int> disks(k,0);
    std::vector<int> heights(n);
    for(int j = 0; j < n; ++j){
        long h; std::cin >> h; 
        if(h%k==goal) {
            std::cout << "yes" << std::endl;
            return;
        }
        heights[j] = h%k;
        disks[h%k]++;
    }
    std::cout << "disk size is: " << disks.size() << std::endl;
    std::cout << "disks: ";
    for(int j = 0; j < disks.size(); ++j){
        std::cout << "j is: " << j << " disks[j] is:" << disks[j] << std::endl;
    }

   
    for(int j = 0; j < k; )
    std::cout << std::endl;
    std::vector<std::vector<int> > assignment1(2), assignment2(2);
    std::vector<std::pair<int, int> > F1, F2;

    recursive(0, n/2, k, final, assignment1, F1);
    recursive(n/2, n, k, final, assignment2, F2);

    std::cout << "F1: ";
    for(int j = 0; j < F1.size(); ++j) std::cout << F1[j].first << " ";
    std::cout <<"\nF2: ";
    for(int j = 0; j < F2.size(); ++j) std::cout << F2[j].first << " ";
    std::cout << std::endl;

    std::sort(F2.begin(), F2.end());
    std::vector<int> F22;
    for(int j = 0; j < F2.size(); ++j){
        F22.push_back(F2[i].first);
    }

    for(int j = 0; j < F1.size(); ++j){
        int curr = (goal - F1[i].first)%k;
        while(curr < 0) curr+= k;
        auto it = std::equal_range(F22.begin(), F22.end(), curr);
        for(; it.first != it.second; it.first++){
            if(F2[it.first - F22.begin()].second + F1[i].second){
                std::cout << "yes" << std::endl;
                return;
            }
        }
    }  
    std::cout << "no" << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t; 
    while(t--) testcase();
}