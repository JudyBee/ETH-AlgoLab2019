#include <iostream> //input/output
#include <cassert>
#include <boost/graph/adjacency_list.hpp> //graph 
#include <boost/graph/kruskal_min_spanning_tree.hpp> //minimum spanning tree
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::property<boost::vertex_distance_t, int>,                         
  boost::property<boost::edge_weight_t, int>  
> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph> ::edge_descriptor edge_desc;
typedef boost::property_map<weighted_graph, boost::vertex_distance_t>::type distance_map;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;


void testcase();

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for (int i = 0; i < t; i++){
        testcase();
    }
}

void testcase(){
    int n,m; std::cin >>n>>m;
    int u,v,w;
    edge_desc e;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    for(int i =0; i < m; i++){
        std::cin >> u>>v>>w;
        e = boost::add_edge(u, v, G).first; 
        weights[e]=w;
    }

	//Kruskal minimum spanning tree:
    std::vector<edge_desc> mst_w;
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst_w));
    int weight_mst = 0;
    for(auto it = mst_w.begin(); it != mst_w.end(); it++){
        weight_mst += weights[*it];// add the weight of all edges in mst
    }

    std::vector<int> dist_map(n);
    std::vector<vertex_desc> pred_map(n);
    vertex_desc s = 0;
    boost::dijkstra_shortest_paths(G, s, 
        boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
    int max_dist = *std::max_element(dist_map.begin(), dist_map.end()); // determine the maximum distances
    std::cout << weight_mst << " " << max_dist << std::endl;
}