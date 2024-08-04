// This astar implementation is purposely implemented in such
// a way that makes it easier for the reader to see how it is
// just a modified dijkstra algorihtm with the addition
// of a heuristic function and a goal node given a starting node.
// see algorihtms/graph/dijkstra.cpp to compare the two.

// In dijkstra, the second element in each pair in the priority queue
// is just the distance from the start node to that node, so
// {x, d} means the distance from start to x is d.

// In A*, the second element in each pair in the priority queue has
// and added information called the heuristic, which is the distance
// from that node to the goal, auto solution = Solution();
// {x, dh} means the distance from start to x + distance from x to goal
// where dh = dists[x] + heuristic(x, goal)

#include "bits/stdc++.h"

using namespace std;

vector<int> astar(int n, vector<vector<int>> g[], int s, int goal,
                  vector<int> heuristic) {
    vector<int> dists(n, INT_MAX);
    dists[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>> pq;
    pq.push({s, heuristic[s]});

    while (!pq.empty()) {
        pair<int, int> curr = pq.top();
        int node = curr.first;
        int dist = dists[node];
        pq.pop();

        if (node == goal) {
            break; // Stop if we've reached the goal
        }

        for (const auto &p : g[node]) {
            int nbr = p[0];
            int weight = p[1];

            if (dist + weight < dists[nbr]) {
                dists[nbr] = dist + weight;
                pq.push({nbr, dists[nbr] + heuristic[nbr]});
            }
        }
    }

    return dists;
}

int heuristic(int node, int goal) {
    // This example uses a simple Euclidean distance for the heuristic.
    // The actual implementation would depend on the specific problem.
    return abs(goal - node);
}
