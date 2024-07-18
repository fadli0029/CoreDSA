#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"
using namespace std;

vector<int> kahn(int n, vector<int> adj_list[]) {
  vector<int> in_degree(n, 0);
  for (int i = 0; i < n; i++) {
    for (const auto& j : adj_list[i]) {
      in_degree[j]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (in_degree[i] == 0) {
      q.push(i);
    }
  }

  vector<int> topo_sort;
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    topo_sort.push_back(node);

    for (const auto& i : adj_list[node]) {
      in_degree[i]--;
      if (in_degree[i] == 0) q.push(i);
    }
  }

  return topo_sort;
}

TEST_CASE("Kahn's Algorithm: Basic Tests") {
    SECTION("Single node graph") {
        vector<int> adj_list[1];
        vector<int> result = kahn(1, adj_list);
        vector<int> expected = {0};
        REQUIRE(result == expected);
    }

    SECTION("Two node graph with one edge") {
        vector<int> adj_list[2];
        adj_list[0].push_back(1);
        vector<int> result = kahn(2, adj_list);
        vector<int> expected = {0, 1};
        REQUIRE(result == expected);
    }

    SECTION("Three node graph with a cycle") {
        vector<int> adj_list[3];
        adj_list[0].push_back(1);
        adj_list[1].push_back(2);
        adj_list[2].push_back(0);
        vector<int> result = kahn(3, adj_list);
        vector<int> expected = {};
        REQUIRE(result == expected);
    }

    SECTION("Disconnected graph with two components") {
        vector<int> adj_list[4];
        adj_list[0].push_back(1);
        adj_list[2].push_back(3);
        vector<int> result = kahn(4, adj_list);
        vector<int> expected1 = {0, 2, 1, 3};
        vector<int> expected2 = {2, 0, 3, 1};
        REQUIRE((result == expected1 || result == expected2));
    }

    SECTION("Graph with multiple valid topological sorts") {
        vector<int> adj_list[6];
        adj_list[5].push_back(2);
        adj_list[5].push_back(0);
        adj_list[4].push_back(0);
        adj_list[4].push_back(1);
        adj_list[2].push_back(3);
        adj_list[3].push_back(1);
        vector<int> result = kahn(6, adj_list);
        vector<vector<int>> expected = {
            {4, 5, 2, 0, 3, 1},
            {5, 4, 2, 0, 3, 1},
            {4, 5, 0, 2, 3, 1},
            {5, 4, 0, 2, 3, 1},
            {5, 4, 2, 3, 0, 1},
            {4, 5, 2, 3, 0, 1}
        };
        REQUIRE(find(expected.begin(), expected.end(), result) != expected.end());
    }
}

TEST_CASE("Kahn's Algorithm: Complex Graphs") {
    SECTION("Graph with no edges") {
        vector<int> adj_list[5];
        vector<int> result = kahn(5, adj_list);
        vector<int> expected = {0, 1, 2, 3, 4};
        REQUIRE(result == expected);
    }

    SECTION("Graph with multiple edges and nodes") {
        vector<int> adj_list[6];
        adj_list[0].push_back(3);
        adj_list[1].push_back(3);
        adj_list[1].push_back(4);
        adj_list[2].push_back(4);
        adj_list[3].push_back(5);
        adj_list[4].push_back(5);
        vector<int> result = kahn(6, adj_list);
        vector<vector<int>> expected = {
            {0, 1, 2, 3, 4, 5},
            {1, 0, 2, 3, 4, 5},
            {2, 0, 1, 4, 3, 5},
            {2, 1, 0, 4, 3, 5}
        };
        REQUIRE(find(expected.begin(), expected.end(), result) != expected.end());
    }

    SECTION("Graph with cycle detection") {
        vector<int> adj_list[4];
        adj_list[0].push_back(1);
        adj_list[1].push_back(2);
        adj_list[2].push_back(3);
        adj_list[3].push_back(1);
        vector<int> result = kahn(4, adj_list);
        REQUIRE(result.size() < 4);
    }
}
