#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <algorithm>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
// choose input type (input coefficients must fit)
// typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;
// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef K::Point_2 P;

void testcase(){
    int a, s, b;
    ET e; 
    std::cin >> a >> s >> b >> e;
    std::vector<std::pair<P, int> > asteroid(a);
    for(int i = 0; i < a; ++i){
        int x,y,d; std::cin >> x >> y >> d;
        asteroid[i] = std::make_pair(P(x,y), d);
    }

    std::vector<P> shooting_points(s);
    for(int i = 0; i < s; ++i){
        int x,y; std::cin  >> x >> y;
        shooting_points[i] = P(x,y);
    }

    std::vector<P> hunters(b);
    for(int i = 0; i < b; ++i){
        int x,y; std::cin >> x >> y;
        hunters[i] = P(x,y);
    }

    Triangulation t;
    t.insert(hunters.begin(), hunters.end());


    std::vector<K::FT> max_r(s);
    if(b){
        for(int i = 0; i < s; ++i){
            P closest = t.nearest_vertex(shooting_points[i])->point();
            max_r[i] = CGAL::squared_distance(closest, shooting_points[i]);
        }
    }
    
    Program lp (CGAL::LARGER, true, 0, false, 0); 
    for(int i = 0; i < a; ++i){
        for(int j = 0; j < s; ++j){
            K::FT f = CGAL::squared_distance(asteroid[i].first, shooting_points[j]);
            if(b && f > max_r[j]) continue;
            if(f < 1) f=1;
            lp.set_a(j,i,1/f);
        }
        lp.set_b(i, asteroid[i].second);
    }

    for(int i = 0; i < s; ++i)
        lp.set_c(i,1);
    
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if(!sol.is_infeasible() && sol.objective_value() <= e) std::cout << "y" << std::endl;
    else std::cout << "n" << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}