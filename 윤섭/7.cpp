#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

struct Point {
	int y, x, cost;
};

struct compare {
	bool operator()(Point a, Point b) {
		return a.cost > b.cost;
	}
};

int N, M;
int map[50][50];
int limit[50][50];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

Point snowman;
Point diamond;

void dijkstra(Point start, Point target) {
	priority_queue<Point, vector<Point>, compare> pq;
	pq.push(start);
	limit[start.y][start.x] = 0;

	while (!pq.empty()) {
		Point cp = pq.top();
		pq.pop();

		if (cp.cost > limit[cp.y][cp.x]) continue;
		if (cp.y == target.y && cp.x == target.x) {
			snowman.cost = cp.cost;
			return;
		}

		for (int dir = 0; dir < 4; dir++) {
			int ny = cp.y + dy[dir];
			int nx = cp.x + dx[dir];
			if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;

			/*     좌우 이동     */
			if (dir == 2 || dir == 3) {
				if (map[ny][nx] == 0) continue;
				int next_cost = cp.cost;
				if (next_cost < limit[ny][nx]) {
					limit[ny][nx] = next_cost;
					pq.push({ ny, nx, next_cost });
				}
			}

			/*     상하 이동     */
			else {
				int jump = 1;
				int ty = ny;
				int tx = nx;
				while (ty >= 0 && ty < N && tx >= 0 && tx < M && map[ty][tx] == 0) {
					jump++;
					ty += dy[dir];
					tx += dx[dir];
				}
				if (ty < 0 || ty >= N || tx < 0 || tx >= M) continue;
				int next_cost = max(cp.cost, jump);
				if (next_cost < limit[ty][tx]) {
					limit[ty][tx] = next_cost;
					pq.push({ ty, tx, next_cost });
				}
			}
		}
	}
}

int main() {
	cin >> N >> M;
	memset(map, 0, sizeof(map));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			limit[i][j] = 21e8;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) snowman = { i, j, 0 };
			else if (map[i][j] == 3) diamond = { i, j, 0 };
		}
	}

	dijkstra(snowman, diamond);

	cout << snowman.cost;
}
