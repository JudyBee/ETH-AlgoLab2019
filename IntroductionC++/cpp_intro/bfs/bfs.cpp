#include <iostream>
#include <vector>
#include <queue>
#include <set>

int main(){
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++){
        int n, m, v;
        std::cin >> n >> m >> v;
        std::set<int> edges[n];
        int a,b;
        
        //build graph
        for(int j = 0; j < m; j++){
            std::cin >> a >> b; 
            edges[a].insert(b);
            edges[b].insert(a);
        }
        
        std::vector<int> distance(n, -1);
        std::vector<bool> visited(n, false);
        distance[v] = 0;
        visited[v] = true;
        std::queue<int> que;
        que.push(v);
        int curr;

        while(!que.empty()){
            curr = que.front();
            que.pop();
            std::set<int>::iterator it = edges[curr].begin();
            for(int k = 0; k < edges[curr].size(); k++){
                if(!visited[*it]){
                    que.push(*it);
                }
                if (distance[*it] == -1){
                    distance[*it] = distance[curr] + 1;
                }
                it++;
            }
            visited[curr] = true;
        }
        
        std::vector<int>::iterator it;
        for (it = distance.begin(); it != distance.end(); it++){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}