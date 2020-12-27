#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

void gen_configs(int id, int ubound, int M, std::vector<std::vector<int> > & assignment, std::vector<std::vector<int> > & switches, std::vector<std::pair<std::vector<int>, int> > &settings){
    if(id>=ubound){ 
        std::vector<int> curr(M,0);
        for(int i = 0; i < (int)assignment[0].size(); ++i){
            for(int j = 0; j < M; ++j){
                curr[j] += switches[assignment[0][i]][2*j];
            }
        }
        for(int i = 0; i < (int)assignment[1].size(); ++i){
            for(int j = 0; j<M; ++j){
                curr[j] += switches[assignment[1][i]][2*j+1];
            }
        }
        settings.push_back(std::make_pair(curr, assignment[1].size()));
        return;
    }
    else{
        for(int i = 0; i < 2; ++i){
            assignment[i].push_back(id);
            gen_configs(id+1, ubound,M, assignment, switches, settings);
            assignment[i].pop_back();
        }
    }
}

void testcase(){
    int N, M; // N: number switches     M: number rooms
    std::cin >> N >> M;
    std::vector<int> demand(M);
    std::vector<std::vector<int> > switches (N, std::vector<int> (2*M));

    // read in demand for rooms
    for(int i = 0; i < M; ++i){
        std::cin >> demand[i];
    }

    // read in switch setting
    for(int i = 0; i < N; ++i){
        for(int j=0; j < 2*M; ++j){
            std::cin >> switches[i][j];
        }
    }

    std::vector<std::vector<int> > assignment1(2), assignment2(2);
    std::vector<std::pair<std::vector<int>,int> > settings1, settings2;
    gen_configs(0, N/2, M, assignment1, switches, settings1);
    gen_configs(N/2, N, M, assignment2, switches, settings2);

    std::sort(settings2.begin(), settings2.end());
    std::vector<std::vector<int> > t;
    for(int i = 0; i < (int) settings2.size(); ++i){
        t.push_back(settings2[i].first);
    }
    int min_s = INT_MAX;
    bool found = false;
    for(int i = 0; i < (int) settings1.size(); ++i){
        std::vector<int>  curr = settings1[i].first;
        for(int i = 0; i < (int) demand.size(); ++i){
            curr[i] =  demand[i] - curr[i];
        }
        auto bounds = std::equal_range(t.begin(), t.end(), curr);
        if(bounds.first != bounds.second){
            found = true;
            min_s = std::min(min_s, settings2[bounds.first-t.begin()].second + settings1[i].second);
        }
    }
    if(found) std::cout << min_s << std::endl;
    else std::cout << "impossible" << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while(t--){
        testcase();
    }
}