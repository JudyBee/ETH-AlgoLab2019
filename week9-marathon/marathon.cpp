#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> 
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

struct edge{
    int a, b, c, d;
};

void testcase(){
    int n, m, s, f; std::cin >> n >> m >> s >> f; // n: number intersections, m: number streets s: start f: finish
    weighted_graph G(n);

    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc e;
    int a,b,c,d; // from, to, width, length
    std::vector<edge> all_edge;
    for(int i = 0; i < m; ++i){
        std::cin >> a >> b >> c >> d;
        all_edge.push_back({a,b,c,d});
        e = boost::add_edge(a,b, G).first; 
        weights[e] = d;
        all_edge.push_back({b,a,c,d});
        e = boost::add_edge(b,a, G).first; 
        weights[e] = d;
    }
    std::vector<int> dist_map1(n);

    boost::dijkstra_shortest_paths(G, s,boost::distance_map(boost::make_iterator_property_map(dist_map1.begin(), boost::get(boost::vertex_index, G))));
    int goal = dist_map1[f];
    std::vector<int> dist_map2(n);
    boost::dijkstra_shortest_paths(G, f,boost::distance_map(boost::make_iterator_property_map(dist_map2.begin(), boost::get(boost::vertex_index, G))));

    graph final(n);
    edge_adder adder(final);
    for(int i = 0; i < all_edge.size(); ++i){
        edge ed = all_edge[i];
        if(dist_map1[ed.a] + ed.d + dist_map2[ed.b] == goal)
        adder.add_edge(ed.a, ed.b, ed.c);
    }
    long flow = boost::push_relabel_max_flow(final, s, f);
    std::cout << flow << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}