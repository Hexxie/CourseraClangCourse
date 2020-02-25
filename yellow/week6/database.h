#pragma once

#include "date.h"

#include <ostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class Database {
public:

  void Add(const Date& date, const string& event);
  bool DeleteEvent(const Date& date, const string& event);
  int DeleteDate(const Date& date);
  set<string> Find(const Date& date) const;
  void Print(ostream &os) const;

private:
  map<Date, set<string>> storage;
};
