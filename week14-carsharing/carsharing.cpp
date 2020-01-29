#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <set>
#include <unordered_map>

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

struct request{
    int start;
    int end;
    int to;
    int profit;
    int ind;
    request(int s, int e, int t, int p, int i) : start(s), end(e), to(t), profit(p), ind(i) {};
    bool operator<(const request& other) const{
        if(start == other.start) return ind < other.ind;
        return start < other.start;
    }
};

void testcase(){
    int n,s; std::cin >> n >> s;
    std::vector<int> cars(s,0);
    int num_cars = 0;
    for(int i = 0; i < s; ++i) {
        std::cin >> cars[i];
        num_cars+=cars[i];
    }

    std::vector<std::vector<request> > demand(s);
    std::vector<std::vector<int> > times (s);
    int max_time = 0;
    long min_time = 1000000;
    for(int i = 0; i < n; ++i){
        int starts, ends,startt,endt,profit; std::cin >> starts >> ends >> startt >> endt >> profit;
        demand[starts-1].push_back(request(startt,endt,ends,profit,i));
        times[starts-1].push_back(startt);
        times[ends-1].push_back(endt);
        if(endt > max_time) max_time = endt;
        if(startt < min_time) min_time = startt;
    }

    // determine how many vertices are needed
    for(int i = 0;i <s; ++i){
        std::unique(times[i].begin(), times[i].end());
        std::sort(times[i].begin(), times[i].end());
    }

    std::vector<int> num_v_s(s);
    int num_v = 0;
    for(int i = 0; i <s; ++i){
        num_v_s[i] = times[i].end() - times[i].begin();
        num_v+=num_v_s[i];
    }

    // set up graph
    graph G(num_v);
    edge_adder adder(G); 
    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);


    // determine index for each vertex
    int index = 0;
    std::vector<std::vector<int> > vertex_index (s);
    for(int i = 0; i <s; ++i){
        for(int j = 0; j < num_v_s[i]; ++j){
            vertex_index[i].push_back(index);
            index++;
        }
    }

    // add cars to stations
    for(int i = 0; i < s; ++i){
        if(cars[i] && num_v_s[i]){
            int start_time = times[i][0];
            adder.add_edge(v_source, vertex_index[i][0], cars[i], (start_time-min_time) * 100);
        } else if (cars[i] && !num_v_s[i]) {
            num_cars-=cars[i];
        }
    }

    // connect vertices at station
    for(int i = 0; i < s; ++i){
        for(int j = 0; j < num_v_s[i]-1; ++j){
            int time1 = times[i][j];
            int time2 = times[i][j+1];
            adder.add_edge(vertex_index[i][j], vertex_index[i][j+1], num_cars, (time2 - time1)*100);
        }
    }

    // add demands
    for(int i = 0; i < s; ++i){
        for(int j = 0; j < demand[i].size(); ++j){
            // determine start index
            int start_time = demand[i][j].start;
            int ind1 = vertex_index[i][std::find(times[i].begin(), times[i].end(), start_time) - times[i].begin()];
            // determine end index
            int end_time = demand[i][j].end;
            int to = demand[i][j].to-1;
            int ind2 = vertex_index[to][std::find(times[to].begin(), times[to].end(), end_time) - times[to].begin()];
            adder.add_edge(ind1, ind2, 1,(end_time-start_time)*100-demand[i][j].profit);
        }
    }

    
    for(int i = 0; i < s; ++i){
        if(num_v_s[i]){
            int ind = vertex_index[i][num_v_s[i]-1];
            int time = times[i][num_v_s[i]-1];
            adder.add_edge(ind, v_target, num_cars, (max_time-time)*100);
        } 
    }

    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    long cost2 = boost::find_flow_cost(G);
    // long cost1 = boost::find_flow_cost(G);
    long adjust = num_cars*100 *(max_time-min_time);
    std::cout << adjust-cost2 << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}