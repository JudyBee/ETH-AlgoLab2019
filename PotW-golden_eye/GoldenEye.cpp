
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, K::FT> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;


std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}

void compute_emst() {
    Index n, m;
    long p;
    std::cin >> n >> m >> p;
    typedef std::pair<K::Point_2,Index> IPoint;
    std::vector <IPoint> jammers (n);
    for(Index i = 0; i < n; i++){
        long x,y; std::cin >> x >> y;
        jammers.emplace_back(K::Point_2(x, y), i);
    }
    std::cout << "1" << std::endl;
    Delaunay t;
    t.insert(jammers.begin(), jammers.end());

    // extract edges and sort by (squared) length
    // This step takes O(n log n) time (for the sorting).
    EdgeV edges;
    edges.reserve(3*n); // there can be no more in a planar graph
    weighted_graph G(n);// build minimum spanning tree
    weight_map weights = boost::get(boost::edge_weight, G);
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second+1)%3)->info();
        Index i2 = e->first->vertex((e->second+2)%3)->info();
        // ensure smaller index comes first
        if(t.segment(e).squared_length()<= 2* p/4){
            edge_desc edge;
            edge = boost::add_edge(11, 12, G).first; weights[edge]=(t.segment(e).squared_length()); 
        } 
        edges.emplace_back(i1, i2, t.segment(e).squared_length());
    }
    
    std::vector<std::string> output(m);

    // for(int i = 0; i < m; i++){
    //     long s_x, s_y, t_x, t_y;
    //     std::cin >> s_x >> s_y >> t_x >> t_y;
    //     std::cout << "i1: " << i << std::endl;
    //     K::Point_2 s = K::Point_2(s_x, s_y);
    //     K::Point_2 ta = K::Point_2(t_x, t_y);
    //     K::Point_2 cs = t.nearest_vertex(s)->point();
    //     K::Point_2 cta = t.nearest_vertex(ta)->point();
    //     std::cout << "i2: " << i << std::endl;
    //     K::FT dist_s = CGAL::squared_distance(s,cs);
    //     K::FT dist_t = CGAL::squared_distance(ta,cta);
    //     std::cout << "i3: " << i << std::endl;
    //     Index s1 = t.nearest_vertex(s)->info();
    //     Index ta1 = t.nearest_vertex(ta)->info();
    //     std::vector<K::FT> dist_map(n, 0);
    //     std::cout << "nearest vertex s " << s1 << std::endl;
    //     std::cout << "dist t is" << dist_t << std::endl;
    //     boost::dijkstra_shortest_paths(G, s1,
    //     boost::distance_map(boost::make_iterator_property_map(
    //         dist_map.begin(), boost::get(boost::vertex_index, G))));
    //     std::cout << "i4: " << i << std::endl;
    //     if(dist_map[ta1] && dist_s <= p/4 && dist_t <= p/4 ){
    //         output[i] = "y";
    //     } else {
    //         output[i] = "n";
    //     }
    // }
    // std::cout << "4" << std::endl;


    for(int i = 0; i < m; i++){
        std::cout<<output[i];
    }
    std::cout << std::endl;
    std::cout << 4*p << std::endl;
    std::cout << p << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    std::size_t t;
    for (std::cin >> t; t > 0; --t) compute_emst();
    return 0;
}