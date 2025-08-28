#include <iostream>
#include <cstring>
#include <set>
using namespace std;

struct point {
	int y, x;
};


point st;
int T, N;
int total_cnt;
int arr[51][51];
set <pair<int, int>> eat;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };


void init() {
	std::cin >> N;

	eat.clear();
	memset(arr, 0, sizeof(arr));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::cin >> arr[i][j];

			if (arr[i][j] == 2) {
				st.y = i;
				st.x = j;
			}
		}
	}
}


void dfs(point sp, int cnt) {
	if (cnt == 3) {
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = sp.y;
		int nx = sp.x;
		bool jump = false;

		while (1) {
			ny += dy[i];
			nx += dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
				break;
			}

			// [1] 점프 여부
			if (!jump) {
				if (arr[ny][nx] == 1) {
					jump = true;
				}
			}

			// [2] 착지 여부
			else {
				if (arr[ny][nx] == 0) {
					dfs({ ny, nx }, cnt + 1);
				}
				else if (arr[ny][nx] == 1) {
					eat.insert({ ny, nx });
					arr[ny][nx] = 0;
					dfs({ ny, nx }, cnt + 1);
					arr[ny][nx] = 1;
					break;
				}
			}

		}
	}
}


int main() {
	std::cin >> T;

	for (int i = 1; i < T + 1; i++) {
		init();
		dfs(st, 0);
		std::cout << "#" << i << " " << eat.size() << "\n";
	}

	return 0;
}
