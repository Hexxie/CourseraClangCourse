#pragma once

#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

class Date {
public:
  Date(int new_year, int new_month, int new_day);

  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;

private:
  int year;
  int month;
  int day;
};

extern bool operator<(const Date& lhs, const Date& rhs);
extern bool operator==(const Date& lhs, const Date& rhs);
extern bool operator!=(const Date& lhs, const Date& rhs);
extern bool operator<=(const Date& lhs, const Date& rhs);
extern bool operator>=(const Date& lhs, const Date& rhs);
extern bool operator>(const Date& lhs, const Date& rhs);
extern ostream& operator<<(ostream& stream, const Date& date);

extern Date ParseDate(istream& date_stream);