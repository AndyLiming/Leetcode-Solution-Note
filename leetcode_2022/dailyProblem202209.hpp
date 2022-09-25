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
  //2022.09.10 - No 669
  TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (!root) return nullptr;
    if (root->val < low) return trimBST(root->right, low, high);
    else if (root->val > high) return trimBST(root->left, low, high);
    else {
      root->left = trimBST(root->left, low, high);
      root->right = trimBST(root->right, low, high);
    }
    return root;
  }
  //2022.09.11 - No 857
  double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
    int n = quality.size();
    vector<int> h(n, 0);
    iota(h.begin(), h.end(), 0);
    sort(h.begin(), h.end(), [&](int& a, int& b) {
      return quality[a] * wage[b] > quality[b] * wage[a];
    });
    double res = 1e9;
    double totalq = 0.0;
    priority_queue<int, vector<int>, less<int>> q;
    for (int i = 0; i < k - 1; i++) {
      totalq += quality[h[i]];
      q.push(quality[h[i]]);
    }
    for (int i = k - 1; i < n; i++) {
      int idx = h[i];
      totalq += quality[idx];
      q.push(quality[idx]);
      double totalc = ((double)wage[idx] / quality[idx]) * totalq;
      res = min(res, totalc);
      totalq -= q.top();
      q.pop();
    }
    return res;
  }
  //2022.09.12 - No 1608
  int specialArray(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    for (int x = 0; x <= nums[n - 1]; ++x) {
      auto pos = lower_bound(nums.begin(), nums.end(), x);
      int count = (nums.end() - pos);
      if (count == x) return x;
    }
    return -1;
  }
  //2022.09.13 - No 670
  int maximumSwap(int num) {
    vector<int>dig;
    int tmp = num;
    while (tmp) {
      dig.push_back(tmp % 10);
      tmp /= 10;
    }
    reverse(dig.begin(), dig.end());
    for (int i = 0; i < dig.size(); ++i) {
      bool s = false;
      int md = -1,id=-1;
      for (int j = i + 1; j < dig.size(); ++j) {
        if (dig[j] > dig[i] && dig[j] >= md) {
          md = dig[j];
          id = j;
        }
      }
      if (md != -1) {
        int tmp = dig[i];
        dig[i] = dig[id];
        dig[id] = tmp;
        break;
      }
    }
    int ans = 0;
    for (int i = 0; i < dig.size(); ++i) {
      ans *= 10;
      ans += dig[i];
    }
    return ans;
  }
  //2022.09.14 - No 1619
  double trimMean(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    int n = arr.size();
    int k = n / 20;
    double total = 0.0;
    for (int i = k; i < n - k; ++i) {
      total += (double)arr[i];
    }
    return total / (double)(n - 2 * k);
  }
  //2022.09.15 - No 672
  int flipLights(int n, int presses) {
    unordered_set<int> seen;
    for (int i = 0; i < 1 << 4; i++) {
      vector<int> pressArr(4);
      for (int j = 0; j < 4; j++) {
        pressArr[j] = (i >> j) & 1;
      }
      int sum = accumulate(pressArr.begin(), pressArr.end(), 0);
      if (sum % 2 == presses % 2 && sum <= presses) {
        int status = pressArr[0] ^ pressArr[1] ^ pressArr[3];
        if (n >= 2) {
          status |= (pressArr[0] ^ pressArr[1]) << 1;
        }
        if (n >= 3) {
          status |= (pressArr[0] ^ pressArr[2]) << 2;
        }
        if (n >= 4) {
          status |= (pressArr[0] ^ pressArr[1] ^ pressArr[3]) << 3;
        }
        seen.emplace(status);
      }
    }
    return seen.size();
  }
  //2022.09.16 - No 850
  //int rectangleArea(vector<vector<int>>& rectangles) {

  //}
  //2022.09.17 - No 1624
  int maxLengthBetweenEqualCharacters(string s) {
    vector<int>first(26, -1),last(26,-1);
    int ans = -1;
    for (int i = 0; i < s.size(); ++i) {
      if (first[s[i] - 'a'] == -1) first[s[i] - 'a'] = i;
      last[s[i] - 'a'] = i;
    }
    
    for (int i = 0; i < 26; ++i) {
      if (first[i] != -1 && last[i] != -1) {
        ans = max(ans, (last[i] - first[i] - 1));
      }
    }
    return ans;
  }
  //2022.09.18 - No
  //2022.09.19 - No 1636
  vector<int> frequencySort(vector<int>& nums) {
    unordered_map<int, int> tab;
    for (auto& i : nums) {
      if (tab.count(i)) tab[i]++;
      else tab[i] = 1;
    }
    vector<pair<int, int>>vp;
    for (auto it : tab) {
      vp.push_back({ it.second,it.first });
    }
    sort(vp.begin(), vp.end(), [](pair<int, int>& p1, pair<int, int>& p2) {return (p1.first < p2.first) || (p1.first == p2.first && p1.second > p2.second); });
    vector<int>ans;
    for (auto& p : vp) {
      for (int i = 0; i < p.first; ++i) {
        ans.push_back(p.second);
      }
    }
    return ans;
  }
  //2022.09.20 - No 698
  bool dfs_698(int state, int cur,int n,vector<bool>&dp,vector<int>&nums,int target) {
    if (state == 0) return true;
    if (!dp[state]) return dp[state];
    dp[state] = false;
    for (int i = 0; i < n; ++i) {
      if (nums[i] + cur > target) break;
      if (state & (1 << i)) { //avail
        if(dfs_698(state^(1<<i),(cur+nums[i])%target,n,dp,nums,target)) return true;
      }
    }
    return false;
  }
  bool canPartitionKSubsets(vector<int>& nums, int k) {
    int all = accumulate(nums.begin(), nums.end(), 0);
    if (all % k != 0) return false;
    int avg = all / k;
    sort(nums.begin(), nums.end());
    if (nums.back() > avg) return false;
    int n = nums.size();
    int start = (1<<n)-1;
    vector<bool>dp(1 << n, true);
    return dfs_698(start, 0, n, dp, nums, avg);
  }
  //2022.09.21 - No xxx
  //2022.09.22 - No 1640
  bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
    unordered_map<int,int> tab;
    int n = arr.size(), m = pieces.size();
    for (int i = 0; i < m; ++i) {
      tab[pieces[i][0]] = i;
    }
    int id = 0;
    while (id < n) {
      auto it = tab.find(arr[id]);
      if (it == tab.end()) return false;
      for (int x : pieces[it->second]) {
        if (x != arr[id++]) return false;
      }
    }
    return true;
  }
  //2022.9.24 - No 1652
  vector<int> decrypt(vector<int>& code, int k) {
    int n = code.size();
    vector<int>ans;
    for (int i = 0; i < n; ++i) {
      if (k == 0) ans.push_back(0);
      else if (k < 0) {
        int tmp = 0;
        for (int j = 1; j <= k; ++j) {
          tmp += code[(i - j + n) % n];
        }
        ans.push_back(tmp);
      }

      else {
        int tmp = 0;
        for (int j = 1; j <= -k; ++j) {
          tmp += code[(i + j) % n];
        }
        ans.push_back(tmp);
      }
    }
    return ans;
  }
  //2022.9.25 - No 788
  // 学一下数位DP
  int rotatedDigits(int n) {
    int cnt = 0;
    for (int x = 1; x <= n; ++x) {
      vector<int>tmp(10, 0);
      int val = x;
      while (val) {
        tmp[val % 10]++;
        val /= 10;
      }
      int invalid = tmp[3] + tmp[4] + tmp[7];
      int must = tmp[2] + tmp[5] + tmp[6] + tmp[9];
      if (invalid == 0 && must > 0) ++cnt;
    }
    return cnt;
  }
};