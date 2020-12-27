#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include<cmath> 

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(){
    int h, t; std::cin >> h >> t;
    std::vector<std::vector<int> > healthy;
    std::vector<std::vector<std::pair<bool,ET> > > powHX (h,std::vector<std::pair<bool,ET> >(31,std::make_pair(false,-1)));
    std::vector<std::vector<std::pair<bool,ET> > > powHY (h,std::vector<std::pair<bool,ET> >(31,std::make_pair(false,-1)));
    std::vector<std::vector<std::pair<bool,ET> > > powHZ (h,std::vector<std::pair<bool,ET> >(31,std::make_pair(false,-1)));
    std::vector<std::vector<int> > tumor;
    std::vector<std::vector<std::pair<bool,ET> > > powTX (t,std::vector<std::pair<bool,ET> >(31,std::make_pair(false,-1)));
    std::vector<std::vector<std::pair<bool,ET> > > powTY (t,std::vector<std::pair<bool,ET> >(31,std::make_pair(false,-1)));
    std::vector<std::vector<std::pair<bool,ET> > > powTZ (t,std::vector<std::pair<bool,ET> >(31,std::make_pair(false,-1)));
    // read in healthy and compute powers
    for(int i = 0; i< h; ++i){
        int x,y,z; std::cin >> x >> y >> z;
        std::vector<int> curr (3);
        curr[0] = x; curr[1] = y; curr[2] = z;
        healthy.push_back(curr);
    }

    // read in tumor and compute powers
    for(int i = 0; i < t; ++i){
        int x,y,z; std::cin >> x >> y >> z;
        std::vector<int> curr (3);
        curr[0] = x; curr[1] = y; curr[2] = z;
        tumor.push_back(curr);
    }

    for(int i = 0; i <=30; ++i){// current degree of polynomial
        Program lp (CGAL::SMALLER, false, 0, false, 0);
        for(int a = 0; a < h; ++a){
            int count = 0;
            for(int j = 0; j <= i; ++j){// degree x
                for(int k = 0; k <= i; ++k){ // degree y
                    for(int l = 0; l <= i; ++l){// degree z
                        if(j+k+l>i) continue;
                        if(!powHX[a][j].first) powHX[a][j] = std::make_pair(true,std::pow(healthy[a][0],j));
                        if(!powHY[a][k].first) powHY[a][k] = std::make_pair(true,std::pow(healthy[a][1],k));
                        if(!powHZ[a][l].first) powHZ[a][l] = std::make_pair(true,std::pow(healthy[a][2],l));
                        ET val = powHX[a][j].second* powHY[a][k].second*powHZ[a][l].second;
                        lp.set_a(count, a, val);
                        count++;
                    }
                }
            }
            lp.set_b(a,-1);
        }
        for(int a = 0; a < t; ++a){
            int count = 0;
            for(int j = 0; j <= i; ++j){// degree x
                for(int k = 0; k <= i; ++k){ // degree y
                    for(int l = 0; l <= i; ++l){// degree z
                        if(j+k+l>i) continue;
                        if(!powTX[a][j].first) powTX[a][j] = std::make_pair(true,std::pow(tumor[a][0],j));
                        if(!powTY[a][k].first) powTY[a][k] = std::make_pair(true,std::pow(tumor[a][1],k));
                        if(!powTZ[a][l].first) powTZ[a][l] = std::make_pair(true,std::pow(tumor[a][2],l));
                        ET val = powTX[a][j].second* powTY[a][k].second*powTZ[a][l].second;
                        lp.set_a(count, a+h, val);
                        count++;
                    }
                }
            }
            lp.set_r(a+h,CGAL::LARGER);
            lp.set_b(a+h,1);
        }
        CGAL::Quadratic_program_options options;
        options.set_pricing_strategy(CGAL::QP_BLAND);
        Solution s = CGAL::solve_linear_program(lp, ET(), options);
        if(!s.is_infeasible()){
            std::cout << i << std::endl;
            return;
        }
    }
    std::cout << "Impossible!" << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int N; std::cin >> N;
    while(N--) testcase();
}