/* ==============================================================================
   This is an implementation of the disjoint set data structure. In particular,
   it implements the Quick-Union variant, with union by rank and path compression
   optimization.

   @author: Muhammad Fadli Alim Arsani
===============================================================================*/

// TODO:
// - if user optionally passes a graph in the constructor of DisjointSet, then
//   the disjoint set will be initialized with the content of the graph, meaning
//   it will create the vertices and union them as described in the graph. The
//   accepted representation of the graph input is either an adjacency list or
//   an adjacency matrix.
// - for user convenience, the disjoint set will also have a map that tracks,
//   the corresponding node given data. This way, user can call union/find on the
//   data directly, without having to know the node representation.
// - although it is obvious, by definition of a set, duplicate data is not allowed.

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#endif // end of disjointset.h definition
