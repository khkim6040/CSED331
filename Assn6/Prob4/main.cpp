#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, K;
struct Node {
    int index;
    int cost;
};

vector<vector<Node>> graph;
queue<Node> q;
priority_queue<int> kth_path[1005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> K;
    graph.assign(N+1, vector<Node>());
    for(int i=0; i<M; i++) {
        int s, e, c;
        cin >> s >> e >> c;
        graph[s].push_back({e, c});
    }

    kth_path[1].push(0);
    q.push({1, 0});
    while(!q.empty()) {
        Node cur = q.front();
        q.pop();
        for(auto next: graph[cur.index]) {
            next.cost = next.cost+cur.cost;
            if(kth_path[next.index].size() < K) {
                kth_path[next.index].push(next.cost);
                q.push(next);
            }
            else if(kth_path[next.index].top() > next.cost) {
                kth_path[next.index].pop();
                kth_path[next.index].push(next.cost);
                q.push(next);
            }
        }
    }

    for(int i=1; i<=N; i++) {
        if(kth_path[i].size()!=K) {
            cout << -1 << '\n';
        }
        else {
            cout << kth_path[i].top() << '\n';
        }
    }
    return 0;
}