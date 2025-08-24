#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Point {
	int cost, y, x;
};

struct Compare {
	bool operator()(Point a, Point b) {
		return a.cost > b.cost;
	}
};

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		int N;
		cin >> N;
		vector<vector<int>> map(N, vector<int>(N));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		vector<vector<int>> dist(N, vector<int>(N, 1e9));
		priority_queue<Point, vector<Point>, Compare> pq;

		dist[0][0] = 0;
		pq.push({ 0, 0, 0 });

		while (!pq.empty()) {
			Point cp = pq.top(); pq.pop();
			int fuel = cp.cost, y = cp.y, x = cp.x;

			if (dist[y][x] < fuel) continue;

			for (int dir = 0; dir < 4; dir++) {
				int ny = y + dy[dir];
				int nx = x + dx[dir];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;

				int cost;
				if (map[ny][nx] < map[y][x]) cost = 0;
				else if (map[ny][nx] == map[y][x]) cost = 1;
				else cost = (map[ny][nx] - map[y][x]) * 2;

				int newFuel = fuel + cost;
				if (newFuel < dist[ny][nx]) {
					dist[ny][nx] = newFuel;
					pq.push({ newFuel, ny, nx });
				}
			}
		}

		cout << "#" << tc << " " << dist[N - 1][N - 1] << "\n";
	}

	return 0;
}
