#include "database.h"
#include "../condition_parser/condition_parser.h"
#include "../../include/test_runner.h"

#include <sstream>
#include <string>
#include <set>
#include <vector>

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
   {
      Database db;
      db.Add({2017, 6, 1}, "1st of June");
      db.Add({2017, 1, 1}, "Holiday");
      db.Add({2017, 3, 8}, "Holiday");
      db.Add({2017, 1, 1}, "New Year");
      db.Add({2017, 1, 1}, "New Year");
      db.Add({2017, 1, 1}, "Holiday");
      db.Add({2017, 3, 8}, "Holiday");
      db.Add({2017, 1, 1}, "New Year");
      db.Add({2017, 5, 9}, "Holiday");
      db.Add({2017, 1, 1}, "New Year");
      db.Add({2017, 3, 8}, "Holiday");
      db.Add({2017, 1, 1}, "Holiday");

      AssertEqual(db.Last({2016, 12, 31}), "No entries", "Last 4");
      AssertEqual(db.Last({2017, 1, 1}), "2017-01-01 Holiday", "Last 5");
   }
   {
      Database db;
      db.Add({2017, 1, 1}, "1st of June");
      db.Add({2017, 1, 1}, "Holiday");

      AssertEqual(db.Last({2017, 1, 1}), "2017-01-01 Holiday", "Last 6");
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

      AssertEqual(db.RemoveIf(predicate), 2, "RemoveIf 1");
   }

   {
       Database db;
       db.Add({2017, 6, 1}, "1st of June");
       db.Add({2017, 7, 8}, "8th of July");
       db.Add({2017, 7, 8}, "Someone's birthday");

      istringstream is("");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 3, "RemoveIf 2");
   }

   {
       Database db;
       db.Add({2017, 6, 1}, "1st of June");
       db.Add({2017, 7, 8}, "8th of July");
       db.Add({2017, 7, 8}, "Someone's birthday");
       db.Add({2017, 6, 1}, "1st of June");

      istringstream is("date == 2017-07-08");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      AssertEqual(db.RemoveIf(predicate), 2, "RemoveIf 3");
   }
   {
      Database db;
      db.Add({2017, 6, 1}, "1st of June");
      db.Add({2017, 6, 1}, "1st of June");

      istringstream is("date == 2017-06-01");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
         return condition->Evaluate(date, event);
   };

   AssertEqual(db.RemoveIf(predicate), 1, "RemoveIf 4");
   AssertEqual(db.RemoveIf(predicate), 0, "RemoveIf 5");
   }
      {
      Database db;

      istringstream is("");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
         return condition->Evaluate(date, event);
   };

   AssertEqual(db.RemoveIf(predicate), 0, "RemoveIf 6");
   }
}


void TestFindIf() {
   {
      Database db;
      db.Add({2017, 1, 1}, "New Year");
      db.Add({2017, 3, 8}, "Holiday");
      db.Add({2017, 1, 1}, "Holiday");

      istringstream is(R"(event != "working day")");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      vector<string> expected = {"2017-01-01 Holiday", "2017-01-01 New Year", "2017-03-08 Holiday"};

      AssertEqual(entries, expected, "FindIf 1");
      AssertEqual(entries.size(), 3, "FindIf 2");
   }
   {
      Database db;
      db.Add({2017, 11, 21}, "Tuesday");
      db.Add({2017, 11, 20}, "Monday");
      db.Add({2017, 11, 21}, "Weekly meeting");

      istringstream is(R"(event != "Weekly meeting")");
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      vector<string> expected = {"2017-11-20 Monday", "2017-11-21 Tuesday"};

      AssertEqual(entries, expected, "FindIf 3");
      AssertEqual(entries.size(), 2, "FindIf 4");
   }
}
