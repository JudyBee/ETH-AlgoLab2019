#include <iostream>
#include <vector>
#include <algorithm> 

int min_move(int pos, std::vector<std::vector<int> > & trans, std::vector<int> min_m, std::vector<int> max_m);

int max_move(int pos, std::vector<std::vector<int> > &trans, std::vector<int> min_m, std::vector<int> max_m){
    if(max_m[pos]!= -1) return min_m[pos];
    for(auto it = trans[pos].begin(); it != trans[pos].end(); ++it)
        max_m[pos] = std::max(max_m[pos], 1 + min_move(*it, trans, min_m, max_m));
    return max_m[pos];
}

int min_move(int pos, std::vector<std::vector<int> > & trans, std::vector<int> min_m, std::vector<int> max_m){
    if(min_m[pos]!= INT_MAX) return min_m[pos];
    for(auto it = trans[pos].begin(); it != trans[pos].end(); ++it)
        min_m[pos] = std::min(min_m[pos], max_move(*it, trans, min_m, max_m)+1);
    return min_m[pos];
}


void testcase(){
    // holmes even -> moves black
    // holmes odd -> moves red
    // moriarty even -> moves black
    // moriarty odd -> moves red

    // holmes win = red
    // moriarty win = black

    int n, m; std::cin >> n >> m;
    int r, b; std::cin >> r >> b;
    std::vector<std::vector<int> > trans(n+1);
    for(int i = 0; i < m; ++i){
        int u, v; std::cin >> u >> v;
        trans[u].push_back(v);
    }

    std::vector<int> min_m(n+1,INT_MAX);
    min_m[n] = 0;
    std::vector<int> max_m(n+1, -1);
    max_m[n] = 0;
    int count_red = min_move(r, trans, min_m, max_m);
    int count_black = min_move(b, trans, min_m, max_m);

    if(count_red < count_black) std::cout << 0 << std::endl;
    else if(count_black < count_red) std::cout << 1 << std::endl;
    else if(count_red%2) std::cout << 0 << std::endl;
    else std::cout << 1 << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    int count = 1;
    while(t--) testcase();
}