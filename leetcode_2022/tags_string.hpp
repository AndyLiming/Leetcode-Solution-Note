#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

//tags:
// array, list, hash_table, string, double_pointer, stack_queue, tree, back_tracking, search, greedy, graph, bit_op, math
// union_find, slide_window, matrix, simulate, design
// others


class Tag_String {
public:
  //No 28 KMP
  int strStr(string haystack, string needle) {
    int n = haystack.size(), m = needle.size();
    if (m == 0) return 0;
    vector<int>next(m);
    for (int i = 1, j = 0; i < m; ++i) {
      while (j > 0 && needle[i] != needle[j]) {
        j = next[j - 1];
      }
      if (needle[i] == needle[j]) {
        ++j;
      }
      next[i] = j;
    }
    for (int i = 0, j = 0; i < n; ++i) {
      while (j > 0 && haystack[i] != needle[j]) {
        j = next[j - 1];
      }
      if (haystack[i] == needle[j]) {
        ++j;
      }
      if (j == m) {
        return i - m + 1;
      }
    }
    return -1;
  }
  //No 5 longestPalindrome
  string longestPalindrome(string s) {
    int start = 0, end = 0;
    for (int i = 0; i < s.size(); ++i) {
      int left1 = i, right1 = i;
      while (left1 >= 0 && right1 < s.size() && s[left1] == s[right1]) {
        --left1;
        ++right1;
      }
      ++left1;
      --right1;
      int left2 = i, right2 = i + 1;
      while (left2 >= 0 && right2 < s.size() && s[left2] == s[right2]) {
        --left2;
        ++right2;
      }
      ++left2;
      --right2;
      if (right1 - left1 > end - start) {
        start = left1;
        end = right1;
      }
      if (right2 - left2 > end - start) {
        start = left2;
        end = right2;
      }
    }
    return s.substr(start, end - start + 1);
  }
  string longestPalindrome_manacher(string s) {
    string tmp = "$#";
    for (auto c : s) {
      tmp += c;
      tmp += '#';
    }
    vector<int>rad(tmp.size(), 0);
    int id = 0, mx = 0, resCenter = 0, resLen = 0;
    for (int i = 1; i < tmp.size(); ++i) {
      rad[i] = mx > i ? min(rad[2 * id - i], mx - i) : 1;
      while (tmp[i + rad[i]] == tmp[i - rad[i]]) ++rad[i];
      if (i + rad[i] > mx) {
        id = i;
        mx = i + rad[i];
      }
      if (resLen < rad[i]) {
        resLen = rad[i];
        resCenter = i;
      }
    }
    return s.substr((resCenter - resLen) / 2, resLen - 1);
  }
};