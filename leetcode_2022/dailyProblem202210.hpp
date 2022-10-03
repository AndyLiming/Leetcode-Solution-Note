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
};