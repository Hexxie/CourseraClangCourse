#pragma once

#include "date.h"

#include <ostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

class Database {
public:

  void Add(const Date& date, const string& event);
  void Print(ostream &os) const;
  string Last(const Date &lastDate) const;

  template <typename Func>
  int RemoveIf(Func predicate)
  {
    int result = 0;

    if(!storage_unique.empty()) {
      vector<Date> empty_dates;

      for(auto &item : storage) {
        Date d = item.first;
        //Rearrenge events to remove in the end of the vector
        auto it = stable_partition(item.second.begin(), item.second.end(),
                  [predicate, d](string s) {return !predicate(d, s);});

        //Erase items from the unique set
        for(auto i = it; i !=  item.second.end(); ++i) {
          if(storage_unique[d].count(*i) > 0) {
            ++result;
            storage_unique[d].erase(*i);
          }
        }

        //Erase items from the vector
        item.second.erase(it, item.second.end());

        //Erase date if all events were cleared
        if(item.second.empty()) {
          empty_dates.push_back(d);

        }
      }

      for(auto item : empty_dates) {
        storage.erase(item);
        storage_unique.erase(item);
      }
    }

    return result;
  }

  template <typename Func>
 vector<string> FindIf(Func predicate) const
  {
     vector<string> found;

    if(!storage_unique.empty()) {
      for(const auto& item : storage_unique) {
        Date d = item.first;
        auto it = item.second.begin();
        while(it != item.second.end()) {
          it = find_if(it, item.second.end(), [predicate, d](string s) {
            return predicate(d, s);
          });
          if(it != item.second.end()) {
            ostringstream item;
            item << d << " " << *it;
            found.push_back(item.str());
            it++;
          }
        }
      }
    }
    sort(found.begin(), found.end());
    return found;
  }

private:
  map<Date, vector<string>> storage;
  map<Date, set<string>> storage_unique;
};

extern ostream& operator<< (ostream& stream, const pair<const Date, set<string>>& item);

