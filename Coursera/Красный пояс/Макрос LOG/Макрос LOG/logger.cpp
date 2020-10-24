#include "test_runner.h"
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
