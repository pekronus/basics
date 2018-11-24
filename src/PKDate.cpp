#include "PKDate.hpp"

using namespace pekronus;

PKDate::DMYType PKDate::_days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
PKDate::DMYType PKDate::_days_before_month[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 272, 304, 334};

int
PKDate::_date_to_num()
{
  int ret = 365*_year + _day;
  // add all days in the months before
  ret += _days_before_month[_month-1];
  // add a day for each leap year before
  ret += _count_leap_years();
  return ret;
}

PKDate::DMYType
PKDate::_count_leap_years() const
{
  DMYType t = _month <= 2 ? _year - 1 : _year;
  return t/4 - t/100 + t/400;
}
