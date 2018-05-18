#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct exam {
   exam(int num, int begin, int dayX, int days) 
      : num(num)
      , begin(begin)
      , dayX(dayX)
      , days(days) {}
 
   int begin;
   int dayX;
   int days;
   int num;
};


bool operator < (const exam& x, const exam& y) {
   return x.dayX < y.dayX;
}

vector<exam> exams;
vector<int> session;


void SESSION_FAILED() {
   cout << -1;
   exit(0);
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   int sesCnt, examCnt;
   cin >> sesCnt >> examCnt;
   session.resize(sesCnt + 1);

   int begin, dayX, days;
   for (int i = 0; i < examCnt; ++i) {
      cin >> begin >> dayX >> days;
      exams.push_back(exam(i + 1, begin, dayX, days));
      session[dayX] = examCnt + 1;
   }

   sort(exams.begin(), exams.end());

   for (int i = 1; i <= sesCnt; ++i) {
      if (session[i] == 0) {
         for (exam& e : exams) {
            if (e.days == 0) {
               continue;
            }
            if (e.days && e.dayX < i) {
               SESSION_FAILED();
            }
            if (e.begin <= i) {
               --e.days;
               session[i] = e.num;
               break;
            }
         }
      }
   }

   for (const exam& e : exams) {
      if (e.days != 0) {
         SESSION_FAILED();
      }
   }

   for (int i = 1; i < session.size(); ++i) {
      cout << session[i] << ' ';
   }



   return 0;
}