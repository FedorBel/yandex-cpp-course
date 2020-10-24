#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>

using namespace std;

struct Student
{
	string first_name;
	string last_name;
	int day_of_birth;
	int month_of_birth;
	int year_of_birth;
};

int main()
{
	vector<Student> students;
	int n = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		Student student;
		cin >> student.first_name >> student.last_name
			>> student.day_of_birth >> student.month_of_birth
			>> student.year_of_birth;
		students.push_back(student);
	}

	int m = 0;
	cin >> m;

	for (int i = 0; i < m; i++)
	{
		string request;
		int num;
		cin >> request >> num;

		if (request == "name")
		{			
			if (num > 0 && num <= students.size())
			{
				num--;
				cout << students[num].first_name << " "
					<< students[num].last_name << endl;
			}
			else
			{
				cout << "bad request" << endl;
			}
		}
		else if (request == "date")
		{		
			if (num > 0 && num <= students.size())
			{
				num--;
				cout << students[num].day_of_birth << "."
					<< students[num].month_of_birth << "."
					<< students[num].year_of_birth << endl;
			}
			else
			{
				cout << "bad request" << endl;
			}
		}
		else
		{
			cout << "bad request" << endl;
		}
	}

	return 0;
}