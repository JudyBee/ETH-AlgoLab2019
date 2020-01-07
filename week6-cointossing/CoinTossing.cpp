#include <iostream> 
#include <vector>

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

// Custom edge adder class, highly recommended
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
    int n, m;
    std::cin >> n >> m;
    graph G(m+n);
    edge_adder adder(G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);
   
    std::vector <int> scores_known (n, 0);
    int games = m;
    //read in games
    int a, b, c;
    for(int i = 0; i < m; i++){
        std::cin >> a>> b>>c;
        if(c == 0){// score unknown
            adder.add_edge(v_source, i, 1);
            adder.add_edge(i, a + m, 1);
            adder.add_edge(i, b + m, 1);
        } else if(c==1){// player a won
            scores_known[a]++;
            games--;
        } else{ //player b won
            scores_known[b]++;
            games--;
        }
    }

    //read in actual scores
    std::vector<int> scores(n);
    for(int i = 0; i < n; i++){
        std::cin >> scores[i];
    }

    bool possible = true;
    int remaining = 0;
    int player = 0;
    for(int i = 0; i < n; i++){
        player = scores[i] - scores_known[i];
        if(player < 0){
            possible = false;
        } else {
            remaining += player;
            adder.add_edge(m+i, v_target, player);
        }
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    
    if(remaining != flow || remaining != games){
        possible=false;
    }
    if(possible){
        std::cout << "yes" << std::endl;
    }else {
        std::cout << "no" << std::endl;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for(int i = 0; i < t; i++){
        testcase();
    }
}