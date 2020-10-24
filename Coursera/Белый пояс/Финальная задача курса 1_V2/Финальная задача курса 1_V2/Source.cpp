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

	void SetDate(const string& new_date)
	{
		stringstream ss(new_date);
		int year, month, day = EOF;
		char def;

		ss >> year;
		if (ss.fail()) { throw invalid_argument("Wrong date format: " + new_date); }

		ss >> def;
		if (def != '-') { throw invalid_argument("Wrong date format: " + new_date); }

		ss >> month;
		if (ss.fail()) { throw invalid_argument("Wrong date format: " + new_date); }

		ss >> def;
		if (def != '-') { throw invalid_argument("Wrong date format: " + new_date); }

		ss >> day;
		if (ss.fail()) { throw invalid_argument("Wrong date format: " + new_date); }

		if (ss.peek()!= EOF) { throw invalid_argument("Wrong date format: " + new_date); }

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
		string check_date = get_string(date);
		auto it = events.find(check_date);

		if (it != events.end())
		{
			if (it->second.find(event) != it->second.end())
			{
				it->second.erase(event);
				return true;
			}
		}

		return false;
	}
	int  DeleteDate(const Date& date)
	{
		string check_date = get_string(date);
		if (events.find(check_date) != events.end())
		{
			int size = events.at(check_date).size();
			events.erase(check_date);
			return size;
		}
		return 0;
	}

	void Find(const Date& date) const
	{
		string check_date = get_string(date);
		if (events.find(check_date) != events.end())
		{
			for (const auto& ev : events.at(check_date))
			{
				cout << ev << endl;
			}
			
		}
	}

	void Print() const
	{
		for (const auto& dates : events)
		{
			string data = dates.first;

			for (const auto& ev : dates.second)
			{
				cout << data << " " << ev << endl;
			}
		}
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
					string new_date;
					ss >> new_date;
					date.SetDate(new_date);
					string event;
					ss >> event;
					db.AddEvent(date, event);
				}
				else if (com == "Del")
				{
					string new_date, event;
					ss >> new_date >> event;
					Date date;
					date.SetDate(new_date);
					if (event.size() != 0)
					{
						if (db.DeleteEvent(date, event))
						{
							cout << "Deleted successfully" << endl;
						}
						else
						{
							cout << "Event not found" << endl;
						}
					}
					else
					{
						cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
					}
				}
				else if (com == "Find")
				{
					Date date;
					string new_date;
					ss >> new_date;
					date.SetDate(new_date);
					db.Find(date);
				}
				else if (com == "Print")
				{
					db.Print();
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