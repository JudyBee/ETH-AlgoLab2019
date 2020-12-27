#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <queue> 
#include <map>
#include <algorithm>
//typedef long L;
// enum Color{ Black = 0, White = 1, Red = 2};
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<long, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,  Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;
typedef K::Point_2 P;
typedef Triangulation::Face_handle Face;
//typedef std::map<Face, long> distmap;

int main(){
    std::ios_base::sync_with_stdio(false);
    int n; 
    for(std::cin >> n; n> 0; std::cin >> n){
        std::vector<P> infected;
        for(int i = 0; i < n; ++i){
            K::FT x,y; std::cin >> x >> y;
            P pt = P(x,y);
            infected.push_back(pt);
        }

        Triangulation t;
        t.insert(infected.begin(), infected.end());

        int m; std::cin >> m;
        std::vector<std::pair<P, long> > healthy(m);
        for(int i = 0; i < m; ++i){
            int x,y; long d; std::cin >> x >> y >> d;
            healthy[i] = std::make_pair(P(x,y), d);
        }
        
        std::priority_queue<std::pair<long, Face> > dijk;

        // update info for finite faces
        for(Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f){
            f -> info() = 0; // black has not been visited
        }
      
        // update info for infinite faces
        Triangulation::Face_circulator f = t.incident_faces(t.infinite_vertex()); 
        do {
            for(int i = 0; i < 3; ++i){
                Face curr = f->neighbor(i);
                if(!t.is_infinite(curr)){
                    P p1 = f->vertex((i+1)%3)->point();
                    P p2 = f->vertex((i+2)%3)->point();
                    // std::cout << p1 << " " << p2 << " " << CGAL::squared_distance(p1, p2) << std::endl;
                    long length = CGAL::squared_distance(p1, p2);
                    dijk.push(std::make_pair(length, curr));
                    f->info() = length; 
                }
            }
        }while (++f != t.incident_faces(t.infinite_vertex())); 
        
        while(!dijk.empty()){
            std::pair<long, Face> curr = dijk.top();
            dijk.pop();
            if(curr.second -> info() < curr.first){
                curr.second -> info() = curr.first;
                for(int i = 0; i < 3; ++i){
                    Face temp = curr.second->neighbor(i);
                    if(t.is_infinite(temp)) continue;
                    long edge_length = CGAL::squared_distance(curr.second->vertex((i+1)%3)->point(),curr.second->vertex((i+2)%3)->point());
                    edge_length = std::min(edge_length, curr.second->info());
                    if (temp ->info() < edge_length) dijk.push(std::make_pair(edge_length, temp));
                }
            }
        }

        for(int i = 0; i < m; ++i){
            if (CGAL::squared_distance(healthy[i].first, t.nearest_vertex(healthy[i].first)->point()) < healthy[i].second) {
                std::cout << "n";
                continue;
            }
            Triangulation::Locate_type lt;
            int x;
            Triangulation::Face_handle pos = t.locate(healthy[i].first,lt,x);
            if(lt==Triangulation::Locate_type::EDGE){
                if(pos->neighbor(x)->info() > pos->info()){
                pos = pos->neighbor(x);
                } 
            }
            if(pos->info() >= healthy[i].second*4 || t.is_infinite(pos))
                std::cout << "y";
            else
                std::cout << "n";
        }
        // std::cout << "\n\n\n" <<std::endl;
        std::cout << std::endl;
    }
}