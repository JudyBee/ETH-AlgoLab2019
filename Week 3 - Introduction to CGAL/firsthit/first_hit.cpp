#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <type_traits>
#include <vector>
#include <iomanip>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

void floor_to_double(K::Point_2 hit){
    double x = std::floor(CGAL::to_double(hit.x()));
    double y = std::floor(CGAL::to_double(hit.y()));
    while (x > hit.x()){
        x -= 1;
    }
    while (x+1 <= hit.x()){
        x += 1;
    }
    while (y > hit.y()){
        y -= 1;
    }
    while (y+1 <= hit.y()){
        y += 1;
    }
    std::cout <<  std::floor(x)  << " " <<  std::floor(y) << std::endl;
}

void testcase(int n){
    long sx, sy, ex, ey;
    std::cin >> sx >> sy >> ex >> ey; // values for ray
    K::Point_2 RS (sx,sy); // starting point of ray will be always be one endpoint of segment
    K::Ray_2 R (RS, K::Point_2(ex, ey));
    bool intersection = false;
    K::Point_2 first_hit;
    std::vector<K::Segment_2> save;
    K::Segment_2 EASY;
    std::vector<K::Segment_2> segments;
    for(int i = 0; i < n; i++){
        std::cin >> sx >> sy >> ex >> ey; 
        K::Segment_2 S(K::Point_2(sx, sy), K::Point_2(ex, ey));
        segments.push_back(S);
    }
    std::random_shuffle(segments.begin(), segments.end());
    for(int i = 0; i < n; i++){
        //std::cin >> sx >> sy >> ex >> ey; 
        K::Segment_2 S = segments[i];
        if(!intersection){
            if(CGAL::do_intersect(R, S)){
                // we found an intersection -- change ray to segment and compare to segment intersectrion from now on
                intersection = true; 
                auto o = CGAL::intersection(S, R); // computation !
                if (const K::Point_2 *p = boost::get<K::Point_2>(&*o) ){
                    first_hit=*p;
                    EASY = K::Segment_2(RS, first_hit); // use EASY instead of ray from now on
                } else if (const K::Segment_2* os = boost::get<K::Segment_2>(&*o)){
                    if(CGAL::squared_distance(RS,os->source()) < CGAL::squared_distance(RS,os->target())){
                        first_hit = os->source();
                    } else {
                        first_hit = os->target();
                    }
                    EASY = K::Segment_2(RS, first_hit);
                }
            }
        } else {
            if(CGAL::do_intersect(EASY, S)){
                auto o = CGAL::intersection(S, EASY); // computation !
                if (const K::Point_2 *p = boost::get<K::Point_2>(&*o) ){
                    first_hit=*p;
                    EASY = K::Segment_2(RS, first_hit); // shorten ray
                } else if (const K::Segment_2* os = boost::get<K::Segment_2>(&*o)){
                    save.push_back(*os);
                }
            }
        }
    }

    for(std::vector<K::Segment_2>::iterator it = save.begin(); it != save.end(); it++){
        if(CGAL::do_intersect(EASY, *it)){
            K::Segment_2 os = *it;
            if(CGAL::squared_distance(RS,os.vertex(0)) < CGAL::squared_distance(RS,os.vertex(1))){
                first_hit = os.vertex(0);
            } else {
                first_hit = os.vertex(1);
            }
            EASY = K::Segment_2(RS, first_hit);
        }
    }
    if(intersection){
        floor_to_double(first_hit);
    } else {
        std::cout << "no" << std::endl;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false); // Always!
    std::cout << setiosflags(std::ios::fixed) << std::setprecision(0);
    long n;
    std::cin >> n;
    while(n != 0){
        testcase(n);
        std::cin >> n;
    }
}