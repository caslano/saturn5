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