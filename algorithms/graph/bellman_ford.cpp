/* =====================================================================================
   This file contains the implementation of the Bellman-Ford's algorithm. It returns
   the shortest distance from the starting node to all other nodes.

   @param n:            the number of vertices in the graph
   @param e:            the edge list representation of the graph
   @param s:            the starting node
   @return vector<int>: the shortest distance from the starting node to all other nodes,
                        {-1} if there is a negative cycle in the graph

   @author: Muhammad Fadli Alim Arsani
======================================================================================*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"
using namespace std;

vector<int> bellman_ford(int n, vector<vector<int>>& e, int s) {
  vector<int> dists(n, INT_MAX);
  dists[s] = 0;

  for (int i=0; i<n-1; i++) {
    for (const auto& edge : e) {
      int u = edge[0], v = edge[1], w = edge[2];

      // Edge relaxation step
      if (dists[u] != INT_MAX && dists[u] + w < dists[v]) {
        dists[v] = dists[u] + w;
      }
    }
  }

  // Check for negative cycle existence by doing
  // one more iteration (i.e: n iteration instead of n-1)
  for (const auto& edge : e) {
    int u = edge[0], v = edge[1], w = edge[2];

    // Edge relaxation step
    if (dists[u] != INT_MAX && dists[u] + w < dists[v]) {
      return {-1};
    }
  }

  return dists;
}

TEST_CASE("Bellman-Ford algorithm test cases") {
    SECTION("Simple graph without negative weights") {
        int n = 5;
        vector<vector<int>> e = {
            {0, 1, 2},
            {0, 3, 6},
            {1, 2, 3},
            {1, 3, 8},
            {1, 4, 5},
            {2, 4, 7},
            {3, 4, 9}
        };
        int start = 0;
        vector<int> expected = {0, 2, 5, 6, 7};
        vector<int> result = bellman_ford(n, e, start);

        REQUIRE(result == expected);
    }

    SECTION("Graph with negative weights but no negative cycle") {
        int n = 5;
        vector<vector<int>> e = {
            {0, 1, -1},
            {0, 2, 4},
            {1, 2, 3},
            {1, 3, 2},
            {1, 4, 2},
            {3, 2, 5},
            {3, 1, 1},
            {4, 3, -3}
        };
        int start = 0;
        vector<int> expected = {0, -1, 2, -2, 1};
        vector<int> result = bellman_ford(n, e, start);

        REQUIRE(result == expected);
    }

    SECTION("Graph with a negative cycle") {
        int n = 4;
        vector<vector<int>> e = {
            {0, 1, 1},
            {1, 2, -1},
            {2, 3, -1},
            {3, 0, -1}
        };
        int start = 0;
        vector<int> expected = {-1};
        vector<int> result = bellman_ford(n, e, start);

        REQUIRE(result == expected);
    }

    SECTION("Disconnected graph") {
        int n = 4;
        vector<vector<int>> e = {
            {0, 1, 4},
            {1, 2, 5}
        };
        int start = 0;
        vector<int> expected = {0, 4, 9, INT_MAX};
        vector<int> result = bellman_ford(n, e, start);

        REQUIRE(result == expected);
    }

    SECTION("Graph with a single node") {
        int n = 1;
        vector<vector<int>> e = {};
        int start = 0;
        vector<int> expected = {0};
        vector<int> result = bellman_ford(n, e, start);

        REQUIRE(result == expected);
    }
}

