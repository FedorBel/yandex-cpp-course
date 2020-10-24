#include "stats.h"

#include <sstream>

void Stats::AddMethod(string_view method)
{
	if (method == "GET")
	{
		methods_count[methods[0]]++;
	}
	else if (method == "POST")
	{
		methods_count[methods[1]]++;
	}
	else if (method == "PUT")
	{
		methods_count[methods[2]]++;
	}
	else if (method == "DELETE")
	{
		methods_count[methods[3]]++;
	}
	else
	{
		methods_count[methods[4]]++;
	}
}

void Stats::AddUri(string_view uri)
{
	if (uri == "/")
	{
		uri_count[uris[0]]++;
	}
	else if (uri == "/order")
	{
		uri_count[uris[1]]++;
	}
	else if (uri == "/product")
	{
		uri_count[uris[2]]++;
	}
	else if (uri == "/basket")
	{
		uri_count[uris[3]]++;
	}
	else if (uri == "/help")
	{
		uri_count[uris[4]]++;
	}
	else
	{
		uri_count[uris[5]]++;
	}
}

const map<string_view, int>& Stats::GetMethodStats() const
{
	return methods_count;
}

const map<string_view, int>& Stats::GetUriStats() const
{
	return uri_count;
}

HttpRequest ParseRequest(string_view line)
{
	auto rem_space = line.find_first_not_of(' ');
	line = line.substr(rem_space, line.size() - rem_space);
	HttpRequest result;
	auto m_end = line.find(' ');	

	result.method = line.substr(0, m_end);

	auto uri_end = line.find(' ', ++m_end);
	result.uri = line.substr(m_end, uri_end - m_end);
	result.protocol = line.substr(++uri_end, line.size() - uri_end);

	return result;
}
