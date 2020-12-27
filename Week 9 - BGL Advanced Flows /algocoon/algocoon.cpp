#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <queue>
#include <vector>
#include <climits>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
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
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    // auto w_map = boost::get(boost::edge_weight, G);
    edge_adder adder(G);
    for(int i = 0; i < m; ++i){
        int a,b,c; std::cin >> a >> b >> c;
        adder.add_edge(a, b, c, 0);
    }

    int from=0, to=1;
    int best_flow = INT_MAX;

    for(int i = 0; i < n; ++i){
        int flow = boost::push_relabel_max_flow(G, i, (i+1)%(n));
        if(flow < best_flow) {
            // std::cout << "found new best flow: " << flow << " it goes from " << i << " to " << (i+1)%n<< std::endl;
            from = i; 
            to = (i+1)%n; 
            best_flow = flow;
        }
    }
    int count = 1;
    
    int flow = boost::push_relabel_max_flow(G, from, to);
    std::vector<int> vis(n, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[from] = true; // Mark the source as visited
	Q.push(from);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		out_edge_it ebeg, eend;
		for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = boost::target(*ebeg, G);
			// Only follow edges with spare capacity
			if (rc_map[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
            count ++;
			Q.push(v);
		}
	}

    std::cout << flow << std::endl;
    std::cout << count;
	for (int i = 0; i < n; ++i) {
		if (vis[i]) std::cout << " " << i;
	}
	std::cout << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}