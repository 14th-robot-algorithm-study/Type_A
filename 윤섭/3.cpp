//문제 풀이법
//지역구 나누기는 지역구를 A와 B 둘로 나누고, (DFS)
//A지역구와 B지역구가 각각 연결되어있는지를 확인 (BFS)

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int T, N;
int map[8][8];
int P[8];
int city[8];	
int ans;

void bfs() {
	int visited[8] = { 0 };	//모든 지역구가 방문되었는지 체크
	int startA = -1;
	int startB = -1;

	// startA를 찾는 이유는 A지역구가 모두 다 연결되었다고 가정하면 
	// A에 속해있는 어느 점에서든 연결이 가능해야해서 for문을 통해 아무점이나 찾는 것
	for (int i = 0; i < N; i++) {
		if (city[i] == 1) {
			startA = i;
			break;
		}
	}

	for (int i = 0; i < N; i++) {
		if (city[i] == 0) {
			startB = i;
			break;
		}
	}

	// 지역구가 하나로만 이루어져있을 시 return;
	if (startA == -1 || startB == -1) return;

	// A점이 전부 연결되어있는지 확인
	queue<int> qA;
	qA.push(startA);
	visited[startA] = 1;

	while (!qA.empty()) {
		int st = qA.front();
		qA.pop();
		for (int i = 0; i < N; i++) {
			if (city[i] == 1 && map[st][i] == 1 && visited[i] == 0) {
				visited[i] = 1;
				qA.push(i);
			}
		}
	}

	// B점이 전부 연결되어있는지 확인
	queue<int> qB;
	qB.push(startB);
	visited[startB] = 1;

	while (!qB.empty()) {
		int st2 = qB.front();
		qB.pop();
		for (int i = 0; i < N; i++) {
			if (city[i] == 0 && map[st2][i] == 1 && visited[i] == 0) {
				visited[i] = 1;
				qB.push(i);
			}
		}
	}

	// visited는 모든 지역구가 방문되었는지 체크하는 배열
	// 만약 visited가 0인 경우가 생기면 방문을 안한 지역이 있다고 간주
	for (int i = 0; i < N; i++) {
		if (visited[i] == 0) return;	
	}

	int sumA = 0, sumB = 0;
	for (int i = 0; i < N; i++) {
		if (city[i] == 1) sumA += P[i];
		else sumB += P[i];
	}
	int diff = abs(sumA - sumB);
	if (diff < ans) ans = diff;
}

void dfs(int lev) {
	if (lev == N) {	// N개의 마을이 지역구가 결정되었을 때 연결 확인!
		bfs();
		return;
	}

	for (int i = 0; i <= 1; i++) {	// 1일 때, A지역구, 0일 때 B지역구
		city[lev] = i;
		dfs(lev + 1);
		city[lev] = -1;
	}
}

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		/*     초기화     */
		memset(map, 0, sizeof(map));
		memset(P, 0, sizeof(P));
		memset(city, -1, sizeof(city));
		/* city를 -1로 초기화하는 이유는 1일 때, A지역구, 0일 때 B지역구로 나누기 위해서 */
		ans = 1e9;

		/*     입력     */
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}
		for (int i = 0; i < N; i++) {
			cin >> P[i];
		}

		
		dfs(0);		// A지역구와 B지역구 나누기
		if (ans == 1e9) ans = -1;

		cout << "#" << tc << " " << ans << "\n";
	}
	return 0;
}
