#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int T, N;
int arr[31][31];
int gas[31][31];
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

struct Edge {
	int y, x;
	int gas;
};

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

		if (gas[now.y][now.x] < now.gas) {
			continue;
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
				continue;
			}

			if (arr[now.y][now.x] < arr[ny][nx]) {
				if (gas[now.y][now.x] + 2 * abs(arr[ny][nx] - arr[now.y][now.x]) >= gas[ny][nx]) {
					continue;
				}
				gas[ny][nx] = gas[now.y][now.x] + 2 * abs(arr[ny][nx] - arr[now.y][now.x]);
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
}

int main() {
	std::cin >> T;

	for (int i = 1; i < T + 1; i++) {
		std::cin >> N;

		init();

		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				std::cin >> arr[j][k];
			}
		}

		dijkstra(0, 0);

		std::cout << "#" << i << " " << gas[N - 1][N - 1] << '\n';

	}
	return 0;
}
