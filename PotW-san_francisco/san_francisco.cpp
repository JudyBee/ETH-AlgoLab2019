#include <iostream>
#include <vector>
#include <climits>
#include <queue> 

void testcase(){
    int n, m; long x, k; std::cin >> n >> m >> x >> k;
    std::vector<std::vector<std::pair<int,long>>>  moves(n);
    for(long i = 0; i < m; ++i){
        int u,v; long p; std::cin >> u >> v >> p;
        // std::cout << "move from " << u << " to " << v << " gives " << p << std::endl;
        moves[u].push_back(std::make_pair(v,p));
    }

    std::vector<std::vector<std::pair<bool, long>>> game (k+1, std::vector<std::pair<bool, long>> (m, std::make_pair(false, 0)));
    game[0][0] = std::make_pair(true, 0);
    for(int i = 0; i<k; ++i){ // i: current move
        for(int j = 0; j < m; ++j){ // j: current position
            if(game[i][j].first){
                for(int l = 0; l < moves[j].size(); ++l){ 
                    int to = moves[j][l].first; // where we are going
                    long roll_score = moves[j][l].second; // score we get for going
                    long curr_score = game[i][j].second; // score we have so far
                    long new_score = std::max(game[i+1][to].second, curr_score+roll_score);
                    game[i+1][to] = std::make_pair(true, new_score);
                    if(new_score >= x){
                        std::cout << i+1 << std::endl;
                        return;
                    }
                }
            }
        }
        for(int j = 0; j < n; ++j){
            if(game[i+1][j].first && moves[j].size() == 0){
                game[i+1][0] = std::make_pair(true, std::max(game[i+1][0].second, game[i+1][j].second));
                game[i+1][j].first = false;
            }
        }
    }
    if(!found)
    std::cout << "Impossible" << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}