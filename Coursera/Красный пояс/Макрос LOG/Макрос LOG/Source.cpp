#include "test_runner.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Logger {
public:
	explicit Logger(ostream& output_stream) : os(output_stream) {
	}

	void SetLogLine(bool value) { log_line = value; }
	void SetLogFile(bool value) { log_file = value; }

	bool GetLogLine() { return log_line; }
	bool GetLogFile() { return log_file; }

	void SetLineNumber(long value) { line = value; }
	void SetFileName(string value) { file = value; }

	void Log(const string& message)
	{
		if (log_file && log_line)
		{
			os << file << ":" << line << " " << message << endl;
		}
		else if (log_file)
		{
			os << file << " " << message << endl;
		}
		else if (log_line)
		{
			os << "Line " << line << " " << message << endl;
		}
		else
		{
			os << message << endl;
		}
	}

private:
	ostream& os;
	bool log_line = false;
	bool log_file = false;
	long line;
	string file;
};

#define LOG(logger, message) { \
	logger.SetLineNumber(__LINE__);\
	logger.SetFileName(__FILE__);\
	logger.Log(message);\
}


void TestLog() {
	/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
	 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
	 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
	 * и наш тест начинает падать. Это неудобно.
	 *
	 * Чтобы этого избежать, мы используем специальный макрос #line
	 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
	 * переопределить номер строки, а также имя файла. Благодаря ему, номера
	 * строк внутри функции TestLog будут фиксированы независимо от того, какой
	 * код мы добавляем перед ней*/


	ostringstream logs;
	Logger l(logs);
	LOG(l, "hello");

	l.SetLogFile(true);
	LOG(l, "hello");

	l.SetLogLine(true);
	LOG(l, "hello");

	l.SetLogFile(false);
	LOG(l, "hello");

	cout << logs.str() << endl;

	string expected = "hello\n";
	expected += "logger.cpp hello\n";
	expected += "logger.cpp:10 hello\n";
	expected += "Line 13 hello\n";
	//ASSERT_EQUAL(logs.str(), expected);
}

int main() {
	//TestRunner tr;
	//RUN_TEST(tr, TestLog);
	TestLog();
}
