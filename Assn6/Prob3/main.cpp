#include <iostream>
#include <vector>
using namespace std;
using vvc = vector<vector<char>>;
#define MAX 15
int N, M;
vvc board;
int min_count = MAX;

void rotate(vvc &board) {
    vvc old = board;
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            board[i][j] = old[N-1-j][i];
        }
    }
}

void findOriginalPos(const vvc &board, int &red_y, int &red_x, int &blue_y, int &blue_x) {
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(board[i][j]=='R') {
                red_y = i; red_x = j;
            }
            else if(board[i][j]=='B') {
                blue_y = i; blue_x = j;
            }
        }
    }
}

vvc push(vvc board, int &res) {
    int red_y, red_x, blue_y, blue_x;
    findOriginalPos(board, red_y, red_x, blue_y, blue_x);
    int red = red_y;
    int blue = blue_y;
    bool blue_in_hole = false;
    bool red_in_hole = false;
    // 다른 구슬 고려하지 않고 각각 이동할 수 있는만큼 이동함
    while(true) {
        blue--;
        if(board[blue][blue_x]=='O') {
            blue_in_hole = true;
            break;
        }
        else if(board[blue][blue_x]=='#') {
            blue++;
            break;
        }
    }
    while(true) {
        red--;
        if(board[red][red_x]=='O') {
            red_in_hole = true;
            break;
        }
        else if(board[red][red_x]=='#') {
            red++;
            break;
        }
    }

    if(blue_in_hole) {
        res = -1;
        return board;
    }
    else if(red_in_hole) {
        res = 1;
        return board;
    }
    else {
        // 이동 후 겹치는 경우, 출발 지점에 따라 고려
        if(red_x==blue_x && red==blue) {
            if(red_y < blue_y) {
                blue_y++;
            }
            else {
                red_y++;
            }
        }
        board[red][red_x] = 'R';
        board[blue][blue_x] = 'B';
        board[red_y][red_x] = '.';
        board[blue_y][blue_x] = '.';
        res = 0;
        return board;
    }
}

void backTrack(vvc board, const int &depth) {
    if(depth==10) {
        return;
    }

    for(int i=0; i<4; i++) {
        rotate(board);
        int res;
        vvc new_board = push(board, res);
        if(res==1) {
            min_count = min(min_count, depth+1);
            continue;
        }
        else if(res==0) {
            backTrack(new_board, depth+1);
        }
    }
    
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    board.assign(N, vector<char>());
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            char x;
            cin >> x;
            board[i].push_back(x);
        }
    }

    backTrack(board, 0);

    if(min_count==MAX) {
        cout << -1;
    }
    else {
        cout << min_count;
    }
    return 0;
}