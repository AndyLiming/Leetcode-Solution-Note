#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

class daily202308 {
public:
  // 2023.08.01 - No 2681
  int sumOfPower(vector<int>& nums) {
    long long M = 1e9 + 7;
    sort(nums.begin(), nums.end());
    int len = nums.size();
    long long times = (long long)nums[0];
    long long ans = ((((long long)nums[0] * (long long)nums[0]) % M) * times) % M;
    for (int i = 1; i < len; ++i) {
      long long sq = ((long long)nums[i] * (long long)nums[i]) % M;
      times = ((times * 2) % M) + (nums[i] - nums[i - 1]);
      ans =(ans+ ((sq * times) % M)) % M;
    }
    return ans;
  }
  // 2023.08.02 - No 822
  int flipgame(vector<int>& fronts, vector<int>& backs) {
    int ans = 0;
    int len = fronts.size();
    set<int> cand;
    for (auto n : fronts) cand.insert(n);
    for (auto n : backs) cand.insert(n);
    for (auto it = cand.begin(); it != cand.end(); ++it) {
      int num = *it;
      bool yes = true;
      for (int i = 0; i < len; ++i) {
        if (fronts[i] == num && backs[i] == num) {
          yes = false;
          break;
        }
      }
      if (yes) {
        ans = num;
        break;
      }
    }
    return ans;
  }
   //2023.08.07
  void reverseString(vector<char>& s) {
    int len = s.size();
    for (int i = 0; i < len / 2; ++i) {
      char tmp = s[i];
      s[i] = s[len - i - 1];
      s[len - i - 1] = tmp;
    }
  }
  // 2023.08.08 - No 1749
  int maxAbsoluteSum(vector<int>& nums) {
    int len = nums.size();
    int maxPos = 0, minNeg = 0;
    int sumPos = 0, sumNeg = 0;
    for (int i = 0; i < len; ++i) {
      sumPos = sumPos + nums[i];
      sumPos = max(0, sumPos);
      maxPos = max(maxPos, sumPos);
      sumNeg = sumNeg + nums[i];
      sumNeg = min(0, sumNeg);
      minNeg = min(minNeg, sumNeg);
    }
    return max(maxPos, -minNeg);
  }
  //2023.08.09 - 1281
  int subtractProductAndSum(int n) {
    int times = 1, add = 0;
    while (n) {
      int tmp = n % 10;
      times *= tmp;
      add += tmp;
      n /= 10;
    }
    return times - add;
  }

  //2023.08.10 - 1289
  int minFallingPathSum(vector<vector<int>>& grid) {
    vector<int>curSum(grid[0].begin(), grid[0].end());
    vector<int>nextSum(grid[0].begin(), grid[0].end());
    for (int i = 1; i < grid.size(); ++i) {
      for (int j = 0; j < grid.size(); ++j) {
        int prevMinSum = 1e9;
        for (int k = 0; k < grid.size(); ++k) {
          if (j != k) {
            prevMinSum = min(prevMinSum, curSum[k]);
          }
        }
        nextSum[j] = prevMinSum + grid[i][j];
      }
      curSum = nextSum;
    }
    int minSum = 1e9;
    for (auto c : curSum) minSum = min(c, minSum);
    return minSum;
  }

  //2023.08.11 - 1572
  int diagonalSum(vector<vector<int>>& mat) {
    int n = mat.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ans += mat[i][i];
      ans += mat[i][n - 1 - i];
    }
    if (n % 2 == 1) ans -= mat[(n - 1) / 2][(n - 1) / 2];
    return ans;
  }

  //2023.08.12 - 23
  ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
    if ((!l1) || (!l2)) return l1 ? l1 : l2;
    ListNode* head = new ListNode(-1);
    ListNode* p = head;
    ListNode* p1 = l1;
    ListNode* p2 = l2;
    while (p1 && p2) {
      if (p1->val <= p2->val) {
        p->next = p1;
        p1 = p1->next;
      }
      else {
        p->next = p2;
        p2 = p2->next;
      }
      p = p->next;
    }
    if (p1) p->next = p1;
    if (p2) p->next = p2;
    return head->next;
  }
  ListNode* mergeCore(vector<ListNode*>& lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    //cout << l << " " << r << " " << mid << endl;
    return merge2Lists(mergeCore(lists, l, mid), mergeCore(lists, mid + 1, r));
  }
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    return mergeCore(lists, 0, lists.size() - 1);
  }

  //2023.08.13 - 88
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if (m == 0) nums1 = nums2;
    int i = m - 1, j = n - 1,k=n+m-1;
    while (i >= 0 || j >= 0) {
      if (i == -1 || j==-1) {
        if (i == -1) {
          nums1[k] = nums2[j];
          --j;
        }
        else {
          nums1[k] = nums1[i];
          --i;
        }
      }
      else if (nums1[i] >= nums2[j]) {
        nums1[k] = nums1[i];
        --i;
      }
      else {
        nums1[k] = nums2[j];
        --j;
      }
      --k;
    }
  }
  //2023.08.14
  TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (!root1) return root2;
    if (!root2) return root1;
    int val = root1->val + root2->val;
    TreeNode* root = new TreeNode(val);
    root->left = mergeTrees(root1->left, root2->left);
    root->right = mergeTrees(root1->right, root2->right);
    return root;
  }
  //2023.08.15 - 833
  string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
    string ans = "";
    int k = indices.size();
    priority_queue<pair<int, int>,vector<pair<int,int>>,greater<pair<int,int>>>vp;
    for (int i = 0; i < k; ++i) vp.push({ indices[i],i });
    int curPos = 0;
    for (int i = 0; i < k; ++i) {
      int id = vp.top().second;
      vp.pop();
      int p1 = indices[id];
      ans += s.substr(curPos, p1 - curPos);
      curPos = p1;
      string tmp = sources[id];
      int m = tmp.size(), pt = 0;
      bool replace = true;
      while (pt < m) {
        if (s[p1] == tmp[pt]) {
          ++pt;
          ++p1;
        }
        else {
          replace = false;
          break;
        }
      }
      if (replace) {
        ans += targets[id];
        curPos = curPos + m;
      }
    }
    if (curPos < s.size()) ans += s.substr(curPos);
    return ans;
  }
  //2023.8.16
  vector<int> circularGameLosers(int n, int k) {
    unordered_set<int>win;
    win.insert(1);
    int i = 1,last=1;
    while (true) {
      int next = (last + i * k)%n;
      if (next ==0)next = n;
      if (win.find(next) != win.end()) {
        break;
      }
      win.insert(next);
      last = next;
      i += 1;
    }
    vector<int>ans;
    for (int i = 1; i <= n; ++i) {
      if (win.find(i) == win.end()) ans.push_back(i);
    }
    return ans;
  }

  //2023.8.18
  //int maxSizeSlices(vector<int>& slices) {

  //}

  //2023.8.21
  bool canChange(string start, string target) {
    int n = start.length();
    int i = 0, j = 0;
    while (i < n && j < n) {
      while (i < n && start[i] == '_') {
        i++;
      }
      while (j < n && target[j] == '_') {
        j++;
      }
      if (i < n && j < n) {
        if (start[i] != target[j]) {
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
      if (start[i] != '_') {
        return false;
      }
      i++;
    }
    while (j < n) {
      if (target[j] != '_') {
        return false;
      }
      j++;
    }
    return true;
  }
  //2023.8.26
  vector<string> summaryRanges(vector<int>& nums) {
    vector<string>ans;
    int i = 0, j = 0,n=nums.size();
    while (i < n) {
      j = i + 1;
      while (j < n && (long long)nums[j] - (long long)nums[j - 1] == 1)++j;
      j = j - 1;
      if (i == j) ans.push_back(to_string(nums[i]));
      else {
        ans.push_back(to_string(nums[i]) + "->" + to_string(nums[j]));
      }
      i = j + 1;
    }
    return ans;
  }
  //2023.8.27
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.size() <= 1) return intervals;
    sort(intervals.begin(), intervals.end(), [](const vector<int>& p1, const vector<int>& p2) {return (p1[0] < p2[0]) || (p1[0] == p2[0] && p1[1] < p2[1]); });
    vector<vector<int>>ans;
    int start = intervals[0][0], end = intervals[0][1];
    for (int i = 1; i < intervals.size(); ++i) {
      if (intervals[i][0] <= end) end = max(end,intervals[i][1]);
      else {
        ans.push_back({ start,end });
        start = intervals[i][0];
        end = intervals[i][1];
      }
    }
    ans.push_back({ start,end });
    return ans;
  }
  //2023.8.28
  vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> ans;
    int n = intervals.size(), cur = 0;
    for (int i = 0; i < n; ++i) {
      if (intervals[i][1] < newInterval[0]) {
        ans.push_back(intervals[i]);
        ++cur;
      }
      else if (intervals[i][0] > newInterval[1]) {
        ans.push_back(intervals[i]);
      }
      else {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
      }
    }
    ans.insert(ans.begin() + cur, newInterval);
    return ans;
  }
  //2023.8.29
  int numFactoredBinaryTrees(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    int n = arr.size();
    long long M = 1e9 + 7;
    long long ans = 0;
    vector<long long> dp(n, 1);
    ans = ans + dp[0];
    for (int i = 1; i < n; ++i) {
      int left = 0, right = i - 1;
      while (left <= right) {
        while (left <= right && (long long)arr[left] * (long long)arr[right] > (long long)arr[i]) --right;
        if (left <= right && (long long)arr[left] * (long long)arr[right] == (long long)arr[i]) {
          if (left == right) dp[i] = (dp[i] + (dp[left] * dp[right]) % M) % M;
          else dp[i] = (dp[i] + (dp[left] * dp[right] * 2) % M) % M;
        }
        ++left;
      }
      ans = (ans + dp[i]) % M;
    }
    return ans;
  }
  //2023.8.30
  int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
    unordered_set<int>fb(forbidden.begin(), forbidden.end());
    unordered_set<int>visited;
    queue<tuple<int, int, int>>q;
    q.push({ 0,1,0 });
    visited.insert(0);
    int lower = 0, upper = max(*max_element(forbidden.begin(), forbidden.end()) + a, x) + b;
    while (!q.empty()) {
      auto [pos, dir, step] = q.front();
      q.pop();
      if (pos == x) return step;
      int next_pos = pos + a;
      int next_dir = 1;
      if (next_pos >= lower && next_pos <= upper &&
        !visited.count(next_pos) && !fb.count(next_pos)) {
        visited.insert(next_pos * next_dir);
        q.push({ next_pos,next_dir,step + 1 });
      }
      if (dir == 1) {
        next_pos = pos - b;
        next_dir = -1;
        if (next_pos >= lower && next_pos <= upper &&
          !visited.count(next_pos) && !fb.count(next_pos)) {
          visited.insert(next_pos * next_dir);
          q.push({ next_pos,next_dir,step + 1 });
        }
      }
    }
    return -1;
  }
};

class daily202309 {
public:
  //2023.9.1
  long long waysToBuyPensPencils(int total, int cost1, int cost2) {
    long long ans=0;
    while (total>=0) {
      if (total >= 0) ans += (long long)total / cost2+1;
      total -= cost1;
    }
    return ans;
  }
  //2023.9.2
  int captureForts(vector<int>& forts) {
    int ans = 0;
    int n = forts.size();
    for (int i =0; i < n; ++i) {
      int f = forts[i];
      if (f!=0) {
        int j = i - 1;
        while (j >= 0 && forts[j] == 0)--j;
        if (j >= 0 && forts[j] == -f) ans = max(ans, i - j - 1);
        j = i + 1;
        while (j <n && forts[j] == 0)++j;
        if (j<n && forts[j] == -f) ans = max(ans, j-i-1);
      }
    }
    return ans;
  }
  //2023.9.3
  int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
    int n = dist.size();
    vector<int>time(n);
    for (int i = 0; i < n; ++i) {
      time[i] = dist[i] / speed[i] + (dist[i] % speed[i] > 0);
    }
    sort(time.begin(), time.end());
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (time[i] < i + 1) return i;
    }
    return n;
  }
  //class Codec {
  //public:

  //  // Encodes a tree to a single string.
  //  string serialize(TreeNode* root) {

  //  }

  //  // Decodes your encoded data to tree.
  //  TreeNode* deserialize(string data) {

  //  }
  //};
  bool check_repair_num(long long time, vector<int>& ranks,int cars) {
    long long cnt = 0;
    for (int i = 0; i < ranks.size();++i) {
      long long r = ranks[i];
      cnt += sqrt(time / r);
    }
    return cnt >= (long long)cars;
  }
  long long repairCars(vector<int>& ranks, int cars) {
    long long low = 1, high = (long long)ranks[0] * (long long)cars * (long long)cars;
    while (low < high) {
      long long mid = (high + low) / 2;
      if (check_repair_num(mid, ranks, cars)) high = mid;
      else low = mid + 1;
    }
    return low;
  }

  //
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int>in_degree(numCourses);
    vector<vector<int>>connect(numCourses, vector<int>());
    for (auto pre : prerequisites) {
      in_degree[pre[0]]++;
      connect[pre[1]].push_back(pre[0]);
    }
    queue<int>q;
    int cnt = 0;
    for (int i = 0; i < numCourses; ++i) {
      if (in_degree[i] == 0)q.push(i);
    }
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      ++cnt;
      for (auto nx : connect[cur]) {
        if (in_degree[nx] > 0) {
          --in_degree[nx];
          if(in_degree[nx]==0) q.push(nx);
        }
      }
    }
    return cnt == numCourses;
  }
};