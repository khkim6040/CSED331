#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Class {
    int start;
    int end;
    bool operator< (const Class &other) const {
        if(end == other.end) {
            return start < other.start;
        }
        return end < other.end;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<Class> classes;
        for(int i=0; i<N; i++) {
            int s, e;
            cin >> s >> e;
            classes.push_back({s, e});
        }
        sort(classes.begin(), classes.end());

        int count = 1;
        int cur_end = classes[0].end;
        for(int i=1; i<N; i++) {
            if(classes[i].start >= cur_end) {
                count++;
                cur_end = classes[i].end;
            }
        }
        
        cout << count << '\n';
    }

    return 0;
}
