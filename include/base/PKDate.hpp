
#ifndef __PKDate_H__
#define __PKDate_H__

#include <ostream>

//namespace pekronus
//{
  class PKDate
  {
    typedef unsigned short int DMYType;
  public:
    //! default ctor
    PKDate()
      : _day(0),
	_month(0),
	_year(0),
	_day_num(0)
    {}
    //! construct from day/month/year
    PKDate(const DMYType d, const DMYType m, const DMYType y);

    
    //! check for validity
    bool is_valid() const
    {
      return _day_num != 0;
    }

    // invalidate the date
    void invalidate()
    {
      _day_num = _day = _month = _year = 0;
    }
    //! get ordinal days
    int day_num() const
    {return _day_num;}
    
    // add days
    void add_days(int days)
    {
      _day_num += days;
      _day = _month = _year = 0;
    }

    //! add years
    void add_years(int years);

    //! return day
    DMYType day() const
    {
      if (_day == 0)
	_num_to_date();
      return _day;
    }
    //! return day
    DMYType month() const
    {
      if (_month == 0)
	_num_to_date();
      return _month;
    }
    //! return year
    DMYType year() const
    {
      if (_year == 0)
	_num_to_date();
      return _year;
    }
    
    //! check if leap year
    static bool is_leap_year(const DMYType y)
    {
      if (y % 4 != 0)
	return false;
      if (y % 100 == 0)
	return y % 400 == 0 ? true : false;
      return true;
    }
  protected:
    mutable DMYType _day; // 1-31
    mutable DMYType _month; // 1-12
    mutable DMYType _year; // >= 0
    int _day_num;
    
    int _date_to_num();
    void _num_to_date() const;
    // count number of leap years between zero and the date
    static DMYType count_leap_years(const DMYType d, const DMYType m, const DMYType y);
    //! count number of days from 0/0/0
    static int date_to_num(const short d, const short m, const short y);

    
    static DMYType _days_before_month[];
    static DMYType _days_in_month[];
    static DMYType _days_before_month_leap[];
    static DMYType _days_in_month_leap[];

    friend std::ostream& operator<<(std::ostream& os, const PKDate& date);
  };
//}
#endif
