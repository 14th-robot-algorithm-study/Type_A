#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;

int T, N;
int min_val;
int groups[9];
int humans[9];
int arr[9][9];
int visited[9];


void solve() {
	int start_point[2] = { -1, -1 };
	int group_cnt[2]   = { 0, 0 };

	// [1] start point
	for (int i = 0; i < N; i++) {
		int group = groups[i];
		group_cnt[group]++;
		if (start_point[group] == -1) {
			start_point[group] = i;
		}
	}

	// [2] 초기화
	memset(visited, 0, sizeof(visited));

	// [3] BFS
	for (int i = 0; i < 2; i++) {
		queue<int> q;
		q.push(start_point[i]);
		visited[start_point[i]] = 1;
		int bfs_cnt = 1;

		while (!q.empty()) {
			int now = q.front();
			q.pop();

			for (int j = 0; j < N; j++) {
				// 방문 X
				if (visited[j] || arr[now][j] == 0 || groups[j] != i) {
					continue;
				}

				visited[j] = 1;
				q.push(j);
				bfs_cnt++;
			}
		}

		if (bfs_cnt != group_cnt[i]) {
			return;
		}
	}

	int human_sum[2] = { 0, 0 };
	for (int i = 0; i < N; i++) {
		human_sum[groups[i]] += humans[i];
	}

	min_val = min(min_val, abs(human_sum[0] - human_sum[1]));
}



void dfs(int lev) {
	if (lev == N) {
		solve();
		return;
	}

	groups[lev] = 0;
	dfs(lev + 1);

	groups[lev] = 1;
	dfs(lev + 1);
}


void init() {
	min_val = 21e8;
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cin >> arr[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		std::cin >> humans[i];
	}
}


int main() {
	std::cin >> T;
	for (int i = 1; i < T + 1; i++) {
		init();
		dfs(0);

		std::cout << "#" << i << " " << min_val << "\n";

		// 초기화
		memset(arr, 0, sizeof(arr));
		memset(humans, 0, sizeof(humans));
		memset(groups, 0, sizeof(groups));
		memset(visited, 0, sizeof(visited));
	}
	return 0;
}
