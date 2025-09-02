#include <algorithm>
#include <iostream>
using namespace std;

int T, N;
int total;
int arr1[501];
int arr2[501];

int visited[501];

void init() {
	total = 0;
	memset(arr1, 0, sizeof(arr1));
	memset(arr2, 0, sizeof(arr2));
	memset(visited, 0, sizeof(visited));

	std::cin >> N;

	for (int i = 0; i < N; i++) {
		std::cin >> arr1[i];
	}

	for (int i = 0; i < N; i++) {
		std::cin >> arr2[i];
	}
}

int main() {
	std::cin >> T;
	for (int i = 1; i < T + 1; i++) {
		init();

		sort(arr1, arr1 + N);
		sort(arr2, arr2 + N);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visited[j] && abs(arr1[i] - arr2[j]) <= 3) {
					visited[j] = 1;
					total++;
					break;
				}
			}
		}

		std::cout << "#" << i << " " << total << "\n";
	}


	return 0;
}
