#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <tuple>
#include <memory.h>
using namespace std;

int N, M;
long long available_speed[1001][1001];
unordered_map<long long, bool> speed_map;
vector<long long> speed_vec;
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

//stack을 이용해서 speed_limit로 고정된 속력으로 (N, M)까지 갈 수 있는지 확인
bool DFS(const long long &speed_limit) {
    if(available_speed[1][1] < speed_limit) {
        return false;
    }
    stack<tuple<long long, long long>> DFS_stack;
    bool visited[1001][1001];
    memset(visited, false, sizeof(visited));
    DFS_stack.push({1, 1});
    visited[1][1] = true;
    while(!DFS_stack.empty()) {
        auto [y, x] = DFS_stack.top();
        if(y==N && x==M) {
            return true;
        }
        DFS_stack.pop();
        visited[y][x] = true;
        for(int i=0; i<4; i++) {
            int next_y = y + dy[i];
            int next_x = x + dx[i];
            if(!visited[next_y][next_x] && available_speed[next_y][next_x] >= speed_limit 
            && next_y>=1 && next_x>=1 && next_y<=N && next_x<=M) {
                DFS_stack.push({next_y, next_x});
            }
        }
    }
    return false;
}

//이분 탐색으로 가능한 가장 높은 속도 찾기
long long BinarySearchForMaxSpeed(int start, int end) {
    int mid = (start+end)/2;
    long long mid_speed = speed_vec[mid];
    
    if(DFS(mid_speed)) {
        if(start==end) {
            return mid_speed;
        }
        else {
            if(start+1 == end) {
                return BinarySearchForMaxSpeed(mid+1, end);
            }
            else {
                return BinarySearchForMaxSpeed(mid, end);
            }
        }
    }
    else {
        if(start==end) {
            return speed_vec[start-1];
        }
        else {
            return BinarySearchForMaxSpeed(start, mid-1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int T;
    cin >> T;
    while(T--) {
        //input
        cin >> N >> M;
        //자료구조들 초기화
        speed_map = unordered_map<long long, bool>();
        speed_vec = vector<long long>();
        for(int i=1; i<=N; i++) {
            for(int j=1; j<=M; j++) {
                long long speed;
                cin >> speed;
                available_speed[i][j] = speed;
                //speed가 map에 없다면 추가해주고 speed_vec에도 추가
                if(!speed_map[speed]) {
                    speed_map[speed] = true;
                    speed_vec.push_back(speed);
                }
            }
        }
        //가능한 speed 오름차순 정렬
        sort(speed_vec.begin(), speed_vec.end());
        cout << BinarySearchForMaxSpeed(0, speed_vec.size()-1) << '\n';
    }
    return 0;
}