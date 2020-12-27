#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <queue> 

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;

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

void testcase(){
    int Z, J; std::cin >> Z >> J;
    std::vector<int> costs(Z);
    std::vector<int> payoff(J);
    std::vector<std::vector<int>> tickets(J);

    for(int i = 0; i < Z; ++i){
        int c; std::cin >> c;
        costs[i] = c;
    }

    for(int i = 0; i < J; ++i){
        int p; std::cin >> p;
        payoff[i] = p;
    }

    for(int i = 0; i < J; ++i){
        int num; std::cin >> num;
        for(int k = 0; k < num; ++k){
            int t; std::cin >> t;
            tickets[i].push_back(t);
        }
    }

    graph G(Z + J);
    edge_adder adder(G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);
    for(int i = 0; i < J; ++i)
        adder.add_edge(v_source, i, payoff[i]);

    for(int i = 0; i < Z; ++i)
        adder.add_edge(J+i, v_target, costs[i]);

    for(int i = 0; i < J; ++i){
        for(auto it = tickets[i].begin(); it != tickets[i].end(); ++it)
            adder.add_edge(i, *it+J, 500001);
    }

	int flow = boost::push_relabel_max_flow(G, v_source, v_target);
    std::vector<int> vis(J+Z+2, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[v_source] = true; // Mark the source as visited
	Q.push(v_source);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		out_edge_it ebeg, eend;
		for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = boost::target(*ebeg, G);
			if (rc_map[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);
		}
	}

    int profit = 0;
    for(int i = 0; i < J; ++i){
        if(vis[i]) profit+=payoff[i];
    }

    for(int i = J; i < J+Z; ++i){
        if(vis[i]) profit-= costs[i-J];
    }
    std::cout << profit << std::endl;
}


int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}