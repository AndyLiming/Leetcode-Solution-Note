#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

// wangyi no3
int redNum(string s) {
  int n = s.size();
  if (n <= 1) return 0;
  vector<vector<int>>dp(n, vector<int>(3, 0));
  unordered_map<char, int>tab{ {'r',0},{'e',1},{'d',2} };
  for (int i = 0; i < 3; ++i) {
    dp[0][i] = (i - tab[s[0]] + 3) % 3;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < 3; ++j) {
      int tmp = min(dp[i - 1][(j - 1 + 3) % 3], dp[i - 1][(j + 1 + 3) % 3]);
      dp[i][j] = tmp + (j - tab[s[i]] + 3) % 3;
    }
  }
  return min(min(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]);
}