#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <set>
#include <exception>

using namespace std;

string AskTimeServer() 
{
	/* ��� ������������ ������������ ���� ���, ����������� ��������� ��������� ���� ������:
	   * ���������� ������� ���������� ��������
	   * ������ ���������� system_error
	   * ������ ������� ���������� � ����������.
	*/
	int test = 0;
	if (test == 0)
	{
		throw system_error(error_code());
	}
	if (test == 1)
	{
		throw exception("Something gone wrong =(.");
	}

	return "15:29:58";
}

class TimeServer 
{
public:
	string GetCurrentTime()
	{
		try
		{
			LastFetchedTime = AskTimeServer();
		}
		catch (const system_error&) {
		}
		return LastFetchedTime;
	}
private:
	string LastFetchedTime = "00:00:00";
};

int main()
{
	// ����� ���������� ������� AskTimeServer, ���������, ��� ��� ��� �������� ���������
	TimeServer ts;
	try 
	{
		cout << ts.GetCurrentTime() << endl;
	}
	catch (exception& e) 
	{
		cout << "Exception got: " << e.what() << endl;
	}

	return 0;
}