#include <iostream>

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
    int w, n;
    std::cin >> w >> n;
    int v = 2*w;
    graph G(v);
    edge_adder adder(G);
    // vertex constraints
    for(int i =0; i < w-1; i++){
        adder.add_edge(2*i+1, 2*i +2, 1);
        //std::cout << 2*i+1 << ", " << 2*i +2<< std::endl;
    }
    int a, b;
    for(int i = 0; i < n; i++){
        std::cin >>a>>b;
        if(a==b){
            continue;
        }else if(a<b){
            //std::cout << a*2 << ", " << b*2-1 << std::endl;
            adder.add_edge(a*2,b*2-1,1);
        }else{
            //std::cout << b*2 << ", " << a*2-1 << std::endl;
            adder.add_edge(b*2,a*2-1,1);
        }
    }
    long flow = boost::push_relabel_max_flow(G, 0, v-1);
    std::cout << flow << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for(int i = 0; i < t; i++){
        testcase();
    }
}