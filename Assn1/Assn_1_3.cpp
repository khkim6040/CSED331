#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
using namespace std;

int N;
unsigned long long MAX = 18446744073709551615;
vector<int> sorted_vec;

void Merge(vector<int>& vec, int start, int end) {
    int mid = start + (end-start)/2;
    int i = start;
    int j = mid+1;
    int index = start;
    
    while(i <= mid && j <= end) {
        if(vec[i] <= vec[j]) {
            sorted_vec[index++] = vec[i++];
        }
        else {
            sorted_vec[index++] = vec[j++];
        }
    }
    
    while(i <= mid) {
        sorted_vec[index++] = vec[i++];
    }
    while(j <= end) {
        sorted_vec[index++] = vec[j++];
    }
    
    for(int k=start; k<=end; k++) {
        vec[k] = sorted_vec[k];
    }
}

void MergeSort(vector<int>& vec, int start, int end) {
    if(start >= end) {
        return;
    }
    
    int mid = start + (end-start)/2;
    
    MergeSort(vec, start, mid);
    MergeSort(vec, mid+1, end);
    Merge(vec, start, end);
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        
        cin >> N;
        vector<int> vec_x(N);
        vector<int> vec_y(N);
        vector<tuple<int, int>> kingdom(N);
        for(int i=0; i<N; i++) {
            int x, y;
            cin >> x >> y;
            vec_x[i] = x;
            vec_y[i] = y;
            kingdom[i] = {x, y};
        }
        //정렬
        sorted_vec = vector<int>(N);
        MergeSort(vec_x, 0, N-1);
        sorted_vec = vector<int>(N);
        MergeSort(vec_y, 0, N-1);
        //최적값 찾기
        int opt[] = {vec_x[N/2], vec_y[N/2]};
        //최적값과 가장 가까운 도시의 위치 찾기
        unsigned long long min_distance = MAX;
        int opt_city[2];
        for(int i=0; i<N; i++) {
            auto [x, y] = kingdom[i];
            unsigned long long distance = pow(x-opt[0], 2) + pow(y-opt[1], 2);
            if(distance < min_distance) {
                opt_city[0] = x;
                opt_city[1] = y;
                min_distance = distance;
            }
        }
        
        //최소 거리 계산
        unsigned long long sum = 0; 
        for(int i=0; i<N; i++) {
            sum += (abs(vec_x[i] - opt_city[0]) + abs(vec_y[i] - opt_city[1])); 
        }
        
        cout << sum << '\n';
    }

    return 0;
}
