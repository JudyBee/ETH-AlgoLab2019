#include <iostream>
#include <stack>
#include <vector>
#include <set>

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++){
        //declare variables
        int n, m, v, a, b;
        std::vector<bool> visited(n, false);
        std::stack<std::pair<int, char> > order;
        std::pair<int, char> curr;
        std::vector<int> path;

        //read in values from std::cin
        std::cin >> n >> m >> v;
        std::set<int> edges[n];
        
        //build graph
        for(int j = 0; j < m; j++){
            std::cin >> a >> b; 
            edges[a].insert(b);
            edges[b].insert(a);
        }
        order.push(std::make_pair(v, 'n'));
        
        for (int k = 0; !order.empty(); k++){
            curr = order.top();
            order.pop();
            if(visited[curr.first] && curr.second =='n'){
                order.pop();
                continue;
            }
            path.push_back(curr.first);
            if(!visited[curr.first]){
                visited[curr.first] = true;
                for(std::set<int>::iterator it = edges[curr.first].end(); it != edges[curr.first].begin()++; ){
                    it--;
                    if(!visited[*it]){
                        order.push(std::make_pair(curr.first, 'o'));
                        order.push(std::make_pair(*it, 'n'));
                    }
                }
            }
        }

        std::vector<int> in(n, -1);
        std::vector<int> out(n, -1);
        std::vector<int>::iterator it = path.begin();
        for (int index = 0; it != path.end(); index++){
            if(in[*it]==-1){
                in[*it]= index;
            }
            out[*it] = index + 1;
            it++;
        }
        for(int g = 0; g < n; g++){
            std::cout << in[g] << " ";
        }
        std::cout << std::endl;
         for(int g = 0; g < n; g++){
            std::cout << out[g] << " ";
        }
        std::cout << std::endl;
    }
}