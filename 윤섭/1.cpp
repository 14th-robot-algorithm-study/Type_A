#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Point {
    int y, x, dir, turn;
};

int dy[4] = { 0, 1, 0, -1 }; // 오른쪽, 아래, 왼쪽, 위
int dx[4] = { 1, 0, -1, 0 };

vector<vector<int>> map;
vector<Point> target;
vector<vector<vector<int>>> visited;
Point start;
int N;

int bfs(Point goal) {
    visited.assign(N, vector<vector<int>>(N, vector<int>(4, 1e9)));
    queue<Point> q;
    q.push(start);
    visited[start.y][start.x][start.dir] = start.turn;

    int bestTurn = 1e9;
    int bestDir = start.dir;

    while (!q.empty()) {
        Point cp = q.front(); q.pop();

        if (cp.y == goal.y && cp.x == goal.x) {
            if (cp.turn < bestTurn) {
                bestTurn = cp.turn;
                bestDir = cp.dir;
            }
            continue;
        }

        // 직진 한 칸
        int ny = cp.y + dy[cp.dir];
        int nx = cp.x + dx[cp.dir];
        if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
            if (visited[ny][nx][cp.dir] > cp.turn) {
                visited[ny][nx][cp.dir] = cp.turn;
                q.push({ ny, nx, cp.dir, cp.turn });
            }
        }

        // 우회전 + 전진 한 칸
        int nd = (cp.dir + 1) % 4;
        ny = cp.y + dy[nd];
        nx = cp.x + dx[nd];
        if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
            if (visited[ny][nx][nd] > cp.turn + 1) {
                visited[ny][nx][nd] = cp.turn + 1;
                q.push({ ny, nx, nd, cp.turn + 1 });
            }
        }
    }

    start.dir = bestDir;
    return bestTurn;
}

int main() {
    int T; cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        cin >> N;
        map.assign(N, vector<int>(N, 0));
        target.assign(11, { -1,-1,0,0 });

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
                if (map[i][j] != 0) target[map[i][j]] = { i,j,0,0 };
            }
        }

        int ans = 0;
        start = { 0,0,0,0 };

        for (int i = 1; i <= 10; i++) {
            if (target[i].y == -1) continue;
            int cnt = bfs(target[i]);
            ans += cnt;
            start.y = target[i].y;
            start.x = target[i].x;
            start.turn = 0;
        }

        cout << "#" << tc << " " << ans << "\n";
    }
}
