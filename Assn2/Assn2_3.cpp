#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
int pre_x; //Push에 쓰임

struct Line {
    int start;
    int end;
    int height;
};

struct Point{
    int x;
    int y;
    int state; //0 for start, 1 for end
    //1. x 올림차순 2. y 내림차순 3. state 내림차순 순서로 정렬
    bool operator< (const Point &other) {
        if(x!=other.x) {
            return x<other.x;
        }
        else {
            if(y!=other.y) {
                return y>other.y;
            }
            else {
                return state>other.state;
            }
        }
    }
};

void Remove(multiset<int> &set, int target) {
    auto iter = set.find(target);
    set.erase(iter);
}

void Push(vector<Line> &result, multiset<int> &active_set, const Point &p) {
    if(active_set.empty()) {
        pre_x = p.x;
        active_set.insert(p.y);
        return;
    }
    //active_set의 최댓값이 p.y보다 같거나 작다면 선 자르고 result에 넣음
    if(*active_set.rbegin() <= p.y) {
        int height = *active_set.rbegin();
        result.push_back({pre_x, p.x, height});
        pre_x = p.x;
    }
    //이후 point의 state에 따른 set 조정
    //start면 추가
    if(p.state == 0) { 
        active_set.insert(p.y);
    }
    //end면 그 값 삭제
    else { 
        Remove(active_set, p.y);
    }
}

void PrintResult(const vector<Line> result) {
    auto cur = result[0];
    for(int i=1; i<result.size(); i++) {
        if(result[i].height == cur.height && result[i].start == cur.end) {
            cur.end = result[i].end;
        }
        else {
            cout << cur.start << ' ' << cur.end << ' ' << cur.height << '\n';
            cur = result[i];
        }
    }
    //last element
    cout << cur.start << ' ' << cur.end << ' ' << cur.height << '\n';
}

void GenerateTopHull(vector<Point> &points) {
    vector<Line> result; //결과
    multiset<int> active_set; //현재 x = point.x에 들어와있는 line들의 y값. 오름차순으로 자동정렬
    sort(points.begin(), points.end());
    for(const auto& point: points) {
        Push(result, active_set, point);
    }
    PrintResult(result);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int T;
    cin >> T;
    while(T--) {
        //입력
        int N;
        cin >> N;
        vector<Point> points;
        while(N--) {
            int s, e, h;
            cin >> s >> e >> h;
            points.push_back({s, h, 0});
            points.push_back({e, h, 1});
        }
        GenerateTopHull(points);
    }
    return 0;
}