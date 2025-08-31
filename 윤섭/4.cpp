#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct Point {
	int y, x;
};

int dy[2][6] = {
	{-1, -1, 0, 1, 0, -1}, 
	{-1, 0, 1, 1, 1, 0}
};

int dx[2][6] = {
	{0, 1, 1, 0, -1, -1},
	{0, 1, 1, 0, -1, -1}
};

int T;
int N, M;
int map[15][15];
int visited[15][15];
int ans;

void dfs(int lev, Point cp, int sum) {
	if (lev == 4) {
		ans = max(ans, sum);
		return;
	}

	for (int dir = 0; dir < 6; dir++) {
		Point np = { cp.y + dy[cp.x % 2][dir], cp.x + dx[cp.x % 2][dir] };

		if (np.y < 0 || np.y >= N || np.x < 0 || np.x >= M) continue;
		if (visited[np.y][np.x] == 1) continue;

		visited[np.y][np.x] = 1;
		dfs(lev + 1, np, sum + map[np.y][np.x]);
		visited[np.y][np.x] = 0;
	}
}

void triangle(Point cp) {
	int sum = map[cp.y][cp.x];

	for (int dir = 0; dir < 3; dir++) {
		Point np = { cp.y + dy[cp.x % 2][2 * dir], cp.x + dx[cp.x % 2][2 * dir] };
		if (np.y < 0 || np.x < 0 || np.y >= N || np.x >= M) return;
		sum += map[np.y][np.x];
	}
	ans = max(sum, ans);
}


void inverted_triangle(Point cp) {
	int sum = map[cp.y][cp.x];

	for (int dir = 0; dir < 3; dir++) {
		Point np = { cp.y + dy[cp.x % 2][2 * dir + 1], cp.x + dx[cp.x % 2][2 * dir + 1] };
		if (np.y < 0 || np.x < 0 || np.y >= N || np.x >= M) return;
		sum += map[np.y][np.x];
	}
	ans = max(sum, ans);
}

int main() {
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M;

		memset(map, 0, sizeof(map));
		memset(visited, 0, sizeof(visited));
		ans = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				visited[i][j] = 1;
				dfs(1, { i,j }, map[i][j]);
				visited[i][j] = 0;
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				triangle({ i, j });
				inverted_triangle({ i, j });
			}
		}
		cout << "#" << tc << " " << ans << "\n";
	}
}
