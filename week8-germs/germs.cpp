// 
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <cstdlib>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
// we want to store an index with each vertex
typedef int                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;


double ceil_to_double(const EK::FT x){
    double a = std::ceil(CGAL::to_double(x));
    while(a+1>= x) a-=1;
    while(a < x) a+=1;
    return a;
}

EK::FT S_to_hrs(EK::FT const & S){
  return CGAL::sqrt((CGAL::sqrt(S) - 1) / 2);
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    while(true){
        // read number of points
        int n;
        std::cin >> n;
        if(n == 0) break;
        long l,b,r,top;
        std::cin >> l >> b >> r >> top;
        std::vector<K::FT> dist (n);
        // read points
        typedef std::pair<K::Point_2,Index> IPoint;
        std::vector<IPoint> pts;
        pts.reserve(n);
        for (std::size_t i = 0; i < n; ++i) {
            int x, y;
            std::cin >> x >> y;
            pts.emplace_back(K::Point_2(x, y), i);
            long min_x = std::min(std::abs(x-l), std::abs(r-x));
            long min_y = std::min(std::abs(top-y), std::abs(y-b));
            long min = std::min(min_x, min_y);
            dist[i] = 4*min*min;
        }
        // construct triangulation
        Delaunay t;
        t.insert(pts.begin(), pts.end());
        // output all edges
        for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
            int i1 = e->first->vertex((e->second+1)%3)->info();
            int i2 = e->first->vertex((e->second+2)%3)->info();
            K::FT dist_g = t.segment(e).squared_length();
            dist[i1] = std::min(dist[i1], dist_g);
            dist[i2] = std::min(dist[i2], dist_g);
        }
        EK::FT first, median, last;
        std::sort(dist.begin(), dist.end());
        first = S_to_hrs(dist[0]);
        median = S_to_hrs(dist[n/2]);
        last = S_to_hrs(dist[n-1]);
        std::cout << ceil_to_double(first) << " " << ceil_to_double(median) << " " << ceil_to_double(last) << std::endl;
    }
}