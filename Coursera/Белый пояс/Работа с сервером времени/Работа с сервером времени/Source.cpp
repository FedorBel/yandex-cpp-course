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
	/* ƒл€ тестировани€ повставл€йте сюда код, реализующий различное поведение этой функии:
	   * нормальный возврат строкового значени€
	   * выброс исключени€ system_error
	   * выброс другого исключени€ с сообщением.
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
	// ћен€€ реализацию функции AskTimeServer, убедитесь, что это код работает корректно
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