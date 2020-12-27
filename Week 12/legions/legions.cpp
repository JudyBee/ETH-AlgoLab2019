#include <iostream>
// example: how to solve a simple explicit LP
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>
// choose input type (input coefficients must fit)
typedef long L;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(){
    int x,y,n; std::cin >> x >> y >> n;
    Program lp (CGAL::SMALLER, false, 0, false, 0); 
    // 2 constrains: 
    //      -center must be on right side, 
    //      -radius may not cross line

    for(int i = 0; i < n; ++i){
        L a,b,c,v; std::cin >> a >> b >> c >> v;
        ET norm = std::floor(std::sqrt(a*a+b*b));
        ET initial_side = a*x + b*y + c;

        // first constrain
        lp.set_a(0,2*i,a);
        lp.set_a(1,2*i,b);
        lp.set_r(2*i, (initial_side<0)? CGAL::SMALLER : CGAL::LARGER);
        lp.set_b(2*i, -c);

        // second constrain
        lp.set_a(0,2*i+1, a);
        lp.set_a(1,2*i+1, b);
        lp.set_a(2, 2*i+1, (initial_side<0)? 1*norm*v : -1*norm*v);
        lp.set_r(2*i+1, (initial_side<0)? CGAL::SMALLER : CGAL::LARGER);
        lp.set_b(2*i+1, -c);
    }


    lp.set_c(2,-1);
    lp.set_l(2, 0);
    Solution s = CGAL::solve_linear_program(lp, ET());
    std::cout << -s.objective_value().numerator()/s.objective_value().denominator() << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >>t;
    while(t--) testcase();
}