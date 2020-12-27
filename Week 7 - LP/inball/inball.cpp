#include <iostream>
#include <cmath>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Quotient.h>


// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq) typedef CGAL::Gmpz ET;
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


int main(){
    std::ios_base::sync_with_stdio(false);
    int n, d;
    while(true){
        std::cin >> n;
        if(n==0) break;
        std::cin>> d;
        Program lp (CGAL::SMALLER, false, 0, false, 0);
        
        
        for(int i = 0; i < n; i++){
            double sum = 0;
            for(int j = 0; j < d; j++){
                int a; 
                std::cin >> a;
                sum+= a*a;
                lp.set_a(j, i, a);
            }
            double norm = std::floor(std::sqrt(sum));
            lp.set_a(d,i,norm);
            int b;
            std::cin >>b;
            lp.set_b(i,b);
        }
        lp.set_c(d,-1);
        lp.set_l(d,true,0);
        Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()){
            std::cout << "none" << std::endl;
        } else if(s.is_unbounded()){
            std::cout << "inf" << std::endl;
        } else{
            std::cout << -(s.objective_value().numerator()/s.objective_value().denominator()) << std::endl;
        }
    }

}