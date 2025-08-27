#include <algorithm>
#include <iostream>
#include <queue>
using namespace std; 


struct Edge {
	int y, x;
	int dir;
	int cnt;
};

int val;
int T, N;
Edge st_p;
int min_val;
int num_cnt;
int total_cnt;
int arr[51][51];

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };


void init() {
	val = 1;
	num_cnt = 0;
	total_cnt = 0;
	min_val = 21e8;

	std::cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cin >> arr[i][j];
			if (arr[i][j]) {
				num_cnt++;
			}
		}
	}

	st_p = { 0, 0, 0, 0 };
}


// bfs
void bfs(Edge st) {
	queue <Edge> q; 
	q.push(st);

	while (!q.empty()) {
		Edge now = q.front();
		q.pop();

	// [1] 값이 있는 경우: 최소 거리, 시작 위치 갱신
		if (arr[now.y][now.x] == val) {
			min_val = min(min_val, now.cnt);
			st_p = { now.y, now.x, now.dir, 0 };
			return;
		}

	// [2] 값을 못 찾았을 경우: 직진 or 회전
		// [2-1] 직진
		int ny = now.y + dy[now.dir];
		int nx = now.x + dx[now.dir];

		if (!(ny < 0 || ny >= N || nx < 0 || nx >= N)) {
			q.push({ ny, nx, now.dir, now.cnt });
		}


		// [2-2] 우회전
		ny = now.y + dy[(now.dir + 1) % 4];
		nx = now.x + dx[(now.dir + 1) % 4];

		if (!(ny < 0 || ny >= N || nx < 0 || nx >= N)) {
			q.push({ ny, nx, (now.dir + 1) % 4, now.cnt + 1 });
		}
	}
}


int main() {
	std::cin >> T;
	
	for (int i = 1; i < T + 1; i++) {
		init();

	// 숫자가 있는 만큼 반복
		for (int j = 0; j < num_cnt; j++) {
			bfs(st_p);
			total_cnt += min_val;
			min_val = 21e8;
			val++;
		}

		std::cout << "#" << i << " " << total_cnt << '\n';
	}
	
	return 0;
}
