#include <iostream>
#include <cstring>
#define MAX 3005
typedef long long ll;
using namespace std;

int N, M, d;


ll mat[MAX][MAX];
ll row_sum[MAX][MAX];
ll col_sum[MAX][MAX];
ll dp[MAX][MAX];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T;
    cin >> T;
    while(T--) {
        memset(mat, 0, sizeof(mat));
        memset(row_sum, 0, sizeof(row_sum));
        memset(col_sum, 0, sizeof(col_sum));
        memset(dp, 0, sizeof(dp));
        cin >> N >> M >> d;
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                cin >> mat[i][j];
            }
        }
        // row_sum
        for(int i=0; i<N; i++) {
            ll slider = 0;
            for(int k=0; k<d; k++) {
                slider += mat[i][k];
            }
            // cout << slider << ' ';
            row_sum[i][0] = slider;
            for(int j=d; j<M; j++) {
                slider -= mat[i][j-d];
                slider += mat[i][j];
                row_sum[i][j-d+1] = slider;
                // cout << slider << ' ';
            }
            // cout << '\n';
        }
        // col_sum
        for(int j=0; j<M; j++) {
            ll slider = 0;
            for(int k=0; k<d; k++) {
                slider += mat[k][j];
                
            }
            // cout << slider << ' ';
            col_sum[0][j] = slider;
            for(int i=d; i<N; i++) {
                slider -= mat[i-d][j];
                slider += mat[i][j];
                col_sum[i-d+1][j] = slider;
                // cout << slider << ' ';
            }
            // cout << '\n';
        }
        // catculate Convolution Matrix
        for(int k=0; k<d; k++) {
            dp[0][0] += row_sum[k][0];
        }        
        for(int i=0; i<N-d+1; i++) {
            if(i>0) {
                dp[i][0] = dp[i-1][0]-row_sum[i-1][0]+row_sum[i+d-1][0];
            }
            for(int j=1; j<M-d+1; j++) {
                dp[i][j] = dp[i][j-1]-col_sum[i][j-1]+col_sum[i][j+d-1];
            }
        }

        for(int i=0; i<N-d+1; i++) {
            for(int j=0; j<M-d+1; j++) {
                cout << dp[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    
    return 0;
}