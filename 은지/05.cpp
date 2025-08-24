#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, N;
vector <int> v(101);

int main() {
	std::cin >> T;

	for (int i = 1; i < T + 1; i++) {
		fill(v.begin(), v.end(), 0);
		std::cin >> N;

		for (int i = 0; i < N; i++) {
			int num;
			std::cin >> num;
			v.push_back(num);
		}


		sort(v.rbegin(), v.rend());

		int max_val = v[0];
		for (int i = 1; i < N; i++) {
			v[i] = max_val - v[i];
		}

		int even = 0;
		int odd  = 0;
		for (int i = 1; i < N; i++) {
			odd  += v[i] % 2;
			even += v[i] / 2;
		}

		if (even < odd) {
			int num = odd - even;
			std::cout << "#" << i << " " << even * 2 + num * 2 - 1 << "\n";
		}

		else if (even == odd) {
			std::cout << "#" << i << " " << even + odd << "\n";
		}

		else {
			int num = even - odd;
			
			int remain_two = num % 3;
			int set = num / 3;

			if (remain_two == 0) {
				std::cout << "#" << i << " " << odd * 2 + set * 4 << "\n";
			}
			else if (remain_two == 1) {
				std::cout << "#" << i << " " <<  odd * 2 + set * 4 + 2 << "\n";
			}
			else if (remain_two == 2) {
				std::cout << "#" << i << " " <<  odd * 2 + set * 4 + 3 << "\n";
			}
		}
	}

	return 0;
}
