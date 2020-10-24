#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

class MyList
{
	int volume;
public:
	MyList* next;
	MyList()
	{
		volume = 0;
		next = nullptr;
	}

	void set(int volume) { this->volume = volume; }
	int get() { return volume; }
	void print() { cout << volume << " "; }
};

void revert(MyList *&phead)
{
	MyList *tmp = phead;
	MyList &p = *phead;
	vector<int> v;
	
	
	while (tmp)
	{		
		v.push_back(tmp->get());
		tmp = tmp->next;
	}

	reverse(v.begin(), v.end());

	for (auto& i : v)
	{
		phead->set(i);
		phead = phead->next;
	}
	phead = &p;
}

void check(MyList* pList)
{
	if (!pList) return;

	while (pList)
	{
		pList->print();
		pList = pList->next;
	}
	cout << endl;
}

int main()
{
	MyList List[9];
	// init
	for (unsigned int i = 0; i < sizeof(List)/sizeof(*List); i++)
	{
		MyList* pList = &List[i];
		pList->set(i);
		if (i < sizeof(List) / sizeof(*List) - 1)
		{
			pList->next = &List[i + 1];
		}
	}
	// check
	check(List);
	// revert
	MyList *p = List;
	revert(p);
	// check
	check(p);

	return 0;
}