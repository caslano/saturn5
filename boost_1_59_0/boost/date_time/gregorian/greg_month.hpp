#ifndef GREG_MONTH_HPP___
#define GREG_MONTH_HPP___

/* Copyright (c) 2002,2003, 2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/constrained_value.hpp>
#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace gregorian {

  typedef date_time::months_of_year months_of_year;

  //bring enum values into the namespace
  using date_time::Jan;
  using date_time::Feb;
  using date_time::Mar;
  using date_time::Apr;
  using date_time::May;
  using date_time::Jun;
  using date_time::Jul;
  using date_time::Aug;
  using date_time::Sep;
  using date_time::Oct;
  using date_time::Nov;
  using date_time::Dec;
  using date_time::NotAMonth;
  using date_time::NumMonths;

  //! Exception thrown if a greg_month is constructed with a value out of range
  struct BOOST_SYMBOL_VISIBLE bad_month : public std::out_of_range
  {
    bad_month() : std::out_of_range(std::string("Month number is out of range 1..12")) {}
  };
  //! Build a policy class for the greg_month_rep
  typedef CV::simple_exception_policy<unsigned short, 1, 12, bad_month> greg_month_policies;
  //! A constrained range that implements the gregorian_month rules
  typedef CV::constrained_value<greg_month_policies> greg_month_rep;


  //! Wrapper class to represent months in gregorian based calendar
  class BOOST_SYMBOL_VISIBLE greg_month : public greg_month_rep {
  public:
    typedef date_time::months_of_year month_enum;

    //! Construct a month from the months_of_year enumeration
    BOOST_CXX14_CONSTEXPR greg_month(month_enum theMonth) :
      greg_month_rep(static_cast<greg_month_rep::value_type>(theMonth)) {}
    //! Construct from a short value
    BOOST_CXX14_CONSTEXPR greg_month(value_type theMonth) : greg_month_rep(theMonth) {}
    //! Convert the value back to a short
    BOOST_CXX14_CONSTEXPR operator value_type()  const {return value_;}
    //! Returns month as number from 1 to 12
    BOOST_CXX14_CONSTEXPR value_type as_number() const {return value_;}
    BOOST_CXX14_CONSTEXPR month_enum as_enum() const {return static_cast<month_enum>(value_);}

    //! Returns 3 char english string for the month ex: Jan, Feb, Mar, Apr
    const char*
    as_short_string() const
    {
      static const char* const short_month_names[NumMonths]
        = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec", "NAM"};
      return short_month_names[value_-1];
    }

    //! Returns full name of month as string in english ex: January, February
    const char*
    as_long_string() const
    {
      static const char* const long_month_names[NumMonths]
        = {"January","February","March","April","May","June","July","August",
           "September","October","November","December","NotAMonth"};
      return long_month_names[value_-1];
    }

#ifndef BOOST_NO_STD_WSTRING

    //! Returns 3 wchar_t english string for the month ex: Jan, Feb, Mar, Apr
    const wchar_t*
    as_short_wstring() const
    {
      static const wchar_t* const w_short_month_names[NumMonths]
        = {L"Jan",L"Feb",L"Mar",L"Apr",L"May",L"Jun",L"Jul",L"Aug",L"Sep",L"Oct",
           L"Nov",L"Dec",L"NAM"};
      return w_short_month_names[value_-1];
    }

    //! Returns full name of month as wchar_t string in english ex: January, February
    const wchar_t*
    as_long_wstring() const
    {
      static const wchar_t* const w_long_month_names[NumMonths]
        = {L"January",L"February",L"March",L"April",L"May",L"June",L"July",L"August",
           L"September",L"October",L"November",L"December",L"NotAMonth"};
      return w_long_month_names[value_-1];
    }

#endif // BOOST_NO_STD_WSTRING

    /* parameterized as_*_string functions are intended to be called
     * from a template function: "... as_short_string(charT c='\0');" */
    const char* as_short_string(char) const
    {
      return as_short_string();
    }
    const char* as_long_string(char) const
    {
      return as_long_string();
    }
#ifndef BOOST_NO_STD_WSTRING
    const wchar_t* as_short_string(wchar_t) const
    {
      return as_short_wstring();
    }
    const wchar_t* as_long_string(wchar_t) const
    {
      return as_long_wstring();
    }
#endif // BOOST_NO_STD_WSTRING
  };

} } //namespace gregorian

#endif

/* greg_month.hpp
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
*/