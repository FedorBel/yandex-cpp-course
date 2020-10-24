#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

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

struct BusesForStopResponse {
	vector<string> stops_to_buses;	
	bool NoStop = 0;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.NoStop == 1)
	{
		os << "No stop";
	}
	else
	{
		for (const string& bus : r.stops_to_buses) {
			cout << bus << " ";
		}
	}
	
	return os;
}

struct StopsForBusResponse {
	vector<string> buses_to_stops;	
	string bus;
	map<string, vector<string>> stops_to_buses;
	bool NoBus = 0;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	
	if (r.NoBus == 1)
	{
		os << "No bus";
	}
	else
	{
		int count = 0;
		int size = r.buses_to_stops.size();
		for (const string& stop : r.buses_to_stops) {
			count++;
			os << "Stop " << stop << ": ";
			if (r.stops_to_buses.at(stop).size() == 1) {
				os << "no interchange";
			}
			else {
				for (const string& other_bus : r.stops_to_buses.at(stop)) {
					if (r.bus != other_bus) {
						os << other_bus << " ";
					}
				}
			}
			if (count != size)
			{
				os << endl;
			}			
		}
	}
	
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stops;
	bool NoBuses = 0;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.NoBuses == 1)
	{
		os << "No buses";
	}
	else
	{
		int count = 0;
		int size = r.buses_to_stops.size();
		for (const auto& bus_item : r.buses_to_stops) {
			count++;
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			if (count != size)
			{
				os << endl;
			}
		}
	}

	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		
		buses_to_stops[bus] = stops;
		for (const string& stop : stops) {			
			stops_to_buses[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse b;
		if (stops_to_buses.count(stop) == 0) {
			b.NoStop = 1;
		}
		else {
			b.stops_to_buses = stops_to_buses.at(stop);
		}
		return b;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse s;
		if (buses_to_stops.count(bus) == 0) {
			s.NoBus = 1;
		}
		else {
			s.buses_to_stops = buses_to_stops.at(bus);
			s.stops_to_buses = stops_to_buses;
			s.bus = bus;
		}
		return s;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse all;
		if (buses_to_stops.empty()) {
			all.NoBuses = 1;
		}
		else
		{			
			all.buses_to_stops = buses_to_stops;			
		}
		return all;
	}
private:
	//BusesForStopResponse b;
	//StopsForBusResponse s;
	//AllBusesResponse all;

	map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;
	
	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}
