#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int cnt;
int T, N, M;
int total_cnt;
int check[501];
int visited[501];
vector <int> v1[501];
vector <int> v2[501];


void init() {
	fill(check, check + 500, 0);
	fill(visited, visited + 500, 0);

	for (int i = 0; i < 501; i++) {
		v1[i].clear();
		v2[i].clear();
	}

	cnt = 0;
	total_cnt = 0;
	std::cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int from, to;
		std::cin >> from >> to;

		v1[from].push_back(to);
		v2[to].push_back(from);
	}
}


int main() {
	std::cin >> T;

	for (int tc = 1; tc < T + 1; tc++) {
		init();

		for (int i = 1; i < N + 1; i++) {
			cnt = 0;
			queue <int> q;
			q.push(i);

			while (!q.empty()) {
				int now = q.front();
				q.pop();

				for (int j = 0; j < v1[now].size(); j++) {
					int next = v1[now][j];
					if (visited[next]) {
						continue;
					}

					visited[next] = 1;
					q.push(next);
					cnt++;
				}
			}
			check[i] = cnt;
			fill(visited, visited + (N + 1), 0);
		}


		fill(visited, visited + (N + 1), 0);
		for (int i = 1; i < N + 1; i++) {
			cnt = 0;
			queue <int> q;
			q.push(i);

			while (!q.empty()) {
				int now = q.front();
				q.pop();

				for (int j = 0; j < v2[now].size(); j++) {
					int next = v2[now][j];
					if (visited[next]) {
						continue;
					}

					visited[next] = 1;
					q.push(next);
					cnt++;
				}
			}
			check[i] += cnt;
			fill(visited, visited + (N + 1), 0);
		}

		for (int i = 1; i < N + 1; i++) {
			if (check[i] == N - 1) {
				total_cnt++;
			}
		}

		std::cout << "#" << tc << " " << total_cnt << "\n";
	}

	return 0;
}


