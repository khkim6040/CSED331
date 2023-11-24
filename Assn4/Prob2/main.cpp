#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#define MAX 23372036854775807

using namespace std;
struct Node {
    int index; 
    long long cost;
    int type;
};

vector<vector<Node>> graph;
vector<long long> arrive_time;
int T, N, M;
long long s_, t_;

long long FindMinimumArriveTime() {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    arrive_time.assign(N, MAX);
    arrive_time[0] = 0;
    pq.push({0, 0});

    while(!pq.empty()) {
        int cur = pq.top().second;
        pq.pop();
        for(auto next: graph[cur]) {
            if(next.type == 0) {
                if(arrive_time[next.index] > arrive_time[cur]+next.cost) {
                    arrive_time[next.index] = arrive_time[cur]+next.cost;
                    pq.push({arrive_time[next.index], next.index});
                }
            }
            else {
                if(max(arrive_time[cur], s_) + next.cost > t_) {
                    continue;
                }
                else {
                    if(arrive_time[next.index] > max(arrive_time[cur], s_) + next.cost) {
                        arrive_time[next.index] = max(arrive_time[cur], s_) + next.cost;
                        pq.push({arrive_time[next.index], next.index});
                    }
                }
            }
        }
    }

    if(arrive_time[N-1] == MAX) {
        return -1;
    }
    else {
        return arrive_time[N-1];
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> T;
    while(T--) {
        cin >> N >> M >> s_ >> t_;
        graph.assign(N, vector<Node>());
        for(int i=0; i<M; i++) {
            int start, end, type;
            long long cost;
            cin >> start >> end >> cost >> type;
            graph[start].push_back({end, cost, type});
        }
        cout << FindMinimumArriveTime() << '\n';
    }

    return 0;
}