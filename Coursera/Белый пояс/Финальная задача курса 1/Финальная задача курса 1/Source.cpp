#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <sstream>
#include <exception>
#include <iomanip>

using namespace std;

class Date 
{
public:

	Date()
	{
		year = 0;
		month = 0;
		day = 0;
	}

	Date(int year, int month, int day)
	{
		SetDate();
	}

	void SetYear(int year)
	{
		this->year = year;
	}

	void SetMonth(int month)
	{
		if (month > 0 && month <= 12)
		{
			this->month = month;
		}
		else
		{
			throw invalid_argument("Month value is invalid: " + to_string(month));
		}
	}

	void SetDay(int day)
	{
		if (day > 0 && day <= 31)
		{
			this->day = day;
		}
		else
		{
			throw invalid_argument("Day value is invalid: " + to_string(day));
		}
	}

	void SetDate()
	{
		string new_date;
		cin >> new_date;

		stringstream ss(new_date);
		int year, month, day;
		char def;

		ss >> year;
		ss >> def;
		if (def != '-') { throw invalid_argument("Wrong date format: " + new_date); }
		ss >> month;
		ss >> def;
		if (def != '-') { throw invalid_argument("Wrong date format: " + new_date); }
		ss >> day;

		SetYear(year);
		SetMonth(month);
		SetDay(day);
	}

	int GetYear() const { return year; }
	int GetMonth() const { return month; }
	int GetDay() const { return day; }

private:
	
	int year;
	int month;
	int day;
};

string get_string(const Date& date);

bool operator<(const Date& lhs, const Date& rhs)
{
	string lss, rss;
	
	lss = get_string(lhs);
	rss = get_string(rhs);
	return (lss < rss);
}

class Database 
{
public:
	void AddEvent(const Date& date, const string& event)
	{
		string date_str = get_string(date);
		events[date_str].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event)
	{

	}
	int  DeleteDate(const Date& date)
	{

	}

	void Find(const Date& date) const
	{

	}

	void Print() const
	{

	}

private:
	map<string, set<string>> events;
};

int main() 
{
	Database db;

	string command;
	while (getline(cin, command)) 
	{
		if (command.size() != 0)
		{
			stringstream ss(command);
			string com;
			ss >> com;
			try
			{
				if (com == "Add")
				{
					Date date;
					date.SetDate();
					string event;
					cin >> event;
					db.AddEvent(date, event);
				}
				else if (com == "Del")
				{

				}
				else if (com == "Find")
				{

				}
				else if (com == "Print")
				{

				}
				else
				{
					cout << "Unknown command: " << command << endl;
				}
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		}
	}

	return 0;
}

string get_string(const Date & date)
{
	stringstream ss;
	ss << setw(4) << setfill('0') << date.GetYear() << "-" << setw(2) << setfill('0') << date.GetMonth() << "-" << setw(2) << setfill('0') << date.GetDay();
	return ss.str();
}