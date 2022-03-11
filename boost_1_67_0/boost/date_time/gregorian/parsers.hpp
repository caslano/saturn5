#ifndef GREGORIAN_PARSERS_HPP___
#define GREGORIAN_PARSERS_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/date_parsing.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/parse_format_base.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/find_match.hpp>
#include <string>
#include <iterator>

namespace boost {
namespace gregorian {

  //! Return special_value from string argument
  /*! Return special_value from string argument. If argument is
   * not one of the special value names (defined in names.hpp),
   * return 'not_special' */
  inline
  date_time::special_values
  special_value_from_string(const std::string& s) {
    static const char* const special_value_names[date_time::NumSpecialValues]
      = {"not-a-date-time","-infinity","+infinity","min_date_time",
         "max_date_time","not_special"};

    short i = date_time::find_match(special_value_names,
                                    special_value_names,
                                    date_time::NumSpecialValues,
                                    s);
    if(i >= date_time::NumSpecialValues) { // match not found
      return date_time::not_special;
    }
    else {
      return static_cast<date_time::special_values>(i);
    }
  }

  //! Deprecated: Use from_simple_string
  inline date from_string(const std::string& s) {
    return date_time::parse_date<date>(s);
  }

  //! From delimited date string where with order year-month-day eg: 2002-1-25 or 2003-Jan-25 (full month name is also accepted)
  inline date from_simple_string(const std::string& s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_iso);
  }
  
  //! From delimited date string where with order year-month-day eg: 1-25-2003 or Jan-25-2003 (full month name is also accepted)
  inline date from_us_string(const std::string& s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_us);
  }
  
  //! From delimited date string where with order day-month-year eg: 25-1-2002 or 25-Jan-2003 (full month name is also accepted)
  inline date from_uk_string(const std::string& s) {
    return date_time::parse_date<date>(s, date_time::ymd_order_dmy);
  }
  
  //! From iso type date string where with order year-month-day eg: 20020125
  inline date from_undelimited_string(const std::string& s) {
    return date_time::parse_undelimited_date<date>(s);
  }

  //! From iso type date string where with order year-month-day eg: 20020125
  inline date date_from_iso_string(const std::string& s) {
    return date_time::parse_undelimited_date<date>(s);
  }

#if !(defined(BOOST_NO_STD_ITERATOR_TRAITS))
  //! Stream should hold a date in the form of: 2002-1-25. Month number, abbrev, or name are accepted
  /* Arguments passed in by-value for convertability of char[] 
   * to iterator_type. Calls to from_stream_type are by-reference 
   * since conversion is already done */
  template<class iterator_type>
  inline date from_stream(iterator_type beg, iterator_type end) {
    if(beg == end)
    {
      return date(not_a_date_time);
    }
    typedef typename std::iterator_traits<iterator_type>::value_type value_type;
    return  date_time::from_stream_type<date>(beg, end, value_type());
  }
#endif //BOOST_NO_STD_ITERATOR_TRAITS
  
#if (defined(_MSC_VER) && (_MSC_VER < 1300))
    // This function cannot be compiled with MSVC 6.0 due to internal compiler shorcomings
#else
  //! Function to parse a date_period from a string (eg: [2003-Oct-31/2003-Dec-25])
  inline date_period date_period_from_string(const std::string& s){
    return date_time::from_simple_string_type<date,char>(s);
  }
#  if !defined(BOOST_NO_STD_WSTRING)
  //! Function to parse a date_period from a wstring (eg: [2003-Oct-31/2003-Dec-25])
  inline date_period date_period_from_wstring(const std::wstring& s){
    return date_time::from_simple_string_type<date,wchar_t>(s);
  }
#  endif // BOOST_NO_STD_WSTRING
#endif

} } //namespace gregorian

#endif

/* parsers.hpp
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
*/