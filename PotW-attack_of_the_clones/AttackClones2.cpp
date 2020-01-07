#include <iostream>
#include <vector> 
#include <utility> 
#include <algorithm> 
#include <assert.h> 

void testcase(){
    int n, m; // n: number jedi m: number intervals
    std::cin >> n >> m;
    std::vector<std::pair<int, int> > jedi(n);
    std::vector<std::pair<int, int> > pts;
    int count = 0;

    for(int i = 0; i < n; ++i){ // runtime n
        int a, b; std::cin >> a >> b;
        if(a>b)     count++;
        if(a==1)   count++;
        else    pts.push_back(std::make_pair(a,0)); // starting point
        pts.push_back(std::make_pair(b+1,1)); // end point
        jedi[i] = std::make_pair(b,a);
    }
    int best_start = 1;
    std::sort(pts.begin(), pts.end());
    // generate best starting point
    for(int i = 0; i < pts.size() && count > 10; ++i){
        if(pts[i].second==0)    count++;
        else     count--;
        if(count<= 10)   best_start = pts[i].first;
    }
    std::vector<std::pair<int, int> > new_jedi;
    std::vector<std::pair<int, int> > starts;

    // shift jedi segments
    for(auto it : jedi){ // runtime n
        int end = it.first - best_start + 1 > 0? it.first-best_start+1 : it.first-best_start+1+m;
        int start = it.second - best_start + 1 > 0? it.second - best_start + 1: it.second - best_start + 1 + m;
        if(start > end)     starts.push_back(std::make_pair(end, start));
        else     new_jedi.push_back(std::make_pair(end,start));
    }

    std::sort(new_jedi.begin(), new_jedi.end()); // runtime n log n

    //determine solution
    int best_sol = 0; 
    for(int i = -1; i < (int) starts.size(); ++i){ // runs at most 11 times 
        int shielded_from = m+1;
        int shielded_to = 0;
        int curr_solution = 0;
        if(i!=-1){
            curr_solution++;
            shielded_from = starts[i].second;
            shielded_to = starts[i].first;
        }
        for(auto it : new_jedi){ // run time n
            if(it.second <= shielded_to || it.first >= shielded_from)   continue;
            curr_solution++; 
            shielded_to = it.first;
        }
        best_sol = std::max(best_sol, curr_solution);
    }
    std::cout << best_sol << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) 
        testcase();
}