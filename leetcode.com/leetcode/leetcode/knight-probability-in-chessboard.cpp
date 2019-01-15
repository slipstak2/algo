#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <queue>
#include <vector>
#include <string>
#include <numeric>  
#include <iostream>
#include <algorithm>

class Solution {
   typedef std::vector<double> vd;
   typedef std::vector<vd>  vvd;
public:
   bool correct(int row, int col, int N) {
      if (0 <= row && row < N) {
         if (0 <= col && col < N) {
            return true;
         }
      }
      return false;
   }

   double knightProbability(int N, int K, int r, int c) {

      int moveX[8] = {-2, -2, -1, -1, 1,  1, 2,  2};
      int moveY[8] = { 1, -1, -2,  2, -2, 2, -1, 1};

      vvd cur(N, vd(N));
      vvd nxt = cur;

      cur[r][c] = 1;
      while (K--) {
         for (int row = 0; row < N; ++row) {
            for (int col = 0; col < N; ++col) {
               if (cur[row][col]) {
                  for (int p = 0; p < 8; ++p) {
                     int nRow = row + moveX[p];
                     int nCol = col + moveY[p];
                     if (correct(nRow, nCol, N)) {
                        nxt[nRow][nCol] += 0.125 * cur[row][col];
                     }
                  }
               }
            }
         }
         nxt.swap(cur);
         std::fill(nxt.begin(), nxt.end(), vd(N));
      }

      double res = 0;
      for (const vd &row: cur) {
         res = accumulate(row.begin(), row.end(), res);
      }
      return res;

   }
};

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   std::ios::sync_with_stdio(0);

   int n, k, r, c;
   std::cin >> n >> k >> r >> c;

   Solution s;
   std::cout << s.knightProbability(n, k, r, c);

   return 0;
}