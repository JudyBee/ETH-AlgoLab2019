#include <iostream>
#include <vector>
#include <set>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

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
    K::Point_2 cen = c.center();
    K::FT max_dist;
    K::FT temp;
    std::vector<std::vector<K::Point_2>::iterator> max_index;
    for(std::vector<K::Point_2>::iterator it = homes.begin(); it != homes.end(); it++){
        temp = CGAL::squared_distance(*it, cen);
        if(temp > max_dist){
            max_dist = temp;
            max_index.clear();
            max_index.push_back(it);
        } else if (temp == max_dist){
            max_index.push_back(it);
        }
    }
    std::set<K::FT> min_rad;
    K::Point_2 te;
    for(int i = 0; i < max_index.size(); i++){
        te = *max_index[i];
        homes.erase(max_index[i]);
        Min_circle mc2(homes.begin(), homes.end(), true);
        Traits::Circle c2 = mc2.circle();
        K::FT r = CGAL::sqrt(c2.squared_radius());
        min_rad.insert(r);
        homes.insert(homes.begin(), te);
    }
    double rad = ceil_to_double(*min_rad.begin());
    std::cout << rad << std::endl;
}


int main(){
    std::ios_base::sync_with_stdio(false); // Always!s
    std::cout << setiosflags(std::ios::fixed) << std::setprecision(0);
    int n; 
    std::cin >> n;
    while(n!=0){
        testcase(n);
        std::cin>> n;
    }
}