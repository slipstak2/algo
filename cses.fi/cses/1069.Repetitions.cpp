#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef vector<int> vi;

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   ios::sync_with_stdio(0);

   string s;
   cin >> s;

   int maxLen = 1;
   int curLen = 1;
   int pos = 1;
   while (pos < s.size()) {
      if (s[pos - 1] == s[pos]) {
         curLen++;
      } else {
         maxLen = max(maxLen, curLen);
         curLen = 1;
      }
	  ++pos;
   }
   maxLen = max(maxLen, curLen);
   cout << maxLen;
   return 0;
}