#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
using namespace std;
vector<tuple<double, int, int>> points;
vector<tuple<double, int, int>> sorted_points;

double CalculateAngle(int x, int y) {
    if(x==0 && y>0) {
        return 0;
    }
    double degree_maker = 57.2957951;
    //x축을 기준으로 반시계방향은 + 시계는 - 로 재는 atan2(y, x)함수를 y축 기준으로 시계방향으로 가게끔 고치기
    double degree = atan2(y, x)*degree_maker;
    double SMALL_NUM = 1e-6f;
    if(degree > SMALL_NUM && degree-90 <= SMALL_NUM) {
        degree = 90-degree;
    }
    else if(degree-90 > SMALL_NUM) {
        degree = 180-degree+270;
    }
    else if(degree <= SMALL_NUM) {
        degree = -degree+90;
    }
    else {
        cout << "ERROR";
        return -1;
    }
    
    return degree;
}

void Merge(int start, int end) {
    int mid = start + (end-start)/2;
    int i = start;
    int j = mid+1;
    int index = start;
    
    while(i <= mid && j <= end) {
        
        if(get<0>(points[i]) < get<0>(points[j])) {
            sorted_points[index++] = points[i++];
        }
        else if (get<0>(points[i]) > get<0>(points[j])){
            sorted_points[index++] = points[j++];
        }
        //같은 각일때
        else { 
            unsigned long long distance_i = pow(get<1>(points[i]), 2) + pow(get<2>(points[i]), 2);
            unsigned long long distance_j = pow(get<1>(points[j]), 2) + pow(get<2>(points[j]), 2);
            if(distance_i < distance_j) {
                sorted_points[index++] = points[i++];
            }
            else {
                sorted_points[index++] = points[j++];
            }
        }
    }
    
    while(i <= mid) {
        sorted_points[index++] = points[i++];
    }
    while(j <= end) {
        sorted_points[index++] = points[j++];
    }
    
    for(int k=start; k<=end; k++) {
        points[k] = sorted_points[k];
    }
}

void MergeSort(vector<tuple<double, int, int>>& vec, int start, int end) {
    if(start >= end) {
        return;
    }
    
    int mid = start + (end-start)/2;
    
    MergeSort(vec, start, mid);
    MergeSort(vec, mid+1, end);
    Merge(start, end);
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        points = vector<tuple<double, int, int>>();
        sorted_points = vector<tuple<double, int, int>>();
        int N;
        cin >> N;
        for(int i=0; i<N; i++) {
            int x, y;
            cin >> x >> y;
            double angle = CalculateAngle(x, y);
            points.push_back({angle, x, y});
        }
        //정렬
        sorted_points = vector<tuple<double, int, int>>(N+1);
        MergeSort(points, 0, points.size()-1);
        
        for(int i=0; i<N; i++) {
            auto [angle, x, y] = points[i];
            cout << x << ' ' << y << '\n';
        }
        
        cout << '\n';
    }

    return 0;
}
