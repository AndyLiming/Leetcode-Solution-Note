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
};