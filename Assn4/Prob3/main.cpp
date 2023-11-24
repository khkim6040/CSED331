// 다익스트라. start->V 까지 최단거리, end->V 까지 최단거리 리스트 두 개 작성
// 모든 node A에 연결된 edge 돌면서 start->A, A->B, B->end 의 경로에서 A->B만큼을 뺐을 때 최솟값 저장
#include <iostream>
#include <vector>
#include <queue>
#define MAX 3372036854775807
using namespace std;

struct Node {
    int index;
    long long cost;
    bool operator< (const Node &other) const {
        return cost > other.cost;
    }
};

int T, N, M;
vector<long long> result;

// type에 따라 start, end 시작 바뀜
vector<long long> FindMinDistList(int type, vector<vector<Node>> graph) {
    priority_queue<Node> pq;
    result.assign(N, MAX);
    if(type == 0) {
        pq.push({0, 0});
        result[0] = 0;
    }
    else {
        pq.push({N-1, 0});
        result[N-1] = 0;
    }
    
    while(!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        for(auto next: graph[cur.index]) {
            if(result[next.index] > result[cur.index] + next.cost) {
                result[next.index] = result[cur.index] + next.cost;
                pq.push({next.index, result[next.index]});
            }
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    // DFS마다 min_dist = min(min_dist, 경로 금액-최대 edge)로 비교
     cin >> T;
     while(T--) {
        cin >> N >> M;
        vector<vector<Node>> graph(N);
        vector<vector<Node>> reversed_graph(N);
        // graph.assign(N, vector<Node>());
        // reversed_graph.assign(N, vector<Node>());
        for(int i=0; i<M; i++) {
            int start, end;
            long long cost;
            cin >> start >> end >> cost;
            graph[start].push_back({end, cost});
            reversed_graph[end].push_back({start, cost});
        }
        // 시작점 0 부터 다른 점까지 최단거리 리스트 작성
        vector<long long> dist_from_start = FindMinDistList(0, graph); 
        vector<long long> dist_from_end = FindMinDistList(1, reversed_graph);

        long long min_dist;
        if(dist_from_start[N-1] == MAX) {
            min_dist = -1;
        }
        else {
            min_dist = MAX;
            for(int cur=0; cur<N; cur++) {
                long long start_to_cur = dist_from_start[cur];
                for(auto next: graph[cur]) {
                    long long next_to_end = dist_from_end[next.index];
                    min_dist = min(min_dist, start_to_cur+next_to_end);
                }
            }

        }
        cout << min_dist << '\n';
     }

    return 0;
}