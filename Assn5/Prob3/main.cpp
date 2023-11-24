#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int node1;
    int node2;
    long long length;
    bool operator< (const Edge &other) const {
        return length < other.length;
    }
};

int T, I, P, B;
int root[5555];
bool is_portal[5555];

int getRoot(int node) {
    // Make sure set root to its portal
    if(root[node] != node) {
        root[node] = getRoot(root[node]);
    }
    return root[node];
}

void unionNodes(int a, int b) {
    int root_a = getRoot(a);
    int root_b = getRoot(b);
    // Two nodes are not in portal component
    if(!is_portal[root_a] && !is_portal[root_b]) {
        if(root_a < root_b) {
            root[root_b] = root_a;
        }
        else {
            root[root_a] = root_b;
        }
    }
    // One node is in portal component While other is not
    else if (is_portal[root_a] && !is_portal[root_b]) {
        root[root_b] = root_a;
    }
    // This state will be also used part of getting answer
    else {
        root[root_a] = root_b;
    }

}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    while(T--) {
        fill(is_portal, is_portal+5001, false);
        cin >> I >> P >> B;
        for(int i=0; i<P; i++) {
            int x;
            cin >> x;
            is_portal[x] = true;
        }
        vector<Edge> edges;
        for(int i=0; i<B; i++) {
            int a, b;
            long long c;
            cin >> a >> b >> c;
            edges.push_back({a, b, c});
        }

        // select edge greedy for I - P times
        // which Do Not make any cycle, Do Not connect portal's islands 
        sort(edges.begin(), edges.end());
        for(int i=0; i<I; i++) {
            root[i] = i;
        }
        int connected_components = I;
        for(auto edge: edges) {
            if(connected_components == P) {
                break;
            }
            int a = edge.node1;
            int b = edge.node2;
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            // Have to different root of two nodes And Not Both roots are portal
            if(is_portal[root_a] && is_portal[root_b]) {
                continue;
            }

            if(root_a != root_b) {
                unionNodes(a, b);
                connected_components--;
            }
        }
        // Then, Select expensive edge while unconnected_component goes to 1
        long long answer = 0;
        sort(edges.rbegin(), edges.rend());
        for(auto edge: edges) {
            if(connected_components == 1) {
                break;
            }
            int a = edge.node1;
            int b = edge.node2;
            int root_a = getRoot(a);
            int root_b = getRoot(b);
            if(root_a != root_b) {
                answer += edge.length;
                connected_components--;
                unionNodes(root_a, root_b);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}