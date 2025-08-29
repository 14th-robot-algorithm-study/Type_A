#include <algorithm>
#include <iostream>
#include <set>
using namespace std;


struct Point {
	int y, x;
	int gauge;
};


int N, M;
Point sp;
int min_val;
int arr[51][51];
set <int> gauge_set;
int visited[51][51];
int best_val[51][51];

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };


void dfs(Point np, int max_gauge) {
	// [1-가지치기] gauge가 클 경우 
	if (min_val <= max_gauge) {
		return;
	}
	// 바닥일 경우 
	if (arr[np.y][np.x] == 1 || arr[np.y][np.x] == 2 || arr[np.y][np.x] == 3) {
		if (max_gauge < np.gauge) {
			max_gauge = np.gauge;
		}
		np.gauge = 0;
	}

	// 보석을 발견했을 경우 
	if (arr[np.y][np.x] == 3) {
		min_val = min(min_val, max_gauge);
		return;
	}

	// [2-가지치기] 최악의 경로를 발견했을 경우 
	if (best_val[np.y][np.x] <= max_gauge) {
		return;
	}
	else {
		best_val[np.y][np.x] = max_gauge;
	}


	for (int i = 0; i < 4; i++) {
		int ny = np.y;
		int nx = np.x;

		// [1] 상/하 
		if (i == 0 || i == 1) {
			int steps = 0;

			while (1) {
				ny += dy[i];
				nx += dx[i];
				// [1-1] 벽 체크 
				if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
					break;
				}

				// [1-2] 방문 체크 
				if (visited[ny][nx]) {
					break;
				}

				// [1-3] 점프 계산
				if (arr[ny][nx] == 0) {
					steps++;
					continue;
				}

				// [1-4] gauge가 클 경우 
				if (max(np.gauge + steps + 1, max_gauge) >= min_val) {
					break;
				}

				visited[ny][nx] = 1;
				dfs({ ny, nx, np.gauge + steps + 1 }, max_gauge);
				visited[ny][nx] = 0;
				break;
			}
		}

		// [2] 좌/우 
		else {
			ny += dy[i];
			nx += dx[i];

			// [2-1] 벽 체크 
			if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
				continue;
			}
			// [2-2] 좌/우 바닥 체크 
			if ((i == 2 || i == 3) && arr[ny][nx] == 0) {
				continue;
			}

			// [2-3] 방문 체크 
			if (visited[ny][nx]) {
				continue;
			}

			visited[ny][nx] = 1;
			dfs({ ny, nx, np.gauge }, max_gauge);
			visited[ny][nx] = 0;
		}
	}
}


void init() {
	min_val = 21e8;
	std::cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cin >> arr[i][j];
			if (arr[i][j] == 2) {
				sp.y = i;
				sp.x = j;
				sp.gauge = 0;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			best_val[i][j] = 21e8;
		}
	}
}


int main() {
	init();
	dfs(sp, 0);
	std::cout << min_val;
	return 0;
}
