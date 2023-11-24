#include <iostream>
#include <vector>
#include <set>
#include <algorithm> //min()
#include <memory.h> //memset()
using namespace std;
struct Node {
    int index;
    int length;
};

//인접 리스트로 그래프 구성
vector<vector<Node>> graph;
//단절선 노드와 길이 담는 set 만들기 -> 한 개 이상이면 가장 작은 값(첫 번째 값) 출력, 아무것도 없다면 -1 출력
set<int> cut_edges;
//방문 확인 bool visited 배열
bool visited[30001];
//언제 방문됐는지 -> elapsed_time 이용 int discovered_time 배열
int discovered_time[30001];
int T, N, M;

int DFS(int cur, int parent, int length, int elapsed_time) {
    //처음엔 min, discovered[cur] 모두 time으로 저장
    int min_time = elapsed_time;
    discovered_time[cur] = elapsed_time;
    visited[cur] = true;
    //cur과 연결된 노드 모두 돌면서
    for(auto next: graph[cur]) {
        //부모 노드라면 continue
        if(next.index == parent) {
            continue;
        }
        //방문안했다면 elapsed_time 1 늘리고 해당 노드 DFS 후 그 결과를 지금 방문 차례(=discovered_time[cur])와 비교해서 더 크다면 우회 edge없는 것이므로 단절선임
        if(!visited[next.index]) {
            int next_time = DFS(next.index, cur, next.length, elapsed_time+1);
            if(discovered_time[cur] < next_time) {
                cut_edges.insert(next.length);
            }
            //작다면 그 값으로 업데이트
            min_time = min(min_time, next_time);
        }
        //방문했다면 min_time = min(min, discovered[연결된 노드])으로 업데이트
        else {
            min_time = min(min_time, discovered_time[next.index]);
        }
    }

    return min_time;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    //인접 리스트로 그래프 구성
    cin >> T;
    while(T--) {
        cin >> N >> M;
        //전역변수 초기화
        graph = vector<vector<Node>>();
        graph.assign(N, vector<Node>());
        cut_edges = set<int>();
        memset(visited, false, sizeof(visited));
        memset(discovered_time, 0, sizeof(discovered_time));
        //undirected graph 구성
        for(int i=0; i<M; i++) {
            int start, end, length;
            cin >> start >> end >> length;
            graph[start].push_back({end, length});
            graph[end].push_back({start, length});
        }
        //연결 그래프니까 어디서 시작하건 상관 X
        DFS(0, -1, 0, 1);
        //출력
        if(cut_edges.empty()) {
            cout << -1;
        }
        else {
            cout << *cut_edges.begin();
        }
        cout << '\n';
    }

    return 0;
}