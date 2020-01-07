#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <limits>

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Exact_predicates_exact_constructions_kernel EK;
typedef CGAL::Delaunay_triangulation_2<IK>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;
typedef std::size_t Index;

double floor_to_double(const EK::FT&x){
    double a = std::floor(CGAL::to_double(x));
    while(a>x)a-=1;
    while(a+1<=x) a+=1;
    return a;
}



int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout << setiosflags(std::ios::fixed) << std::setprecision(0);
    int n; 
    while(true){
        int i = 0;
        //std::cout << "round: " << i << std::endl;
        i++;
        std::cin >> n; 
        //std::cout << "n is " << n << std::endl;
        if(n==0) break;
        Triangulation t;
        std::vector<IK::Point_2> existing (n);
        int x,y;
        //std::cout << "current resturants: " << std::endl;
        for(int i = 0; i < n; i++){
            std::cin >> x >> y;
            //std::cout << "x is: " << x << " y is:  " << y << std::endl;
            existing[i] = IK::Point_2(x,y);
        }
        t.insert(existing.begin(), existing.end());
        int m; std::cin>> m;
        EK::FT max = 0;
        //std::cout << "locations to consider: " << m << std::endl;
        for(int i = 0; i < m; i++){
            std::cin >> x >> y;
            //std::cout << "x is: " << x << " y is:  " << y << std::endl;
            IK::Point_2 pt = IK::Point_2(x,y);
            IK::Point_2 pt2 = t.nearest_vertex(pt)->point();
            std::cout << floor_to_double(CGAL::squared_distance(pt,pt2)) << std::endl;
        }
    }

}