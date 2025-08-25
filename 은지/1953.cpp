#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int cnt;
int T, N, M;
int R, C, L;
int arr[51][51];
int visited[51][51];

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

struct Edge {
	int y, x;
};


int pipe[8][4] = {
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{1, 1, 0, 0},
	{0, 0, 1, 1},
	{1, 0, 0, 1},
	{0, 1, 0, 1},
	{0, 1, 1, 0},
	{1, 0, 1, 0}
};


void init() {
	std::cin >> N >> M >> R >> C >> L;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			std::cin >> arr[i][j];
		}
	}

	memset(visited, 0, sizeof(visited));
	cnt = 0;
}


void bfs(Edge st) {
	queue <Edge> q;
	q.push(st);
	visited[st.y][st.x] = 1;


	while (!q.empty()) {
		Edge now = q.front();
		q.pop();

		if (visited[now.y][now.x] > L) {
			continue;
		}

		cnt++;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			// [1] 벽 확인
			if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
				continue;
			}

			// [2] 방문 확인
			if (visited[ny][nx]) {
				continue;
			}

			// [3] 다음 pipe 확인 
			if (arr[ny][nx] == 0) {
				continue;
			}

			// [4] 현재 pipe 확인 
			int curpipe = arr[now.y][now.x];
			if (pipe[curpipe][i] == 0) {
				continue;
			}

			// [4] 다음 pipe			
			int nextPipe = arr[ny][nx];
			int nextDir;

			if (i % 2 == 0) {
				nextDir = i + 1;
			}
			else {
				nextDir = i - 1;
			}

			// [5] 다음 pipe 확인
			if (pipe[nextPipe][nextDir] == 0) {
				continue;
			}

			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });

		}
	}
}


int main() {
	std::cin >> T;
	for (int i = 1; i < T + 1; i++) {
		init();
		bfs({ R, C });
		std::cout << "#" << i << " " << cnt << '\n';
	}

	return 0;
}
