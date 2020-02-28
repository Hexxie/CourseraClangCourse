#include "database.h"

#include <set>

void Database::Add(const Date& date, const string& event) {
  storage[date].push_back(event);
  storage_unique[date].insert(event);
}

void Database::Print(ostream &os) const {
  for (const auto& item : storage_unique) {
    os << item;
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

ostream& operator<<(ostream& stream, const pair<const Date, set<string>>& item) {
  for (const string& event : item.second) {
      stream << item.first << " " << event << endl;
    }
    return stream;
}