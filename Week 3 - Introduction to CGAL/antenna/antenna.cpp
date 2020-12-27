#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K> Traits;
typedef  CGAL::Min_circle_2<Traits> Min_circle;

double ceil_to_double(K::FT r){
    double rad = std::ceil(CGAL::to_double(r));
    while (rad+1 >= r){
        rad -= 1;
    }
    while (rad < r){
        rad += 1;
    }
    return rad;
}

void testcase(int n){
    std::vector<K::Point_2> homes;
    long x, y;
    for(int i = 0; i < n; i++){
        std::cin >> x >> y;
        homes.push_back(K::Point_2(x,y));
    }
    Min_circle mc(homes.begin(), homes.end(), true);
    Traits::Circle c = mc.circle();
    K::FT r = CGAL::sqrt(c.squared_radius());
    double rad = ceil_to_double(r);
    std::cout << rad << std::endl;

}

int main(){
    std::ios_base::sync_with_stdio(false); // Always!
    std::cout << setiosflags(std::ios::fixed) << std::setprecision(0);
    int n; 
    std::cin >> n;
    while (n!=0){
        testcase(n);
        std::cin >> n;
    }
}