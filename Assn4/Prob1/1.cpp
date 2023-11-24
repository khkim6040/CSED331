//A delivery driver
#include <iostream>
#include <vector>
#include <queue>
typedef unsigned long long ull;
using namespace std;

vector<vector<int>> DAG; 
vector<vector<int>> reversed_DAG;
bool deliver_spot[2005];
int in_order[2005];

int N, M, S, E, K;

vector<int> TopologicalOrder() {
    vector<int> result;
    queue<int> bfs_queue;
    bfs_queue.push(S);
    result.push_back(S);
    for(int i=0; i<N; i++) {
        if(i==S) {
            continue;
        }
        if(in_order[i]==0) {
            bfs_queue.push(i);
        }
    }
    while(!bfs_queue.empty()) {
        int cur = bfs_queue.front();
        bfs_queue.pop();
        for(auto next: DAG[cur]) {
            in_order[next]--;
            if(in_order[next] == 0) {
                bfs_queue.push(next);
                result.push_back(next);
            }
        }
    }
    // 마지막 노드가 E가 아닐 가능성?
    return result;
}

ull FindNumberOfPath(vector<int> path) {
    vector<int> number_of_path;
    int dp[2005] = {0, };
    int sequence[2005] = {0, };
    int sequence_index = 1;
    dp[path[0]] = 1;
    for(int i: path) {
        sequence[i] = sequence_index;
        for(int pre: reversed_DAG[i]) {
            // 필터링
            if(sequence[i] != sequence[pre]) {
                continue;
            }
            dp[i] = (dp[i] + dp[pre])%20230419;
        }
        // deliver spot인지 check. deliver spot에는 End node도 들어감
        if(deliver_spot[i]) {
            number_of_path.push_back(dp[i]);
            dp[i] = 1;
            sequence[i]++;
            sequence_index++;
        }
    }
    // 모든 deliver_spot을 방문하지 못했다면
    if(number_of_path.size() <= K) {
        return 0;
    }
    // 각 deliver spot까지의 경로 개수 곱함
    ull answer = 1;
    for(ull numbers: number_of_path) {
        answer *= numbers;
        answer %= 20230419;
    }

    return answer;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); 
    int T;
    cin >> T;
    while(T--) {
        cin >> N >> M;
        DAG.assign(N+1, vector<int>());
        reversed_DAG.assign(N+1, vector<int>());
        fill(in_order, in_order+2005, 0);
        for(int i=0; i<M; i++) {
            int start, end;
            cin >> start >> end;
            DAG[start].push_back(end);
            reversed_DAG[end].push_back(start);
            in_order[end]++;
        }
        cin >> S >> E >> K;
        fill(deliver_spot, deliver_spot+2005, false);
        deliver_spot[E] = true;
        for(int i=0; i<K; i++) {
            int x;
            cin >> x;
            deliver_spot[x] = true;
        }
        
        vector<int> path = TopologicalOrder();

        cout << FindNumberOfPath(path) << '\n';
        
    }

    return 0;
}