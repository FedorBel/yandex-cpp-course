#include "query.h"

istream& operator >> (istream& is, Query& q) {
	string type;
	is >> type;

	if (type == "NEW_BUS")
	{
		q.type = QueryType::NewBus;
	}
	else if (type == "BUSES_FOR_STOP")
	{
		q.type = QueryType::BusesForStop;
	}
	else if (type == "STOPS_FOR_BUS")
	{
		q.type = QueryType::StopsForBus;
	}
	else if (type == "ALL_BUSES")
	{
		q.type = QueryType::AllBuses;
	}
	int stop_count = 0;
	switch (q.type) {
	case QueryType::NewBus:

		is >> q.bus >> stop_count;
		q.stops.clear();
		for (int i = 0; i < stop_count; i++)
		{
			string tmp;
			is >> tmp;
			q.stops.push_back(tmp);
		}
		break;
	case QueryType::BusesForStop:
		is >> q.stop;
		break;
	case QueryType::StopsForBus:
		is >> q.bus;
		break;
	case QueryType::AllBuses:

		break;
	}
	return is;
}