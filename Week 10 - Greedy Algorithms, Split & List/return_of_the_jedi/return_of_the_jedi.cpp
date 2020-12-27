#include <iostream> 
#include <vector>
#include <algorithm> 
#include <queue>
#include <boost/pending/disjoint_sets.hpp>

void dfs (int start, int curr, std::vector<std::vector<int> > & tree, std::vector<int> &path, std::vector<int> & path_cost, std::vector<std::vector<int> > & costs, std::vector<std::vector<int> > &heavy, std::vector<int> & vis){
    vis[curr] = 1;  
    for(int i = 0; i < tree[curr].size(); ++i){
        int v = tree[curr][i];
        if(vis[v]) continue;
        path_cost.push_back(costs[curr][v]);
        heavy[start][v] = *std::max_element(path_cost.begin(), path_cost.end());
        path.push_back(v);
        dfs(start, v, tree, path, path_cost, costs, heavy, vis);
    }
    if(start != curr) path_cost.pop_back();
    path.pop_back();
}


void testcase(){
    int n, tan; std::cin >> n >> tan;
    tan--;
    std::vector<std::vector<int> > costs(n, std::vector<int> (n,0));

    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            int c; std::cin >> c;
            costs[i][j] = c;
            costs[j][i] = c;
        }
    }

    std::priority_queue<std::pair<int, std::pair<int,int> > > pq; // cost, to, from    
    for(auto it = costs[tan].begin(); it != costs[tan].end(); ++it)
        pq.push(std::make_pair(-(*it), std::make_pair(-(it-costs[tan].begin()), -tan)));
    int max_cost = 0;
    int count = 0;
    std::vector<std::pair<int, int>> connection;
    boost::disjoint_sets_with_storage<> uf(n);
    int n_components = n;
    while(!pq.empty()){
        std::pair<int, std::pair<int, int> > curr = pq.top();
        pq.pop();
        int to = -curr.second.first;
        int from = -curr.second.second;
        int in1 = uf.find_set(to);
        int in2 = uf.find_set(from);
        if(in1 != in2){
            uf.link(in1,in2);
            n_components--;
            connection.push_back(std::make_pair(to,from));
            count++;
            for(auto it = costs[to].begin(); it != costs[to].end(); ++it)
                pq.push(std::make_pair(-(*it), std::make_pair(-(it-costs[to].begin()), -to)));
        }
        if(n_components ==1) break;
    }

    long cost = 0;
    std::vector<std::vector<int> > my_graph (n);
    std::vector<std::vector<int> > heavy (n, std::vector<int> (n));
    for(int i = 0; i < n-1; ++i){
        int from = connection[i].first;
        int to = connection[i].second;
        my_graph[to].push_back(from);
        my_graph[from].push_back(to);
        cost+= costs[to][from];
    }

    for(int i = 0; i < n; ++i){
        std::vector<int> path (1,i);
        std::vector<int> path_costs;
        std::vector<int> vis(n, 0);
        dfs(i, i, my_graph, path, path_costs, costs, heavy, vis);
    }

    for(int i = 0; i < n-1; ++i){
        int from = connection[i].first;
        int to = connection[i].second;
        costs[to][from] = -1;
        costs[from][to] = -1;
    }

    int min_diff = INT_MAX;
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; j++){
            if(costs[i][j] != -1)
                min_diff = std::min(costs[i][j]-heavy[i][j], min_diff);
        }
    }
    std::cout << cost + min_diff << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}