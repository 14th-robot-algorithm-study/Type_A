#include <algorithm>
#include <iostream>
using namespace std;

int T, n, p;
int arr[2][21];
int dp[21][3];

int main() {
	std::cin >> T;
	for (int i = 1; i < T + 1; i++) {
		std::cin >> n >> p;

		// [1] 첫 번째 비료
		for (int i = 0; i < n; i++) {
			std::cin >> arr[0][i];
		}

		// [2] 두 번째 비료
		for (int i = 0; i < n; i++) {
			std::cin >> arr[1][i];
		}

		dp[0][0] = arr[0][0];
		dp[0][1] = arr[1][0];
		dp[0][2] = 0;

		for (int i = 1; i < n; i++) {
			dp[i][0] = max(max(dp[i - 1][0] + arr[0][i] - p, dp[i - 1][1] + arr[0][i]), dp[i - 1][2] + arr[0][i]);
			dp[i][1] = max(max(dp[i - 1][1] + arr[1][i] - p, dp[i - 1][0] + arr[1][i]), dp[i - 1][2] + arr[1][i]);
			dp[i][2] = max(max(dp[i - 1][0], dp[i - 1][1]), dp[i - 1][2]);
		}

		std::cout << "#" << i << " " << max(max(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]) << "\n";
	}

	return 0;
}
