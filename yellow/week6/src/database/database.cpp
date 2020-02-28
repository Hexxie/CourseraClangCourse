#include "database.h"

#include <set>

void Database::Add(const Date& date, const string& event) {
  storage_unique[date].insert(event);
  if(storage_unique.at(date).count(event) == 0) {
    storage[date].push_back(event);
  }


}

void Database::Print(ostream &os) const {
  for (const auto& item : storage) {
    for (const string& event : item.second) {
        os << item.first << " " << event << "\n";
    }
  }
}

string Database::Last(const Date &lastDate) const {
  string result = "No entries";
  if(!storage.empty()) {
      auto it = storage.upper_bound(lastDate);
    --it;
    if(it != storage.end() && lastDate >= it->first) {
      ostringstream os;
      os << it->first << " " + *--(it->second.end());
      result = os.str();
    }
  }
  return result;
}