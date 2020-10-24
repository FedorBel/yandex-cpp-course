#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <numeric>
#include <thread>

using namespace std;

class Test
{
public:
	Test()
	{
		v.resize(100);
		iota(v.begin(), v.end(), 0);
	}

	void vecSumThread()
	{
		thread(&Test::vecSum, this).detach();
	}
	void makeNewVecThread()
	{

	}
	void showVecThread()
	{

	}

	void vecSum()
	{
		cout << "vecSum start" << endl;
		int sum = 0;
		for (const auto& el : v)
		{
			sum += el;
		}
		cout << "Sum = " << sum << endl;
		cout << "vecSum end;" << endl;
	}

	void makeNewVec()
	{
		cout << "makeNewVec start" << endl;
		iota(v.begin(), v.end(), 100);
		cout << "makeNewVec end;" << endl;
	}

	void showVec()
	{
		cout << "showVec start" << endl;
		for (const auto& el : v)
		{
			cout << el << "\n";
		}
		cout << endl;
		cout << "showVec end;" << endl;
	}

private:
	vector<int> v;
};

int main()
{
	Test t;

	t.vecSumThread();
	t.makeNewVec();

	return 0;
}