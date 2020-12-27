#include <iostream>
#include <vector>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>


typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef traits::vertex_descriptor vertex_desc;
// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void testcase(){
    int c, g, b, k, a; std::cin >> c >> g >> b >> k >> a; // c: num cities g: num guides, b: budget k: start, a: finish
    graph G(c); 
    edge_adder adder(G);
    const vertex_desc v_source = boost::add_vertex(G);
    int x,y,co,e;
    for(int i = 0; i < g; ++i){
        std::cin >> x >> y >> co >> e;
        adder.add_edge(x,y, e,co);
    }

    int curr_max = 0; 
    int l = 0; 
    int h = b; 
    int m = (l+h)/2;

    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    edge_desc edge = boost::add_edge(v_source, k, G).first;
    edge_desc rev_e = boost::add_edge(k, v_source, G).first;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[edge] = rev_e;
    r_map[rev_e] = edge;
    w_map[edge] = 0;   // new assign cost
    w_map[rev_e] = 0;   // new negative cost

    while(true){
        c_map[edge] = m;
        long flow =  boost::push_relabel_max_flow(G, v_source, a);
        boost::successive_shortest_path_nonnegative_weights(G, v_source, a);
        int cost1 = boost::find_flow_cost(G);
        if(cost1 <= b && flow == m) {
            curr_max = std::max(curr_max, m);
            l = m;
        } else {
            h = m;
        }
        int new_m = (l+h)/2;
        if (new_m == m) break;
        m = new_m; 
    }
    std::cout << curr_max << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--){
        testcase();
    }
}