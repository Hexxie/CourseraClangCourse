#include "database.h"
#include "../condition_parser/condition_parser.h"
#include "../../include/test_runner.h"

#include <sstream>
#include <string>

using namespace std;

void TestLastPrint() {
   {
       Database db;
       db.Add({2017, 1, 1}, "New Year");
       db.Add({2017, 3, 8}, "Holiday");
       db.Add({2017, 1, 1}, "Holiday");

        AssertEqual(db.Last({2016, 12, 31}), "No entries", "Last 1");
        AssertEqual(db.Last({2017, 1, 1}), "2017-01-01 Holiday", "Last 2");
        AssertEqual(db.Last({2017, 6, 1}), "2017-03-08 Holiday", "Last 3");
   }
}

void TestRemoveIf() {
   {
       Database db;
       db.Add({2017, 6, 1}, "1st of June");
       db.Add({2017, 7, 8}, "8th of July");
       db.Add({2017, 7, 8}, "Someone's birthday");

      istringstream is("date == 2017-07-08");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);

        AssertEqual(db.RemoveIf(predicate), 2, "RemoveIf 1");
   }
}

/*
void TestFindIf() {
   {
       Database db;
       db.Add({2017, 1, 1}, "New Year");
       db.Add({2017, 3, 8}, "Holiday");
       db.Add({2017, 1, 1}, "Holiday");

        AssertEqual(db.Last({2016, 12, 31}), "No entries", "Last 1");
        AssertEqual(db.Last({2017, 1, 1}), "2017-01-01 Holiday", "Last 2");
        AssertEqual(db.Last({2017, 6, 1}), "2017-03-08 Holiday", "Last 3");
   }
}
*/