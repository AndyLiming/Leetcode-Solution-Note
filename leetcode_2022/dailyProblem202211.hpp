#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

class daily202211 {
public:
  // 2022.11.01 - No 1662
  bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
    string s1 = "", s2 = "";
    for (auto& c : word1)s1 += c;
    for (auto& c : word2)s2 += c;
    return s1 == s2;
  }
  // 2022.11.02 - No 1620
  vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
    int minx = 0, maxx = 0, miny = 0, maxy = 0;
    for (auto t : towers) {
      maxx = max(maxx, t[0]);
      maxy = max(maxy, t[1]);
    }
    int ansx = 0, ansy = 0, p = 0;
    for (int i = minx; i <= maxx; ++i) {
      for (int j = miny; j <= maxy; ++j) {
        int tmp = 0;
        for (auto t : towers) {
          double dis = sqrt((double)(t[0] - i) * (double)(t[0] - i) + (double)(t[1] - j) * (double)(t[1] - j));
          if (dis <= (double)radius) {
            tmp += (int)((double)t[2] / (dis + 1));
          }
        }
        if (tmp > p) {
          p = tmp;
          ansx = i;
          ansy = j;
        }
      }
    }
    return { ansx,ansy };
  }
  // 2022.11.03 - No 1668
  int maxRepeating(string sequence, string word) {
    int ns = sequence.size(), nw = word.size();
    int maxk = ns / nw;
    int i = 1;
    string tmp = word;
    while (i <= maxk) {
      if (sequence.find(tmp) == sequence.npos) {
        return i - 1;
      }
      else {
        ++i;
        tmp += word;
      }
    }
    return maxk;
  }
};