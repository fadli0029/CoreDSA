/* ====================================================================================
   This file contains the implementation of the Dijkstra's algorithm using a priority
   queue. It returns the shortest distance from the starting node to all other nodes.

   @param n: the number of vertices in the graph
   @param g: the adjacency list representation of the graph
   @param s: the starting node
   @return vector<int>: the shortest distance from the starting node to all other nodes

   @author: Muhammad Fadli Alim Arsani
=====================================================================================*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"
using namespace std;

vector<int> dijkstra(int n, vector<vector<int>> g[], int s) {
  vector<int> dists(n, INT_MAX);
  dists[s] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({s, 0});

  while(!pq.empty()) {
    pair<int, int> curr = pq.top();
    int node = curr.first;
    int dist = curr.second;
    pq.pop();

    for (const auto& p : g[node]) {
      int nbr = p[0];
      int weight = p[1];

      if (dist + weight < dists[nbr]) {
        dists[nbr] = dist + weight;
        pq.push({nbr, dists[nbr]});
      }
    }
  }

  return dists;
}

TEST_CASE("Dijkstra's algorithm test cases") {
    SECTION("Simple graph") {
        int n = 5;
        vector<vector<int>> g[5] = {
            {{1, 2}, {3, 6}},
            {{0, 2}, {2, 3}, {3, 8}, {4, 5}},
            {{1, 3}, {4, 7}},
            {{0, 6}, {1, 8}},
            {{1, 5}, {2, 7}}
        };
        int start = 0;
        vector<int> expected = {0, 2, 5, 6, 7};
        vector<int> result = dijkstra(n, g, start);

        REQUIRE(result == expected);
    }

    SECTION("Disconnected graph") {
        int n = 4;
        vector<vector<int>> g[4] = {
            {{1, 1}},
            {{0, 1}},
            {{3, 1}},
            {{2, 1}}
        };
        int start = 0;
        vector<int> expected = {0, 1, INT_MAX, INT_MAX};
        vector<int> result = dijkstra(n, g, start);

        REQUIRE(result == expected);
    }

    SECTION("Graph with a single node") {
        int n = 1;
        vector<vector<int>> g[1] = {};
        int start = 0;
        vector<int> expected = {0};
        vector<int> result = dijkstra(n, g, start);

        REQUIRE(result == expected);
    }

    SECTION("Graph with multiple equal paths") {
        int n = 4;
        vector<vector<int>> g[4] = {
            {{1, 1}, {2, 4}},
            {{0, 1}, {2, 2}, {3, 5}},
            {{0, 4}, {1, 2}, {3, 1}},
            {{1, 5}, {2, 1}}
        };
        int start = 0;
        vector<int> expected = {0, 1, 3, 4};
        vector<int> result = dijkstra(n, g, start);

        REQUIRE(result == expected);
    }
}
