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
cLuEyYAsK9MKBRAKGsAk0CdVMCkFUDwEYTlIK71EyELrKFzaSkCBU2h6wNT5HQqzEGMxtTTIj0qBkJYGYd74xq1EkQVQ6lZQpAp1IT8uuh4uo+t6hQbozElS4tvzyjPvxaBhsIKEzEoJ7TU/HNZikJfKPu53pJT3M1lY5XeysDrKJSiHejibeVnQkboUre2WPRysJ6sUQChoAJNAj1TBpBRA8RCE5SCtVA4hC61DWDeA8o+qcUqV36EwCzERU0vTHdIpENLSIAxdAS3WFSHLyFy3giJVqAu5IGrspZUSL1oJdOYkKeVbayXHemnlMFjlpQFoob1Y5f02gLKz5YLf2XKvYTW01zDq02sIJCorOfXD2QQX/Xpet/VOyxI268kaBRAKGsAk0NlUMCkFUDwEYTlIK5VDyELrKFzaAECBU2h6wNT5HQqzEBMxtTQ9IZ0CIS0NwtAV0GJdEbKMzHUrKFKFupAdUeMyWlnQWgl05iQp5VtrJcd6aeUwWPVKA9BCe7Hq9dsAxgy9HaCi1NOXsp6+lHj65DpwA1RVLG9EAKqfrljFdcqx/EMTYVxOjgTK01f6CIV4+oCmPH2a0yoZ8yt9Y3YCrUPY8z0KkS4fFekwrJD5ZNTTAEW1h3Yrawgn4yjvtyR8H8gt23c7fvvugh/T1ePXdPVGWfflOBYrKLjoRyd7rXdOxqhcRz0KoCgoQFS27lcwKQ3QPNbIcFGbLoQYysNFD9Pl/VAmMHV+h8IsxFhMLQ3yo1IgpKVBGOoCWqwuQpaRuW4FRapQF/IOVi/glWilxIpWAlfYSLIdnlqJeG+t9MuqIHZLS+zNqjC8JQovld3qd/a21c/g9XG/g9dCFPFgz3UV4nBIX7QMPHFMMKC7gitZARQFBagWS1TBpDRA88jLcFE3AIQYysNFjwZQrdRa6HFKld+hMAsxEVNL44R0CoS0NAjzvmduAIosgFK3gkLhkkIOjOawp1Zu1VoJXLCRZBzloZWI99ZKv6wgHrNSEnv3AL4bwFivNTpf/o0dfltIIOyji3D8dhFbuYWAPYkhG9XC+q1a4MmcTAaxFawFCqAoKECNjOkqmJQGaB69Mp7ULQQhhvJ40qOFeD+EC0yd36EwCzEWU0uD/KgUCGlpEIY+gRbrk5BlZK5bQZEq1IUcZVUHnqet1545oAsnmzLqeXwH8V6euWHwgojMS0ntwQvx/ryAZUdJgYjPUVJ12McR+B1Rn9PFAMWDPdeG2LOwfoUSeDK0keEUawo4MUBR0ICYjA0qhJQCaB4FGZfoJoAQQ3lc4tEEvF+2BKbO71CYhZiIqaWJhnUKhLQ0CENZQIuVRcgyMtetoHAVciFzeLRUgodaSryoJdCZk6TEt5daIt5LLYfDKyy8tNTevHw2gd2GdoSPKp3iZewUL8MTKvVsUEZVsryBBqh+ms3hWuVY/qGJMC4nRwI1xSt9ZE2meEBTUzzNyZGNQErjmJ1A6xD2fG9NpIuOEelgWbmyEVlaARKvrytmNeGUElU6NECsz+OKZfvvaMRn/x3zY7yqx/g0XjUU77KnMGsouKjnZ4HHnS4Dtsp2XQVQFBQgLoewK5iUAigegrAcpFV1I2ShdSbsYbziSkGEHqdU+R0KsxBjMbU0yI9KgZCWBmHoCmixrghZRua6FRSpQl3IMdHKiKdWIl5rZYy1UqWMeWplzFsrh8NKbJcW2pNV2Kd3qnJo79Toslrtt40kjDRDDhdiY3wOF+IUD/asr1wS4KKf3o1bxZZOS26TVgChoAEgwZrCKeIKoHgIwnKQVlqJkIXWUbi0jYACp9D0gKnzOxRmISZiamniYZ0CIS0NwlAn0GJ1ErKMzHUrKAQvKeQ=
*/