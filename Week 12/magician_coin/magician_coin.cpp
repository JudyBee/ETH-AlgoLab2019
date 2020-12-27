#include <iostream> 
#include <vector>
#include <iomanip>
#include <algorithm>

double recursion(int d, int k, int m, std::vector<double> & probs, std::vector<std::vector<double> > & game){
    if(game[d][k] != -1) return game[d][k];
    double best = 0.0;
    for(int i = 0; i <= std::min(k, m-k); ++i){
        double win = probs[d]*recursion(d+1, std::min(k+i,m), m, probs, game);
        double loss = (1-probs[d])*recursion(d+1, std::max(k-i,0), m, probs, game);
        best = std::max(win+loss, best);
    }
    game[d][k] = best;
    return best;
}


void testcase(){
    // std::cout << "here1" << std::endl;
    int n, k, m; std::cin >> n >> k >> m;
    std::vector<double> probs (n);
    for(int i = 0; i < n; ++i){
        double p; std::cin >> p;
        probs[i] = p;
    }
    
    if(k>=m) {
        std::cout << 1.0 << std::endl;
        return;
    }
    if(k<=0){
        std::cout << 0.0 << std::endl;
        return;
    }
    std::vector<std::vector<double> > game(n+1, std::vector<double> (m+1, -1));
    for(int i = 0; i < m; ++i) 
        game[n][i] = 0.0;
    game[n][m] = 1.0;

    double output = recursion(0, k, m, probs, game);
    std::cout << output << std::endl;

}


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision (5);
    int t; std::cin >> t;
    while(t--) testcase();
}