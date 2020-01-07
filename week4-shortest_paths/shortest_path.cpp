#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

int main(){
    std::ios_base::sync_with_stdio(false);
    int n, m ,q;
    std::cin >> n >> m >> q;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    std::vector<std::pair<int, int>> positions;
    for(int i = 0; i < n; ++i){
        int lon, lat; std::cin >> lon >> lat;
        positions.push_back(std::make_pair(lon,lat));
    }
    for(int i = 0; i < m; ++i){
        int a,b,c; std::cin >> a >> b >>c;
        edge_desc e;
        e = boost::add_edge(a,b,G).first; weights[e] = c;
    }
    for(int i = 0; i < q; ++i ){
        std::vector<int> dist_map (n,-10);
        int s, t; std::cin >> s >> t;
        boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
        if(dist_map[t]!= INT_MAX) std::cout << dist_map[t] << std::endl;
        else std::cout << "unreachable" << std::endl;
    }
}