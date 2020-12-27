#include <iostream>
#include <vector>
#include <set> 
#include <algorithm>

struct bomb{
    int tick;
    int id;
    bool deactivated;
    bomb(int t, int i, bool s): tick(t), id(i), deactivated(s) {}
};

int t; 
bool success;
int n;
std::vector<bomb> bombs;
std::set<std::pair<int,int> > priority;


void testcase();
void deactivate(bomb curr);

int main(){
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    for(int i = 0; i < t; i ++){
        testcase();
    }
}

void testcase(){
    std::cin >> n;
    int tick;
    priority.clear();
    bombs.clear();
    bombs.reserve(n);
    for(int i = 0; i < n; i++){
        std::cin >> tick;
        bomb curr = bomb(tick, i , false);
        bombs[i] = curr;
        std::pair <int, int> cu (tick, i);
        priority.insert(cu);
    }
    t = 0; 
    success = true;
    // deactivate bombs based on priority
    while(!priority.empty()){
        std::pair<int, int> hp = *priority.begin();
        bomb curr = bombs[hp.second];
        if(curr.deactivated){
            priority.erase(hp);
        } else {
            deactivate(curr);
        }
        if(!success)break;
    }

    // output result
    if(success){
        std::cout<< "yes" << std::endl;
    }
    else{
        std::cout<< "no" << std::endl;
    }
}

void deactivate(bomb curr){
    // if curr is not at bottom level deactivate bombs below first
    // it does not matter in which order we deactivate the bombs below the bomb of highest priority
    // their tick is higher than hp anyways so if things fail hp will also fail
    if(curr.id < (n-1)/2){
        deactivate(bombs[2*curr.id+1]);
        deactivate(bombs[2*curr.id+2]);
    }
    //base case
    if(curr.deactivated) return;
    // deactivate bomb if not exploded yet
    else if(t < curr.tick){
        bombs[curr.id].deactivated=true;
        t++;
    } else { // bomb exploded :(
        success = false;
    }
}