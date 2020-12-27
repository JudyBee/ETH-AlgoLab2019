#include <iostream> 
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include<cmath> 

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main(){
    std::ios_base::sync_with_stdio(false);
    int n;
    for(std::cin >> n; n>0; std::cin >> n){
        Program lp (CGAL::SMALLER, false, 0, false, 0);
        int d; std::cin >> d;
        for(int i = 0; i< n; ++i){
            IT norm = 0;
            for(int j = 0; j < d; ++j){
                IT a; std::cin >> a;
                norm+=a*a;
                lp.set_a(j,i,a);
            }
            norm = std::floor(std::sqrt(norm));
            lp.set_a(d,i,norm);
            IT b; std::cin >> b;
            lp.set_b(i,b);
        }
        lp.set_c(d,-1);
        lp.set_l(d,true,0);
        Solution s = CGAL::solve_linear_program(lp,ET());
        if(s.is_unbounded()) std::cout << "inf" << std::endl;
        else if(s.is_infeasible()) std::cout << "none" << std::endl;
        else std::cout << -(s.objective_value().numerator()/s.objective_value().denominator()) << std::endl;
    }
}