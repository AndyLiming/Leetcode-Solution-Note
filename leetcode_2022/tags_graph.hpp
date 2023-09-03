#include "leetcode.hpp"
#include "stl.hpp"
#include "structures.hpp"

class Tag_graph {
public:
  //dijkstra with adj matrix
  vector<int> dijkstra_mat(int n, int source, vector<vector<int>>& adj_mat) {
    vector<int>dis(n, INT_MAX);
    vector<int>visit(n, 0);
    dis[source] = 0;
    visit[source] = 1;
    for (int i = 0; i < n; ++i) {
      dis[i] = min(dis[i], adj_mat[source][i]);
    }
    for (int i = 1; i < n; ++i) {
      int min_dis = INT_MAX, min_id = -1;
      for (int j = 0; j < n; ++j) {
        if (!visit[j]) {
          if (dis[j] < min_dis) {
            min_dis = dis[j];
            min_id = j;
          }
        }
      }
      visit[min_id] = 1;
      for (int j = 0; j < n; ++j) {
        if (!visit[j] && adj_mat[min_id][j] < INT_MAX) {
          dis[j] = min(dis[j], dis[min_id] + adj_mat[min_id][j]);
        }
      }
    }
    return dis;
  }
  //dijkstra with adj table
  vector<int> dijkstra_mat(int n, int source, unordered_map<int,unordered_map<int,int>>& adj_tab) {
    vector<int>dis(n, INT_MAX);
    vector<int>visit(n, 0);
    dis[source] = 0;
    visit[source] = 1;
    for (int i = 0; i < n; ++i) {
      if (adj_tab[source].count(i)) dis[i] = adj_tab[source][i];
      else dis[i] = INT_MAX;
    }
    for (int i = 1; i < n; ++i) {
      int min_dis = INT_MAX, min_id = -1;
      for (int j = 0; j < n; ++j) {
        if (!visit[j]) {
          if (dis[j] < min_dis) {
            min_dis = dis[j];
            min_id = j;
          }
        }
      }
      visit[min_id] = 1;
      for (int j = 0; j < n; ++j) {
        if (!visit[j] && adj_tab[min_id].count(j)) {
          dis[j] = min(dis[j], dis[min_id] + adj_tab[min_id][j]);
        }
      }
    }
    return dis;
  }
  //spfa with adj mat
  vector<int> spfa_tab(int n, int source, vector<vector<int>>& adj_mat) {
    vector<int>dis(n, INT_MAX);
    vector<int>visit(n, 0);
    queue<int>q;
    dis[source] = 0;
    visit[source] = 1;
    q.push(source);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      visit[cur] = 0;
      for (int i = 0; i < n;++i) {
        if (adj_mat[cur][i] < INT_MAX) {
          int w = adj_mat[cur][i];
          if (dis[i] > dis[cur] + w) {
            dis[i] = dis[cur] + w;
            if (!visit[i]) {
              q.push(i);
              visit[i] = 1;
            }
          }
        }
      }
    }
    return dis;
  }
  //spfa with adj table
  vector<int> spfa_tab(int n, int source, unordered_map<int, unordered_map<int, int>>& adj_tab) {
    vector<int>dis(n, INT_MAX);
    vector<int>visit(n, 0);
    queue<int>q;
    dis[source] = 0;
    visit[source] = 1;
    q.push(source);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      visit[cur] = 0;
      for (auto p : adj_tab[cur]) {
        int i = p.first, w = p.second;
        if (dis[i] > dis[cur] + w) {
          dis[i] = dis[cur] +w;
          if (!visit[i]) {
            q.push(i);
            visit[i] = 1;
          }
        }
      }
    }
    return dis;
  }
  bool topo_sort_circle(int n, unordered_map<int, unordered_map<int, int>>& adj_tab) {
    vector<int> in_degree(n);
    for (auto& start : adj_tab) {
      for (auto& e : start.second) {
        in_degree[e.first]++;
      }
    }
    vector<int>visited(n, 0);
    queue<int>q;
    vector<int>topo_sort;
    for (int i = 0; i < n; ++i) {
      if (in_degree[i] == 0) { q.push(i); visited[i] = 1; }
    }
    while (!q.empty()) {
      auto cur = q.front();
      q.pop();    
      topo_sort.push_back(cur);
      for (auto& e : adj_tab[cur]) {
        in_degree[e.first]--;
        if (in_degree[e.first] == 0) {
          q.push(e.first); 
          visited[e.first] = 1;
        }
      }
    }
    return topo_sort.size() == n;
  }
};