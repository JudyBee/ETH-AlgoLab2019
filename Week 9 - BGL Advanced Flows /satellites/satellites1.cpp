#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <vector> 
#include <queue>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
typedef	boost::graph_traits<graph>::edge_descriptor			edge_desc;
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;

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

void testcase(int t){
    int g, s, l; std::cin >> g >> s >> l;
    graph G(g+s);
    edge_adder adder(G);  
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);
    for(int i = 0; i < g; ++i) adder.add_edge(v_source, i, 1);
    for(int i = 0; i < s; ++i) adder.add_edge(i+g, v_target, 1);
    for(int i = 0; i < l; ++i){
        int a, b; std::cin >> a >> b;
        adder.add_edge(a, b+g, 1);
    }

    boost::push_relabel_max_flow(G, v_source, v_target);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
    std::vector<int> vis(g+s+2, false); 
	std::queue<int> Q; 
	vis[v_source] = true; 
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

    std::vector<int> gr;
    int cg = 0;
    int cs = 0;
    for(int i = 0; i < g; ++i){
        if(!vis[i]) {
            cg++;
            gr.push_back(i);
        }
    }

    for(int i = g; i < g+s; ++i){
        if(vis[i]){
            cs++;
            gr.push_back(i-g);
        }
    }

    std::cout << cg << " " << cs << std::endl;
    for(int i = 0; i < cg+cs; ++i){
        std::cout << gr[i];
        if(i+1 < cg+cs) std::cout << " ";
    }
    if(t) std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase(t);
}