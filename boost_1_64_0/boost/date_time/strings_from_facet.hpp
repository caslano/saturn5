#ifndef DATE_TIME_STRINGS_FROM_FACET__HPP___
#define DATE_TIME_STRINGS_FROM_FACET__HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <cstring>
#include <sstream>
#include <string>
#include <vector>
#include <locale>
#include <iterator>

namespace boost { namespace date_time {

//! This function gathers up all the month strings from a std::locale
/*! Using the time_put facet, this function creates a collection of
 *  all the month strings from a locale.  This is handy when building
 *  custom date parsers or formatters that need to be localized.
 *
 *@param charT The type of char to use when gathering typically char
 *             or wchar_t.
 *@param locale The locale to use when gathering the strings
 *@param short_strings True(default) to gather short strings,
 *                     false for long strings.
 *@return A vector of strings containing the strings in order. eg:
 *        Jan, Feb, Mar, etc.
 */
template<typename charT>
std::vector<std::basic_string<charT> >
gather_month_strings(const std::locale& locale, bool short_strings=true)
{
  typedef std::basic_string<charT> string_type;
  typedef std::vector<string_type> collection_type;
  typedef std::ostreambuf_iterator<charT> ostream_iter_type;
  typedef std::basic_ostringstream<charT> stringstream_type;
  typedef std::time_put<charT>           time_put_facet_type;
  charT short_fmt[3] = { '%', 'b' };
  charT long_fmt[3]  = { '%', 'B' };
  collection_type months;
  string_type outfmt(short_fmt);
  if (!short_strings) {
    outfmt = long_fmt;
  }
  {
    //grab the needed strings by using the locale to
    //output each month
    const charT* p_outfmt = outfmt.c_str(), *p_outfmt_end = p_outfmt + outfmt.size();
    tm tm_value;
    std::memset(&tm_value, 0, sizeof(tm_value));
    for (int m=0; m < 12; m++) {
      tm_value.tm_mon = m;
      stringstream_type ss;
      ostream_iter_type oitr(ss);
      std::use_facet<time_put_facet_type>(locale).put(oitr, ss, ss.fill(),
                                                      &tm_value,
                                                      p_outfmt,
                                                      p_outfmt_end);
      months.push_back(ss.str());
    }
  }
  return months;
}

//! This function gathers up all the weekday strings from a std::locale
/*! Using the time_put facet, this function creates a collection of
 *  all the weekday strings from a locale starting with the string for
 *  'Sunday'.  This is handy when building custom date parsers or
 *  formatters that need to be localized.
 *
 *@param charT The type of char to use when gathering typically char
 *             or wchar_t.
 *@param locale The locale to use when gathering the strings
 *@param short_strings True(default) to gather short strings,
 *                     false for long strings.
 *@return A vector of strings containing the weekdays in order. eg:
 *        Sun, Mon, Tue, Wed, Thu, Fri, Sat
 */
template<typename charT>
std::vector<std::basic_string<charT> >
gather_weekday_strings(const std::locale& locale, bool short_strings=true)
{
  typedef std::basic_string<charT> string_type;
  typedef std::vector<string_type> collection_type;
  typedef std::ostreambuf_iterator<charT> ostream_iter_type;
  typedef std::basic_ostringstream<charT> stringstream_type;
  typedef std::time_put<charT>           time_put_facet_type;
  charT short_fmt[3] = { '%', 'a' };
  charT long_fmt[3]  = { '%', 'A' };

  collection_type weekdays;


  string_type outfmt(short_fmt);
  if (!short_strings) {
    outfmt = long_fmt;
  }
  {
    //grab the needed strings by using the locale to
    //output each month / weekday
    const charT* p_outfmt = outfmt.c_str(), *p_outfmt_end = p_outfmt + outfmt.size();
    tm tm_value;
    std::memset(&tm_value, 0, sizeof(tm_value));
    for (int i=0; i < 7; i++) {
      tm_value.tm_wday = i;
      stringstream_type ss;
      ostream_iter_type oitr(ss);
      std::use_facet<time_put_facet_type>(locale).put(oitr, ss, ss.fill(),
                                                      &tm_value,
                                                      p_outfmt,
                                                      p_outfmt_end);

      weekdays.push_back(ss.str());
    }
  }
  return weekdays;
}

} } //namespace


#endif

/* strings_from_facet.hpp
mZ2qtwRAQ/V6QZLIzSCsYBIi9LFmq6y4Wl6TwjejlMULZ0IQVtWZRVU9AqBUhVs39MJ62rGer/1Lq+eXdq6Ri2rkk/TVqY7ImK6OGqJBG08JddwJc8UljnWIlYuwmn4N9ZUKTFVvaP0QlFLI+2xEnFp7yBMbCES4VNCwPpYPXzPlF5CU++BoKCt0LJ//egJvzhxLuq+migX4A4SYeyDyx4p44QHLSw1ZAT6EBB+rkmpwBb7p0Bt/hvNOvVmDMgBEafkqicbSeOGA5UzXUUzXDycwXbMUXZu+aI9Hfw3ZY3RVxqGc7qkJ2NUus3a14zHpJeJyfh/RU3X1JYLo7EcF7hhgsbinZQINiK9yHIJ/V0nZEWQJLYLh0lmplhKJIzIrh2LsAxY9Vhtn4B6BUYb7is0KFfeTgd5YALyAx85l7DgM2CJP2g3udROKpsOXF678ogLhEmrgItjukaFwUw/5/B+u9GiC4QjXlkwHDmawruhR6JRRhbsi1z3fHk+gF9J5GtP55ONSDOnY52ZXjxVE/wXLW2ZXNLgXV8Pg7g1TEklQC55Gvv495s7dz/d/2H9VKv+ZvRzW++vNK7i4gfklqC7lAk6xcPsp7stvwx5xqtA0NsQLLwmXWm77cUaXwejVfbaVqyun/DyU1IDzYwrlap15UZ4qP3YgB2PBh4RyogfZIWwvaz6+yg/3T9k/Et2Uv+EQE73nr2T0avTAZziQy61BjuUPOelyMOGt/3DCP2PkEYmn7AqJ2BHSG1HjnjognKpvUskCsT040oTRZMIQiAxUaPvjhW5E+/JWQHWYQBXY1cwgSw5nC9XBYPq1NVrvVy53P+GAa9SHNRLbmy2Ge6yscn1PmsGdM8YPYY/6jOYBryNvqMYbx2ycY2E5tu2bhqLRJcjUkLmBC2+eLbnsIFxVZSnbL8vuJTmjLP7gyvVFXPxH1Vx8kAlx/2tY/FLBVm0qH18PciLL57Po5lch/1Ujt1qAjb/ElP8+prXdzzDdPpxuEaW7zJqukNPRFS37crrJlK7Smu7jj9rj3f9Ksu/1aPqcz+Lt2oXIvI7HERryLqjAoPkX9bdu/jiK463oZfpVeHNv+GxwJjqcFOvHE1tWOaD4mVA87w/XZYn9YRA5MObsN01RfkiWEuXvsdH8VWXQtpNzywdeYwl2GxZWFlAdto9sXY8azi/ugRT3YwqQoHBv7ySOG2xgHHNClO/ZBCOUh9PvwrZcHLXYLR9ANO4HNTuOVBUwcDOJ4wGoBOpXfV7eQYQCsJKV620O7FqMEk774ZdhfRov/PoKEu6qYOhUGaFK7ISvs8Li9XFK6L9CdcL6D6mUqsgnIP0roT8KyAA5ekNiNfbcT1Q5aoGjHqgwzB/wbdy9Dsp8BMp0r2utCrfB2LsTitmgkI1MiwFcqHorVX1oZUuUVwfjIBkujebT0uM5HqCQCAcopm+j9HtXtsTE/WCQniH6ReI2Thy9AROoEkbg6Eb0wkFHvHCfK/AGlE8ZxGtBAAFr+E/bOiitRuSFygTt8cJ3L9eq9UIQqpUtqlUduQroVtnyhfCDDXEcvKLNgpuJVk8Eja8kFA5RZboXrREyXpuIdF9+vaVCpZUt33Ax/aAYBsMS102gAuZvxQMZrsj2HWd772jO1iayTcVs/K0Laja+C/DBo5lVWXrJEZF28+oarB+OHNy6+1uPb+MgmuEQO23T5v/5x8pfzNsL+7Qzd+G5k9bccrVYzqvFk4+i1WIYfiLnZ30r5Vwg9SGcYPRR0mH9Xs+kmiyRPf0JojkkjEO+pjno0D5rwXk9Ld8a3TL02UA+dllazVlCe9G9rO9BQdodn+XudSBATEfuW42eIKpxSYfONHk=
*/