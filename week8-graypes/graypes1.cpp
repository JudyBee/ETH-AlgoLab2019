#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <tuple>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt    EK;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2                                             P;
typedef std::tuple<Index,Index,K::FT>                          Edge;
typedef std::vector<Edge>                                      EdgeV;

double ceil_to_double(const EK::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void testcase(int n){
    typedef std::pair<K::Point_2,Index> IPoint;
    std::vector<IPoint> points;
    points.reserve(n);
    for (Index i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points.emplace_back(K::Point_2(x, y), i);
    }
    Delaunay t;
    t.insert(points.begin(), points.end());

    EdgeV edges;
    edges.reserve(3*n); // there can be no more in a planar graph
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second+1)%3)->info();
        Index i2 = e->first->vertex((e->second+2)%3)->info();
        // ensure smaller index comes first
        if (i1 > i2) std::swap(i1, i2);
        edges.emplace_back(i1, i2, t.segment(e).squared_length());
    }
    std::sort(edges.begin(), edges.end(),
            [](const Edge& e1, const Edge& e2) -> bool {
            return std::get<2>(e1) < std::get<2>(e2);
                });
    EK::FT shortest = CGAL::sqrt(std::get<2>(*edges.begin()))/2*100;
    
    std::cout << ceil_to_double(shortest) << std::endl;


}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n; std::cin >> n;
    while(n){
        testcase(n);
        std::cin >> n;
    }
}