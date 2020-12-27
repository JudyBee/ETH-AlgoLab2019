#include <iostream>
// needed for LP solver using just ints
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

#include <CGAL/Quotient.h>

#include <vector>

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq) typedef CGAL::Gmpz ET;
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> SolT;

double floor_to_double(const CGAL::Quotient<ET>& x){
  double a = std::floor(CGAL::to_double(x));
  while(a>x) --a;
  while(a+1<=x) ++a;
  return a;
}



int main(){
    while(true){
        int n, m;
        std::cin>> n>>m;
        if(n== 0 && m==0) break;
        std::vector<std::vector<int> > nutrients (n, std::vector<int>(2)); //[0] -> min , [1] -> max
        for(int i =0; i < n; i++){
            std::cin >> nutrients[i][0] >> nutrients[i][1];
        }
        //std::cout << "here1" << std::endl;
        std::vector<std::vector<int> > food (m,std::vector<int>(n+1));
        for(int i = 0; i < m; i++){
            std::cin >> food[i][0]; //cost
            for(int j =0; j < n; j++){
                std::cin >> food[i][j+1]; //nutrient
            }
        }
        //std::cout << "here2" << std::endl;
        Program lp (CGAL::LARGER, true, 0, false, 0);

        for(int i = 0; i < 2*n; i+=2){ // min and max constrain of nutrient
            for(int j =0; j < m; j++){
                lp.set_a(j,i,food[j][(i/2)+1]); // min constrain
                lp.set_a(j,i+1,-food[j][(i/2)+1]); // max constrain -> inverted
            }
            lp.set_b(i, nutrients[i/2][0]);
            lp.set_b(i+1, -nutrients[i/2][1]);
        }
        //std::cout << "here3" << std::endl;
        for(int i = 0; i< m; i++){
            lp.set_c(i,food[i][0]); // minimize total cost
        }
        //std::cout << "here4" << std::endl;
        Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()){
            std::cout << "No such diet." << std::endl;
        } else {
            std::cout << floor_to_double(s.objective_value()) << std::endl;
        }
    }
}