#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

class weeklySolution {
public:
  //No 1
  bool checkDistances(string s, vector<int>& distance) {
    vector<vector<int>> show(26, vector<int>(2, -1));
    for (int i = 0; i < s.size(); ++i) {
      if (show[s[i] - 'a'][0] == -1) show[s[i] - 'a'][0] = i;
      else show[s[i] - 'a'][1] = i;
    }
    for (int i = 0; i < 26; ++i) {
      if (show[i][0] > -1) {
        if (distance[i] != (show[i][1] - show[i][0] - 1)) return false;
      }
    }
    return true;
  }
  //No 2
  int numberOfWays(int startPos, int endPos, int k) {
    int diff = abs(endPos - startPos);
    if (diff > k) return 0;
    if (diff == k) return 1;
    if ((k - diff) % 2 != 0) return 0;
    int M = 1e9 + 7;
    int left = 0, right = 0;
    left= diff + (k - diff) / 2;
    right = k - left;
    //combine(k,left)
    vector<vector<long long>>combine(k + 1, vector<long long>(k + 1, 0));
    for (int i = 1; i <= k; ++i) {
      combine[i][0] = 1;
      for (int j = 1; j <= i; ++j) {
        combine[i][j] = (combine[i - 1][j - 1] + combine[i - 1][j]) % M;
      }
    }
    return combine[k][left];
  }
  //No 3
  int longestNiceSubarray(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return n;
    int ans = 1;
    int left = 0, right = 1;
    int orrec = nums[left],orright=0;
    while (left < n && right < n) {
      while (right < n && ((orrec & nums[right]) == 0)) {
        orrec |= nums[right];
        ++right;
      }
      ans = max(ans, right - left);
      ++left;
      orrec = 0;
      for (int i = left; i < right; ++i) orrec |= nums[i];
    }
    return ans;
  }
  //No 4
  int mostBooked(int n, vector<vector<int>>& meetings) {
    int m = meetings.size();
    if (m <= n) return 1;
    sort(meetings.begin(), meetings.end(), [](const vector<int>& m1, const vector<int>& m2) {return m1[0] < m2[0]; });
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    int id = 0;
    vector<int>nums(n, 0);
    while (id < n) {
      auto& cur = meetings[id];
      pq.push({ cur[1],cur[0],id });
    }
    while (id < m) {
      auto& fin = pq.top();
      auto& cur = meetings[id];
      pq.pop();
      int room = fin[2];
      pq.push({ cur[1] + fin[0],cur[0],room });
      nums[room] += 1;
      ++id;
    }
    int maxN = 0,r=-1;
    for (int i = 0; i < n; ++i) {
      if (nums[i] > maxN) {
        maxN = nums[i];
        r = i;
      }
    }
    return r;
  }

  int mostFrequentEven(vector<int>& nums) {
    map<int, int>m;
    for (auto& k : nums) {
      if (k % 2 == 0) {
        if (m.find(k) == m.end()) m[k] = 1;
        else m[k]++;
      }
    }
    int ans = -1,times=0;
    for (auto it = m.begin(); it != m.end(); ++it) {
      if (it->second > times) {
        ans = it->first;
        times = it->second;
      }
    }
    return ans;
  }
  int partitionString(string s) {
    int ans = 0;
    vector<int>count(26, 0);
    for (int i = 0; i < s.size(); ++i) {
      if (count[s[i]-'a'] == 0) count[s[i] - 'a']++;
      else {
        ++ans;
        for (int j = 0; j < 26; ++j) count[j] = 0;
        count[s[i] - 'a']++;
      }
    }
    for (int j = 0; j < 26; ++j) {
      if (count[j] > 0) {
        ++ans;
        break;
      }
    }
    return ans;
  }
  int minGroups(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](const vector<int>& v1, const vector<int>& v2) {return (v1[0] < v2[0]) || (v1[0] == v2[0] && v1[1] < v2[1]); });
    vector<int>endNum;
    endNum.push_back(intervals[0][1]);
    for (int i = 1; i < intervals.size(); ++i) {
      sort(endNum.begin(), endNum.end());
      bool flag = false;
      for (int j = 0; j < endNum.size(); ++j) {
        if (intervals[i][0] > endNum[j]) {
          endNum[j] = intervals[i][1];
          flag = true;
        }
      }
      if (!flag) { endNum.push_back(intervals[i][1]); }
    }
    return endNum.size();
  }
  int lengthOfLIS(vector<int>& nums, int k) {

  }
};