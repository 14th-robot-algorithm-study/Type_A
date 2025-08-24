#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int T, N;
int map[8][8]; 
int P[8];       
int ans;        
int visited[8];  

void isConnected() {
	int check[8] = { 0 };
	int startA = -1;
	int startB = -1;

	for (int i = 0; i < N; i++) {
		if (visited[i] == 1) {
			startA = i;
			break;
		}
	}

	for (int i = 0; i < N; i++) {
		if (visited[i] == 0) {
			startB = i;
			break;
		}
	}

	if (startA == -1 || startB == -1) return;

	queue<int> q;
	q.push(startA);
	check[startA] = 1;

	while (!q.empty()) {
		int st = q.front();
		q.pop();
		for (int i = 0; i < N; i++) {
			if (visited[i] == 1 && map[st][i] == 1 && check[i] == 0) {
				check[i] = 1;
				q.push(i);
			}
		}
	}

	queue<int> q2;
	q2.push(startB);
	check[startB] = 1;

	while (!q2.empty()) {
		int st2 = q2.front();
		q2.pop();
		for (int i = 0; i < N; i++) {
			if (visited[i] == 0 && map[st2][i] == 1 && check[i] == 0) {
				check[i] = 1;
				q2.push(i);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (check[i] == 0) return;
	}

	int sumA = 0, sumB = 0;
	for (int i = 0; i < N; i++) {
		if (visited[i] == 1) sumA += P[i];
		else sumB += P[i];
	}
	int diff = sumA - sumB;
	if (diff < 0) diff = -diff;
	if (diff < ans) ans = diff;
}

void dfs(int lev) {
	if (lev == N) {
		isConnected();
		return;
	}

	for (int i = 0; i <= 1; i++) {
		visited[lev] = i;
		dfs(lev + 1);
		visited[lev] = -1;
	}
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		memset(map, 0, sizeof(map));
		memset(P, 0, sizeof(P));
		memset(visited, -1, sizeof(visited));
		cin >> N;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			cin >> P[i];
		}

		ans = 1e9; 
		dfs(0);

		if (ans == 1e9) ans = -1; 
		cout << "#" << tc << " " << ans << "\n";
	}
	return 0;
}
