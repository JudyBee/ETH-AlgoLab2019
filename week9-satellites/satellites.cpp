
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >	graph;
typedef	boost::graph_traits<graph>::edge_descriptor			edge_desc;
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;
typedef traits::vertex_descriptor vertex_desc;
class edge_adder {
 graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity) {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const edge_desc e = boost::add_edge(from, to, G).first;
        const edge_desc rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};

void testcase(){
    int g,s,l;
    std::cin >> g >> s >> l;
    graph G(g+s);
    edge_adder adder(G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);
    // connect ground stations to source
    for(int i = 0; i < g; i++){
        adder.add_edge(v_source,i,1);
    }
    // connect satelites to target
    for(int i = g; i < g+s; i++){
        adder.add_edge(i,v_target,1);
    }
    // add links 
    int a,b;
    for(int i = 0; i<l; ++i){
        std::cin >> a >> b;
        adder.add_edge(a,b+g,1);
    }
    int flow = boost::push_relabel_max_flow(G, v_source, v_target);
	// BFS to find vertex set S
	std::vector<int> vis(g+s+2, false); // visited flags
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

    int count_min_VC_g = 0;
    int count_min_VC_s = 0;
    std::vector<int> vc_g;
    std::vector<int> vc_s;
    for(int i = 0; i < g; i++){
        if(!vis[i]){
            count_min_VC_g++;
            vc_g.push_back(i);
        }
    }
    for(int i = g; i < s+g; i++){
        if(vis[i]){
            count_min_VC_s++;
            vc_s.push_back(i-g);
        }
    }
    int new_line = 0;
    std::cout << count_min_VC_g << " " << count_min_VC_s << std::endl;
    for(auto it=vc_g.begin(); it!=vc_g.end(); it++){
        std::cout << *it << " ";
        new_line++;
    }
    for(auto it=vc_s.begin(); it!=vc_s.end(); it++){
        std::cout << *it << " ";
        new_line++;
    }
    if(new_line) std::cout << std::endl;
}


// Main
int main() {
    std::ios_base::sync_with_stdio(false);
	// build graph
    int t; std::cin >> t;
    while(t--) testcase();
}