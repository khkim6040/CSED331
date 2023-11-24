#include <iostream>
#include <queue>
#include <vector>
#define INF 2222222222222222
using namespace std;

struct Node {
    int index;
    long long cost;
    int type;

    bool operator< (const Node &other) const {
        return cost > other.cost;
    }
};

int T, N, M;
long long S, T_;
vector<vector<Node>> graph;
long long dist[30005];

int main() {
    cin >> T;
    while(T--) {
        cin >> N >> M >> S >> T_;
        graph.assign(N+1, vector<Node>());
        fill(dist, dist+30005, INF);
        for(int i=0; i<M; i++) {
            int s, e, c, t;
            cin >> s >> e >> c >> t;
            graph[s].push_back({e, 1LL*c, t});
        }

        priority_queue<Node> pq;
        pq.push({0, 0, 0});
        while(!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            
            if(cur.index == N-1) {
                break;
            }
            for(auto next: graph[cur.index]) {
                if(cur.cost+next.cost < dist[next.index]) {
                    if(next.type==1 && (max(cur.cost, S)+next.cost >= dist[next.index] || max(cur.cost, S)+next.cost > T_)) {
                        continue;
                    }
                    next.cost = next.type==0 ? next.cost+cur.cost : max(cur.cost, S)+next.cost;
                    dist[next.index] = next.cost;
                    pq.push(next); 
                }
            }
        }
        
        if(dist[N-1]==INF) {
            cout << -1 << '\n';
        }
        else {
            cout << dist[N-1] << '\n';
        }
    }
    return 0;
}