#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct BusesForStopResponse {
	vector<string> stops_to_buses;
	bool NoStop = 0;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
	vector<string> buses_to_stops;
	string bus;
	map<string, vector<string>> stops_to_buses;
	bool NoBus = 0;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stops;
	bool NoBuses = 0;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);