#include <iostream> 
#include <unordered_map>
#include <vector>
#include <string> 

void binary(std::vector<int> &path, std::vector<long> & ages, int curr, std::vector<int> & answers, std::pair<int, int> query){
    int h = -1; 
    int l = path.size()-1;
    while(h+1 < l){
        int m = (h+l)/2;
        if(ages[path[m]] <= query.first){
            l = m; 
        }
        else h = m;
    }
    answers[query.second] = path[l];
}

void DFS(std::vector<int> & path, int curr, std::vector<long> & ages, std::vector<std::vector<int> > & tree, std::vector<std::vector<std::pair<int, int> > > & queries, std::vector<int> & answers){
    for(int i = 0; i < queries[curr].size(); ++i){
        binary(path, ages, curr, answers, queries[curr][i]);
    }   
    for(int i = 0; i < tree[curr].size(); ++i){
        path.push_back(tree[curr][i]);
        DFS(path, tree[curr][i], ages, tree, queries, answers);
    }
    path.pop_back();
}

void testcase(){
    int n, q; std::cin >> n >> q;
    std::unordered_map<std::string, int> species;
    std::vector<std::string> names(n);
    std::vector<long> ages(n);
    int max_age = 0;
    int luca_index;

    for(int i = 0; i < n; ++i){
        std::string name; long age; std::cin >> name >> age;
        names[i] = name;
        species.insert(std::make_pair(name,i));
        ages[i] = age;
        if(max_age < age){
            max_age = age; 
            luca_index = i;
        }
    }
    std::vector<std::vector<int>> tree(n);
    for(int i = 0; i < n-1; ++i){
        std::string s,p; std::cin >> s >> p;
        tree[species.at(p)].push_back(species.at(s));
    }

    std::vector<std::vector<std::pair<int, int> > > queries(n);
    for(int i = 0; i < q; ++i){
        std::string s; long age;
        std::cin >> s >> age;
        queries[species.at(s)].push_back(std::make_pair(age, i));
    }
    
    std::vector<int> answers(q);
    std::vector<int> path (1,luca_index);
    DFS(path, luca_index, ages, tree, queries, answers);

    for(int i = 0; i < q; ++i){
        std::cout << names[answers[i]];
        if(i < q-1) std::cout <<" ";
    }
    std::cout << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--)testcase();
}