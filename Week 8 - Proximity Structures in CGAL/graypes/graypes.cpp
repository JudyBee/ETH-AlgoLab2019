#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <limits>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Delaunay_triangulation_2<IK>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;
typedef std::size_t Index;


double ceil_to_double(EK::FT r){
    double rad = std::ceil(CGAL::to_double(r));
    while (rad+1 >= r){
        rad -= 1;
    }
    while (rad < r){
        rad += 1;
    }
    return rad;
}

int main(){
    std::ios_base::sync_with_stdio(false);
     std::cout << setiosflags(std::ios::fixed) << std::setprecision(0);
    int n; 
    while(true){
        std::cin >> n;
        if(n==0){
            break;
        }
        std::vector<IK::Point_2> p (n);
        int x,y;
        for(int i = 0; i < n; i++){
            std::cin >> x >> y; 
            p[i]= IK::Point_2(x,y);
        }
        Triangulation t;
        t.insert(p.begin(), p.end());
        IK::FT min = DBL_MAX;
        for(auto e = t.finite_edges_begin(); e!=t.finite_edges_end(); e++){
            if(t.segment(e).squared_length() < min){
                min = t.segment(e).squared_length();
            }
        }
        EK::FT dist = CGAL::sqrt(min)/2;
        std::cout << ceil_to_double(dist*100) << std::endl;
    }
}