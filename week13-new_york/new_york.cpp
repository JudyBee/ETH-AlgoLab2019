#include <iostream>
#include <vector> 
#include <algorithm> 
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <set>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS >      weighted_graph;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void testcase(){
    int n, m, k; std::cin >> n >> m >> k; //n: number points, m: optimal trip length k: max risk
    weighted_graph G(n);
    std::vector<int> temps(n); // temperatures
    for(int i = 0; i < n; ++i){
        int t; std::cin >> t;
        temps[i] = t;
    }
    int u, v;
    edge_desc e;
    std::vector<int> pred_map(n); // store parent of each node
    pred_map[0] = 0;
    std::vector<int> l (n,1); // bool array indicating if node is leaf
    // read in graph
    for(int i = 0; i < n-1; ++i){
        std::cin >> u >> v;
        pred_map[v] = u;
        l[u] = 0;
        boost::add_edge(u,v,G); 
    }
    std::vector<int> valid(n,0); // stores output
    bool sol = false;
    std::vector<int> cons (n,0); // stores if we have determined if this vertex is valid yet
    
    for(int i = 1; i < n; ++i){
        if(!l[i]|| cons[i]) continue;
        std::multiset<int> t; // stores all temperatures of current path
        t.insert(temps[i]);
        int curr = i; // current starting point of path
        vertex_desc vertex_index = pred_map[i];
        while(1){
            if(cons[curr]) break;
            t.insert(temps[vertex_index]);
            if(*t.rbegin() - *t.begin() > k) { // not valid path
                cons[curr] = 1; // mark tail
                t.erase(t.find(temps[curr])); // remove tail from temps
                curr= pred_map[curr]; // update tail
            }
            if(t.size()==m){
                cons[curr] = 1; // mark tail
                t.erase(t.find(temps[curr])); // remove tail from temps
                curr = pred_map[curr]; // update tail
                valid[vertex_index] = 1; // add result
                sol=true;
            }
            if(vertex_index==0) break; // cannot go further
            vertex_index = pred_map[vertex_index]; // go further
        }
    }
    // print result
    if(!sol){
        std::cout << "Abort mission" << std::endl;
        return;
    }
    for(int i = 0; i< n; ++i){
        if(valid[i])
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}