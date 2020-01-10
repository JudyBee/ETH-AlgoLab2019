#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> objective_t;

double ceil_to_double( objective_t const & o ) {
    double d = std::ceil( CGAL::to_double( o ) ); 
    while( d < o ) d += 1;
    while(d-1>= o)d-=1;
    return d;
}

double floor_to_double(const CGAL::Quotient<ET>& x){
  double a = std::floor(CGAL::to_double(x));
  while(a>x) --a;
  while(a+1<=x) ++a;
  return a;
}

void max(){
    int a ,b; std::cin >> a >> b;
    Program lp(CGAL::SMALLER, true, 0, false, 0);
    // max by - ax
    lp.set_c(1, -b); lp.set_c(0,a);
    // x + y <= 4
    lp.set_a(0,0,1); lp.set_a(1,0,1); lp.set_b(0,4);
    // 4x +2y <= ab
    lp.set_a(0,1,4); lp.set_a(1,1,2); lp.set_b(1,a*b);
    // -x + y <= 1
    lp.set_a(0,2,-1); lp.set_a(1,2,1); lp.set_b(2,1);

    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_unbounded()) std::cout << "unbounded" << std::endl;
    else if (s.is_infeasible()) std::cout << "no" << std::endl;
    else if (s.is_optimal()) std::cout << std::setprecision( 0 ) << std::fixed << floor_to_double( -s.objective_value() ) << std::endl;

}

void min(){
    int a, b; std::cin >> a >> b;
    Program lp(CGAL::SMALLER, false, 0, true, 0);
    // min ax + by + z
    lp.set_c(0,a); lp.set_c(1,b); lp.set_c(2,1);
    // x + y > = -4
    lp.set_a(0,0,-1); lp.set_a(1,0,-1); lp.set_b(0,4);
    // 4x + 2y + z >= -ab
    lp.set_a(0,1,-4); lp.set_a(1,1,-2); lp.set_a(2,1,-1); lp.set_b(1,a*b);
    // -x+y >=-1
    lp.set_a(0,2,1); lp.set_a(1,2,-1); lp.set_b(2,1);
    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_unbounded()) std::cout << "unbounded" << std::endl;
    else if (s.is_infeasible()) std::cout << "no" << std::endl;
    else if (s.is_optimal()) std::cout << std::setprecision( 0 ) << std::fixed << ceil_to_double( s.objective_value() ) << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int p;  std::cin >> p;
    while(p){
        if(p == 1)
            max();
        else if (p==2)
            min();
        std::cin >> p;
    }
}