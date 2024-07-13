/* ==============================================================================
   This is an implementation of the Breadth First Search (DFS) algorithm.
   The implementation assumes the starting node to be `0` by
   default. It then prints the visited nodes in the order they are visited.

   @param n: the number of vertices in the graph
   @param adj_mat:  the adjacency matrix representation of the graph
     or
   @param adj_list: the adjacency list representation of the graph

   @author: Muhammad Fadli Alim Arsani
===============================================================================*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"

// ======================================================
// BFS implementation: Adjacency matrix
// ======================================================
void bfs(int n, std::vector<std::vector<int>>& adj_mat) {
  std::vector<int> record;

  // ====================================================
  std::queue<int> q;
  q.push(0);
  std::vector<bool> visited(n, false);

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    if (!visited[node]) {
      visited[node] = true;

      record.push_back(node);

      for (int i = 0; i < n; i++) {
        if (adj_mat[node][i] && !visited[i]) q.push(i);
      }
    }
  }
  // ====================================================

  std::cout << "[";
  for (int i = 0; i < record.size(); i++) {
    if (i == record.size() - 1) {
      std::cout << record[i];
    }
    else {
      std::cout << record[i] << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

// ======================================================
// BFS implementation: Adjacency list
// ======================================================
void bfs(int n, std::vector<int> adj_list[]) {
  std::vector<int> record;

  // ====================================================
  std::queue<int> q;
  q.push(0);
  std::vector<bool> visited(n, false);

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    if (!visited[node]) {
      visited[node] = true;

      record.push_back(node);

      for (auto const& neighbor : adj_list[node]) {
        if (!visited[neighbor]) q.push(neighbor);
      }
    }
  }
  // ====================================================

  std::cout << "[";
  for (int i = 0; i < record.size(); i++) {
    if (i == record.size() - 1) {
      std::cout << record[i];
    }
    else {
      std::cout << record[i] << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

TEST_CASE("BFS with adjacency matrix", "[bfs][adjacency_matrix]") {
  int n = 4;
  std::vector<std::vector<int>> adj_mat = {
      {0, 1, 0, 1},
      {1, 0, 1, 0},
      {0, 1, 0, 1},
      {1, 0, 1, 0}
  };

  // Capture the output
  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  bfs(n, adj_mat);

  // Restore the original stream buffer
  std::cout.rdbuf(p_cout_streambuf);

  REQUIRE(oss.str() == "[0, 1, 3, 2]\n");
}

TEST_CASE("BFS with adjacency list", "[bfs][adjacency_list]") {
  int n = 4;
  std::vector<int> adj_list[4];
  adj_list[0] = {1, 3};
  adj_list[1] = {0, 2};
  adj_list[2] = {1, 3};
  adj_list[3] = {0, 2};

  // Capture the output
  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  bfs(n, adj_list);

  // Restore the original stream buffer
  std::cout.rdbuf(p_cout_streambuf);

  REQUIRE(oss.str() == "[0, 1, 3, 2]\n");
}

TEST_CASE("BFS with disconnected graph - adjacency matrix", "[bfs][adjacency_matrix]") {
  int n = 5;
  std::vector<std::vector<int>> adj_mat = {
      {0, 1, 0, 0, 0},
      {1, 0, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0}
  };

  // Capture the output
  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  bfs(n, adj_mat);

  // Restore the original stream buffer
  std::cout.rdbuf(p_cout_streambuf);

  REQUIRE(oss.str() == "[0, 1, 2]\n");
}

TEST_CASE("BFS with disconnected graph - adjacency list", "[bfs][adjacency_list]") {
  int n = 5;
  std::vector<int> adj_list[5];
  adj_list[0] = {1};
  adj_list[1] = {0, 2};
  adj_list[2] = {1};
  adj_list[3] = {4};
  adj_list[4] = {3};

  // Capture the output
  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  bfs(n, adj_list);

  // Restore the original stream buffer
  std::cout.rdbuf(p_cout_streambuf);

  REQUIRE(oss.str() == "[0, 1, 2]\n");
}

TEST_CASE("BFS with single node graph - adjacency matrix", "[bfs][adjacency_matrix]") {
  int n = 1;
  std::vector<std::vector<int>> adj_mat = {{0}};

  // Capture the output
  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  bfs(n, adj_mat);

  // Restore the original stream buffer
  std::cout.rdbuf(p_cout_streambuf);

  REQUIRE(oss.str() == "[0]\n");
}

TEST_CASE("BFS with single node graph - adjacency list", "[bfs][adjacency_list]") {
  int n = 1;
  std::vector<int> adj_list[1];

  // Capture the output
  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  bfs(n, adj_list);

  // Restore the original stream buffer
  std::cout.rdbuf(p_cout_streambuf);

  REQUIRE(oss.str() == "[0]\n");
}
