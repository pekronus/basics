
#ifndef __PKDate_H__
#define __PKDate_H__

namespace pekronus
{
  class PKDate
  {
    typedef unsigned short int DMYType;
  public:
    //! default ctor
    PKDate();
    //! construct from day/monnth/year
    PKDate(const DMYType d, const DMYType m, const DMYType y);
    //! check for validity
    bool is_valid() const;

  protected:
    mutable DMYType _day; // 1-31
    mutable DMYType _month; // 1-12
    mutable DMYType _year; // >= 0
    int _day_num;
    
    int _date_to_num();
    void _num_to_date();
    // count number of leap years between zero and the date
    DMYType _count_leap_years() const;
    //! count number of days from 0/0/0
    static int date_to_num(const short d, const short m, const short y);

    
    static DMYType _days_before_month[];
    static DMYType _days_in_month[];
  };
}
#endif
