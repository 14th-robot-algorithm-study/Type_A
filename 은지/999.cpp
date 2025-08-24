#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int T, N, M, C;
int arr[31][31];
int gas[31][31];
bool flag;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

struct Edge {
	int y, x;
	int gas;
};

Edge tunnel[31][2];

struct cmp {
	bool operator()(Edge a, Edge b) {
		return a.gas > b.gas;
	}
};

void dijkstra(int sy, int sx) {
	priority_queue <Edge, vector<Edge>, cmp> pq;
	pq.push({ sy, sx, 0 });
	gas[sy][sx] = 0;

	while (!pq.empty()) {
		Edge now = pq.top();
		pq.pop();
		flag = false;

		if (gas[now.y][now.x] < now.gas) {
			continue;
		}

		// 터널 
		for (int i = 0; i < M; i++) {
			if (now.y == tunnel[i][0].y && now.x == tunnel[i][0].x) {
				int ny = tunnel[i][1].y;
				int nx = tunnel[i][1].x;

				if (gas[now.y][now.x] + tunnel[i][1].gas >= gas[ny][nx]) {
					continue;
				}

				gas[ny][nx] = gas[now.y][now.x] + tunnel[i][1].gas;
				pq.push({ ny, nx, gas[ny][nx] });
			}

			else if (now.y == tunnel[i][1].y && now.x == tunnel[i][1].x) {
				int ny = tunnel[i][0].y;
				int nx = tunnel[i][0].x;

				if (gas[now.y][now.x] + tunnel[i][0].gas >= gas[ny][nx]) {
					continue;
				}

				gas[ny][nx] = gas[now.y][now.x] + tunnel[i][0].gas;
				pq.push({ ny, nx, gas[ny][nx] });
			}
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
				continue;
			}

			if (arr[now.y][now.x] < arr[ny][nx]) {
				if (gas[now.y][now.x] + 2 * abs(arr[now.y][now.x] - arr[ny][nx]) >= gas[ny][nx]) {
					continue;
				}
				gas[ny][nx] = gas[now.y][now.x] + 2 * abs(arr[now.y][now.x] - arr[ny][nx]);
				pq.push({ ny, nx, gas[ny][nx] });
			}

			else if (arr[now.y][now.x] == arr[ny][nx]) {
				if (gas[now.y][now.x] + 1 >= gas[ny][nx]) {
					continue;
				}
				gas[ny][nx] = gas[now.y][now.x] + 1;
				pq.push({ ny, nx, gas[ny][nx] });
			}
			else {
				if (gas[now.y][now.x] + 0 >= gas[ny][nx]) {
					continue;
				}
				gas[ny][nx] = gas[now.y][now.x] + 0;
				pq.push({ ny, nx, gas[ny][nx] });
			}
		}
	}
}

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			gas[i][j] = 21e8;
		}
	}

	// 터널 초기화
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 2; j++) {
			tunnel[i][j].y = -1;
			tunnel[i][j].x = -1;
			tunnel[i][j].gas = 21e8;
		}
	}
}

void chktunnel() {
	for (int i = 0; i < M; i++) {
		int ay, ax, by, bx, c;
		std::cin >> ay >> ax >> by >> bx >> c;

		tunnel[i][0].y = ay - 1;
		tunnel[i][0].x = ax - 1;
		tunnel[i][0].gas = c;

		tunnel[i][1].y = by - 1;
		tunnel[i][1].x = bx - 1;
		tunnel[i][1].gas = c;
	}
}

int main() {
	std::cin >> T;
	for (int i = 1; i < T + 1; i++) {
		std::cin >> N >> M;

		init();

		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				std::cin >> arr[j][k];
			}
		}

		chktunnel();

		dijkstra(0, 0);

		std::cout << "#" << i << " " << gas[N - 1][N - 1] << '\n';
	}

	return 0;
}
