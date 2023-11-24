#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Line {
    int start;
    int end;
    int height;
};
//height순으로 내림차순 정렬되는 우선순위 큐 => Top Hull 만들 때 사용
struct comp_by_height {
    bool operator()(const Line &a, const Line &b) {
        return a.height < b.height;
    }
};
//start 좌표 순으로 오름차순 정렬되는 우선순위 큐 => 만들어진 TopHull 출력할 때사용
struct comp_by_x {
    bool operator()(const Line &a, const Line &b) {
        return a.start > b.start;
    }
};

void PrintResult(priority_queue<Line, vector<Line>, comp_by_x> &result) {
    Line cur = result.top();
    Line next;
    while(!result.empty()) {
        result.pop();
        next = result.top();
        //두 line이 이어질 때 처리
        if(cur.height == next.height && cur.end == next.start) {
            cur.end = next.end;
            continue;
        }
        cout << cur.start << ' ' << cur.end << ' ' << cur.height << '\n';
        cur = next;
    }
}

void GenerateTopHull() {
    priority_queue<Line, vector<Line>, comp_by_height> lines; //TopHull 만들기 위한 우선순위 큐
    priority_queue<Line, vector<Line>, comp_by_x> result; //결과
    unordered_map<int, bool> overlap_checker; //line의 start 정보를 담고있다. line끼리 겹치는지 확인하기 위해 사용
    //입력
    int num;
    cin >> num;
    while(num--) {
        int s, e, h;
        cin >> s >> e >> h;
        Line line = {s, e, h};
        lines.push(line);
    }
    //Top Hull 구성
    int size = lines.size();
    for(int i=0; i<size; i++) {
        Line cur = lines.top();
        lines.pop();
        int start_position = cur.start;
        int end_position = start_position;
        for(int j=cur.start; j<cur.end; j++) {
            //x=j에 line 이미 있는지 확인
            //해당 지점에 line이 없다면
            if(!overlap_checker[j]) {
                overlap_checker[j] = true;
                end_position = j+1;
            }
            //line이 존재한다면 지금 line 잘라야됨
            else {
                //길이가 1 이상이라면 result에 저장하고 자름
                if(end_position != start_position) {
                    Line line = {start_position, end_position, cur.height};
                    result.push(line);
                }
                //line 자른 효과
                start_position = end_position = j+1;
            }
        }
        //해당 line의 끝 부분 확인후 넣기
        if(end_position != start_position) {
            Line line = {start_position, end_position, cur.height};
            result.push(line);
        }
    }
    //결과 출력
    PrintResult(result);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        GenerateTopHull();
    }
    return 0;
}