#include <iostream>
#include <vector>
#include <algorithm> 
#include <climits>

struct punch_mixture{
	int cost; 
	std::vector<int> drinks; 
	int num_drinks;

	punch_mixture(int c, std::vector<int> d, int num) : cost(c), drinks(d), num_drinks(num){};
	bool operator<(const punch_mixture& other) const {
		if(cost == other.cost)
			return num_drinks > other.num_drinks;
		return cost < other.cost;
	};
};

void testcase(){
	int n,k; std::cin >> n >> k;
	std::vector<std::pair<int, int> > bev_all(n);
	for(int i = 0; i < n; ++i){
		int c, v; std::cin >> c >> v;
		bev_all[i] = std::make_pair(v,c);
	}
	punch_mixture a = punch_mixture(INT_MAX, std::vector<int> (n, 0), 0);
	std::vector<punch_mixture> dp (k+1, a);
	dp[0].cost = 0;
	for(int curr_liter = 1; curr_liter <= k; ++curr_liter){
		for(int curr_bev = 0; curr_bev < n; ++curr_bev){
			int vol_look_up = std::max(0, curr_liter-bev_all[curr_bev].first);
			auto& current = dp[curr_liter];
			auto& newpm = dp[vol_look_up];
			bool is_smaller = false;
			if(current.cost == newpm.cost + bev_all[curr_bev].second)
				is_smaller = current.num_drinks > newpm.num_drinks + 
					!(newpm.drinks[curr_bev]);
			else 
				is_smaller = current.cost < newpm.cost + bev_all[curr_bev].second;
			if(!is_smaller) {
				punch_mixture new_punch = dp[vol_look_up];
				if(!new_punch.drinks[curr_bev]) new_punch.num_drinks++;
				new_punch.drinks[curr_bev]++;
				new_punch.cost += bev_all[curr_bev].second;
				current = new_punch;
			}
		}   
	}
	std::cout << dp[k].cost << " " << dp[k].num_drinks << std::endl;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t--) testcase();     
}