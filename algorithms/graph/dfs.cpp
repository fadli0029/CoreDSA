/* ====================================================================================
   This file contains implementations of the Depth First Search (DFS) algorithm using a
   stack explicitly and using recursion (recursion is using stack implicitly
   by nature of a function call). The implementation assumes the starting node
   to be `0` by default. It then prints the visited nodes in the order they
   are visited.

   @param n: the number of vertices in the graph
   @param adj_mat:  the adjacency matrix representation of the graph
     or
   @param adj_list: the adjacency list representation of the graph

   @author: Muhammad Fadli Alim Arsani
=====================================================================================*/

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"

// ======================================================
// Stack-based DFS implementation: Adjacency matrix
// ======================================================
void dfs(int n, std::vector<std::vector<int>>& adj_mat) {
  std::vector<int> record;

  // ====================================================
  std::stack<int> st;
  st.push(0);
  std::vector<bool> visited(n, false);

  while (!st.empty()) {
    int node = st.top();
    st.pop();

    if (!visited[node]) {
      visited[node] = true;

      record.push_back(node);

      for (int i=0; i<n; i++) {
        if (adj_mat[node][i] && !visited[i]) st.push(i);
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
// Stack-based DFS implementation: Adjacency list
// ======================================================
void dfs(int n, std::vector<int> adj_list[]) {
  std::vector<int> record;

  // ====================================================
  std::stack<int> st;
  st.push(0);
  std::vector<bool> visited(n, false);

  while (!st.empty()) {
    int node = st.top();
    st.pop();

    if (!visited[node]) {
      visited[node] = true;

      record.push_back(node);

      for (const auto& neighbor : adj_list[node]) {
        if (!visited[neighbor]) st.push(neighbor);
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
// Recursive DFS implementation: Adjacency matrix
// ======================================================
void dfs_r(int n, std::vector<std::vector<int>>& adj_mat) {
  std::vector<int> record;

  // ======================================================
  std::vector<bool> visited(n, false);

  std::function<void(int)> dfs = [&](int node) {
    visited[node] = true;

    record.push_back(node);

    for (int i = 0; i < n; ++i) {
      if (adj_mat[node][i] && !visited[i]) dfs(i);
    }
  };

  // normally, you can just call
  // dfs(0);

  // but our test case includes disconnected graphs,
  // so we need to call dfs for each unvisited node.
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  // ======================================================

  std::cout << "[";
  for (size_t i = 0; i < record.size(); ++i) {
    if (i == record.size() - 1) {
      std::cout << record[i];
    } else {
      std::cout << record[i] << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

// ======================================================
// Recursive DFS implementation: Adjacency list
// ======================================================
void dfs_r(int n, std::vector<int> adj_list[]) {
  std::vector<int> record;

  // ======================================================
  std::vector<bool> visited(n, false);

  std::function<void(int)> dfs = [&](int node) {
    visited[node] = true;

    record.push_back(node);

    for (const auto& nbr : adj_list[node]) {
      if (!visited[nbr]) dfs(nbr);
    }

  };

  // normally, you can just call
  // dfs(0);

  // but our test case includes disconnected graphs,
  // so we need to call dfs for each unvisited node.
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  // ======================================================

  std::cout << "[";
  for (size_t i = 0; i < record.size(); ++i) {
    if (i == record.size() - 1) {
      std::cout << record[i];
    } else {
      std::cout << record[i] << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

TEST_CASE("Stack-based DFS with adjacency matrix", "[dfs][adjacency_matrix]") {
  int n = 4;
  std::vector<std::vector<int>> adj_mat = {
      {0, 1, 0, 1},
      {1, 0, 1, 0},
      {0, 1, 0, 1},
      {1, 0, 1, 0}
  };

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs(n, adj_mat);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0, 3, 2, 1]\n");
}

TEST_CASE("Stack-based DFS with adjacency list", "[dfs][adjacency_list]") {
  int n = 4;
  std::vector<int> adj_list[4];
  adj_list[0] = {1, 3};
  adj_list[1] = {0, 2};
  adj_list[2] = {1, 3};
  adj_list[3] = {0, 2};

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs(n, adj_list);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0, 3, 2, 1]\n");
}

TEST_CASE("Recursive DFS with adjacency matrix", "[dfs_r][adjacency_matrix]") {
  int n = 4;
  std::vector<std::vector<int>> adj_mat = {
      {0, 1, 0, 1},
      {1, 0, 1, 0},
      {0, 1, 0, 1},
      {1, 0, 1, 0}
  };

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs_r(n, adj_mat);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0, 1, 2, 3]\n");
}

TEST_CASE("Recursive DFS with adjacency list", "[dfs_r][adjacency_list]") {
  int n = 4;
  std::vector<int> adj_list[4];
  adj_list[0] = {1, 3};
  adj_list[1] = {0, 2};
  adj_list[2] = {1, 3};
  adj_list[3] = {0, 2};

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs_r(n, adj_list);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0, 1, 2, 3]\n");
}

TEST_CASE("Recursive DFS with disconnected graph - adjacency matrix", "[dfs_r][adjacency_matrix]") {
  int n = 5;
  std::vector<std::vector<int>> adj_mat = {
      {0, 1, 0, 0, 0},
      {1, 0, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0}
  };

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs_r(n, adj_mat);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0, 1, 2, 3, 4]\n");
}

TEST_CASE("Recursive DFS with disconnected graph - adjacency list", "[dfs_r][adjacency_list]") {
  int n = 5;
  std::vector<int> adj_list[5];
  adj_list[0] = {1};
  adj_list[1] = {0, 2};
  adj_list[2] = {1};
  adj_list[3] = {4};
  adj_list[4] = {3};

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs_r(n, adj_list);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0, 1, 2, 3, 4]\n");
}

TEST_CASE("Recursive DFS with single node graph - adjacency matrix", "[dfs_r][adjacency_matrix]") {
  int n = 1;
  std::vector<std::vector<int>> adj_mat = {{0}};

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs_r(n, adj_mat);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0]\n");
}

TEST_CASE("Recursive DFS with single node graph - adjacency list", "[dfs_r][adjacency_list]") {
  int n = 1;
  std::vector<int> adj_list[1];

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs_r(n, adj_list);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0]\n");
}

TEST_CASE("Stack-based DFS with disconnected graph - adjacency matrix", "[dfs][adjacency_matrix]") {
  int n = 5;
  std::vector<std::vector<int>> adj_mat = {
      {0, 1, 0, 0, 0},
      {1, 0, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 1},
      {0, 0, 0, 1, 0}
  };

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs(n, adj_mat);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0, 1, 2]\n");
}

TEST_CASE("Stack-based DFS with disconnected graph - adjacency list", "[dfs][adjacency_list]") {
  int n = 5;
  std::vector<int> adj_list[5];
  adj_list[0] = {1};
  adj_list[1] = {0, 2};
  adj_list[2] = {1};
  adj_list[3] = {4};
  adj_list[4] = {3};

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs(n, adj_list);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0, 1, 2]\n");
}

TEST_CASE("Stack-based DFS with single node graph - adjacency matrix", "[dfs][adjacency_matrix]") {
  int n = 1;
  std::vector<std::vector<int>> adj_mat = {{0}};

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs(n, adj_mat);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0]\n");
}

TEST_CASE("Stack-based DFS with single node graph - adjacency list", "[dfs][adjacency_list]") {
  int n = 1;
  std::vector<int> adj_list[1];

  std::ostringstream oss;
  std::streambuf* p_cout_streambuf = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());

  dfs(n, adj_list);

  std::cout.rdbuf(p_cout_streambuf);
  REQUIRE(oss.str() == "[0]\n");
}
