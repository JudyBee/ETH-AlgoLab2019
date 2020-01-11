#include <iostream> 
#include <vector>
#include <iomanip> 
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> SolT;
typedef K::Point_2 P;

struct warehouse{
    int s, a;
    warehouse(int su, int al) : s(su), a(al) {}
};
struct stadium{
    int d,u;
    stadium(int de, int up) : d(de), u(up) {}
};

double floor_to_double(const SolT& x){
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

void testcase(){
    int n,m,c; std::cin >> n >> m >> c;
    // read in warehouse data
    std::vector<warehouse> warehouses;
    std::vector<P> warehouse_positions;
    for(int i = 0; i < n; ++i){
        K::FT x,y;
        int s,a; std::cin >> x >> y >> s >> a;
        warehouses.push_back(warehouse(s,a));
        warehouse_positions.push_back(P(x,y));
    }
    // read in stadium data
    std::vector<stadium> stadiums;
    std::vector<P> stadium_positions;
    for(int i = 0; i < m; ++i){
        K::FT x, y;
        int d,u; std::cin >> x >> y >> d >> u;
        stadiums.push_back(stadium(d,u));
        stadium_positions.push_back(P(x,y));
    }

    // read in revenue data
    std::vector<std::vector<ET> > revenues(n, std::vector<ET>(m));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            ET r; std::cin >> r; 
            revenues[i][j] = r;
        }
    }

    //read in cantors
    std::vector<std::pair<P,int> > cantors;
    for(int i = 0; i < c; ++i){
        K::FT x,y;
        int z; std::cin >> x >> y >> z; 
        cantors.push_back(std::make_pair(P(x,y),z));
    }

    Triangulation t;
    t.insert(warehouse_positions.begin(), warehouse_positions.end());
    t.insert(stadium_positions.begin(), stadium_positions.end());
    for(int i = 0; i < c; ++i){
        P curr = cantors[i].first;
        int r = cantors[i].second;
        P p = t.nearest_vertex(cantors[i].first)->point();
        if(!CGAL::squared_distance(p, curr)< r*r) continue; 
        for(int i = 0; i < n; ++i){
            bool w = CGAL::squared_distance(warehouse_positions[i], curr)< r*r;
            for(int j = 0; j<m; ++j){
                bool s= CGAL::squared_distance(stadium_positions[j], curr) < r*r;
                if(w!=s) revenues[i][j] -= 0.01;
            }
        }
    }

    Program lp(CGAL::SMALLER, true, 0, false, 0);
    
    // set constrains
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            lp.set_a(i*m+j, i, 1); // supply
            lp.set_a(i*m+j, j+n, 1); // demand
            lp.set_a(i*m+j, j+n+m, warehouses[i].a); // alcohol
        }
    }
    for(int i = 0; i < n; ++i){
        lp.set_b(i, warehouses[i].s);
    }
    for(int i = 0; i < m; ++i){
        lp.set_r(n+i, CGAL::EQUAL);
        lp.set_b(i+n, stadiums[i].d);
        lp.set_b(i+n+m, stadiums[i].u*100);
    }

    // objective function (without cantors)
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            lp.set_c(i*m+j, -revenues[i][j]);
        }
    }
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) std::cout << "RIOT!" << std::endl;
    else std::cout << floor_to_double(-s.objective_value()) << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}