#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
int N;
int tree[100];
int max_tree;
int min_day, day;
int one, two;

int main() {
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		memset(tree, 0, sizeof(tree));
		max_tree = 0;
		one = 0, two = 0;
		min_day = 21e8;
		day = 0;

		for (int i = 0; i < N; i++) {
			cin >> tree[i];
			max_tree = max(tree[i], max_tree);
		}

		/*     시뮬레이션     */
		for (int i = 0; i < N; i++) {
			one += (max_tree - tree[i]) % 2;
			two += (max_tree - tree[i]) / 2;
		}

		while (true) {
			int oneday = one * 2 - 1;
			int twoday = two * 2;

			if (oneday > twoday)
				day = oneday;
			else
				day = twoday;

			one += 2;
			two -= 1;

			if (day > min_day)
				break;

			if (day < min_day)
				min_day = day;
		}
		cout << "#" << tc << " " << min_day << "\n";
	}
}
