#include <iostream> 
#include <vector>
#include <cmath>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
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
    int n; std::cin >> n;
    graph G(n); 
    edge_adder adder(G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);
    std::vector<int> supply;
    std::vector<int> cost;
    int s, c;
    for(int i = 0; i< n; ++i){
        std::cin >> s >> c;
        supply.push_back(s);
        cost.push_back(c);
        adder.add_edge(v_source, i, s, c);
    }
    std::vector<int> demand;
    std::vector<int> price;
    int d,  p;
    int total_demand = 0;
    for(int i = 0; i< n; ++i){
        std::cin >> d >> p;
        total_demand += d;
        demand.push_back(d);
        price.push_back(p);
        adder.add_edge(i, v_target, d, -p+20);
    }
    std::vector<int> volume;
    std::vector<int> energy;
    int v,en;
    for(int i = 0; i < n-1; ++i){
        std::cin >> v >> en;
        volume.push_back(v);
        energy.push_back(en);
        adder.add_edge(i, i+1, v, en); // supply to students next day
    }

    int flow1 = boost::push_relabel_max_flow(G, v_source, v_target);
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost1 = boost::find_flow_cost(G);
    if(flow1 == total_demand) std::cout << "possible ";
    else std::cout << "impossible ";
    std::cout << flow1 << " " << -cost1+20*flow1 << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}