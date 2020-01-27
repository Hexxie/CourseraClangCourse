#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>

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
  string operation_code;
  is >> operation_code;

  if (operation_code == "NEW_BUS") {
      q.type = QueryType::NewBus;

      is >> q.bus;

      int stop_count;
      is >> stop_count;
      q.stops.resize(stop_count);
      for (string& stop : q.stops) {
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
  size_t nr_buses;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if(r.nr_buses == 0 ){
      os << "No stop";
  } else {
      for(auto item : r.buses)
        os << item << " ";
  }
  return os;
}

bool operator==(const BusesForStopResponse& lhs, const BusesForStopResponse& rhs){
     return lhs.nr_buses == rhs.nr_buses && lhs.buses == rhs.buses;
}

struct StopsForBusResponse {
  map<string, vector<string>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if(r.stops_for_buses.empty()) {
      os << "No bus";
  } else {
      for(auto item : r.stops_for_buses) {
          os << "Stop " << item.first <<": ";
          if(item.second.empty()) {
              os << "no intercharge";
          } else {
              for(auto other_item : item.second) {
                  if (item.first != other_item) {
                    os << other_item <<" ";
                  }
              }
          }
          os << "\n";
      }
  }
  return os;
}
bool operator==(const StopsForBusResponse& lhs, const StopsForBusResponse& rhs){
     return lhs.stops_for_buses == rhs.stops_for_buses;
}

struct AllBusesResponse {
  map<string, vector<string>> stops_to_buses;
};

bool operator==(const AllBusesResponse& lhs, const AllBusesResponse& rhs){
     return lhs.stops_to_buses == rhs.stops_to_buses;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.stops_to_buses.empty()) {
      os << "No buses";
  } else {
      for(auto const &item : r.stops_to_buses) {
          os <<"Bus " << item.first << ": ";
          for (auto const &other_item : item.second) {
              os << other_item << " ";
          }
          os << "\n";
      }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    //Copy vecotr of stops for current bus
    buses_to_stops[bus] = stops;

    //Assign for each stop - current bus
    for(auto& stop : stops)
    {
        stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if(stops_to_buses.find(stop) != stops_to_buses.end()) {
        return {stops_to_buses.at(stop).size(), stops_to_buses.at(stop)};
    } else {
        return {0, {}};
    }
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    StopsForBusResponse result;
    if(buses_to_stops.find(bus) != buses_to_stops.end()) {

        for(auto item : buses_to_stops.at(bus)) {
            if(stops_to_buses.at(item).size() == 1) {
                result.stops_for_buses.insert({item, {}});
            } else {
                for(auto other_item : stops_to_buses.at(item)) {
                    result.stops_for_buses[item].push_back(other_item);
                }
            }
        }
    }
    return result;
  }

  AllBusesResponse GetAllBuses() const {
    return {buses_to_stops};
  }

  void RunAllTests()
  {
    testAddBus();
    testGetBusesForStop();
  }

private:

  /********************** TESTS ******************************/
  void testAddBus()
  {
      AddBus("32", {"A", "B", "C"});
      map<string, vector<string>> b_to_s_expected = {{"32", {"A", "B", "C"}}};
      assert(b_to_s_expected == buses_to_stops);

      map<string, vector<string>> s_to_b_expected = {{"A", {"32"}}, {"B", {"32"}}, {"C", {"32"}}};
      assert(s_to_b_expected == stops_to_buses);

      AddBus("32K", {"B", "C", "D"});
      b_to_s_expected = {{"32", {"A", "B", "C"}}, {"32K", {"B", "C", "D"}}};
      assert(b_to_s_expected == buses_to_stops);

      s_to_b_expected = {{"A", {"32"}}, {"B", {"32", "32K"}}, {"C", {"32", "32K"}}, {"D", {"32K"}}};
      assert(s_to_b_expected == stops_to_buses);

      buses_to_stops.clear();
      stops_to_buses.clear();
  }

  void testGetBusesForStop()
  {
      AddBus("32", {"A", "B", "C"});
      AddBus("32K", {"B", "C", "D"});
      BusesForStopResponse actual = GetBusesForStop("E");
      BusesForStopResponse expected = {0, {}};
      assert(actual == expected);

      actual = GetBusesForStop("D");
      expected = {1, {"32K"}};
      assert(actual == expected);

      actual = GetBusesForStop("B");
      expected = {2, {"32", "32K"}};
      assert(actual == expected);

      buses_to_stops.clear();
      stops_to_buses.clear();
  }

void testGetStopsForBus()
{
      AddBus("32", {"A", "B", "C"});
      AddBus("32K", {"B", "C", "D"});
      AddBus("27", {"B", "C", "D"});

      StopsForBusResponse actual = GetStopsForBus("32");
      StopsForBusResponse expected = {{{"A", {}}, {"B", {"32K", "27"}}, {"C", {"32K", "27"}}}};
      assert(actual == expected);

      buses_to_stops.clear();
      stops_to_buses.clear();
}

void testGetAllBuses()
{
      AddBus("32", {"A", "B", "C"});
      AddBus("32K", {"B", "C", "D"});
      AddBus("950", {"B", "C", "D"});
      AddBus("272", {"B", "C", "D"});

      AllBusesResponse actual = GetAllBuses();
      AllBusesResponse expected = {{{"272", {"B", "C", "D"}}, {"272", {"B", "C", "D"}},
                                    {"272", {"B", "C", "D"}}, {"272", {"B", "C", "D"}}}};
      assert(actual == expected);

      buses_to_stops.clear();
      stops_to_buses.clear();
}

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

  return 0; */

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
