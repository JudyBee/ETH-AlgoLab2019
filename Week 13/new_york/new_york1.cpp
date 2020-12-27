#include <iostream>
#include <vector>
#include <set>

void testcase(){
    int n, m, k; std::cin >> n >> m >> k;
    std::vector<int> temp(n);
    for(int i = 0; i < n; ++i){
        int t; std::cin >> t;
        temp[i] = t;
    }
    std::vector<int> leaf(n,1);
    std::vector<int> p(n);
    p[0] = 0;
    for(int i = 0; i < n-1; ++i){
        int u,v; std::cin >> u >> v;
        p[v] = u;
        leaf[u] = 0;
    }
    std::vector<int> sol(n,0);
    bool found = false;
    std::vector<int> cons (n, 0);
    
    for(int i = 0; i < n; ++i){
        if(leaf[i]){
            int start = i;
            int end = i;
            std::multiset<int> path_temps;
            while(1){
                if(cons[end]) break;
                path_temps.insert(temp[start]);
                int min_t = *path_temps.begin();
                int max_t = *path_temps.rbegin();
                if(max_t - min_t > k){
                    path_temps.erase(path_temps.find(temp[end]));
                    cons[end] = 1;
                    end = p[end];
                }
                if(path_temps.size() == m){
                    sol[start] = 1;
                    cons[end] = 1;
                    found = true;
                    path_temps.erase(path_temps.find(temp[end]));
                    end=p[end];
                }
                if(start == 0) break;
                start = p[start];
            } 
        }
    }
    if(!found){
        std::cout << "Abort mission" << std::endl;
        return;
    }
    for(int i = 0; i < n; ++i){
        if(sol[i]) std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}