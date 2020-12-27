#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

void testcase(IK::FT n){
    IK::FT ox, oy, dx, dy;
    std::cin >> ox >> oy >> dx >> dy;
    IK::Ray_2 R (IK::Point_2(ox, oy), IK::Point_2(dx,dy));
    IK::Segment_2 S;
    bool useful = true;
    for(int i = 0; i < n; i++){
        std::cin >> ox >> oy >> dx >> dy;
        if(useful){
            S = IK::Segment_2(IK::Point_2(ox, oy), IK::Point_2(dx, dy));
            if(CGAL::do_intersect(R, S)){
                std::cout << "yes" << std::endl;
                useful = false;
            }
        }
    }
    if(useful){
        std::cout << "no" << std::endl;
    }
}


int main(){
    std::ios_base::sync_with_stdio(false); // Always!
    IK::FT n;
    std::cin >> n;
    while(n != 0){
        testcase(n);
        std::cin >> n;
    }
}