#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct Edge {
        int to;
        int weight;
    };

    int shortestPath(
        int n,
        vector<vector<int>>& edges,
        string labels,
        int k
    ) {
        vector<vector<Edge>> graph(n);

        for (const auto& edge : edges) {
            graph[edge[0]].push_back({edge[1], edge[2]});
        }

        using State = tuple<long long, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq;

        // Use a flat array to reduce vector overhead and memory fragmentation.
        const long long INF = LLONG_MAX;
        vector<long long> dist(static_cast<size_t>(n) * (k + 1), INF);

        auto id = [k](int node, int runLength) -> size_t {
            return static_cast<size_t>(node) * (k + 1) + runLength;
        };

        dist[id(0, 1)] = 0;
        pq.emplace(0LL, 0, 1);

        while (!pq.empty()) {
            auto [currentDistance, node, runLength] = pq.top();
            pq.pop();

            if (currentDistance != dist[id(node, runLength)]) {
                continue;
            }

            if (node == n - 1) {
                return static_cast<int>(currentDistance);
            }

            for (const auto& edge : graph[node]) {
                int nextNode = edge.to;

                int nextRunLength =
                    labels[node] == labels[nextNode]
                        ? runLength + 1
                        : 1;

                if (nextRunLength > k) {
                    continue;
                }

                long long nextDistance =
                    currentDistance + edge.weight;

                size_t nextState = id(nextNode, nextRunLength);

                if (nextDistance < dist[nextState]) {
                    dist[nextState] = nextDistance;
                    pq.emplace(nextDistance, nextNode, nextRunLength);
                }
            }
        }

        return -1;
    }
};
