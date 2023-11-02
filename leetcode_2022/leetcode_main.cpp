#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"
#include "lcTop100.hpp"
#include "dailyProblem202308.hpp"
#include "lcweekly20221009.hpp"
#include "some_contest_problem.hpp"


class find_median {
public:
  priority_queue<int, vector<int>, less<int>> pqMin;
  priority_queue<int, vector<int>, greater<int>> pqMax;

  void addNum(int num) {
    if (pqMin.empty() || num <= pqMin.top()) {
      pqMin.push(num);
      if (pqMax.size() + 1 < pqMin.size()) {
        pqMax.push(pqMin.top());
        pqMin.pop();
      }
    }
    else {
      pqMax.push(num);
      if (pqMax.size() > pqMin.size()) {
        pqMin.push(pqMax.top());
        pqMax.pop();
      }
    }
  }

  pair<double,bool> findMedian() {
    if (pqMin.size() > pqMax.size()) {
      return { pqMin.top(),0 };
    }
    else {
      if((pqMin.top() + pqMax.top())%2==0) return { (pqMin.top() + pqMax.top()) / 2.0,0 };
      else return { (pqMin.top() + pqMax.top()) / 2.0,1 };
    }
  }
};
/*2
5
2 2 1 3 5
3 1 2 5
4
1 1 1 1
1 2 3
*/

//int find_num_g(int n, vector<vector<int>>& diff) {
//  vector<int>color(n, 0);
//  queue<int>q;
//  q.push(0);
//  color[0] = 1;
//  while (!q.empty()) {
//    int cur = q.front();
//    q.pop();
//
//  }
//}

//int min_upper(int n, int k, vector<int>& A, vector<int>& B) {
//  vector<vector<int>>diff(n, vector<int>(n, 0));
//  for (int i = 0; i < n; ++i) {
//    for (int j = 0; j < n; ++j) {
//      diff[i][j] = abs(A[i] - A[j]) + abs(B[i] - B[j]);
//    }
//  }
//  int low = 0, high = 2e5 + 1;
//  while (low < high) {
//    int mid = (low + high) / 2;
//    UnionFind uf=UnionFind(n);
//    for (int i = 1; i < n; ++i) {
//      for (int j = 0; j < i; ++j) {
//        if (diff[i][j] <= mid) uf.connect(i, j);
//      }
//    }
//    unordered_set<int>par;
//    for (int i = 0; i < n; ++i) par.insert(uf.find(i));
//    int g = par.size();
//    if (g > k) low = mid + 1;
//    else high = mid;
//  }
//  return low;
//}
//int min_upper(int n, int k, vector<int>& A, vector<int>& B) {
//  vector<vector<int>>diff(n, vector<int>(n, 0));
//  for (int i = 0; i < n; ++i) {
//    for (int j = 0; j < n; ++j) {
//      diff[i][j] = abs(A[i] - A[j]) + abs(B[i] - B[j]);
//    }
//  }
//  int low = 0, high = 2e5 + 1;
//  while (low < high) {
//    int mid = (low + high) / 2;
//    int g = 1;
//    for (int i = 1; i < n; ++i) {
//      bool new_g = true;
//      for (int j = 0; j < i; ++j) {
//        new_g = new_g && (diff[i][j] > mid);
//      }
//      if (new_g)++g;
//    }
//    if (g > k) low = mid + 1;
//    else high = mid;
//  }
//  return low;
//}

int main() {
  /*
  3 2
1 9 3
2 7 8

4 2
1 1 1 1
1 6 2 7
*/
  //int n, k;
  //cin >> n >> k;
  //vector<int>A(n), B(n);
  //for (int i = 0; i < n; ++i) cin >> A[i];
  //for (int i = 0; i < n; ++i) cin >> B[i];
  //cout << min_upper(n, k, A, B) << endl;
  return 0;
  /*int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int>a(n), b(n - 1);
    unordered_set<int>ns;
    vector<int>orderA;
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      ns.insert(i + 1);
    }
    for (int i = 0; i < n - 1; ++i) {
      cin >> b[i];
      orderA.push_back(a[b[i] - 1]);
      ns.erase(b[i]);
    }
    for (auto i : ns) orderA.push_back(a[i-1]);
    find_median fm;
    vector<double>ans;
    vector<bool>is_double;
    for (int i = 0; i < n; ++i) {
      fm.addNum(orderA.back());
      orderA.pop_back();
      auto med = fm.findMedian();
      ans.push_back(med.first);
      is_double.push_back(med.second);
    }
    for (int i = 0; i < n; ++i) {
      if (is_double.back()) {
        cout << fixed << setprecision(1) << ans.back() << " ";
      }
      else {
        int tmp = (int)ans.back();
        cout << tmp << " ";
      }
      ans.pop_back();
      is_double.pop_back();
    }
    cout << endl;
  }
  return 0;*/
  //int n;
  //cin >> n;
  //if (n % 4 != 0 && (n + 1) % 4 != 0) cout<<-1;
  //else {
  //  vector<int>ans(n);
  //  if (n % 4 == 0) {
  //    int i = 0, j = n;
  //    while (i < j) {
  //      ans[i++] = i + 1;
  //      ans[i++] = j;
  //      ans[--j] = j - 1;
  //      ans[--j] = i;
  //    }
  //  }
  //  else {
  //    for (int i = 0; i < n / 2; i += 2) {
  //      ans[i] = i * 2 + 1;
  //      ans[i + 1] = i * 2 + 2;
  //    }
  //    for (int i = n / 2 + 1; i + 1 < n; i += 2) {
  //      ans[i] = (i - n / 2 - 1) * 2 + 3;
  //      ans[i + 1] = (i - n / 2 - 1) * 2 + 4;
  //    }
  //    ans[n - 1] = n;
  //  }
  //  for (auto a : ans) cout << a << " ";
  //}
  //return 0;

  /*vector<int>a{ 1,3,2,9,1 }, b{ 4,6,1 };
  cout << game(5, 3, 15, a, b) << endl;*/
  /*auto ans = splitStr("hello world", 7);*/
  /*auto ans = splitStr("hello $U0077orld", 8);
  for (auto a : ans) {
    cout << a << ", ";
  }
  cout << endl;
  return 0;*/
  //Top100Solution
  // check test
  //cout << cal_iou(4, 4, 5, 3, -5, 4, 3, 5) << endl;
  //cout << cal_iou(4, 4, 5, 3, -5, 4, 3, 5) << endl;
  //lc weekyly 20220904 *weeklySolution*
  //Top100Solution tp100;
  //vector<int>stones{ 2,1,5,6,2,3 };
  //cout << tp100.largestRectangleArea(stones)<< endl;

  //daily202309 daily;
  ////string s = "vmokgggqzp";
  ////vector<int>indices{ 3,5,1 };
  ////vector<string>sources{ "kg","ggq","mo" };
  ////vector<string>targets = { "s","so","bfr" };
  //cout << daily.waysToBuyPensPencils(20, 10, 5) << endl;

  //weekly20230813 week;
  //auto check = solve(&daily202209::decrypt);

  //check({ 12,5,6,13 }, {2,4,9,3},-2);

}
Settings;