#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef K::Point_2 P;

void testcase(int n){
    std::vector<P> old(n);
    for(int i = 0; i < n; ++i){
        int x,y; std::cin >> x >> y;
        old[i] = P(x,y);
    }

    int m; std::cin >> m;
    std::vector<P> new_l(m);
    for(int i = 0; i < m; ++i){
        int x,y; std::cin >> x >> y;
        new_l[i] = P(x,y);
    }

    Triangulation t;
    t.insert(old.begin(), old.end());

    for(int i = 0; i < m; ++i){
        P p1 = new_l[i];
        P p2 = t.nearest_vertex(p1)->point();
        K::FT min = CGAL::squared_distance(p1,p2);
        std::cout << std::setprecision(0);
        std::cout << (long)min << std::endl;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n; std::cin >> n;
    while(n){
        testcase(n);
        std::cin >> n;
    }
}