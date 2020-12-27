#include <iostream>
#include <vector>
#include <algorithm> 
#include <list> 
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

struct biker{
    int128_t y0;
    int128_t x1;
    int128_t y1;
    int id;
    biker(int128_t ys, int128_t x, int128_t y, int i) : y0(ys), x1(x), y1(y), id(i) {};
};


// return 0: bikers do not hit
// return 1: biker a continues
// return 2: biker b continues
int hit(const biker & a, const biker & b){
    int128_t val1= (a.y1 - a.y0)*(b.x1);
    int128_t val2 = (b.y1-b.y0)*(a.x1); 
    if(a.y0 > b.y0){// case 1 : a starts higher than b
        if(a.y1 >= a.y0){  //case 1a : a goes up -> survives need to check if b also survives
            if(val1 >= val2) return 0;  // a is steeper than b (or b goes down)
            return 1; 
        } else{  // case 1b: a goes down
            if(b.y0 > b.y1){// both go down 
                if(val1 < val2) return 2; 
                return 0; // b is steeper than a
            } else{ // b goes up
                if(val1 * (-1) >= val2) return 2; // a is steeper than b
                return 1; // b is steeper than a
            }
        }
    } else{// case 2 : b starts higher than a
        if(b.y1 >= b.y0){  //case 2a : b goes up -> survives need to check if b also survives
            if(val2 >= val1)   return 0; // b is steeper than a (or a goes down)
            return 2; 
        } else{  // case 1b: a goes down
            if(a.y0 > a.y1){// both go down 
                if(val2 < val1)  return 1; 
                return 0; // a is steeper than b
            } else{ // a goes up 
                if(val2 * (-1) >= val1)return 1; // b is steeper than a
                return 2; // a is steeper than b
            }
        }
    }
}

void testcase(int count){
    int n; std::cin >>n;
    std::list<biker> m;
    for(int i = 0; i < n; ++i){
        int128_t ys, x, y; std::cin >> ys >> x >> y;
        m.push_back(biker(ys,x,y, i));
    }
    
    m.sort([](const biker & a, const biker &b){   
        return a.y0 < b.y0;
    });

    std::list<biker> alive;
  
    for(auto it = m.begin(); it!= m.end(); ){
        bool going = true;
        for(auto it1 = alive.begin(); it1 != alive.end(); ++it1){
            int case1 = hit(*it,*it1);
            if(case1 == 0) break;
            else if(case1 == 1){
                it1 = alive.erase(it1);
                it1--;
            } else {
                going = false;
                break;
            }
        }
        if(going) alive.push_front(*it);
        m.erase(it);
        it = m.begin();
    }

    alive.sort([](const biker & a, const biker &b){
        return a.id < b.id;
    });

    for(auto it = alive.begin(); it != alive.end(); ++it)
        std::cout << it->id << " ";
    std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    int count =1;
    while(t--) {
        testcase(count);
        count++;
    }
}