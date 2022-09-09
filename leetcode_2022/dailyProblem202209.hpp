#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

class daily202209 {
public:
// 2022.09.03 - No 646
  int findLongestChain(vector<vector<int>>& pairs) {
    if (pairs.empty()) return 0;
    sort(pairs.begin(), pairs.end(), [](const vector<int>& p1, const vector<int>& p2) {return (p1[0] < p2[0]) || (p1[0] == p2[0] && p1[1] < p2[1]); });
    // for(auto p:pairs){
    //     cout<<p[0]<<","<<p[1]<<endl;
    // }
    int ans = 1, n = pairs.size();
    vector<int>dp(n, 1);
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (pairs[j][1] < pairs[i][0]) dp[i] = max(dp[i], dp[j] + 1);
      }
      ans = max(ans, dp[i]);
    }
    return ans;
  }
  int findLongestChain_greedy(vector<vector<int>>& pairs) {
    if (pairs.empty()) return 0;
    sort(pairs.begin(), pairs.end(), [](const vector<int>& p1, const vector<int>& p2) {return  p1[1] < p2[1]; });
    int cur = INT_MIN, ans = 0;
    for (auto& p : pairs) {
      if (cur < p[0]) {
        cur = p[1]; ++ans;
      }
    }
    return ans;
  }
  //2022.09.04 - No 1582
  int numSpecial(vector<vector<int>>& mat) {
    if (mat.empty()) return 0;
    int n = mat.size(), m = mat[0].size();
    vector<int>rowsum(n, 0);
    vector<int>colsum(m, 0);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        rowsum[i] += mat[i][j];
        colsum[j] += mat[i][j];
      }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (rowsum[i] == 1 && colsum[j] == 1 && mat[i][j] == 1) ++ans;
      }
    }
    return ans;
  }

  //2022.09.06 - No 828
  int uniqueLetterString(string s) {
    vector<vector<int>>ids(26, vector<int>());
    for (int i = 0; i < s.size(); ++i) {
      ids[(s[i] - 'A')].push_back(i);
    }
    int ans = 0;
    int n = s.size();
    for (int i = 0; i < 26; ++i) {
      if (!ids[i].empty()) {
        int k = ids[i].size();
        for (int j = 0; j < k; ++j) {
          int left = -1,right=n;
          if (j > 0) left = ids[i][j - 1];
          if (j < k - 1)right = ids[i][j + 1];
          ans += (ids[i][j]-left) * (right-ids[i][j]);
        }
      }
    }
    return ans;
  }

  //2022.09.07 - No 1592
  string reorderSpaces(string text) {
    int allnum = text.size(), textNum = 0, spaceNum = 0;
    stringstream ss(text);
    vector<string> vs;
    string tmp;
    while (ss >> tmp) {
      vs.push_back(tmp);
      textNum += tmp.size();
    }
    spaceNum = allnum - textNum;
    //cout<<allnum<<","<<textNum<<","<<spaceNum<<endl;
    string ans = "";
    if (vs.size() == 1) {
      ans += vs[0];
      string endspace(spaceNum, ' ');
      ans += endspace;
    }
    else {
      int each = spaceNum / (vs.size() - 1), last = spaceNum - each * (vs.size() - 1);
      //cout<<vs.size()<<","<<each<<","<<last<<endl;
      string split(each, ' '), endspace(last, ' ');
      //cout<<endspace.size()<<endl;
      for (int i = 0; i < vs.size(); ++i) {
        ans += vs[i];
        if (i < vs.size() - 1) ans += split;
      }
      ans += endspace;
    }
    return ans;
  }

  //2022.09.08 - No 667
  vector<int> constructArray(int n, int k) {
    vector<int>ans;
    if (n == 1) return{ 1 };
    int m = k + 1;
    int i = 1, j = m;
    while (i <= j) {
      if (i < j) {
        ans.push_back(i);
        ans.push_back(j);
      }
      else {
        ans.push_back(i);
      }
      ++i;
      --j;
    }
    for (int i = m + 1; i <= n; ++i) ans.push_back(i);
    return ans;
  }
  //2022.09.09 - No 1598
  int minOperations(vector<string>& logs) {
    int ans = 0;
    for (auto& l : logs) {
      if (l == "../") {
        if (ans > 0)--ans;
      }
      else if (l != "./") {
        ++ans;
      }
    }
    return ans;
  }
};