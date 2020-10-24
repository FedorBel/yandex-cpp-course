#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {

	buses_to_stops[bus] = stops;
	for (const string& stop : stops) {
		stops_to_buses[stop].push_back(bus);
	}
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	BusesForStopResponse b;
	if (stops_to_buses.count(stop) == 0) {
		b.NoStop = 1;
	}
	else {
		b.stops_to_buses = stops_to_buses.at(stop);
	}
	return b;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
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