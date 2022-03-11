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