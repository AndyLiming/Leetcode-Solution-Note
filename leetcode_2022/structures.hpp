#pragma once

#include "stl.hpp"

using namespace std;

// Union Find template
class UnionFind {
  int n;
  vector<int> parent;
  vector<int> size;

public:
  UnionFind(int n_) {
    this->n = n_;
    parent = vector<int>(n);
    size = vector<int>(n, 1);
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int idx) {
    if (parent[idx] == idx)
      return idx;
    return find(parent[idx]);
  }

  void connect(int a, int b) {
    int fa = find(a), fb = find(b);
    if (fa != fb) {
      if (size[fa] > size[fb]) {
        parent[fb] = fa;
        size[fa] += size[fb];
      }
      else {
        parent[fa] = fb;
        size[fb] += size[fa];
      }
    }
  }
};

//class Solution {
//public:
//  //No 1
//
//  //No 2
//  
//  //No 3
//  
//  //No 4
//};
//int main() {
//  // check test
//  //auto check = solve( & Solution::reinitializePermutation);
//  //check(6,8);
//  Solution so;
//}
//Settings;