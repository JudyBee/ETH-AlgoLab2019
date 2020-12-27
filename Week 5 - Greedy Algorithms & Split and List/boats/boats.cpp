#include <iostream> 
#include <vector>
#include <algorithm>

int build_to; 
std::vector<std::pair<int, int> > boats;
std::vector<int> boats_selected;

void testcase();
void include(int curr_boat);

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for(int i = 0; i < t; i++){
        boats.clear();
        boats_selected.clear();
        build_to = 0;
        testcase();
    }
}

void testcase(){
    int num_boats; std::cin >> num_boats;
    boats = std::vector<std::pair<int, int> > (num_boats);
    int ring, length;
    for(int i = 0; i < num_boats; i++){
        std::cin >> length >> ring;
        std::pair<int, int> add = std::make_pair(ring, length);
        boats[i] = add;
    }
    std::sort(boats.begin(), boats.end());
    boats_selected.clear();
    boats_selected.push_back(0);
    build_to = boats[0].first;
   
    for(int i = 1; i < num_boats; i++){
        include(i);
    }
    std::cout << boats_selected.size() << std::endl;
}

void include(int curr_boat){
    if(build_to > boats[curr_boat].first){
        return;
    }
    if(boats[curr_boat].first - boats[curr_boat].second > build_to){
        boats_selected.push_back(curr_boat);
        build_to = boats[curr_boat].first;
        return;
    }
    int new_end = build_to + boats[curr_boat].second;
    int next = curr_boat +1;
    bool better_option = false;
    while(next < boats.size()){
        if(new_end <= boats[next].first){
            break;
        } else if(boats[next].first - boats[next].second >= build_to){
            better_option = true;
            break;
        } else if(build_to + boats[next].second < new_end){
            better_option = true;
            break;
        }
        next++;
    }
    if(!better_option){
        boats_selected.push_back(curr_boat);
        build_to = new_end;
    }
}