// https://leetcode.com/problems/maximum-subarray/description/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)

class Solution {
public:
	int maxSubArray(vector<int>& nums) 	{
		if (nums.size() == 0) {
			return 0;
		}

		ll res = nums[0];
		ll cur = 0;
		for (size_t i = 0; i < nums.size(); ++i) {
			cur = max(cur + nums[i], (ll)nums[i]);
			res = max(res, cur);
		}
		return res;
	}
};

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(0);

	int n;
	cin >> n;
	vi v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	
	Solution s;
	cout << s.maxSubArray(v);

	return 0;
}