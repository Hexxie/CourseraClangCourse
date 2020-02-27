#pragma once

#include "../date/date.h"

#include <ostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Database {
public:

  void Add(const Date& date, const string& event);
  void Print(ostream &os) const;
  string Last(const Date &lastDate) const;

  template <typename Func>
  int RemoveIf(Func predicate)
  {
    /*
    Упорядочив в соответствии с требованиями предиката вектор
    (сохранив при этом , что важно, порядок прочих элементов)
    - вы уже сможете имея диапазон в векторе сначала удалить
    все ненужное в сете, потом просто сделать erase диапазона
    в векторе, ну и при необходимости потереть дату, если отсутствуют все события.
    */
    return result;
  }

  template <typename Func>
  vector<string> FindIf(Func predicate)
  {

  }

private:
  map<Date, vector<string>> storage;
  map<Date, set<string>> storage_unique;
};

extern void TestLastPrint();
extern void TestRemoveIf();
