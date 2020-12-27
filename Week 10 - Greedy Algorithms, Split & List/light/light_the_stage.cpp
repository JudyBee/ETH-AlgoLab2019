#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;

void testcase(){
    int n, m, h; std::cin >> m >> n;
    std::vector<std::pair<K::Point_2, K::FT>> p(m);
    for(int i = 0; i < m; ++i){
        int x,y;
        K::FT r;
        std::cin >> x >> y >> r;
        p[i] = std::make_pair(K::Point_2(x,y), r);
    }
    std::cin >> h;
    std::vector<std::pair<K::Point_2, int> > lambs(n);
    for(int i = 0; i < n; ++i){
        int x, y; std::cin >> x >> y;
        lambs[i] = std::make_pair(K::Point_2(x,y), i);
    }
    Delaunay t;
    t.insert(lambs.begin(), lambs.end());
    std::vector<bool> alive(m,true);
    int count = m;
    std::vector<int> oldest;;
    int age = -1;
    int old = 0;
    for(int i = 0; i < m; ++i){
        K::Point_2 pp = p[i].first;
        K::Point_2 p1 = t.nearest_vertex(pp)->point();
        if(CGAL::squared_distance(pp, p1) >= (p[i].second + h)*(p[i].second + h)) continue;
        alive[i] = false;
        count--;
        for(int j = 0; j < n; ++j){
            p1 = lambs[j].first;
            if(CGAL::squared_distance(pp, p1) >= (p[i].second + h)*(p[i].second + h)) continue;
            int curr_age = j;
            if(curr_age > age){
                old = 1;
                age = curr_age;
                oldest.clear();
                oldest.push_back(i);
            } else if(curr_age == age){
                old++;
                oldest.push_back(i);
            }
            break;
        }
    }
    if(!count) {
        for(int i = 0; i < old; ++i) std::cout << oldest[i] << " ";
    } else{
        for(int i = 0; i < m; ++i) {
            if(alive[i]) std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}