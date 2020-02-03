#include <iostream>
#include <set>
#include<vector>
#include <algorithm>


void testcase(){

    long n, m; std::cin >> n >> m;
    std::vector<std::pair<int, int> > jedi;
    int count = 0;
    std::vector<std::pair<int, int> > seg(n);

    for(int i = 0; i < n; ++i){
        int a, b; std::cin >> a >> b;
        if(b<a || a == 1) count++;
        jedi.push_back(std::make_pair(b,1));
        if(a!= 1) jedi.push_back(std::make_pair(a,0));
        seg[i] = std::make_pair(b,a);
    }

    std::sort(jedi.begin(), jedi.end());
    int pos = 1;

    // find best starting point
    for(auto it = jedi.begin(); it != jedi.end() && count > 10 ; ++it){
        pos = it->first;
        if(it->second==1) count--;
        else count++;
    }

    // std::cout << "found position " << pos << std::endl;

    std::vector<std::pair<int, int> > starts;
    std::vector<std::pair<int, int> > final;
    // update segments and find starting points
    for(auto it = seg.begin(); it != seg.end(); ++it){
        bool start = false;
        std::pair<int, int> curr = *it;
        int new_b = curr.first - pos;
        int new_a = curr.second - pos;
        if(new_a < 0) new_a+=m;
        if(new_b < 0) new_b+=m;
        if(new_a == 0 || new_b < new_a) {
            start = true;
            starts.push_back(std::make_pair(new_b, new_a));
        }
        if(!start) final.push_back(std::make_pair(new_b, new_a));
    }

    std::sort(final.begin(), final.end());
    // determine how many we can schedule without any jedi from start
    int num_jedi = 0;
    int build_to = 0;
    for(auto it = final.begin(); it!= final.end(); ++it){
       std::pair<int, int> curr = *it;
       if(curr.second > build_to){
           num_jedi++;
           build_to = curr.first;
       }
    }

    for(auto it1 = starts.begin(); it1 != starts.end(); ++it1){
        int curr_count = 1;
        int build_to = it1->first;
        int end = it1-> second;
        if(end == 0) end+=m;
        for(auto it = final.begin(); it != final.end(); ++it){
            std::pair<int, int> curr = *it;
            if(curr.second > build_to && curr.first < end){
                curr_count++;
                build_to = curr.first;
            }
        }
        num_jedi = std::max(num_jedi, curr_count);
    }
    std::cout << num_jedi << std::endl;
}


int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}