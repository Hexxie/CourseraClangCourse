#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
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

  void clearStructure(Query& q) {
      q.bus = "";
      q.stop = "";
      q.stops.clear();
  }

istream& operator >> (istream& is, Query& q) {
  string operation_code;
  is >> operation_code;

  clearStructure(q);

  if (operation_code == "NEW_BUS") {
      q.type = QueryType::NewBus;
      string stop;

      is >> q.bus;

      int stop_count;
      is >> stop_count;
      for (int i = 0; i < stop_count; i++) {
        is >> stop;
        q.stops.push_back(stop);
      }
  } else if (operation_code == "STOPS_FOR_BUS") {
      q.type = QueryType::StopsForBus;

      is >> q.bus;

  } else if (operation_code == "BUSES_FOR_STOP") {
       q.type = QueryType::BusesForStop;

       is >> q.stop;

  } else if (operation_code == "ALL_BUSES") {
      q.type = QueryType::AllBuses;
  }

  return is;
}

struct BusesForStopResponse {
  vector<string> response;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  for(auto item : r.response)
    os << item;
  return os;
}



struct StopsForBusResponse {
    vector<string> response;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  for(auto item : r.response)
    os << item;
  return os;
}

struct AllBusesResponse {
  vector<string> response;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  for(auto item : r.response)
    os << item;
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    //Copy vector of stops for current bus
    buses_to_stops[bus] = stops;

    //Assign for each stop - current bus
    for(auto& stop : stops)
    {
        stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
      BusesForStopResponse result;
      if (stops_to_buses.count(stop) == 0) {
          result.response.push_back("No stop");
      } else {
        for (const string& bus : stops_to_buses.at(stop)) {
            result.response.push_back(bus);
            result.response.push_back(" ");
        }
        result.response.push_back("\n");
      }
      return result;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
      StopsForBusResponse result;
      if (buses_to_stops.count(bus) == 0) {
          result.response.push_back("No bus");
      } else {
        for (const string& stop : buses_to_stops.at(bus)) {
            result.response.push_back("Stop ");
            result.response.push_back(stop);
            result.response.push_back(": ");
          if (stops_to_buses.at(stop).size() == 1) {
              result.response.push_back("no interchange");
          } else {
            for (const string& other_bus : stops_to_buses.at(stop)) {
              if (bus != other_bus) {
                  result.response.push_back(other_bus);
                  result.response.push_back(" ");
              }
            }
          }
          result.response.push_back("\n");
        }
      }
      return result;
  }

  AllBusesResponse GetAllBuses() const {
      AllBusesResponse result;
      if (buses_to_stops.empty()) {
          result.response.push_back("No buses");
      } else {
        for (const auto& bus_item : buses_to_stops) {
            result.response.push_back("Bus ");
            result.response.push_back(bus_item.first);
            result.response.push_back(": ");
          for (const string& stop : bus_item.second) {
              result.response.push_back(stop);
              result.response.push_back(" ");
          }
          result.response.push_back("\n");
        }
      }
      return result;
  }

private:

  //Buses drives through given stop
  //Stop - buses
  map<string, vector<string>> buses_to_stops;

  //Description of bus route
  //Bus - it's stops
  map<string, vector<string>> stops_to_buses;
};



// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
 /* BusManager bm;
  bm.RunAllTests();

  return 0;
*/
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
