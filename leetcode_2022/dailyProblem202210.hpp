#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"
class daily202210 {
public:
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
};