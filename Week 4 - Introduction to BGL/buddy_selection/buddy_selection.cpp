#include <iostream>
#include <unordered_map>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <string>
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

void testcase(){
    int n, ca, f; std::cin >> n >> ca >> f;
    graph G (n);
    graph G1 (n);
    int count = 0;
    std::unordered_map<std::string, int> cha;
    std::vector<std::vector<int> > students (n, std::vector<int> (ca));

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < ca; ++j){
            std::string c; std::cin >> c;
            if(cha.find(c)== cha.end()){
                cha[c] = count;
                count++;
            }
            students[i][j]= cha.find(c)->second;
        }
    }
    std::vector<int> sizes (count, 0);
    std::vector<std::vector<int> > characteristics (count);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < ca; ++j){
            characteristics[students[i][j]].push_back(i);
            sizes[students[i][j]]++;
        }
    }
    std::vector<std::vector<int> > connections (n, std::vector<int> (n, 0));
    for(int i = 0; i < count; ++i){
        for(int j = 0; j < sizes[i]; ++j){
            for(int k = j+1; k < sizes[i]; ++k){
                connections[characteristics[i][j]][characteristics[i][k]]++;
                connections[characteristics[i][k]][characteristics[i][j]]++;
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            if(connections[i][j] >= f) boost::add_edge(i,j,G);
            if(connections[i][j] >= f+1) boost::add_edge(i,j,G1);
        }
    }
    std::vector<vertex_desc> mate_map(n);
    std::vector<vertex_desc> mate_map1(n);  // exterior property map
    const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();
    
    boost::edmonds_maximum_cardinality_matching(G, boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
    int matching_size = boost::matching_size(G,boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

    boost::edmonds_maximum_cardinality_matching(G1, boost::make_iterator_property_map(mate_map1.begin(), boost::get(boost::vertex_index, G1)));
    int matching_size1 = boost::matching_size(G1,boost::make_iterator_property_map(mate_map1.begin(), boost::get(boost::vertex_index, G1)));

    if(f == 0 && matching_size1 == n/2) std::cout << "not optimal" << std::endl;
    else if(matching_size == n/2 && matching_size1!= n/2) std::cout << "optimal" << std::endl;
    else std::cout << "not optimal" << std::endl;
    
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}