#include <iostream>
#include <vector>
#include <algorithm>

int64_t MaxPairwiseProduct(const std::vector<int>& numbers) {
	int n = numbers.size();

	int max_1, max_2;
	max_1 = max_2 = 0;

	int max_1_ind = 0;

	for (int i = 0; i < n; ++i) {		
		if (numbers[i] > max_1)
		{
			max_1 = numbers[i];
			max_1_ind = i;
		}
	}
	for (int i = 0; i < n; ++i) {
		if (numbers[i] > max_2 && i != max_1_ind)
		{
			max_2 = numbers[i];
		}
	}

	return (int64_t)max_1 * max_2;
}

int main() {
	int n;
	std::cin >> n;
	std::vector<int> numbers(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> numbers[i];
	}

	std::cout << MaxPairwiseProduct(numbers) << "\n";
	return 0;
}
