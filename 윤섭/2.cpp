#include <iostream>
#include <cstring>
using namespace std;

int N;
int ans;
int map[50][50];
struct Point {
    int y, x;
};
int dy[4] = { -1, 1, 0, 0 }; // 상, 하, 좌, 우
int dx[4] = { 0, 0, -1, 1 };
Point start;
int visited[50][50];

void dfs(int lev, Point st) {
    if (lev == 3) {
        return;
    }

    for (int dir = 0; dir < 4; dir++) {
        Point np = { st.y, st.x };
        int jumpFlag = 0;

        // 한 방향으로 이동
        while (true) {
            np.y += dy[dir];
            np.x += dx[dir];

            // 범위 밖이면 종료
            if (np.y < 0 || np.y >= N || np.x < 0 || np.x >= N) break;

            // 처음으로 쫄을 만나면 점프 활성화
            if (map[np.y][np.x] == 1 && jumpFlag == 0) {
                jumpFlag = 1;
                continue;
            }



            if (jumpFlag == 1) {
                if (map[np.y][np.x] == 1) {
                    visited[np.y][np.x] = 0;
                    map[np.y][np.x] = 0;
                    dfs(lev + 1, { np.y, np.x });
                    map[np.y][np.x] = 1;
                    break;  // 두개 이상 뛰어넘을 수 없음
                }

                else if (map[np.y][np.x] == 0) {
                    dfs(lev + 1, { np.y, np.x });
                }
            }
        }
    }

}

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        ans = 0;
        cin >> N;

        memset(map, 0, sizeof(map));
        memset(visited, 0, sizeof(visited));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
                visited[i][j] = map[i][j];

                if (map[i][j] == 2) {
                    start.y = i;
                    start.x = j;
                    map[i][j] = 0;
                    visited[i][j] = 0;
                }
            }
        }

        dfs(0, start);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (map[i][j] != visited[i][j]) ans++;
            }
        }

        cout << "#" << tc << " " << ans << "\n";
    }
}
