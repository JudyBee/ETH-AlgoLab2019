#include <iostream>
#include <vector>
#include <algorithm>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void testcase(){
    int k; std::cin >> k;
    weighted_graph G(k*(k+1)/2 ); 
    weight_map weights = boost::get(boost::edge_weight, G);
    std::vector<int> wi (k*(k+1)/2);
    for(int l = 1; l <= k; ++l){
        for(int i = 1; i <= l; ++i){
            int curr_index = l*(l-1)/2+i -1;
            int w; std::cin >> w;
            wi[curr_index] = w;
            if(i > 1 && l > 1){
                int a = (l-1)*(l-2)/2 + i-1 -1;
                edge_desc e = boost::add_edge(curr_index, a, G).first;
                weights[e] = w;
            }
            if(l > 1 && i < l){
                int b = (l-1)*(l-2)/2 + i-1;
                edge_desc e = boost::add_edge(curr_index, b, G).first;
                weights[e] = w;
            }
            if(i<l){
                int c = curr_index +1;
                edge_desc e = boost::add_edge(curr_index, c, G).first;
                weights[e] = w;
            }
            if(l < k){
                int d = l*(l+1)/2 + i;
                edge_desc e = boost::add_edge(curr_index, d, G).first;
                weights[e] = w;
            }
            if(l<k){
                int e = l*(l+1)/2 + i-1;
                edge_desc ed = boost::add_edge(curr_index, e, G).first;
                weights[ed] = w;
            }
            if(i > 1){
                int f = curr_index -1;
                edge_desc e = boost::add_edge(curr_index, f, G).first;
                weights[e] = w;
            }
        }
    }

    std::vector<int> dist_map1(k*(k+1)/2);
    std::vector<int> dist_map2(k*(k+1)/2);
    std::vector<int> dist_map3(k*(k+1)/2);
    boost::dijkstra_shortest_paths(G, 0,boost::distance_map(boost::make_iterator_property_map(dist_map1.begin(), boost::get(boost::vertex_index, G))));
    boost::dijkstra_shortest_paths(G, k*(k-1)/2,boost::distance_map(boost::make_iterator_property_map(dist_map2.begin(), boost::get(boost::vertex_index, G))));
    boost::dijkstra_shortest_paths(G, k*(k+1)/2-1,boost::distance_map(boost::make_iterator_property_map(dist_map3.begin(), boost::get(boost::vertex_index, G))));

    int min_value = dist_map1[0] + dist_map2[0] + dist_map3[0];
    for(int i = 1; i < k*(k+1)/2; ++i){
        min_value = std::min(min_value, dist_map1[i] + dist_map2[i] + dist_map3[i] + wi[i]);
    }
    std::cout << min_value << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >>t;
    while(t--) testcase();
}