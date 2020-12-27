#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <cassert>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp> //minimum spanning tree
#include <boost/graph/adjacency_list.hpp> //graph 
#include<bits/stdc++.h> 

using namespace std;
using namespace boost;

typedef adjacency_list < vecS, vecS, undirectedS, property<vertex_distance_t, int>, property < edge_weight_t, int > > weighted_graph;
typedef graph_traits<weighted_graph>::edge_descriptor Edge_w;
typedef graph_traits<weighted_graph>::vertex_descriptor Vertex_w;
typedef property_map<weighted_graph, edge_weight_t>::type weight_map_me;
typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> graph_u;
typedef graph_traits<graph_u>::edge_descriptor Edge;

// global variables
int n, e, s, a, b;
vector<weight_map_me> weights;
vector<weighted_graph> species;
vector<int> hives;

void clear_globals();
void read_in_values();
void testcase();

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for(int i = 0; i < t; i++){
        clear_globals();
        read_in_values();
        testcase();
    }
}

void clear_globals(){
    weights.clear();
    species.clear();
    //forrest.clear();
    hives.clear();
}

void read_in_values(){
    cin >> n >> e >> s >> a >> b;
    weights = std::vector<weight_map_me> (s);
    for(int i = 0; i < s; i++){
        weights[i] = boost::get(boost::edge_weight, species[i]);
    }
    species = std::vector<weighted_graph> (s, weighted_graph(n));
    //forrest = graph_u(n);
    hives = vector<int> (s);
    Edge ed;
    Edge_w  e_w;
    int u,v, w;
    for (int i = 0; i < e; i++){
        cin >> u >> v;
        //ed = boost::add_edge(u,w,forrest).first;
        for(int j = 0; j < s; j++){
            cin >> w;
            e_w = boost::add_edge(u,v, species[j]).first; 
            weights[j][e_w] = w;
        }
    }
    for(int i = 0; i < s; i++){
        cin >> hives[i];
    }
}

void testcase(){
    //build mst for each species
    vector<vector< Edge_w> > mst_w(s);
    for(int i = 0; i < s; i++){
        kruskal_minimum_spanning_tree(species[i], back_inserter(mst_w[i]));
    }
    
    // build final graph based on edges of species mst's > final edge weight will be minimum of all weights
    weighted_graph final_graph = weighted_graph(n);
    weight_map_me e_w = get(edge_weight, final_graph);
    Edge_w ed;

    for(int i = 0; i < s; i++){
        for(auto it = mst_w[i].begin(); it!=mst_w[i].end(); it++){
            int curr_weight = weights[i][*it];
            // if edge already in graph check if weight needs to be updated, else add edge
            int u = std::min(source(*it, species[i]), target(*it, species[i]));
            int v = std::max(source(*it, species[i]), target(*it, species[i]));
            if(edge(u,v, final_graph).second){
                e_w[edge(u,v, final_graph).first] = std::min(curr_weight, e_w[edge(u,v, final_graph).first]);
            } else{
                ed = boost::add_edge(u, v, final_graph).first; 
                e_w[ed] = curr_weight;
            }
        }
    }
    vector<int> dist_map(n);
    dijkstra_shortest_paths(final_graph, a, distance_map(make_iterator_property_map(dist_map.begin(), get(vertex_index, final_graph))));
    cout << dist_map[b] << endl;
}