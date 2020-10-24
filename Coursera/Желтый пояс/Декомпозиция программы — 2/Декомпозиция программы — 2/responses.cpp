#include "responses.h"

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