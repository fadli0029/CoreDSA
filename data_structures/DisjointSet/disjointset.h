/* ==============================================================================
   This is an implementation of the disjoint set data structure. In particular,
   it implements the Quick-Union variant, with union by rank and path compression
   optimization.

   @author: Muhammad Fadli Alim Arsani
===============================================================================*/

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

class DisjointSet {
  public:
    DisjointSet(int size) {
      root.resize(size);
      rank.resize(size);

      for (int i=0; i<size; i++) {
        root[i] = i;
        rank[i] = 1;
      }
    }

    int find(int i) {
      if (i == root[i]) {
        return i;
      }

      return root[i] = find(root[i]);
    }

    void merge(int i, int j) {
      int root_i = find(i);
      int root_j = find(j);

      if (root_i != root_j) {
        if (rank[root_i] > rank[root_j]) {
          root[root_j] = root_i;
        }
        else if (rank[root_i] < rank[root_j]) {
          root[root_i] = root_j;
        }
        else {
          root[root_j] = root_i;
          rank[root_i]++;
        }
      }
    }

    bool connected(int i, int j) {
      return find(i) == find(j);
    }

  private:
    std::vector<int> root;
    std::vector<int> rank;
};

#endif // end of disjointset.h definition
