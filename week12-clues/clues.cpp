#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::pair<int, bool>                                   Inf; // int: component bool: color
typedef CGAL::Triangulation_vertex_base_with_info_2<Inf,K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Delaunay;
typedef K::Point_2                                             P;

void testcase(){
    int n, m;
    long r; std::cin >> n >> m >> r;
    std::vector<P> points(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points[i] = P(x, y);
    }
    std::vector<std::pair<P,P>> clues(m);
    for(int i = 0; i < m; ++i){
        int x1,y1,x2,y2; std::cin >> x1 >> y1 >> x2 >> y2;
        clues[i] = std::make_pair(P(x1,y1), P(x2,y2));
    }
    Delaunay t;
    t.insert(points.begin(), points.end());
    for(auto f = t.finite_vertices_begin(); f!= t.finite_vertices_end(); ++f)
        f-> info() =std::make_pair(0, false);
    int components = 0;
    bool valid_coloring = true;
    Delaunay t1, t2;

    for(auto f = t.finite_vertices_begin(); f!= t.finite_vertices_end() && valid_coloring; ++f){
        if(f->info().first == 0){// vertex has not been put into a component yet
            f->info() = std::make_pair(++components,true); // assign it to a new component
            std::vector<Delaunay::Vertex_handle> stack(1,f);
            while(!stack.empty()&& valid_coloring){
                auto curr = stack.back();
                stack.pop_back(); 
                auto v = t.incident_vertices(curr);
                do{
                    if(!t.is_infinite(v) && CGAL::squared_distance(curr->point(), v->point()) <= r*r){// should be in the same component
                        if(curr->info().first == v->info().first && curr->info().second == v->info().second){
                            valid_coloring = false;
                            break;
                        }
                        else if (v->info().first == 0){
                            v->info() = std::make_pair(curr->info().first, !(curr->info().second));
                            stack.push_back(v);
                        } 
                    }
                }while(++v != t.incident_vertices(curr)&& valid_coloring);
            }
        }
        if(f->info().second) t1.insert(f->point());
        else t2.insert(f->point());
    }

    for(auto it = t1.finite_edges_begin(); it!= t1.finite_edges_end() && valid_coloring; ++it){
        if(t1.segment(it).squared_length() <= r*r) valid_coloring = false;
    }

    for(auto it = t2.finite_edges_begin(); it!= t2.finite_edges_end() && valid_coloring; ++it){
        if(t2.segment(it).squared_length() <= r*r) valid_coloring = false;
    }

    for(int i = 0; i < m; ++i){
        if(!valid_coloring){
            std::cout <<"n";
            continue;
        }
        if(CGAL::squared_distance(clues[i].first, clues[i].second)<r*r){
            std::cout << "y";
            continue;
        }
        auto p1 = t.nearest_vertex(clues[i].first);
        auto p2 = t.nearest_vertex(clues[i].second);
        if(CGAL::squared_distance(p1->point(), clues[i].first) <= r*r && CGAL::squared_distance(p2->point(), clues[i].second) <= r*r && p1->info().first == p2->info().first)
            std::cout << "y";
        else std::cout << "n";
    }
    std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >>t;
    while(t--) testcase();
}