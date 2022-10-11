#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

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
  //No 4
  //No 5
  //No 6
  //No 7
  //No 8
  //No 9
  //No 10
  //No 11
  //No 12
  //No 13
  //No 14
  //No 15
  //No 16
  //No 17
  //No 18
  //No 19
  //No 20
  //No 21
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
  //No 34
  //No 35
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
    //No 51
  //No 52
  //No 53
  //No 54
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
  //No 63
  //No 64
  //No 65
  //No 66
  //No 67
  //No 68
  //No 69
  //No 70
    //No 71
  //No 72
  //No 73
  //No 74
  //No 75
  //No 76
  //No 77
  //No 78
  //No 79
  //No 80
    //No 81
  //No 82
  //No 83
  //No 84
  //No 85
  //No 86
  //No 87
  //No 88
  //No 89
  //No 90
    //No 91
  //No 92
  //No 93
  //No 94
  //No 95
  //No 96
  //No 97
  //No 98
  //No 99
  //No 100
};