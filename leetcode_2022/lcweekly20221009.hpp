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

class weekly20230813 {
public:
  //No 1
  int maxSum(vector<int>& nums) {
    int max_ans = -1;
    int n = nums.size();
    vector<int>max_digit(n, 0);
    for (int i = 0; i < n; ++i) {
      int tmp = nums[i];
      while (tmp) {
        max_digit[i] = max(max_digit[i], tmp % 10);
        tmp /= 10;
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = i+1; j < n; ++j) {
        if (max_digit[i] == max_digit[j]) {
          max_ans = max(max_ans, nums[i] + nums[j]);
        }
      }
    }
    return max_ans;
  }
  //No 2
  ListNode* reverse(ListNode* head) {
    if (!head) return nullptr;
    ListNode* p = head, * q = head->next;
    p->next = nullptr;
    while (q) {
      ListNode *t= q->next;
      q->next = p;
      p = q;
      q = t;
    }
    return p;
  }
  ListNode* doubleIt(ListNode* head) {
    ListNode* rev = reverse(head);
    int ca = 0;
    ListNode* d_start =new ListNode(-1);
    ListNode* p = d_start,*q=rev;
    while (q) {
      int new_val = q->val * 2+ca;
      if (new_val > 9) ca = 1;
      else ca = 0;
      new_val = new_val % 10;
      p->next = new ListNode(new_val);
      p = p->next;
      q = q->next;
    }
    if (ca == 1) {
      p->next = new ListNode(1);
    }
    return reverse(d_start->next);
  }
  //No 3
  int minAbsoluteDifference(vector<int>& nums, int x) {
    if (x == 0) return 0;
    int n = nums.size();
    multiset<int>ms;
    for (int i = x; i < n; ++i) ms.insert(nums[i]);
    int ans = 1e9;
    for (int i = 0; i < n; ++i) {
      auto it = ms.lower_bound(nums[i]);
      if (it != ms.end()) ans = min(ans, *it - nums[i]);
      if (it != ms.begin()) ans = min(ans, nums[i] - *prev(it));
      if (i + x < n) ms.erase(ms.find(nums[i + x]));
      if (i + 1 - x >= 0) ms.insert(nums[i + 1 - x]);
    }
    return ans;
  }
  //No 4

  //2023.9.10
  //No 1
  int numberOfPoints(vector<vector<int>>& nums) {
    unordered_set<int>np;
    for (auto p : nums) {
      for (int i = p[0]; i <= p[1]; ++i) np.insert(i);
    }
    return np.size();
  }
  //No 2
  bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
    long long row_diff = abs(fx - sx);
    long long col_diff = abs(fy - sy);
    long long step = max(row_diff, col_diff);
    if ((step==0 && t==1) || step > t) return false;
    else return true;
  }
  //No 3
  int minnum(vector<vector<int>>& zero, vector<int>& used_zeros, int zero_num,vector<vector<int>>& many,vector<int>&used_many) {
    if (zero_num == 0) return 0;
    int ans = INT_MAX;
    for (int d0 = 0; d0 < zero.size();++d0) {
      if(!used_zeros[d0]){
        for (int dm = 0; dm < many.size();++dm) {
          if (!used_many[dm]) {
            int tmp = abs(zero[d0][0] - many[dm][0]) + abs(zero[d0][1] - many[dm][1]);
            used_zeros[d0] = 1;
            used_many[dm] = 1;
            tmp += minnum(zero, used_zeros,zero_num -1,many, used_many);
            ans = min(ans, tmp);
            used_zeros[d0] = 0;
            used_many[dm] = 0;
        }
      }
      }
    }
    return ans;
  }
  int minCore(string g, unordered_map<string, int>& M) {
    if (M.count(g)) return M[g];
    if (g == "111111111") {
      M[g] = 0;
      return M[g];
    }
    int ans = INT_MAX;
    for (int i = 0; i < 9; ++i) {
      if (g[i] == '0') {
        g[i] = '1';
        for (int j = 0; j < 9; ++j) {
          if (g[j] - '1' > 0) {
            g[j]--;
            int tmp = abs(i / 3 - j / 3) + abs(i % 3 - j % 3);
            int tmp_n = minCore(g, M);
            M[g] = tmp_n;
            ans = min(ans, tmp+tmp_n);
            g[j]++;
          }
        }
        g[i] = '0';
      }
    }
    return ans;
  }
  int minimumMoves(vector<vector<int>>& grid) {
    /*vector<vector<int>>zero;
    vector<vector<int>>many;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (grid[i][j] == 0) zero.push_back({ i,j });
        if (grid[i][j] > 1) {
         for(int k= grid[i][j];k>=1;--k)
          many.push_back({ i,j });
        }
      }
    }
    if (zero.size() == 0) return 0;
    vector<int>used_many(many.size(), 0);
    return ans;*/
    unordered_map<string, int>M;
    string g;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        g += ('0' + grid[i][j]);
      }
    }
    return minCore(g, M);
    /*vector<vector<int>>zero;
    vector<vector<int>>many;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (grid[i][j] == 0) zero.push_back({ i,j,0 });
        if (grid[i][j] >1) many.push_back({ i,j,grid[i][j] });
      }
    }
    int ans = 0;
    for (int i = 0; i < zero.size(); ++i) {
      int tmp_pos = -1, tmp_val = 9;
      for (int j = 0; j < many.size(); ++j) {
        int t = abs(zero[i][0] - many[j][0]) + abs(zero[i][1] - many[j][1]);

      }
    }*/
  }
  //No 4
  //int numberOfWays(string s, string t, long long k) {
  //  long long M = 1e9 + 7;
  //  

  //}
  // No 1
  int sumIndicesWithKSetBits(vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 0) return k == 0 ? nums[0] : 0;
    vector<int>N1(n);
    N1[0] = 0;
    N1[1] = 1;
    for (int i = 2; i < n; ++i) {
      if (i % 2 == 0) N1[i] = N1[i / 2];
      else N1[i] = N1[i / 2] + 1;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (N1[i] == k) ans += nums[i];
    }
    return ans;
  }
  int countWays(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int ans = 0;
    if (nums[0] > 0)++ans;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] > i && nums[i - 1] < i) ++ans;
    }
    if (nums.back() < nums.size())++ans;
    return ans;
  }
  bool checkAlloys(long long numa,int n, long long budget, vector<int>& comps, vector<int>& stock, vector<int>& cost) {
    long long money = 0;
    for (int i = 0; i < n; ++i) {
      long long di = max((long long)0, (long long)comps[i] * numa - stock[i]);
      money += di * cost[i];
    }
    return money <= budget;
  }
  bool check_all_comp(long long numa, int n, int k, long long budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
    for (int i = 0; i < k; ++i) {
      if (checkAlloys(numa, n, budget, composition[i], stock, cost)) return true;
    }
    return false;
  }
  int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
    long long low = 0, high = budget;
    long long maxS = 0;
    for (auto s : stock)maxS = max((long long)s, maxS);
    high += maxS;
    while (low < high) {
      long long mid = (high + low) / 2+1;
      if (check_all_comp(mid, n, k, (long long)budget, composition, stock, cost)) {
        low = mid;
      }
      else high = mid - 1;
    }
    return low;
  }
  long long maximumSum(vector<int>& nums) {
    int K = 101,n=nums.size();
    vector<int>base(K+1);
    long long ans = 0;
    for (auto c : nums) ans = max(ans, (long long)c);
    for (int i = 0; i <= K; ++i) base[i] = i * i;
    int d = 1;
    while(base[1]*d<=n) {
      long long tmp = 0;
      for (int i = 1; i <= K; ++i) {
        if (base[i] * d <= n)tmp += nums[base[i] * d - 1];
        else break;
      }
      ans = max(ans, tmp);
      ++d;
    }
    return ans;
  }
};