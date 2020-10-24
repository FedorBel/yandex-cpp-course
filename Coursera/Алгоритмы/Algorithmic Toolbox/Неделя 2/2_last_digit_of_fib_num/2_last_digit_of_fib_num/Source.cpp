#include <iostream>
#include <vector>

using namespace std;

int get_fibonacci_last_digit_fast(int n)
{
	vector<int> f(n + 1);
	f[0] = 0;
	if (f.size() > 1)
		f[1] = 1;
	for (size_t i = 2; i < n + 1; i++)
	{
		f[i] = (f[i - 1] + f[i - 2]) % 10;
	}
	return f[n];
}

int get_fibonacci_last_digit_naive(int n) {
	if (n <= 1)
		return n;

	int previous = 0;
	int current = 1;

	for (int i = 0; i < n - 1; ++i) {
		int tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	return current % 10;
}

int main() {
	int n;
	std::cin >> n;
	int c = get_fibonacci_last_digit_fast(n);
	
	std::cout << c << '\n';
	//std::cin >> n;
	//int d = get_fibonacci_last_digit_fast(n);
	//std::cout << d << '\n';
}
