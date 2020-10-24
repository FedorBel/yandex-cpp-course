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
		
	void Log(const string& message);

private:
	ostream& os;
	bool log_line = false;
	bool log_file = false;
};

void Logger::Log(const string& message)
{
	if (log_file && log_line)
	{
		os << __FILE__ << ":" << __LINE__ << " " << message << endl;
	}
	else if (log_file)
	{
		os << __FILE__ << " " << message << endl;
	}
	else if (log_line)
	{
		os << "Line " << __LINE__ << " " << message << endl;
	}
	else
	{
		os << message << endl;
	}
}

#define LOG(logger, message) \
	logger.Log(message);
