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
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
*/