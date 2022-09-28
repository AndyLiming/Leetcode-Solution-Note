#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

// wangyi no3
int redNum(string s) {
  int n = s.size();
  if (n <= 1) return 0;
  vector<vector<int>>dp(n, vector<int>(3, 0));
  unordered_map<char, int>tab{ {'r',0},{'e',1},{'d',2} };
  for (int i = 0; i < 3; ++i) {
    dp[0][i] = (i - tab[s[0]] + 3) % 3;
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < 3; ++j) {
      int tmp = min(dp[i - 1][(j - 1 + 3) % 3], dp[i - 1][(j + 1 + 3) % 3]);
      dp[i][j] = tmp + (j - tab[s[i]] + 3) % 3;
    }
  }
  return min(min(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]);
}

int game(int n, int m, int t, vector<int>& a, vector<int>& b) {
  int ida = -1,idb=-1,res=0;
  if (a[0] > t&& b[0] > t) return 0;
  long long curSum = 0;
  while (ida < n-1 && curSum+a[ida+1]<=t) {
    curSum += a[ida+1];
    ++ida;
    ++res;
  }
  while (idb < m-1 && curSum + b[idb+1] <= t) {
    curSum += b[idb+1];
    ++idb;
    ++res;
  }
  int tmp = res;
  while (ida >= 0 && idb < m) {
    curSum -= a[ida];
    --tmp;
    --ida;
    while (idb+1 < m && curSum + b[idb+1] <= t) {
      curSum += b[idb + 1];
      ++idb;
      ++tmp;
    }
    res = max(res, tmp);
  }
  return res;
}

int numOp(vector<int>& nums, int n, int x) {
  vector<int>preSum(nums);
  unordered_map<int, int>tab;
  tab.insert({ 0,-1 });
  tab.insert({ nums[0],0 });
  for (int i = 1; i < n; ++i) {
    preSum[i] = preSum[i - 1] + nums[i];
    if (tab.find(preSum[i]) == tab.end()) tab.insert({ preSum[i],i });
  }
  int res = n + 1;
  if (tab.find(x) != tab.end()) res = tab[x];
  int t = 0;
  for (int j = n - 1; j >= 0; --j) {
    t += nums[j];
    auto it = tab.find(x - t);
    if (it != tab.end()) {
      int i = it->second;
      if (i < j) res = min(res, i + n - j+1);
    }
  }
  return (res == n + 1) ? -1 : res;
}

vector<string>splitStr(string s,int n) {
  int len = s.size();
  vector<string>ans;
  int i = 0,c=0;
  while (i < len) {
    int start = i;
    while (i<len &&c < n) {
      if (s[i] != '$') {
        ++i;
        ++c;
      }
      else {
        if (s[i + 1] == 'x') {
          i += 4;
          c += 4;
        }
        else if (s[i + 1] == 'U') {
          i += 6;
          c += 6;
        }
        else {

        };
      }
    }
    ans.push_back(s.substr(start, c));
    c = 0;
    }
  return ans;
}
string trans(string s,int k) {
  char t = s[k - 1];
  int start = k - 1, end = k - 1;
  while (start >= 0 && s[start] == t) --start;
  while (end < s.size() && s[end] == t)++end;
  string ans = "";
  if (start >= 0) ans += s.substr(0, start + 1);
  ans += s.substr(start + 1, end - start - 1);
  if (end < s.size()) ans += s.substr(end);
  return ans;
}
vector<string> coins(string s, int k) {
  unordered_map<string, int>tab;
  int num = 0;
  tab.insert({ s,num });
  string cir = "";
  int start = -1;
  int length = -1;
  while (1) {
    ++num;
    string next = trans(s, k);
    if (tab.count(next)) {
      cir = next;
      start = tab[next];
      length = num - start;
      return { cir,to_string(start),to_string(length) };
    }
    tab[next] = num;
  }
}

double area_tixing(double w1, double w2, double h) {
  return (w1 + w2) * h / 2;
}
vector<double>inter(double x11, double y11, double x12, double y12, double x21, double y21, double x22, double y22) {
  double A1 = y12 - y11;
  double B1 = x11 - x12;
  double C1 = x12 * y11 - x11 * y12;
  double A2 = y22 - y21;
  double B2 = x21 - x22;
  double C2 = x22 * y21 - x21 * y22;
  double k = A1 * B2 - A2 * B1;
  if (k == 0) return {};
  else return { (C1 * B2 - C2 * B1) / k,(C1 * A2 - C2 * A1) / k };
}
double cal_iou(double ya, double ha, double wa1, double wa2, double yb, double hb, double wb1, double wb2) {
  double ha1 = ya + ha / 2, ha2 = ya - ha / 2;
  double hb1 = yb + hb / 2, hb2 = yb - hb / 2;
  double inter_area = 0;
  if (ha1 <= hb2 || hb1 <= ha2) inter_area= 0.0; //bu xiang jiao
  else {
    double h_up = min(ha1, hb1), h_down = max(ha2, hb2);
    double w_up = min(wa1 + (ha1 - h_up) / (ha1 - ha2) * (wa2 - wa1), wb1 + (hb1 - h_up) / (hb1 - hb2) * (wb2 - wb1));
    double w_down = min(wb1 + (ha1 - h_down) / (ha1 - ha2) * (wa2 - wa1), wb1 + (hb1 - h_down) / (hb1 - hb2) * (wb2 - wb1));
    auto inter_point = inter(wa2 / 2, ha2, wa1 / 2, ha1, wb2 / 2, hb2, wb1 / 2, hb1);
    if (inter_point.empty() || (inter_point[1] >= h_up) || (inter_point[1] <= h_down)) {
      // 1 ti xing
      inter_area = area_tixing(w_up, w_down, (h_up - h_down));
    }
    else {
      // 2 tixing
      double big_w = 2 * inter_point[0];
      inter_area = area_tixing(w_up, big_w, (h_up - inter_point[1])) + area_tixing(big_w, w_down, (inter_point[1] - h_down));
    }
  }
  double area_a = area_tixing(wa1, wa2, ha),area_b=area_tixing(wb1,wb2,hb);
  return inter_area / (area_a + area_b - inter_area);
}


int cnt = 0;
void dfs(int number, int n, int location, int sum,vector<int>& nums) {//第一个参数为当前因子的大小。
  if (sum == n&& nums.size()>1) {
    for (int j = 1; j < nums.size(); ++j) {
      if (nums[j] != nums[0]) {
        ++cnt;
        break;
      }
    }
    return;
  }
  if (sum > n) return;
  for (int i = number; i < n; ++i) {
    nums.push_back(i);
    dfs(i, n, location + 1, sum + i, nums);
    nums.pop_back();
  }
}
