#include <cstdio>
#include <map>
#include <vector>
#include <queue>
 
using namespace std;
 
int n, k, l;
int cnt[4];
 
struct state {
    int c[4];
    bool e;
    state() {
        for (int i = 0; i < 4; ++i)
            c[i] = 0;
    }
};
 
bool operator < (const state &a, const state &b) {
    for (int i = 0; i < 4; ++i)
        if (a.c[i] != b.c[i])
            return a.c[i] < b.c[i];
    return a.e < b.e;
}
 
map <state, long long> dp;
 
int toint(char *s) {
    return (s[0] - 'A') * 2 + (s[1] - 'A');
}
 
int main() {
    scanf("%d %d", &n, &k);
    char buf[3];
    scanf("%s", buf);
    l = toint(buf);
    for (int i = 0; i < n; ++i) {
        scanf("%s", buf);
        cnt[toint(buf)]++;
    }
   
    state start;
    queue <state> q;
    start.e = l & 1;
    dp[start] = 1;
    q.push(start);
    long long res = 0;
    while (!q.empty()) {
        state s = q.front(); q.pop();
        int avg = 0;
        for (int i = 0; i < 4; ++i)
            avg += s.c[i];
        if (avg == k) {
            if (s.e == l/2)
                res += dp[s];
            continue;
        }
       
        for (int i = 0; i < 2; ++i) {
            int v = s.e * 2 + i;
            if (s.c[v] < cnt[v]) {
                state ns = s; ns.c[v]++; ns.e = i;
                if (dp.find(ns) == dp.end()) {
                    dp[ns] = dp[s];
                    q.push(ns);
                } else
                    dp[ns] += dp[s];
            }
        }
    }
   
    if (res)
        printf("YES\n%lld\n", res);
    else
        printf("NO\n");
    return 0;
}