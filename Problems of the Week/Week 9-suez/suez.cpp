#include <iostream> 
#include <climits>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <cmath> 

typedef int IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> objective_t;

double ceil_to_double( objective_t const & o ) {
    double d = std::ceil( CGAL::to_double( o ) );
    while( d < o ) d += 1;
    while(d-1>= o)d-=1;
    return d;
}
void testcase(){
    IT n, m, h, w; std::cin >> n >> m >> h >> w;
    std::vector<std::pair<int, int> > free(n);
    for(int i = 0; i< n; ++i){
        int x, y; std::cin >> x >> y;
        free[i] = std::make_pair(x,y);
    }
    std::vector<std::pair<int, int> > occu(m);
    for(int i = 0; i < m; ++i){
        int x,y; std::cin >> x >> y;
        occu[i] = std::make_pair(x,y);
    }
    Program lp(CGAL::SMALLER, true,1,false,0);

    // set objective function
    for(int i = 0; i < n; ++i)
        lp.set_c(i, -2*(h+w));
    // constrains between free nails
    int count = 0;
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            ET dx = std::abs(free[i].first - free[j].first);
            ET dy = std::abs(free[i].second - free[j].second);
            lp.set_a(i, count, 1);
            lp.set_a(j, count, 1);
            lp.set_b(count, 2*std::max(dx/w, dy/h));
            count++;
        }
    }
    // constrains to old nails
    for(int i = 0; i < n; ++i){
        ET upper = INT_MAX;
        for(int j = 0; j < m; ++j){
            ET dx = std::abs(free[i].first - occu[j].first);
            ET dy = std::abs(free[i].second - occu[j].second);
            ET curr = 2* std::max(dx/w, dy/h)-1;
            upper = std::min(upper, curr);
        }
        lp.set_u(i,true, upper);
    }
    
    Solution s = CGAL::solve_linear_program(lp, ET());
    std::cout<< std::setprecision( 0 ) << std::fixed
         << ceil_to_double(-s.objective_value())<< std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t; 
    while(t--) testcase();
} 