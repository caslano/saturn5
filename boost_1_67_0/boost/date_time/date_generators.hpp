#ifndef DATE_TIME_DATE_GENERATORS_HPP__
#define DATE_TIME_DATE_GENERATORS_HPP__

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

/*! @file date_generators.hpp
  Definition and implementation of date algorithm templates
*/

#include <stdexcept>
#include <sstream>
#include <boost/throw_exception.hpp>
#include <boost/date_time/date.hpp>
#include <boost/date_time/compiler_config.hpp>

namespace boost {
namespace date_time {

  //! Base class for all generators that take a year and produce a date.
  /*! This class is a base class for polymorphic function objects that take
    a year and produce a concrete date.
    @tparam date_type The type representing a date.  This type must
    export a calender_type which defines a year_type.
  */
  template<class date_type>
  class year_based_generator
  {
  public:
    typedef typename date_type::calendar_type calendar_type;
    typedef typename calendar_type::year_type        year_type;
    year_based_generator() {}
    virtual ~year_based_generator() {}
    virtual date_type get_date(year_type y) const = 0;
    //! Returns a string for use in a POSIX time_zone string
    virtual std::string to_string() const =0;
  };

  //! Generates a date by applying the year to the given month and day.
  /*!
    Example usage:
    @code
    partial_date pd(1, Jan);
    partial_date pd2(70);
    date d = pd.get_date(2002); //2002-Jan-01
    date d2 = pd2.get_date(2002); //2002-Mar-10
    @endcode
    \ingroup date_alg
  */
  template<class date_type>
 class partial_date : public year_based_generator<date_type>
 {
 public:
   typedef typename date_type::calendar_type calendar_type;
   typedef typename calendar_type::day_type         day_type;
   typedef typename calendar_type::month_type       month_type;
   typedef typename calendar_type::year_type        year_type;
   typedef typename date_type::duration_type        duration_type;
   typedef typename duration_type::duration_rep     duration_rep;
   partial_date(day_type d, month_type m) :
     day_(d),
     month_(m)
   {}
   //! Partial date created from number of days into year. Range 1-366
   /*! Allowable values range from 1 to 366. 1=Jan1, 366=Dec31. If argument
    * exceeds range, partial_date will be created with closest in-range value.
    * 60 will always be Feb29, if get_date() is called with a non-leap year
    * an exception will be thrown */
   partial_date(duration_rep days) :
     day_(1), // default values
     month_(1)
   {
     date_type d1(2000,1,1);
     if(days > 1) {
       if(days > 366) // prevents wrapping
       {
         days = 366;
       }
       days = days - 1;
       duration_type dd(days);
       d1 = d1 + dd;
     }
     day_ = d1.day();
     month_ = d1.month();
   }
   //! Return a concrete date when provided with a year specific year.
   /*! Will throw an 'invalid_argument' exception if a partial_date object,
    * instantiated with Feb-29, has get_date called with a non-leap year.
    * Example:
    * @code
    * partial_date pd(29, Feb);
    * pd.get_date(2003); // throws invalid_argument exception
    * pg.get_date(2000); // returns 2000-2-29
    * @endcode
         */
   date_type get_date(year_type y) const
   {
     if((day_ == 29) && (month_ == 2) && !(calendar_type::is_leap_year(y))) {
       std::ostringstream ss;
       ss << "No Feb 29th in given year of " << y << ".";
       boost::throw_exception(std::invalid_argument(ss.str()));
     }
     return date_type(y, month_, day_);
   }
   date_type operator()(year_type y) const
   {
     return get_date(y);
     //return date_type(y, month_, day_);
   }
   bool operator==(const partial_date& rhs) const
   {
     return (month_ == rhs.month_) && (day_ == rhs.day_);
   }
   bool operator<(const partial_date& rhs) const
   {
     if (month_ < rhs.month_) return true;
     if (month_ > rhs.month_) return false;
     //months are equal
     return (day_ < rhs.day_);
   }

   // added for streaming purposes
   month_type month() const
   {
     return month_;
   }
   day_type day() const
   {
     return day_;
   }

   //! Returns string suitable for use in POSIX time zone string
   /*! Returns string formatted with up to 3 digits:
    * Jan-01 == "0"
    * Feb-29 == "58"
    * Dec-31 == "365" */
   virtual std::string to_string() const
   {
     std::ostringstream ss;
     date_type d(2004, month_, day_);
     unsigned short c = d.day_of_year();
     c--; // numbered 0-365 while day_of_year is 1 based...
     ss << c;
     return ss.str();
   }
 private:
   day_type day_;
   month_type month_;
 };

  //! Returns nth arg as string. 1 -> "first", 2 -> "second", max is 5.
  inline const char* nth_as_str(int ele)
  {
    static const char* const _nth_as_str[] = {"out of range", "first", "second",
                                              "third", "fourth", "fifth"};
    if(ele >= 1 && ele <= 5) {
      return _nth_as_str[ele];
    }
    else {
      return _nth_as_str[0];
    }
  }

  //! Useful generator functor for finding holidays
  /*! Based on the idea in Cal. Calc. for finding holidays that are
   *  the 'first Monday of September'. When instantiated with
   *  'fifth' kday of month, the result will be the last kday of month
   *  which can be the fourth or fifth depending on the structure of
   *  the month.
   *
   *  The algorithm here basically guesses for the first
   *  day of the month.  Then finds the first day of the correct
   *  type.  That is, if the first of the month is a Tuesday
   *  and it needs Wenesday then we simply increment by a day
   *  and then we can add the length of a week until we get
   *  to the 'nth kday'.  There are probably more efficient
   *  algorithms based on using a mod 7, but this one works
   *  reasonably well for basic applications.
   *  \ingroup date_alg
   */
  template<class date_type>
  class nth_kday_of_month : public year_based_generator<date_type>
  {
  public:
    typedef typename date_type::calendar_type calendar_type;
    typedef typename calendar_type::day_of_week_type  day_of_week_type;
    typedef typename calendar_type::month_type        month_type;
    typedef typename calendar_type::year_type         year_type;
    typedef typename date_type::duration_type        duration_type;
    enum week_num {first=1, second, third, fourth, fifth};
    nth_kday_of_month(week_num week_no,
                      day_of_week_type dow,
                      month_type m) :
      month_(m),
      wn_(week_no),
      dow_(dow)
    {}
    //! Return a concrete date when provided with a year specific year.
    date_type get_date(year_type y) const
    {
      date_type d(y, month_, 1); //first day of month
      duration_type one_day(1);
      duration_type one_week(7);
      while (dow_ != d.day_of_week()) {
        d = d + one_day;
      }
      int week = 1;
      while (week < wn_) {
        d = d + one_week;
        week++;
      }
      // remove wrapping to next month behavior
      if(d.month() != month_) {
        d = d - one_week;
      }
      return d;
    }
    // added for streaming
    month_type month() const
    {
      return month_;
    }
    week_num nth_week() const
    {
      return wn_;
    }
    day_of_week_type day_of_week() const
    {
      return dow_;
    }
    const char* nth_week_as_str() const
    {
      return nth_as_str(wn_);
    }
    //! Returns string suitable for use in POSIX time zone string
    /*! Returns a string formatted as "M4.3.0" ==> 3rd Sunday in April. */
    virtual std::string to_string() const
    {
     std::ostringstream ss;
     ss << 'M'
       << static_cast<int>(month_) << '.'
       << static_cast<int>(wn_) << '.'
       << static_cast<int>(dow_);
     return ss.str();
    }
  private:
    month_type month_;
    week_num wn_;
    day_of_week_type dow_;
  };

  //! Useful generator functor for finding holidays and daylight savings
  /*! Similar to nth_kday_of_month, but requires less paramters
   *  \ingroup date_alg
   */
  template<class date_type>
  class first_kday_of_month : public year_based_generator<date_type>
  {
  public:
    typedef typename date_type::calendar_type calendar_type;
    typedef typename calendar_type::day_of_week_type  day_of_week_type;
    typedef typename calendar_type::month_type        month_type;
    typedef typename calendar_type::year_type         year_type;
    typedef typename date_type::duration_type        duration_type;
    //!Specify the first 'Sunday' in 'April' spec
    /*!@param dow The day of week, eg: Sunday, Monday, etc
     * @param m The month of the year, eg: Jan, Feb, Mar, etc
     */
    first_kday_of_month(day_of_week_type dow, month_type m) :
      month_(m),
      dow_(dow)
    {}
    //! Return a concrete date when provided with a year specific year.
    date_type get_date(year_type year) const
    {
      date_type d(year, month_,1);
      duration_type one_day(1);
      while (dow_ != d.day_of_week()) {
        d = d + one_day;
      }
      return d;
    }
    // added for streaming
    month_type month() const
    {
      return month_;
    }
    day_of_week_type day_of_week() const
    {
      return dow_;
    }
    //! Returns string suitable for use in POSIX time zone string
    /*! Returns a string formatted as "M4.1.0" ==> 1st Sunday in April. */
    virtual std::string to_string() const
    {
     std::ostringstream ss;
     ss << 'M'
       << static_cast<int>(month_) << '.'
       << 1 << '.'
       << static_cast<int>(dow_);
     return ss.str();
    }
  private:
    month_type month_;
    day_of_week_type dow_;
  };



  //! Calculate something like Last Sunday of January
  /*! Useful generator functor for finding holidays and daylight savings
   *  Get the last day of the month and then calculate the difference
   *  to the last previous day.
   *  @tparam date_type A date class that exports day_of_week, month_type, etc.
   *  \ingroup date_alg
   */
  template<class date_type>
  class last_kday_of_month : public year_based_generator<date_type>
  {
  public:
    typedef typename date_type::calendar_type calendar_type;
    typedef typename calendar_type::day_of_week_type  day_of_week_type;
    typedef typename calendar_type::month_type        month_type;
    typedef typename calendar_type::year_type         year_type;
    typedef typename date_type::duration_type        duration_type;
    //!Specify the date spec like last 'Sunday' in 'April' spec
    /*!@param dow The day of week, eg: Sunday, Monday, etc
     * @param m The month of the year, eg: Jan, Feb, Mar, etc
     */
    last_kday_of_month(day_of_week_type dow, month_type m) :
      month_(m),
      dow_(dow)
    {}
    //! Return a concrete date when provided with a year specific year.
    date_type get_date(year_type year) const
    {
      date_type d(year, month_, calendar_type::end_of_month_day(year,month_));
      duration_type one_day(1);
      while (dow_ != d.day_of_week()) {
        d = d - one_day;
      }
      return d;
    }
    // added for streaming
    month_type month() const
    {
      return month_;
    }
    day_of_week_type day_of_week() const
    {
      return dow_;
    }
    //! Returns string suitable for use in POSIX time zone string
    /*! Returns a string formatted as "M4.5.0" ==> last Sunday in April. */
    virtual std::string to_string() const
    {
      std::ostringstream ss;
      ss << 'M'
         << static_cast<int>(month_) << '.'
         << 5 << '.'
         << static_cast<int>(dow_);
      return ss.str();
    }
  private:
    month_type month_;
    day_of_week_type dow_;
   };


  //! Calculate something like "First Sunday after Jan 1,2002
  /*! Date generator that takes a date and finds kday after
   *@code
     typedef boost::date_time::first_kday_after<date> firstkdayafter;
     firstkdayafter fkaf(Monday);
     fkaf.get_date(date(2002,Feb,1));
   @endcode
   *  \ingroup date_alg
   */
  template<class date_type>
  class first_kday_after
  {
  public:
    typedef typename date_type::calendar_type calendar_type;
    typedef typename calendar_type::day_of_week_type day_of_week_type;
    typedef typename date_type::duration_type        duration_type;
    first_kday_after(day_of_week_type dow) :
      dow_(dow)
    {}
    //! Return next kday given.
    date_type get_date(date_type start_day) const
    {
      duration_type one_day(1);
      date_type d = start_day + one_day;
      while (dow_ != d.day_of_week()) {
        d = d + one_day;
      }
      return d;
    }
    // added for streaming
    day_of_week_type day_of_week() const
    {
      return dow_;
    }
  private:
    day_of_week_type dow_;
  };

  //! Calculate something like "First Sunday before Jan 1,2002
  /*! Date generator that takes a date and finds kday after
   *@code
     typedef boost::date_time::first_kday_before<date> firstkdaybefore;
     firstkdaybefore fkbf(Monday);
     fkbf.get_date(date(2002,Feb,1));
   @endcode
   *  \ingroup date_alg
   */
  template<class date_type>
  class first_kday_before
  {
  public:
    typedef typename date_type::calendar_type calendar_type;
    typedef typename calendar_type::day_of_week_type day_of_week_type;
    typedef typename date_type::duration_type        duration_type;
    first_kday_before(day_of_week_type dow) :
      dow_(dow)
    {}
    //! Return next kday given.
    date_type get_date(date_type start_day) const
    {
      duration_type one_day(1);
      date_type d = start_day - one_day;
      while (dow_ != d.day_of_week()) {
        d = d - one_day;
      }
      return d;
    }
    // added for streaming
    day_of_week_type day_of_week() const
    {
      return dow_;
    }
  private:
    day_of_week_type dow_;
  };

  //! Calculates the number of days until the next weekday
  /*! Calculates the number of days until the next weekday.
   * If the date given falls on a Sunday and the given weekday
   * is Tuesday the result will be 2 days */
  template<typename date_type, class weekday_type>
  inline
  typename date_type::duration_type days_until_weekday(const date_type& d, const weekday_type& wd)
  {
    typedef typename date_type::duration_type duration_type;
    duration_type wks(0);
    duration_type dd(wd.as_number() - d.day_of_week().as_number());
    if(dd.is_negative()){
      wks = duration_type(7);
    }
    return dd + wks;
  }

  //! Calculates the number of days since the previous weekday
  /*! Calculates the number of days since the previous weekday
   * If the date given falls on a Sunday and the given weekday
   * is Tuesday the result will be 5 days. The answer will be a positive
   * number because Tuesday is 5 days before Sunday, not -5 days before. */
  template<typename date_type, class weekday_type>
  inline
  typename date_type::duration_type days_before_weekday(const date_type& d, const weekday_type& wd)
  {
    typedef typename date_type::duration_type duration_type;
    duration_type wks(0);
    duration_type dd(wd.as_number() - d.day_of_week().as_number());
    if(dd.days() > 0){
      wks = duration_type(7);
    }
    // we want a number of days, not an offset. The value returned must
    // be zero or larger.
    return (-dd + wks);
  }

  //! Generates a date object representing the date of the following weekday from the given date
  /*! Generates a date object representing the date of the following
   * weekday from the given date. If the date given is 2004-May-9
   * (a Sunday) and the given weekday is Tuesday then the resulting date
   * will be 2004-May-11. */
  template<class date_type, class weekday_type>
  inline
  date_type next_weekday(const date_type& d, const weekday_type& wd)
  {
    return d + days_until_weekday(d, wd);
  }

  //! Generates a date object representing the date of the previous weekday from the given date
  /*! Generates a date object representing the date of the previous
   * weekday from the given date. If the date given is 2004-May-9
   * (a Sunday) and the given weekday is Tuesday then the resulting date
   * will be 2004-May-4. */
  template<class date_type, class weekday_type>
  inline
  date_type previous_weekday(const date_type& d, const weekday_type& wd)
  {
    return d - days_before_weekday(d, wd);
  }

} } //namespace date_time




#endif


/* date_generators.hpp
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
*/