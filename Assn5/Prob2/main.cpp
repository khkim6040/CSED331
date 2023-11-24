#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct City {
    long long left;
    long long right;
    long long height;
    bool operator< (const City &other) const {
        return left < other.left;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    // left 오름차순 정렬
    // 한개씩 돌면서(=cur)
        // top의 높이보다 크다면 cur 넣음
        // top의 높이보다 작다면 top의 넓이 구한 후 pop후 cur 넣음
        // 같다면 pop후 right 늘여서 다시 넣음
    // 마지막까지 넣고난 뒤 
    // top 빼놓고 그 다음 top(=cur)이랑 비교
        // cur이 없다면 즉, top이 마지막 요소라면 top.height*w
        // top이 cur보다 크다면 (w-cur.right)*top.height
        // top이 cur보다 작다면 w*top.height 하고 w = top.left로 바꿈
        // 같다면 아무것도 안함
        // top = cur, pop 후 새로운 top(=cur)과 비교
    int T;
    cin >> T;
    while(T--) {
        long long N, W;
        cin >> N >> W;
        vector<City> cities;
        for(int i=0; i<N; i++) {
            long long l, r, h;
            cin >> l >> r >> h;
            cities.push_back({l, r, h});
        }
        sort(cities.begin(), cities.end());

        stack<City> city_stack;
        long long max_space = 0;
        city_stack.push(cities[0]);
        for(int i=1; i<N; i++) {
            City cur = cities[i];
            if(cur.height > city_stack.top().height) {
                city_stack.push(cur);
            }
            else if(cur.height < city_stack.top().height) {
                while(!city_stack.empty() && cur.height < city_stack.top().height) {
                    long long space = (cur.left - city_stack.top().left)*city_stack.top().height;
                    max_space = max(max_space, space);
                    city_stack.pop();
                }
                cur.left = city_stack.empty() ? 0 : city_stack.top().right;
                city_stack.push(cur);
            }
            else {
                City new_city = {city_stack.top().left, cur.right, cur.height};
                city_stack.pop();
                city_stack.push(new_city);
            }
        }

        City top = city_stack.top();
        city_stack.pop();
        while(!city_stack.empty()) {
            City cur = city_stack.top();
            if(top.height > cur.height) {
                long long space = (W-cur.right)*top.height;
                max_space = max(max_space, space);
            }
            else if(top.height < cur.height) {
                long long space = W*top.height;
                W = top.left;
                max_space = max(max_space, space);
            }
            top = cur;
            city_stack.pop();
        }
        long long space = top.height*W;
        max_space = max(max_space, space);

        cout << max_space << '\n';
    }

    return 0;
}