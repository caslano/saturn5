#ifndef GREG_WEEKDAY_HPP___
#define GREG_WEEKDAY_HPP___

/* Copyright (c) 2002,2003,2020 CrystalClear Software, Inc.
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

  //bring enum values into the namespace
  using date_time::Sunday;
  using date_time::Monday;
  using date_time::Tuesday;
  using date_time::Wednesday;
  using date_time::Thursday;
  using date_time::Friday;
  using date_time::Saturday;


  //! Exception that flags that a weekday number is incorrect
  struct BOOST_SYMBOL_VISIBLE bad_weekday : public std::out_of_range
  {
    bad_weekday() : std::out_of_range(std::string("Weekday is out of range 0..6")) {}
  };
  typedef CV::simple_exception_policy<unsigned short, 0, 6, bad_weekday> greg_weekday_policies;
  typedef CV::constrained_value<greg_weekday_policies> greg_weekday_rep;


  //! Represent a day within a week (range 0==Sun to 6==Sat)
  class BOOST_SYMBOL_VISIBLE greg_weekday : public greg_weekday_rep {
  public:
    typedef boost::date_time::weekdays weekday_enum;
    BOOST_CXX14_CONSTEXPR greg_weekday(value_type day_of_week_num) :
      greg_weekday_rep(day_of_week_num)
    {}

    BOOST_CXX14_CONSTEXPR value_type as_number() const {return value_;}
    BOOST_CXX14_CONSTEXPR weekday_enum as_enum() const {return static_cast<weekday_enum>(value_);}

    //! Return a 3 digit english string of the day of week (eg: Sun)
    const char* as_short_string() const
    {
      static const char* const short_weekday_names[]
        = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

      return short_weekday_names[value_];
    }

    //! Return a point to a long english string representing day of week
    const char* as_long_string() const
    {
      static const char* const long_weekday_names[]
        = {"Sunday","Monday","Tuesday","Wednesday", "Thursday", "Friday", "Saturday"};

      return long_weekday_names[value_];
    }


#ifndef BOOST_NO_STD_WSTRING

    //! Return a 3 digit english wchar_t string of the day of week (eg: Sun)
    const wchar_t* as_short_wstring() const
    {
      static const wchar_t* const w_short_weekday_names[]={L"Sun", L"Mon", L"Tue",
                                                           L"Wed", L"Thu", L"Fri", L"Sat"};
      return w_short_weekday_names[value_];
    }

    //! Return a point to a long english wchar_t string representing day of week
    const wchar_t* as_long_wstring()  const
    {
      static const wchar_t* const w_long_weekday_names[]= {L"Sunday",L"Monday",L"Tuesday",
                                                           L"Wednesday", L"Thursday",
                                                           L"Friday", L"Saturday"};
      return w_long_weekday_names[value_];
    }

#endif // BOOST_NO_STD_WSTRING


  };



} } //namespace gregorian



#endif

/* greg_weekday.hpp
/lCPpjHG+ynTsFLtqhw/sb5PcDUGSEl4hgUhp9krunsd+8/NyP7vhNYqG2XXbGrXbcJ6p+1sPp1tgmIx4ucOZ3qrJ8mAIvJA2DW3AcLCFgGWiW5chl3dnheawLtFgPePJb9C6p4Tjkzy49WfoxlAl8NQF/vAKAMaum+y404825gBp+FtOeyQzLXfYiIvhrf9i1+WZsSIwkkbd9f8ytykfpvNqSWw43Pz98rZ9yGvojDE09hsj/eb6bU2qtW1Ye4YycJufTG1pMz7wKrDFoxYhrpvdFq38jUX9S1YRK+c9tKR3olw9kwe8gxg5a1yoQWaqDUOTEg/s3uXHRPklPXMrvQfseXngLe1otMLiXQDxpbdngcMOD21bnxvJVST5zj9wG94/g1Jd4/3AzSwKCK2nKrE+fpclMT5YLJlS8a8nIkVXIoDDBoYEWaJNFIyOwV4EerdC+VLyhm04m/2Sd5a0XCTotkplnZ5I+GDmuslyqSk1ajvj/WhMjQONxZMsKVJFJqQXrPsIQAX1pPP9k5wDnuHeqpPcdMq7lqEQOH4PmX4g+tLJDmOCvDLyA==
*/