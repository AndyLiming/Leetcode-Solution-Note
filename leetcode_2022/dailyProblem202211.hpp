#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

class daily202211 {
public:
  // 2022.11.01 - No 1662
  bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
    string s1 = "", s2 = "";
    for (auto& c : word1)s1 += c;
    for (auto& c : word2)s2 += c;
    return s1 == s2;
  }
  // 2022.11.02 - No 1620
  vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
    int minx = 0, maxx = 0, miny = 0, maxy = 0;
    for (auto t : towers) {
      maxx = max(maxx, t[0]);
      maxy = max(maxy, t[1]);
    }
    int ansx = 0, ansy = 0, p = 0;
    for (int i = minx; i <= maxx; ++i) {
      for (int j = miny; j <= maxy; ++j) {
        int tmp = 0;
        for (auto t : towers) {
          double dis = sqrt((double)(t[0] - i) * (double)(t[0] - i) + (double)(t[1] - j) * (double)(t[1] - j));
          if (dis <= (double)radius) {
            tmp += (int)((double)t[2] / (dis + 1));
          }
        }
        if (tmp > p) {
          p = tmp;
          ansx = i;
          ansy = j;
        }
      }
    }
    return { ansx,ansy };
  }
  // 2022.11.03 - No 1668
  int maxRepeating(string sequence, string word) {
    int ns = sequence.size(), nw = word.size();
    int maxk = ns / nw;
    int i = 1;
    string tmp = word;
    while (i <= maxk) {
      if (sequence.find(tmp) == sequence.npos) {
        return i - 1;
      }
      else {
        ++i;
        tmp += word;
      }
    }
    return maxk;
  }
  // 2022.11.09 - No 764
  int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
    vector<vector<int>>grid(n, vector<int>(n, 1));
    for (auto m : mines) {
      grid[m[0]][m[1]] = 0;
    }
    int ans = 0;
    vector < vector<int>>dir{ {-1,0},{1,0},{0,-1},{0,1} };
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == 1) {
          int tmp = n;
          for (int d = 0; d < 4; ++d) {
            int dx = i+dir[d][0], dy = j+dir[d][1];
            int curdir = 0;
            while (dx < n && dx >= 0 && dy < n && dy >= 0 && grid[dx][dy] == 1) {
              ++curdir;
              dx += dir[d][0];
              dy += dir[d][1];
            }
            tmp = min(tmp, curdir);
          }
          tmp += 1;
          ans = max(tmp, ans);
        }        
      }
    }
    return ans;
  }
  int orderOfLargestPlusSign_dp(int n, vector<vector<int>>& mines) {
    vector<vector<int>> dp(n, vector<int>(n, n));
    unordered_set<int> banned;
    for (auto&& vec : mines) {
      banned.emplace(vec[0] * n + vec[1]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int count = 0;
      /* left */
      for (int j = 0; j < n; j++) {
        if (banned.count(i * n + j)) {
          count = 0;
        }
        else {
          count++;
        }
        dp[i][j] = min(dp[i][j], count);
      }
      count = 0;
      /* right */
      for (int j = n - 1; j >= 0; j--) {
        if (banned.count(i * n + j)) {
          count = 0;
        }
        else {
          count++;
        }
        dp[i][j] = min(dp[i][j], count);
      }
    }
    for (int i = 0; i < n; i++) {
      int count = 0;
      /* up */
      for (int j = 0; j < n; j++) {
        if (banned.count(j * n + i)) {
          count = 0;
        }
        else {
          count++;
        }
        dp[j][i] = min(dp[j][i], count);
      }
      count = 0;
      /* down */
      for (int j = n - 1; j >= 0; j--) {
        if (banned.count(j * n + i)) {
          count = 0;
        }
        else {
          count++;
        }
        dp[j][i] = min(dp[j][i], count);
        ans = max(ans, dp[j][i]);
      }
    }
    return ans;
  }
  // 2022.11.11 - No 1704
  bool halvesAreAlike(string s) {
    int n = s.size(), count = 0;
    unordered_set<char>y{ 'a','e','i','o','u','A','E','I','O','U' };
    for (int i = 0; i < n / 2; ++i) {
      if(y.count(s[i]))++count;
    }
    for (int i = n / 2; i < n; ++i) {
      if (y.count(s[i]))--count;
    }
    return count == 0;
  }
  // 2022.11.12 - No 790
  int numTilings(int n) {
    // 00->0, 01->1, 10->2, 11->3
    //0=ÎÞ£¬1=ÓÐ£»up-down
    vector<vector<long long>>dp(n+1, vector<long long>(4, 0));
    dp[0][3] = 1;
    int M = 1e9 + 7;
    for (int i = 1; i <= n; ++i) {
      dp[i][0] = dp[i - 1][3];
      dp[i][1] = (dp[i - 1][0] + dp[i - 1][2])%M;
      dp[i][2] = (dp[i - 1][0] + dp[i - 1][1])%M;
      dp[i][3] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][3])%M;
    }
    return dp[n][3];
  }
  // 2022.11.13 - No 791
  string customSortString(string order, string s) {
    sort(s.begin(), s.end(), [order](char& c1, char& c2) {return order.find(c1) < order.find(c2); });
    return s;
  }
  // 2022.11.14 - No 805
  bool splitArraySameAverage(vector<int>& nums) {
    int n = nums.size(), m = n / 2;
    if (n == 1) {
      return false;
    }

    int sum = accumulate(nums.begin(), nums.end(), 0);
    for (int& x : nums) {
      x = x * n - sum;
    }

    unordered_set<int> left;
    for (int i = 1; i < (1 << m); i++) {
      int tot = 0;
      for (int j = 0; j < m; j++) {
        if (i & (1 << j)) {
          tot += nums[j];
        }
      }
      if (tot == 0) {
        return true;
      }
      left.emplace(tot);
    }

    int rsum = accumulate(nums.begin() + m, nums.end(), 0);
    for (int i = 1; i < (1 << (n - m)); i++) {
      int tot = 0;
      for (int j = m; j < n; j++) {
        if (i & (1 << (j - m))) {
          tot += nums[j];
        }
      }
      if (tot == 0 || (rsum != tot && left.count(-tot))) {
        return true;
      }
    }
    return false;
  }
  // 2022.11.15 - No 1710
  int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    sort(boxTypes.begin(), boxTypes.end(), [](const vector<int>& v1, const vector<int>& v2) {return v1[1] > v2[1]; });
    int ans = 0;
    for (auto box : boxTypes) {
      int nb = box[0], bu = box[1];
      if (nb < truckSize) {
        ans += nb * bu;
        truckSize -= nb;
      }
      else {
        ans += truckSize * bu;
        break;
      }
    }
    return ans;
  }
};