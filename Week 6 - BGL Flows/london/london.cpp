#include <iostream>
#include <vector>
#include <string>


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
    int h, w; 
    std::cin >> h >> w;
    std::string message;
    std::cin >> message;
    // determine how many times which char appears in message
    std::vector<int> message_count (26,0);
    for(auto it = message.begin(); it != message.end(); it++){
        message_count[int(*it)-65]++;
    }
   
    // start building graph
    graph G(364);
    edge_adder adder(G);
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);
    for(int i = 0; i < 26; i++){
        adder.add_edge(i,v_target, message_count[i]);
    }
   
    // read in messages
    std::vector<std::string> front (h);
    std::vector<std::string> back (h);
    for(int i = 0; i < h; i++){
        std::cin >> front[i];
        //std::cout << front[i]<< std::endl;
    }
    for(int i = 0; i < h; i++){
        std::cin >> back[i];
        //std::cout<< back[i] << std::endl;
    }
    
    // determine coind
    std::vector <std::vector<int> > coins = std::vector<std::vector<int> > (26, std::vector <int> (26, 0));
    
    for(int i = 0; i < h; i++){
        for(int j = 0 ; j < w; j++){
            coins[(int(front[i][j]) - 65)][(int(back[i][w-j-1])-65)]++;
        }
    }

    for(int i = 0; i < 26; i++){
        for(int j = i; j < 26; j++){
            int f = coins[i][j]; 
            if(i!=j) {
                f+= coins[j][i];
            }
            int v = 26 + i*26 + j;
            adder.add_edge(v_source, v, f);
            adder.add_edge(v, i, f);
            adder.add_edge(v, j, f);
        }
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    //std::cout << flow << std::endl;
    if(flow == message.size()){
        std::cout << "Yes" << std::endl;
    } else{
        std::cout << "No" << std::endl;
    }

}



int main(){
    std::ios_base::sync_with_stdio(false);
    int t; 
    std::cin >> t;
    for(int i = 0; i < t; i++){
        testcase();
    }
}