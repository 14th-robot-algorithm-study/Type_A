#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

int T;
int sj;
int res;
int max_val;
int N, M, C;
int max_1, max_2;
int arr[11][11];


// [1] 초기화
void init() {
	res = 0;
	memset(arr, 0, sizeof(arr));

	std::cin >> N >> M >> C;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cin >> arr[i][j];
		}
	}
}


// [2] dfs
void dfs(int n, int cnt, int sum, int ci, int cj) {
	if (cnt > C) {
		return;
	}

	if (n == M) {
		max_val = max(max_val, sum);
		return;
	}

	// 포함 
	dfs(n + 1, cnt + arr[ci][cj + n], sum + pow(arr[ci][cj + n], 2), ci, cj);

	// 포함 X
	dfs(n + 1, cnt, sum, ci, cj);
}


// [3] solve
void solve() {
	for (int i1 = 0; i1 < N; i1++) {
		for (int j1 = 0; j1 < N - M + 1; j1++) {
			max_val = 0;
			dfs(0, 0, 0, i1, j1);
			max_1 = max_val;
			for (int i2 = 0; i2 < N; i2++) {
				// 같은 행
				if (i1 == i2) {
					sj = j1 + M;
				}
				// 다른 행
				else
				{
					sj = 0;
				}

				for (int j2 = sj; j2 < N - M + 1; j2++) {
					max_val = 0;
					dfs(0, 0, 0, i2, j2);
					max_2 = max_val;
					res = max(res, max_1 + max_2);
				}
			}
		}
	}
}


int main() {
	std::cin >> T;

	for (int i = 1; i < T + 1; i++) {
		init();
		solve();

		std::cout << "#" << i << " " << res << "\n";
	}


	return 0;
}
