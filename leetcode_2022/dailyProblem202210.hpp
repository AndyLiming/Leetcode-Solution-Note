#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"
class daily202210 {
public:
  // 2022.10.01 - No 1694
  string reformatNumber(string number) {
    string only_num = "";
    for (auto& c : number) {
      if (c >= '0' && c <= '9') only_num.push_back(c);
    }
    vector<string> vs;
    int i = 0, n = only_num.size();
    while (i < n - 4) {
      vs.push_back(only_num.substr(i, 3));
      i += 3;
    }
    if (i == (n - 2) || i == (n - 3)) vs.push_back(only_num.substr(i));
    else {
      vs.push_back(only_num.substr(i, 2));
      i += 2;
      vs.push_back(only_num.substr(i, 2));
    }
    string ans = vs[0];
    for (int j = 1; j < vs.size(); ++j) {
      ans.push_back('-');
      ans += vs[j];
    }
    return ans;
  }
  // 2022.10.02 - No 777
  bool canTransform(string start, string end) {
    int n = start.length();
    int i = 0, j = 0;
    while (i < n && j < n) {
      while (i < n && start[i] == 'X') {
        i++;
      }
      while (j < n && end[j] == 'X') {
        j++;
      }
      if (i < n && j < n) {
        if (start[i] != end[j]) {
          return false;
        }
        char c = start[i];
        if ((c == 'L' && i < j) || (c == 'R' && i > j)) {
          return false;
        }
        i++;
        j++;
      }
    }
    while (i < n) {
      if (start[i] != 'X') {
        return false;
      }
      i++;
    }
    while (j < n) {
      if (end[j] != 'X') {
        return false;
      }
      j++;
    }
    return true;
  }
  //2022.10.03 - No 1784
  bool checkOnesSegment(string s) {
    //int cnt = 0,i=0,n=s.size();
    //while (i < n) {
    //  while (i < n && s[i] == '1')++i;
    //  ++cnt;
    //  while (i < n && s[i] == '0')++i;
    //}
    //return cnt <= 1;
    return s.find("01") == string::npos;
  }
  // 2022.10.04 - No 921
  int minAddToMakeValid(string s) {
    int ans = 0, cnt = 0;
    for (auto c : s) {
      if (c == '(') { ++cnt; }
      else {
        if (cnt > 0)--cnt;
        else ++ans;
      }
    }
    ans += cnt;
    return ans;
  }
  // 2022.10.05 - No 811
  vector<string> subdomainVisits(vector<string>& cpdomains) {
    unordered_map<string, int>tab;
    for (auto& dom : cpdomains) {
      int space = dom.find(' ');
      int num = stoi(dom.substr(0, space));
      string d = dom.substr(space + 1);
      int i = 0,m=d.size();
      tab[d] += num;
      while (i < m) {
        while (i < m && d[i] != '.')++i;
        if (i < m) {
          tab[d.substr(i + 1)] += num;
          ++i;
        }
      }
    }
    vector<string>ans;
    for (auto [dom, num] : tab) {
      ans.push_back(to_string(num) + " " + dom);
    }
    return ans;
  }
  // 2022.10.06 - No 927
  vector<int> threeEqualParts(vector<int>& arr) {
    int sum = 0,n=arr.size();
    for (int i = 0; i < n; ++i) {
      sum += arr[i];
    }
    if (sum % 3 != 0) return { -1,-1 };
    if (sum == 0) return{ 0,2 };
    int partial = sum / 3;
    int first = 0, second = 0, third = 0, cur = 0;
    for (int i = 0; i < arr.size(); i++) {
      if (arr[i] == 1) {
        if (cur == 0) {
          first = i;
        }
        else if (cur == partial) {
          second = i;
        }
        else if (cur == 2 * partial) {
          third = i;
        }
        cur++;
      }
    }
    int len = (int)arr.size() - third;
    if (first + len <= second && second + len <= third) {
      int i = 0;
      while (third + i < arr.size()) {
        if (arr[first + i] != arr[second + i] || arr[first + i] != arr[third + i]) {
          return { -1, -1 };
        }
        i++;
      }
      return { first + len - 1, second + len };
    }
    return { -1, -1 };
  }
  // 2022.10.07 - No 1800
  int maxAscendingSum(vector<int>& nums) {
    int n = nums.size(),ans=0,tmp=0;
    for (int i = 0; i < n; ++i) {
      if (i == 0) tmp = nums[i];
      else {
        if (nums[i] > nums[i - 1]) {
          tmp += nums[i];
        }
        else {
          tmp = nums[i];
        }
      }
      ans = max(ans, tmp);
    }
    return ans;
  }
  // 2022.10.08 - No 870
  vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
    int i = 0,j = 0,n = nums1.size();
    vector<int>ans(n,-1),flag(n,0);
    vector<int>other;
    vector<pair<int, int>> np1,np2;
    for (int k = 0; k < n; ++k) {
      np1.push_back({ nums1[k],k });
      np2.push_back({ nums2[k],k });
    }
    sort(np1.begin(), np1.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {return p1.first < p2.first; });
    sort(np2.begin(), np2.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {return p1.first < p2.first; });
    while (i < n && j < n) {
      auto& [n1, p1] = np1[i];
      auto& [n2, p2] = np2[j];
      if (n1>n2) {
        ++i;
        ++j;
        ans[p2] = n1;
        flag[p2] = 1;
      }
      else {
        other.push_back(n1);
        ++i;
      }
    }
    
    for (int k = 0; k < n; ++k) {
      if (ans[k] == -1) {
        ans[k] = other.back();
        other.pop_back();
      }
    }
    return ans;
  }
  // 2022.10.09 - No 856
  int scoreOfParentheses(string s) {
    stack<int>st;
    st.push(0);
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '(') st.push(0);
      else {
        int v = st.top();
        st.pop();
        int tmp = (v == 0) ? 1 : 2 * v;
        st.top() += tmp;
      }
    }
    return st.top();
  }
  int scoreOfParentheses_2(string s) {
    int ans = 0, deep = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '(')++deep;
      else {
        if (s[i - 1] == '(') ans += (1 << deep);
        --deep;
      }
    }
    return ans;
  }
  // 2022.10.10 - No 801
  int minSwap(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int a = 0, b = 1;
    for (int i = 1; i < n; ++i) {
      int at = a, bt = b;
      a = b = n;
      if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]) {
        a = min(a, at);
        b = min(b, bt+1);
      }
      if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
        a = min(a, bt);
        b = min(b, at + 1);
      }
    }
    return min(a, b);
  }
  // 2022.10.11 - No 801
  bool areAlmostEqual(string s1, string s2) {
    if (s1.size() != s2.size()) return false;
    int n = s1.size();
    vector<int>c1, c2;
    int diff = 0;
    for (int i = 0; i < n; ++i) {
      if (s1[i] != s2[i]) {
        ++diff;
        c1.push_back(s1[i]);
        c2.push_back(s2[i]);
      }
      if (diff > 2) return false;
    }
    if (diff == 0 || (diff == 2 && c1[0] == c2[1] && c1[1] == c2[0])) return true;
    return false;
  }
  // 2022.10.12 - No 817
  int numComponents(ListNode* head, vector<int>& nums) {
    unordered_set<int> numsSet;
    for (int num : nums) {
      numsSet.emplace(num);
    }
    bool inSet = false;
    int res = 0;
    while (head != nullptr) {
      if (numsSet.count(head->val)) {
        if (!inSet) {
          inSet = true;
          res++;
        }
      }
      else {
        inSet = false;
      }
      head = head->next;
    }
    return res;
  }
  //2022.10.13 - No 769
  int maxChunksToSorted(vector<int>& arr) {
    int m = 0, res = 0;
    for (int i = 0; i < arr.size(); i++) {
      m = max(m, arr[i]);
      if (m == i) {
        res++;
      }
    }
    return res;
  }
  //2022.10.14 - No 940
  int distinctSubseqII(string s) {
    int n = s.size();
    int MOD = 1e9 + 7;
    vector<int>dp(26, -1);
    for (int i = 0; i < n; ++i) {
      long long total = 1;
      for (int j = 0; j < 26; ++j) {
        if (dp[j] != -1) {
          total = (total + dp[j]) % MOD;
        }
      }
      dp[s[i] - 'a'] = total;
    }
    long long ans = 0;
    for (int j = 0; j < 26; ++j) {
      if (dp[j] != -1) {
        ans = (ans + dp[j]) % MOD;
      }
    }
    return ans;
  }
  //2022.10.15 - No 1441
  vector<string> buildArray(vector<int>& target, int n) {
    vector<string>ans;
    int cur = 1,id=0,len=target.size();
    while (id < len) {
      ans.push_back("Push");
      if (target[id] == cur) {
        ++id;
        ++cur;
      }
      else {
        ans.push_back("Pop");
        ++cur;
      }
    }
    return ans;
  }
  //2022.10.16 - No 886
  bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    UnionFind uf(n + 1);
    vector<vector<int>>g(n + 1, vector<int>());
    for (auto& p : dislikes) {
      g[p[0]].push_back(p[1]);
      g[p[1]].push_back(p[0]);
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < g[i].size(); ++j) {
        uf.connect(g[i][0], g[i][j]);
        if (uf.isconnected(i,g[i][j])) return false;
      }
    }
    return true;
  }
  //2022.10.17 - No 904
  int totalFruit(vector<int>& fruits) {
    int ans = 0,n=fruits.size();
    unordered_map<int, int>tab;
    int l = 0, r = 0;
    while (l < n && r < n) {
      tab[fruits[r]]++;
      while (tab.size() > 2) {
        auto it = tab.find(fruits[l]);
        --it->second;
        if (it->second == 0) {
          tab.erase(it);
        }
        ++l;
        }
      ans = max(ans, r - l + 1);
      ++r;
      }
    return ans;
  }
  //2022.10.18 - No 902
  int atMostNGivenDigitSet(vector<string>& digits, int n) {
    string sn = to_string(n);
    int len = sn.size(),num_d=digits.size();
    vector<vector<int>>dp(len + 1, vector<int>(2));
    dp[0][1] = 1;
    for (int i = 1; i <= len; ++i) {
      for (int j = 0; j < num_d; ++j) {
        if (digits[j][0] == sn[i - 1]) {
          dp[i][1] = dp[i - 1][1];
        }
        else if (digits[j][0] < sn[i - 1]) {
          dp[i][0] += dp[i - 1][1];
        }
        else {
          break;
        }
      }
      if (i > 1) {
        dp[i][0] += (num_d * dp[i - 1][0] + num_d);
      }
    }
    return dp[len][0] + dp[len][1];
  }
  //2022.10.19
  int countStudents(vector<int>& students, vector<int>& sandwiches) {
    int n = students.size();
    int n1 = 0,n0=0;
    for (int i = 0; i < n; ++i) n1 += students[i];
    n0 = n - n1;
    for (int i = 0; i < sandwiches.size(); ++i) {
      if (sandwiches[i] == 0 && n0 > 0) {
        --n0;
      }
      else if (sandwiches[i] == 1 && n1 > 0) {
        --n1;
      }
      else break;
    }
    return n0 + n1;
  }
  //2022.10.20
  int kthGrammar(int n, int k) {
    k = k - 1;
    int ans = 0;
    while (k) {
      k &= k - 1;
      ans ^= 1;
    }
    return ans;
  }
  //2022.10.21 - No 901
  class StockSpanner {
  public:
    StockSpanner() {
      this->stk.push({ -1,INT_MAX });
      this->idx = -1;
    }

    int next(int price) {
      idx++;
      while (price >= stk.top().second) {
        stk.pop();
      }
      int ret = idx - stk.top().first;
      stk.push({ idx, price });
      return ret;
    }
    stack<pair<int, int>> stk;
    int idx;
  };
  //2022.10.22 - No 1235
  int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
    vector<vector<int>>jobs;
    int n = startTime.size();
    for (int i = 0; i < n; ++i) {
      jobs.push_back({ startTime[i],endTime[i],profit[i] });
    }
    sort(jobs.begin(), jobs.end(), [](const vector<int> & v1, const vector<int> & v2) {return (v1[1] < v2[1]); });
    vector<int>dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      int stt = jobs[i - 1][0];
      int left = 0, right = i - 1;
      while (left < right) {
        int mid = (left + right+1) / 2;
        if (jobs[mid][1] > stt) right = mid - 1;
        else {
          left = mid;
        }
      }
      if (left == 0 && jobs[left][1] > stt) left = -1;
      dp[i] = max(dp[i - 1], dp[left+1] + jobs[i - 1][2]);
    }
    return dp[n];
  }
  //2022.10.23 - No 1768
  string mergeAlternately(string word1, string word2) {
    int n1 = word1.size(), n2 = word2.size();
    int i1 = 0, i2 = 0;
    string ans;
    while (i1 < n1 && i2 < n2) {
      ans.push_back(word1[i1]);
      ans.push_back(word2[i2]);
      ++i1;
      ++i2;
    }
    while (i1 < n1) {
      ans.push_back(word1[i1++]);
    }
    while (i2 < n2) {
      ans.push_back(word2[i2++]);
    }
    return ans;
  }
  //2022.10.24 - No 915
  int partitionDisjoint(vector<int>& nums) {
    int n = nums.size(), ans = 0;
    vector<int>minR(n, 0);
    minR[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      minR[i] = min(minR[i + 1], nums[i]);
    }
    int maxL = 0;
    for (int i = 0; i < n - 1; ++i) {
      maxL = max(maxL, nums[i]);
      if (maxL <= minR[i + 1]) return i + 1;
    }
    return 0;
  }
  int partitionDisjoint_2(vector<int>& nums) {
    int n = nums.size();
    int leftMax = nums[0], leftPos = 0, curMax = nums[0];
    for (int i = 1; i < n - 1; i++) {
      curMax = max(curMax, nums[i]);
      if (nums[i] < leftMax) {
        leftMax = curMax;
        leftPos = i;
      }
    }
    return leftPos + 1;
  }
  //2022.10.25 - No 934
  int shortestBridge(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> dirs = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
    vector<pair<int, int>> island;
    queue<pair<int, int>> qu;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          qu.emplace(i, j);
          grid[i][j] = -1;
          while (!qu.empty()) {
            auto [x, y] = qu.front();
            qu.pop();
            island.emplace_back(x, y);
            for (int k = 0; k < 4; k++) {
              int nx = x + dirs[k][0];
              int ny = y + dirs[k][1];
              if (nx >= 0 && ny >= 0 && nx < n && ny < n && grid[nx][ny] == 1) {
                qu.emplace(nx, ny);
                grid[nx][ny] = -1;
              }
            }
          }
          for (auto&& [x, y] : island) {
            qu.emplace(x, y);
          }
          int step = 0;
          while (!qu.empty()) {
            int sz = qu.size();
            for (int i = 0; i < sz; i++) {
              auto [x, y] = qu.front();
              qu.pop();
              for (int k = 0; k < 4; k++) {
                int nx = x + dirs[k][0];
                int ny = y + dirs[k][1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                  if (grid[nx][ny] == 0) {
                    qu.emplace(nx, ny);
                    grid[nx][ny] = -1;
                  }
                  else if (grid[nx][ny] == 1) {
                    return step;
                  }
                }
              }
            }
            step++;
          }
        }
      }
    }
    return 0;
  }
  //2022.10.26 - No 862
  int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size(),ans=n+1;
    vector<long long>presum(n + 1);
    for (int i = 0; i < n; ++i) {
      presum[i + 1] = nums[i] + presum[i];
    }
    deque<int> qu;
    for (int i = 0; i <= n; i++) {
      long curSum = presum[i];
      while (!qu.empty() && curSum - presum[qu.front()] >= k) {
        ans = min(ans, i - qu.front());
        qu.pop_front();
      }
      while (!qu.empty() && presum[qu.back()] >= curSum) {
        qu.pop_back();
      }
      qu.push_back(i);
    }
    return ans < n + 1 ? ans : -1;
  }
  //2022.10.27 - No 1822
  int arraySign(vector<int>& nums) {
    int n_neg = 0;
    for (auto& i : nums) {
      if (i == 0) return 0;
      else if (i < 0)++n_neg;
    }
    if (n_neg % 2 == 1) return -1;
    else return 1;
  }
  //2022.10.28 - No 907
  int sumSubarrayMins(vector<int>& arr) {
    int n = arr.size();
    stack<int>st;
    vector<int>left(n, -1),right(n,n);
    for (int i = 0; i < n; ++i) {
      while (!st.empty() && (arr[st.top()] >= arr[i])) st.pop();
      if (!st.empty()) left[i] = i-st.top();
      else left[i] = i+1;
      st.push(i);
    }
    st = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
      while(!st.empty() && (arr[st.top()] > arr[i])) st.pop();
      if (!st.empty()) right[i] = st.top()-i;
      else right[i] = n-i;
      st.push(i);
    }
    long long ans = 0, M=1e9+7;
    for (int i = 0; i < n; ++i) {
      ans = (ans+(long long)arr[i]*left[i] * right[i]) % M;
    }
    return ans;
  }
  //2022.10.29 - No 1773
  int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
    unordered_map<string, int>key{ {"type",0},{"color",1},{"name",2} };
    int id = key[ruleKey];
    int ans = 0;
    for (auto& it : items) {
      if (it[id] == ruleValue)++ans;
    }
    return ans;
  }
  //2022.10.30 - No 784
  void dfslcp784(string s, int id, string cur, vector<string>& ans) {
    if (id == s.size()) {
      ans.push_back(cur);
      return;
    }
    if (isalpha(s[id])) {
      char l = s[id],u=s[id];
      if (islower(s[id])) {
        l = s[id];
        u = toupper(s[id]);
      }
      else {
        u = s[id];
        l = tolower(s[id]);
      }
      cur.push_back(l);
      dfslcp784(s, id + 1, cur, ans);
      cur.pop_back();
      cur.push_back(u);
      dfslcp784(s, id + 1, cur, ans);
      cur.pop_back();
    }
    else {
      cur.push_back(s[id]);
      dfslcp784(s, id + 1, cur, ans);
      cur.pop_back();
    }
  }
  vector<string> letterCasePermutation(string s) {
    int id = 0;
    string cur = "";
    vector<string>ans;
    dfslcp784(s, id, cur, ans);
    return ans;
  }
  //2022.10.31 - No 481
  int magicalString(int n) {
    vector<int>s{ 1,2,2 };
    if (n <= 3) return 1;
    int cur = 1, j = 2,len=3;
    while (len < n) {
      int num = s[j];
      for (int i = 0; i < num; ++i) s.push_back(cur);
      cur = cur + 1;
      if (cur > 2)cur -= 2;
      ++j;
      len += num;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == 1) ++ans;
    }
    return ans;
  }
};