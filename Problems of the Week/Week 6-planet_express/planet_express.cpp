#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>
#include <algorithm> 

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void testcase(){
    int n, m, k, t; std::cin >> n >> m >> k >> t;
    std::vector<int> tele(t);
    for(int i = 0; i < t; ++i){
        int te; std::cin >> te;
        tele[i] = te;
    }

    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    for(int i = 0; i < m; ++i){
        int u,v,w; std::cin >> u >> v >> w;
        edge_desc e = boost::add_edge(v,u, G).first;
        weights[e] = w;
    }


    std::vector<int> scc_map(n);  // exterior property map
    int nscc = boost::strong_components(G,
    boost::make_iterator_property_map(scc_map.begin(), boost::get(boost::vertex_index, G)));

    std::vector<std::vector<int>> network(nscc);

    for(auto it = tele.begin(); it!= tele.end(); ++it){
        network[scc_map[*it]].push_back(*it);
    }
    
    int num_new = n;
    for(int i = 0; i < nscc; ++i){
        if(network[i].empty()) continue;
        int time = network[i].size() -1;
        for(auto it = network[i].begin(); it != network[i].end(); ++it){
            edge_desc e = boost::add_edge(*it, num_new, G).first;
            weights[e] = time;
            boost::add_edge(num_new, *it, G);
        }
        num_new++;
    }
    std::vector<int> dist_map(num_new);

    boost::dijkstra_shortest_paths(G, n-1,
        boost::distance_map(boost::make_iterator_property_map(
        dist_map.begin(), boost::get(boost::vertex_index, G))));

    int best = INT_MAX;
    for(int i = 0; i < k; ++i)
        best = std::min(best, dist_map[i]);
    if(best <= 1000000) std::cout << best << std::endl;
    else std::cout << "no" << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}