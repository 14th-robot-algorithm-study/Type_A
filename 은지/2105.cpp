#include <iostream>
#include <cstring>
using namespace std;

int T, N;
int res;
int arr[21][21];
int visited[101];

int dy[4] = { 1, 1, -1, -1 };
int dx[4] = { 1, -1, -1, 1 };

struct Point {
	int y, x;
};

void init() {
	memset(arr, 0, sizeof(arr));
	memset(visited, 0, sizeof(visited));
}

void input() {
	res = -1;
	std::cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cin >> arr[i][j];
		}
	}
}

void dfs(Point np, Point sp, int dir, int sum) {
	if (sum > 0 && np.y == sp.y && np.x == sp.x) {
		res = max(res, sum);
		return;
	}

	np = { np.y + dy[dir], np.x + dx[dir] };

	if (np.y < 0 || np.y >= N || np.x < 0 || np.x >= N) {
		return;
	}

	if (visited[arr[np.y][np.x]]) {
		return;
	}

	visited[arr[np.y][np.x]] = 1;
	if (dir < 3) {
		dfs(np, sp, dir + 1, sum + 1);
	}

	dfs(np, sp, dir, sum + 1);

	visited[arr[np.y][np.x]] = 0;
}

void solve() {
	for (int i = 0; i < N - 1; i++) {
		for (int j = 1; j < N - 1; j++) {
			dfs({ i, j }, { i, j }, 0, 0);
		}
	}
}

int main() {
	std::cin >> T;
	for (int i = 1; i < T + 1; i++) {
		init();
		input();
		solve();
		std::cout << "#" << i << " " << res << '\n';
	}

	return 0;
}
