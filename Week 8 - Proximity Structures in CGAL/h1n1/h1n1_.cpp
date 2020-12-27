#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <map>
#include <queue>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K; 
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef K::FT path_width;
typedef CGAL::Triangulation_face_base_with_info_2<path_width, K> Fb; 
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds; 
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 P;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef std::map<Triangulation::Face_handle,std::vector<std::pair<Triangulation::Face_handle, K::FT>>> neighbor_map;
enum Color { Black = 0, White = 1};
typedef std::map<Triangulation::Face_handle,Color> Colormap;

void testcase(int n){
    std::vector<P> pts(n);
    for(int i = 0; i < n; ++i){
        int x,y; std::cin >> x >> y;
        pts[i] = P(x,y);
    }

    int m; std::cin >>m;
    std::vector<std::pair<P, long>> queries(m);
    for(int i = 0; i < m; ++i){
        int y,x; long d; std::cin >> x >> y >> d;
        queries[i] = std::make_pair(P(x,y), d);
    }
    Triangulation t;
    t.insert(pts.begin(), pts.end());

    neighbor_map neighbor;
    Colormap Color;
    std::priority_queue<std::pair<K::FT, Triangulation::Face_handle>> pq;

    for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f){
        std::vector<std::pair<Triangulation::Face_handle, K::FT>> curr (3);
        Color[f] = White;
        for(int i = 0; i < 3; ++i){
            Triangulation::Face_handle fh = f->neighbor(i);
            K::FT length = CGAL::squared_distance(f->vertex((i+1)%3)->point(), f->vertex((i+2)%3)->point());
            curr[i] = std::make_pair(fh, length);
            if(t.is_infinite(fh)){
                pq.push(std::make_pair(length, f));
            }
        }
        neighbor[f] = curr;
    }

    while(!pq.empty()){
        std::pair<K::FT, Triangulation::Face_handle> curr = pq.top();
        Triangulation::Face_handle curr_v = curr.second;
        K::FT curr_l = curr.first;
        pq.pop();
        if(Color[curr_v] == White){// have not been here yet
            curr_v->info() = curr_l;
            Color[curr_v] = Black;
            for(auto it = neighbor[curr_v].begin(); it != neighbor[curr_v].end(); ++it){
                if(Color[it->first] == White){
                    K::FT new_l = std::min(it->second, curr_l);
                    Triangulation::Face_handle new_v = it->first;
                    pq.push(std::make_pair(new_l, new_v));
                }
            }
        }
    }

    for(int i = 0; i < m; ++i){
        std::pair<P, K::FT> curr = queries[i];
        P p1 = t.nearest_vertex(curr.first)->point();
        if(CGAL::squared_distance(p1, curr.first) <  curr.second){
            std::cout << "n";
            continue;
        }
        Triangulation::Face_handle f = t.locate(curr.first);
        if(t.is_infinite(f) || f->info() >= 4*curr.second){
            std::cout << "y";
            continue;
        }
        std::cout << "n";
    }
    std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n; std::cin >> n;
    while(n){
        testcase(n);
        std::cin >> n;
    }
}