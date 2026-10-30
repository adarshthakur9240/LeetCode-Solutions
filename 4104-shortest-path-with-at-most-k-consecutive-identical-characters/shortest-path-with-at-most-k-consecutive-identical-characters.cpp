class Solution {
public:
    struct Node {
        int dist;
        int id;
        int run;
        int last;

        bool operator>(const Node& other) const {
            return dist > other.dist;
        }
    };

    static long long encode(int node, int run, int last) {
        return ((long long)node << 16) |
               ((long long)run << 8) |
               last;
    }

    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {

        vector<vector<pair<int,int>>> g(n);

        for (auto &e : edges) {
            g[e[0]].push_back({e[1], e[2]});
        }

        unordered_map<long long, int> dist;
        dist.reserve(edges.size() * 4);

        priority_queue<Node,
                       vector<Node>,
                       greater<Node>> pq;

        int startChar = labels[0] - 'a';

        long long startKey = encode(0, 1, startChar);

        dist[startKey] = 0;

        pq.push({0, 0, 1, startChar});

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            long long curKey =
                encode(cur.id, cur.run, cur.last);

            auto it = dist.find(curKey);

            if (it == dist.end() || it->second != cur.dist)
                continue;

            for (auto &[v, w] : g[cur.id]) {

                int chr = labels[v] - 'a';

                int nextRun;

                if (chr == cur.last) {
                    nextRun = cur.run + 1;

                    if (nextRun > k)
                        continue;
                } else {
                    nextRun = 1;
                }

                int nd = cur.dist + w;

                long long nxtKey =
                    encode(v, nextRun, chr);

                auto jt = dist.find(nxtKey);

                if (jt == dist.end() || nd < jt->second) {
                    dist[nxtKey] = nd;
                    pq.push({
                        nd,
                        v,
                        nextRun,
                        chr
                    });
                }
            }
        }

        int ans = INT_MAX;

        for (int run = 1; run <= k; run++) {
            for (int c = 0; c < 26; c++) {
                auto it =
                    dist.find(
                        encode(n - 1, run, c)
                    );

                if (it != dist.end()) {
                    ans = min(ans, it->second);
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};