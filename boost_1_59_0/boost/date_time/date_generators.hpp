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

#include <sstream>
#include <stdexcept>
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
    virtual std::string to_string() const = 0;
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
   date_type get_date(year_type y) const BOOST_OVERRIDE
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
   std::string to_string() const BOOST_OVERRIDE
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
   *  and it needs Wednesday then we simply increment by a day
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
    date_type get_date(year_type y) const BOOST_OVERRIDE
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
    std::string to_string() const BOOST_OVERRIDE
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
    date_type get_date(year_type year) const BOOST_OVERRIDE
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
    std::string to_string() const BOOST_OVERRIDE
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
    date_type get_date(year_type year) const BOOST_OVERRIDE
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
    std::string to_string() const BOOST_OVERRIDE
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