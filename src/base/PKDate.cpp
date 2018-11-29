#include <PKDate.hpp>

//using namespace pekronus;

PKDate::DMYType PKDate::_days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
PKDate::DMYType PKDate::_days_before_month[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 272, 304, 334};
PKDate::DMYType PKDate::_days_in_month_leap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
PKDate::DMYType PKDate::_days_before_month_leap[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 273, 305, 335};


//! construct from day/month/year
PKDate::PKDate(const DMYType d, const DMYType m, const DMYType y)
    : _day(d),
      _month(m),
      _year(y)
{
    if (m > 12 || m < 1 || d < 1 || d > 31 || y < 0)
    {
        invalidate();
        return;
    }
    const DMYType days_in_month =   is_leap_year(y) ? _days_in_month_leap[m-1]
                      : _days_in_month[m-1];
    if (d > days_in_month)
    {
        invalidate();
        return;
    }

    // convert to ordinal days
    _date_to_num();
  
}

void
PKDate::_num_to_date() const
{
    if (!is_valid())
    {
        _day = _month = _year = 0;
        return;
    }
    int tyear = _day_num/365;
    int nly = count_leap_years(1, 1, tyear);
    tyear -= nly/365;
    nly = count_leap_years(1, 1, tyear);

    int remainder_days = _day_num - 365*tyear - nly;
    // determine year first
    int count = 0;
    int add_years = 0;
    for (add_years = 0; ;++add_years)
    {
        count += is_leap_year(tyear + add_years) ? 365 : 364;
        if (count >= remainder_days)
            break;
    }
    // now we know the year
    _year = tyear + add_years;
    if (add_years)
        remainder_days = _day_num - 365*_year - count_leap_years(1, 1, _year);
  
    const bool leap_year = is_leap_year(_year);
    const DMYType* dim =  leap_year ? &_days_in_month_leap[0] : &_days_in_month[0];
    const DMYType* dbm =  leap_year ? &_days_before_month_leap[0] : &_days_before_month[0];
    // cycle through months
    for (int m = 1; m <= 12; ++m)
    {
        const int days = remainder_days - dbm[m-1];
        if (days <= dim[m-1])
	{
            _day = days;
            _month = m;
            break;
	}
    }
}


int
PKDate::_date_to_num()
{
    _day_num = 365*_year + _day;
    // add all days in the months before
    _day_num += _days_before_month[_month-1];
    // add a day for each leap year before
    _day_num += count_leap_years(_day, _month, _year);
  
    return _day_num;
}

PKDate::DMYType
PKDate::count_leap_years(const DMYType d, const DMYType m, const DMYType y) 
{
    DMYType t = m <= 2 ? y - 1 : y;
    return t/4 - t/100 + t/400;
}

//! add years
void
PKDate::add_years(int years)
{
    _year += years;
    // check for leap issues
    if (_day == 29 && _month == 2 && !is_leap_year(_year))
        _day = 29;

    _date_to_num();
}

std::ostream&
operator<<(std::ostream& os, const PKDate& date)
{
    os << date.month() << "/" << date.day() << "/" << date.year();
    return os;
}
