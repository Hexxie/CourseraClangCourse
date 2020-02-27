#include "database.h"

#include <set>

void Database::Add(const Date& date, const string& event) {
  storage[date].push_back(event);
  storage_unique[date].insert(event);
}

/*
bool Database::DeleteEvent(const Date& date, const string& event) {
  if (storage.count(date) > 0 && storage[date].count(event) > 0) {
    storage[date].erase(event);
    return true;
  }
  return false;
}

int Database::DeleteDate(const Date& date) {
  if (storage.count(date) == 0) {
    return 0;
  } else {
    const int event_count = storage[date].size();
    storage.erase(date);
    return event_count;
  }
}

set<string> Database::Find(const Date& date) const {
  if (storage.count(date) > 0) {
    return storage.at(date);
  } else {
    return {};
  }
}

*/

void Database::Print(ostream &os) const {
  for (const auto& item : storage_unique) {
    for (const string& event : item.second) {
      os << item.first << " " << event << endl;
    }
  }
}

string Database::Last(const Date &lastDate) const {
  string result;
  auto it = storage.lower_bound(lastDate);
  --it;
  if(it != storage.end() && lastDate >= it->first) {
    ostringstream os;
    os << it->first << " " + *--(it->second.end());
    result = os.str();
  } else {
    result = "No entries";
  }
  return result;
}