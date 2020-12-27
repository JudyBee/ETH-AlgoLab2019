#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <climits>
#include <algorithm>
#include <set>

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
    int n, m; std::cin >> n >> m;
    graph G(n);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);
    std::vector<std::vector<int> > min_c (n, std::vector<int> (n,INT_MAX));

    for(int i = 0; i < n-1; ++i){
        int c; std::cin >> c;
        min_c[i][i+1]=c;
        for(int j = 0; j < i+1; ++j){
            min_c[j][i+1] = std::min(c, min_c[j][i]);
        }
        adder.add_edge(i, i+1, c, 128);
        adder.add_edge(v_source,i,c,0);
        adder.add_edge(i+1,v_target,c,0);
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j <= i; ++j)
        min_c[i][j] = 0;
    }
    std::vector<std::vector<int> > demand(n, std::vector<int> (n,0));
    std::vector<std::vector<std::vector<int> > > eee (n, std::vector<std::vector<int> > (n));
    for(int i = 0; i < m; ++i){
        int a,b,d; std::cin >> a >> b >> d;
        demand[a][b]++;
        eee[a][b].push_back((b-a)*128-d);
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(min_c[i][j] < demand[i][j]){
                for(int k = min_c[i][j]; k > 0; --k){
                    std::sort(eee[i][j].begin(),eee[i][j].end());
                    adder.add_edge(i,j,1, eee[i][j][k-1]);
                }
            } else {
                for(auto it = eee[i][j].begin(); it!=eee[i][j].end(); ++it)
                    adder.add_edge(i,j,1, *it);
            }
        }
    }
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost2 = boost::find_flow_cost(G);
    int s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
        s_flow += c_map[*e] - rc_map[*e];     
    }
    std::cout << -cost2 + 128*s_flow << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) {
        testcase();
    }
}