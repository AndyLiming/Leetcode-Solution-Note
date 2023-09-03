#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

class Node {
public:
  int val;
  Node* next;
  Node* random;

  Node(int _val) {
    val = _val;
    next = NULL;
    random = NULL;
  }
};

class Top100Solution {
public:
  //No 1 Two Sum
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int>hash_table;
    for (int i = 0; i < nums.size(); ++i) {
      auto it = hash_table.find(target - nums[i]);
      if (it != hash_table.end()) {
        return{ it->second,i };
      }
      hash_table.insert({ nums[i],i });
    }
    return vector<int>();
  }
  /////////////////////////////////////////////////////
  //No 2
  //No 3
  /*双指针*/ 
  //No 4 Move zero
  void moveZeroes(vector<int>& nums) {
    int i = 0, j = 0;
    while(j<nums.size()){
      if (nums[j]) {
        swap(nums[i], nums[j]);
        ++i;
      }
      ++j;
    }
  }
  //No 5
  //No 6
  //No 7
  /*滑窗*/ 
  //No 8
  //No 9
  vector<int> findAnagrams(string s, string p) {
    int n = s.size(), m = p.size();
    if (n < m) return vector<int>();
    vector<int>pat_p(26, 0);
    for (auto c : p) pat_p[c - 'a']++;
    vector<int>pat_s(26, 0);
    vector<int>ans;
    int left = 0, right = m - 1;
    for (int i = left; i <= right; ++i) pat_s[s[i] - 'a']++;
    while (right < n) {
      if (pat_s == pat_p)
      {
        ans.push_back(left);
      }
      pat_s[s[left] - 'a']--;
      ++left;
      ++right;
      if(right<n) pat_s[s[right] - 'a']++;
    }
    return ans;
  }
  /*子串*/
  //No 10
  //No 11
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    /*int n = nums.size();
    priority_queue <pair< int, int >> pq;
    for (int i = 0; i < k; ++i) {
      pq.push({ nums[i],i });
    }
    vector<int> ans;
    ans.push_back(pq.top().first);
    for (int i = k; i < n; ++i) {
      pq.push({ nums[i],i });
      while ((i - k) >= pq.top().second) pq.pop();
      ans.push_back(pq.top().first);
    }
    return ans;*/
    int n = nums.size();
    deque<int>q;
    for (int i = 0; i < k; ++i) {
      while (!q.empty() && nums[i] >= nums[q.back()]) {
        q.pop_back();
      }
      q.push_back(i);
    }
      vector<int> ans = { nums[q.front()] };
      for (int i = k; i < n; ++i) {
        while (!q.empty() && nums[i] >= nums[q.back()]) {
          q.pop_back();
        }
        q.push_back(i);
        while (q.front() <= i - k) {
          q.pop_front();
        }
        ans.push_back(nums[q.front()]);
      }
      return ans;
    }
  //No 12
  /*数组*/ 
  //No 13
  //No 14
  //No 15
  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    for (int i = 0; i < n / 2; ++i) {
      swap(nums[i], nums[n - i - 1]);
    }
    for (int i = 0; i < k / 2; ++i) {
      swap(nums[i], nums[k - i - 1]);
    }
    for (int i = k; i < (n - k) / 2+k; ++i) {
      swap(nums[i], nums[n - i - 1 + k]);
    }
  }
  //No 16
  //No 17
  /*矩阵*/ 
  //No 18
  void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<int>rows(n,0), cols(m,0);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (matrix[i][j] == 0) {
          rows[i]=1;
          cols[j]=1;
        }
      }
    }
    for (int i = 0; i < m; ++i) {
      if (rows[i] == 1) {
        for (int j = 0; j < n; ++j) {
          matrix[i][j] = 0;
        }
      }
    }
    for (int j = 0; j < n; ++j) {
      if (cols[j] == 1) {
        for (int i = 0; i < m; ++i) {
          matrix[i][j] = 0;
        }
      }
    }
  }
  void setZeroes_2(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    int flag_col0 = false, flag_row0 = false;
    for (int i = 0; i < m; i++) {
      if (!matrix[i][0]) {
        flag_col0 = true;
      }
    }
    for (int j = 0; j < n; j++) {
      if (!matrix[0][j]) {
        flag_row0 = true;
      }
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (!matrix[i][j]) {
          matrix[i][0] = matrix[0][j] = 0;
        }
      }
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (!matrix[i][0] || !matrix[0][j]) {
          matrix[i][j] = 0;
        }
      }
    }
    if (flag_col0) {
      for (int i = 0; i < m; i++) {
        matrix[i][0] = 0;
      }
    }
    if (flag_row0) {
      for (int j = 0; j < n; j++) {
        matrix[0][j] = 0;
      }
    }
  }
  //No 19
  //No 20
  //No 21
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int i = 0, j = n - 1;
    while (i < m && j >= 0) {
      if (matrix[i][j] == target) return true;
      else if (matrix[i][j] < target) {
        ++i;
      }
      else {
        --j;
      }
    }
    return false;
  }
  /*链表*/
  //No 22
  //No 23
  ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
    if ((!l1) || (!l2)) return l1 ? l1 : l2;
    ListNode* head = new ListNode(-1);
    ListNode* p = head, * p1 = l1, * p2 = l2;
    while (p1 && p2) {
      if (p1->val < p2->val) {
        p->next = p1;
        p1 = p1->next;
      }
      else {
        p->next = p2;
        p2 = p2->next;
      }
      p = p->next;
    }
    p->next = (p1 ? p1 : p2);
    return head->next;
  }
  ListNode* mergeCore(vector<ListNode*>& lists, int l, int r) {
    if (l == r) return lists[l];
    if (l > r) return nullptr;
    int mid = (l + r) / 2;
    cout << l << " " << r << " " << mid << endl;
    return merge2Lists(mergeCore(lists, l, mid), mergeCore(lists, mid + 1, r));
  }
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    return mergeCore(lists, 0, lists.size() - 1);
  }
  //No 24
  //No 25
  //No 26
  //No 27
  //No 28
  //No 29
  //No 30
    //No 31
  //No 32
  //No 33
  ListNode* sortList(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) return head;
    ListNode* pivot = head, * greater = head->next;
    while (greater && greater->val <= pivot->val) greater = greater->next;
    if (greater) {
      ListNode *p = greater->next;
      while (p) {
        if (p->val <= pivot->val) {
          int tmp = p->val;
          p->val = greater->val;
          greater->val = tmp;
          greater = greater->next;
        }
        p = p->next;
      }
    }
    ListNode* less = pivot->next;
    pivot->next = nullptr;
    if (less == greater) less = nullptr;
    else {
      ListNode* q = less;
      while (q->next != greater && q->next != nullptr) q = q->next;
      q->next = nullptr;
    }
    ListNode* helper = new ListNode(-1);
    ListNode* q = helper;
    less = sortList(less);
    greater = sortList(greater);
    if (less) helper->next = less;
    while (q->next)q = q->next;
    q->next = pivot;
    q = q->next;
    if (greater)q->next = greater;
    return helper->next;
  }
  //No 34
  unordered_map<Node*, Node*> cachedNode;
  Node* copyRandomList(Node* head) {
    if (!head) return nullptr;
    if (!cachedNode.count(head)) {
      Node* newhead = new Node(head->val);
      cachedNode[head] = newhead;
      newhead->next = copyRandomList(head->next);
      newhead->random = copyRandomList(head->random);
    }
    return cachedNode[head];
  }
  //No 35
  /*二叉树*/ 
  //No 36
  //No 37
  //No 38
  //No 39
  //No 40
    //No 41
  //No 42
  //No 43
  //No 44
  //No 45
  //No 46
  //No 47
  //No 48
  //No 49
  //No 50
  /*图*/ 
    //No 51
  //No 52
  //No 53
  //No 54
  /*回溯*/ 
  //No 55
  bool canJump(vector<int>& nums) {
    int n = nums.size(),far=0;
    for (int i = 0; i < n; ++i) {
      if (far >= i) {
        far = max(far, i + nums[i]);
        if (far >= n - 1) return true;
      }
    }
    return false;
  }
  //No 56
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const vector<int>& v1, const vector<int>& v2) {return (v1[0] < v2[0]) || (v1[0] == v2[0]) && v1[1] < v2[1]; });
    vector < vector<int>>ans;
    int i = 0, n = intervals.size();
    while (i < n) {
      int start = intervals[i][0];
      int end = intervals[i][1];
      ++i;
      while (i < n && intervals[i][0] <= end) {
        end = max(end,intervals[i][1]);
        ++i;
      }
      ans.push_back({ start,end });
    }
    return ans;
  }
  vector<vector<int>> merge_no56(vector<vector<int>>& intervals) {
    if (intervals.size() == 0) {
      return {};
    }
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged;
    for (int i = 0; i < intervals.size(); ++i) {
      int L = intervals[i][0], R = intervals[i][1];
      if (!merged.size() || merged.back()[1] < L) {
        merged.push_back({ L, R });
      }
      else {
        merged.back()[1] = max(merged.back()[1], R);
      }
    }
    return merged;
  }
  //No 57
  //No 58
  //No 59
  //No 60
    //No 61
  //No 62
  int uniquePaths(int m, int n) {
    vector<vector<int>>dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i)dp[i][0] = 1;
    for (int j = 0; j < n; ++j)dp[0][j] = 1;
    for (int i = 1; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }
    return dp[m - 1][n - 1];
  }
  /*二分查找*/
  //No 63
  //No 64
  //No 65
  //No 66
  //No 67
  //No 68
  /*栈*/ 
  //No 69
  //No 70
    //No 71
  //No 72
  int minDistance(string word1, string word2) {
    int n = word1.size(), m = word2.size();
    vector<vector<int>>dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i)dp[i][0] = i;
    for (int j = 0; j <= m; ++j)dp[0][j] = j;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (word1[i-1] == word2[j-1]) {
          dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1]+1), dp[i - 1][j - 1]);
        }
        else {
          dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1]+1), dp[i - 1][j - 1]+1);
        }
      }
    }
    return dp[n][m];
  }
  //No 73
  /*堆*/ 
  //No 74
  //No 75
  //No 76
  class MedianFinder {
  public:
    priority_queue<int, vector<int>, less<int>> queMin;
    priority_queue<int, vector<int>, greater<int>> queMax;

    MedianFinder() {}

    void addNum(int num) {
      if (queMin.empty() || num <= queMin.top()) {
        queMin.push(num);
        if (queMax.size() + 1 < queMin.size()) {
          queMax.push(queMin.top());
          queMin.pop();
        }
      }
      else {
        queMax.push(num);
        if (queMax.size() > queMin.size()) {
          queMin.push(queMax.top());
          queMax.pop();
        }
      }
    }

    double findMedian() {
      if (queMin.size() > queMax.size()) {
        return queMin.top();
      }
      return (queMin.top() + queMax.top()) / 2.0;
    }
  };
  /*贪心*/ 
  //No 77
  //No 78
  //No 79
  //No 80
  /*动规*/
    //No 81
  //No 82
  vector<vector<int>> generate(int numRows) {
    if (numRows == 1) return { {1} };
    if (numRows == 2)return { {1},{1,1} };
    vector<vector<int>> ans;
    ans.push_back({ 1 });
    ans.push_back({ 1,1 });
    for (int i = 3; i <= numRows; ++i) {
      auto last = ans.back();
      vector<int>cur;
      cur.push_back(1);
      for (int j = 0; j < last.size() - 1; ++j) cur.push_back(last[j] + last[j + 1]);
      cur.push_back(1);
      ans.push_back(cur);
    }
    return ans;
  }
  //No 83
  //No 84
  int largestRectangleArea(vector<int>& heights) {
    /*int n = heights.size();
    vector<int>right_first_less(n, n),left_first_less(n,-1);
    stack<int>s;
    int i = 0,ans=0;
    while (i < n) {
       while (!s.empty() && heights[s.top()] >= heights[i]) {
            s.pop();
          }
       left_first_less[i] = (s.empty() ?  - 1:s.top());
      s.push(i);
      ++i;
    }
    s = stack<int>();
    i = n - 1;
    while (i >=0) {
      while (!s.empty() && heights[s.top()] >= heights[i]) {
        s.pop();
      }
      right_first_less[i] = (s.empty() ? n : s.top());
      s.push(i);
      --i;
    }
    for (int i = 0; i < n; ++i) {
      ans = max(ans, (right_first_less[i] - left_first_less[i] - 1) * heights[i]);
    }
    return ans;*/
    int n = heights.size();
    vector<int>right_first_less(n, n), left_first_less(n, -1);
    stack<int>s;
    int i = 0, ans = 0;
    while (i < n) {
      while (!s.empty() && heights[s.top()] > heights[i]) {
        right_first_less[s.top()] = i;
        s.pop();
      }
      s.push(i);
      ++i;
    }
    s = stack<int>();
    i = n - 1;
    while (i >= 0) {
      while (!s.empty() && heights[s.top()] > heights[i]) {
        left_first_less[s.top()] = i;
        s.pop();
      }
      s.push(i);
      --i;
    }
    for (int i = 0; i < n; ++i) {
      ans = max(ans, (right_first_less[i] - left_first_less[i] - 1) * heights[i]);
    }
    return ans;
  }
  //No 85
  int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j * j <= i; j++) {
        dp[i] = min(dp[i], dp[i - j * j]);
      }
      dp[i] = dp[i] + 1;
    }
    return dp[n];
  }
  //No 86
  int coinChange(vector<int>& coins, int amount) {
    vector<int>dp(amount + 1, INT_MAX);
    dp[0] = 0;
    //for(int i=0;i<coins.size();++i) dp[coins[i]]=1;
    for (int i = 1; i <= amount; ++i) {
      for (int j = 0; j < coins.size(); ++j) {
        if (i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX) dp[i] = min(dp[i], dp[i - coins[j]] + 1);
      }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
  }
  //No 87
  //No 88
  //No 89
  //No 90
  /*多维动态规划*/
    //No 91
  //No 92
  //No 93
  //No 94
  //No 95
  /*技巧*/ 
  //No 96
  //No 97
  int majorityElement(vector<int>& nums) {
    int ans = nums[0], count = 1;
    for (int i = 1; i < nums.size(); ++i) {
      if (count > 0) {
        if (nums[i] == ans) ++count;
        else --count;
      }
      else {
        ans = nums[i];
        count = 1;
      }
    }
    return ans;
  }
  //No 98
  //No 99
  //No 100
};