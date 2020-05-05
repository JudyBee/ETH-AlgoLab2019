#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt    EK;
typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2 P;
typedef std::pair<P,int> IP;

double ceil_to_double(const EK::FT& x){
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

void testcase(int n){
    K::FT l, b, r, top; std::cin >> l >> b >> r >> top;
    std::vector<IP> pts(n);
    for(int i = 0; i < n; ++i){
        K::FT x, y; std::cin >> x >> y;
        pts[i] = std::make_pair(P(x,y), i);
    }
    Delaunay t;
    t.insert(pts.begin(), pts.end());

    std::vector<K::FT> dist(n);
    for(int i = 0; i < n; ++i){
        P curr = pts[i].first; 
        K::FT dist_x = std::min(curr.x()-l, r - curr.x());
        K::FT dist_y = std::min(top - curr.y(), curr.y()- b);
        dist[i] = std::min(dist_x, dist_y);
        dist[i] = 4*dist[i]*dist[i];
    }

    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        int i1 = e->first->vertex((e->second+1)%3)->info();
        P p1 = e->first->vertex((e->second+1)%3)->point();
        int i2 = e->first->vertex((e->second+2)%3)->info();
        P p2 = e->first->vertex((e->second+2)%3)->point();
        K::FT d = CGAL::squared_distance(p1,p2);
        dist[i1] = std::min(dist[i1], d);
        dist[i2] = std::min(dist[i2], d);
    }   
    
    std::sort(dist.begin(), dist.end());
    EK::FT first = CGAL::sqrt((CGAL::sqrt(dist[0])-1)/2);
    EK::FT median = CGAL::sqrt((CGAL::sqrt(dist[n/2])-1)/2);
    EK::FT last = CGAL::sqrt((CGAL::sqrt(dist[n-1])-1)/2);
    std::cout << std::fixed << std::setprecision(0);
    std::cout << ceil_to_double(first) << " " << ceil_to_double(median) << " " << ceil_to_double(last) << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n; std::cin >> n;
    while(n){
        testcase(n);
        std::cin >> n;
    }
}