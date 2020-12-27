#include <iostream> 
#include <vector>
#include <set>

void testcase(){
    int n; std::cin >> n;
    std::vector<int> occs(n);
    for(int i = 0; i < n; ++i){
        int o; std::cin >> o;
        occs[i] = o;
    }
    std::vector<std::vector<int> > locations(n);
    std::vector<std::pair<int, int> > all;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < occs[i]; ++j){
            int curr; std::cin >> curr;
            locations[i].push_back(curr);
            all.push_back(std::make_pair(curr, i));
        }
    }

    std::sort(all.begin(), all.end());

    std::vector<int> count(n,0);
    int curr_min = INT_MAX;
    int seen = 0;
    int curr_max = -1;
    int it1 = 0;
    int it2 = 0;

    while(seen < n) {
        std::pair<int, int>  curr = all[it1];
        seen+= !count[curr.second];
        count[curr.second]++;
        it1++;
    }
    it1--;
    curr_max = all[it1].first;
    std::pair<int, int> curr = all[it2];
    while(count[curr.second] > 1){
        count[curr.second]--;
        it2++;
        curr = all[it2];
    }
    curr_min = all[it2].first;
    int length = curr_max - curr_min +1;

    curr = all[it1];

    while(it1 +1 < all.size() && it2 < all.size()){
        int to_find = all[it2].second;
        it2++;
        it1++;
        curr = all[it1];
        while(it1+1 < all.size()){
            if(curr.second == to_find) break;
            count[curr.second]++;
            it1++;
            curr = all[it1];
        }
        if(curr.second!= to_find) break;
        
        curr = all[it2];
        while(it2+1 < all.size()){
            if(count[curr.second] == 1) break;
            count[curr.second]--;
            it2++;
            curr = all[it2];
        }
        curr_max = all[it1].first;
        curr_min = all[it2].first;
        length = std::min(length, curr_max-curr_min+1);
    }

    std::cout << length << std::endl;




    // std::set<std::pair<int, int>> intervals;
    // for(int i = 0; i < n; ++i)
    //     intervals.insert(std::make_pair(locations[i][0], i));
    
    // int length = std::numeric_limits<int>::max();
    // std::vector<int> ind(n, 0);
    // while(true){
    //     int front = intervals.rbegin()->first;
    //     int back = intervals.begin()->first;
    //     length = std::min(length, front - back + 1);
    //     int back_index = intervals.begin()->second;
    //     if(ind[back_index]+1== occs[back_index]) break;
    //     intervals.erase(intervals.begin());
    //     ind[back_index]++;
    //     int new_ind = locations[back_index][ind[back_index]];
    //     intervals.insert(std::make_pair(new_ind, back_index));
    // }
    // std::cout << length << std::endl;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) testcase();
}