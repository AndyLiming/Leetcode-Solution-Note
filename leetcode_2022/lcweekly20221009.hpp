#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"
class weekly20221009 {
public:
  //No 1
  int hardestWorker(int n, vector<vector<int>>& logs) {
    int len = 0, id = -1,start=0;
    for (auto l : logs) {
      int time = l[1] - start;
      if (time > len) {
        len = time;
        id = l[0];
      }
      else if (time == len) {
        id = min(id, l[0]);
      }
      start = l[1];
    }
    return id;
  }
  //No 2
  vector<int> findArray(vector<int>& pref) {
    int n = pref.size();
    vector<int> ans(n, 0);
    ans[0] = pref[0];
    for (int i = 1; i < n; ++i) {
      ans[i] = pref[i - 1] ^ pref[i];
    }
    return ans;
  }
  //No 3
  string robotWithString(string s) {
    int n = s.size();
    int n = s.size();
    vector<char> f(n + 1);
    f[n] = 'z' + 1;
    for (int i = n - 1; i >= 0; i--) f[i] = min(f[i + 1], s[i]);

    string ans;
    stack<char> stk;
    for (int i = 0; i < n; i++) {
      stk.push(s[i]);
      while (!stk.empty() && stk.top() <= f[i + 1]) ans.push_back(stk.top()), stk.pop();
    }
    return ans;
  }
  //No 4
  int numberOfPaths(vector<vector<int>>& grid, int K) {
    int n = grid.size(); int m = grid[0].size();
    const int MOD = 1e9+7;
    vector<vector<vector<long long>>> f(n, vector<vector<long long>>(m, vector<long long>(K,0)));    // 初值
    f[0][0][grid[0][0] % K] = 1;

    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) for (int k = 0; k < K; k++) {
      // 从上方走过来
      if (i > 0) f[i][j][k] = (f[i][j][k] + f[i - 1][j][(k - grid[i][j] % K + K) % K]) % MOD;
      // 从左方走过来
      if (j > 0) f[i][j][k] = (f[i][j][k] + f[i][j - 1][(k - grid[i][j] % K + K) % K]) % MOD;
    }
    return f[n - 1][m - 1][0];
  }
};