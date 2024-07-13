// SPFA (Shortest Path Faster Algorithm) is an improvement of Bellman-Ford algorithm.
// At the worst case, you need N-1 iterations to find the shortest path from a source to all other vertices.
// We can prove that this is because the number of iterations depends on the order of how we
// relax the edges. If we relax the edges in a different order, we might need less iterations.
// The idea of SPFA is to use a queue to store the vertices that need to be relaxed.
