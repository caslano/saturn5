
#ifndef DATE_TIME_FORMAT_DATE_PARSER_HPP__
#define DATE_TIME_FORMAT_DATE_PARSER_HPP__

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/lexical_cast.hpp"
#include "boost/date_time/string_parse_tree.hpp"
#include "boost/date_time/strings_from_facet.hpp"
#include "boost/date_time/special_values_parser.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#ifndef BOOST_NO_STDC_NAMESPACE
#  include <cctype>
#else
#  include <ctype.h>
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std {
  using ::isspace;
  using ::isdigit;
}
#endif
namespace boost { namespace date_time {

//! Helper function for parsing fixed length strings into integers
/*! Will consume 'length' number of characters from stream. Consumed
 * character are transfered to parse_match_result struct.
 * Returns '-1' if no number can be parsed or incorrect number of
 * digits in stream. */
template<typename int_type, typename charT>
inline
int_type
fixed_string_to_int(std::istreambuf_iterator<charT>& itr,
                    std::istreambuf_iterator<charT>& stream_end,
                    parse_match_result<charT>& mr,
                    unsigned int length,
                    const charT& fill_char)
{
  //typedef std::basic_string<charT>  string_type;
  unsigned int j = 0;
  //string_type s;
  while (j < length && itr != stream_end &&
      (std::isdigit(*itr) || *itr == fill_char)) {
    if(*itr == fill_char) {
      /* Since a fill_char can be anything, we convert it to a zero.
       * lexical_cast will behave predictably when zero is used as fill. */
      mr.cache += ('0');
    }
    else {
      mr.cache += (*itr);
    }
    itr++;
    j++;
  }
  int_type i = static_cast<int_type>(-1);
  // mr.cache will hold leading zeros. size() tells us when input is too short.
  if(mr.cache.size() < length) {
    return i;
  }
  try {
    i = boost::lexical_cast<int_type>(mr.cache);
  }catch(bad_lexical_cast&){
    // we want to return -1 if the cast fails so nothing to do here
  }
  return i;
}

//! Helper function for parsing fixed length strings into integers
/*! Will consume 'length' number of characters from stream. Consumed
 * character are transfered to parse_match_result struct.
 * Returns '-1' if no number can be parsed or incorrect number of
 * digits in stream. */
template<typename int_type, typename charT>
inline
int_type
fixed_string_to_int(std::istreambuf_iterator<charT>& itr,
                    std::istreambuf_iterator<charT>& stream_end,
                    parse_match_result<charT>& mr,
                    unsigned int length)
{
  return fixed_string_to_int<int_type, charT>(itr, stream_end, mr, length, '0');
}

//! Helper function for parsing varied length strings into integers
/*! Will consume 'max_length' characters from stream only if those
 * characters are digits. Returns '-1' if no number can be parsed.
 * Will not parse a number preceeded by a '+' or '-'. */
template<typename int_type, typename charT>
inline
int_type
var_string_to_int(std::istreambuf_iterator<charT>& itr,
                  const std::istreambuf_iterator<charT>& stream_end,
                  unsigned int max_length)
{
  typedef std::basic_string<charT>  string_type;
  unsigned int j = 0;
  string_type s;
  while (itr != stream_end && (j < max_length) && std::isdigit(*itr)) {
    s += (*itr);
    ++itr;
    ++j;
  }
  int_type i = static_cast<int_type>(-1);
  if(!s.empty()) {
    i = boost::lexical_cast<int_type>(s);
  }
  return i;
}


//! Class with generic date parsing using a format string
/*! The following is the set of recognized format specifiers
 -  %a - Short weekday name
 -  %A - Long weekday name
 -  %b - Abbreviated month name
 -  %B - Full month name
 -  %d - Day of the month as decimal 01 to 31
 -  %j - Day of year as decimal from 001 to 366
 -  %m - Month name as a decimal 01 to 12
 -  %U - Week number 00 to 53 with first Sunday as the first day of week 1?
 -  %w - Weekday as decimal number 0 to 6 where Sunday == 0
 -  %W - Week number 00 to 53 where Monday is first day of week 1
 -  %x - facet default date representation
 -  %y - Year without the century - eg: 04 for 2004
 -  %Y - Year with century

 The weekday specifiers (%a and %A) do not add to the date construction,
 but they provide a way to skip over the weekday names for formats that
 provide them.

 todo -- Another interesting feature that this approach could provide is
         an option to fill in any missing fields with the current values
         from the clock.  So if you have %m-%d the parser would detect
         the missing year value and fill it in using the clock.

 todo -- What to do with the %x.  %x in the classic facet is just bad...

 */
template<class date_type, typename charT>
class format_date_parser
{
 public:
  typedef std::basic_string<charT>        string_type;
  typedef std::basic_istringstream<charT>  stringstream_type;
  typedef std::istreambuf_iterator<charT> stream_itr_type;
  typedef typename string_type::const_iterator const_itr;
  typedef typename date_type::year_type  year_type;
  typedef typename date_type::month_type month_type;
  typedef typename date_type::day_type day_type;
  typedef typename date_type::duration_type duration_type;
  typedef typename date_type::day_of_week_type day_of_week_type;
  typedef typename date_type::day_of_year_type day_of_year_type;
  typedef string_parse_tree<charT> parse_tree_type;
  typedef typename parse_tree_type::parse_match_result_type match_results;
  typedef std::vector<std::basic_string<charT> > input_collection_type;

  // TODO sv_parser uses its default constructor - write the others

  format_date_parser(const string_type& format_str,
                     const input_collection_type& month_short_names,
                     const input_collection_type& month_long_names,
                     const input_collection_type& weekday_short_names,
                     const input_collection_type& weekday_long_names) :
    m_format(format_str),
    m_month_short_names(month_short_names, 1),
    m_month_long_names(month_long_names, 1),
    m_weekday_short_names(weekday_short_names),
    m_weekday_long_names(weekday_long_names)
  {}

  format_date_parser(const string_type& format_str,
                     const std::locale& locale) :
    m_format(format_str),
    m_month_short_names(gather_month_strings<charT>(locale), 1),
    m_month_long_names(gather_month_strings<charT>(locale, false), 1),
    m_weekday_short_names(gather_weekday_strings<charT>(locale)),
    m_weekday_long_names(gather_weekday_strings<charT>(locale, false))
  {}

  format_date_parser(const format_date_parser<date_type,charT>& fdp)
  {
    this->m_format = fdp.m_format;
    this->m_month_short_names = fdp.m_month_short_names;
    this->m_month_long_names = fdp.m_month_long_names;
    this->m_weekday_short_names = fdp.m_weekday_short_names;
    this->m_weekday_long_names = fdp.m_weekday_long_names;
  }

  string_type format() const
  {
    return m_format;
  }

  void format(string_type format_str)
  {
    m_format = format_str;
  }

  void short_month_names(const input_collection_type& month_names)
  {
    m_month_short_names = parse_tree_type(month_names, 1);
  }
  void long_month_names(const input_collection_type& month_names)
  {
    m_month_long_names = parse_tree_type(month_names, 1);
  }
  void short_weekday_names(const input_collection_type& weekday_names)
  {
    m_weekday_short_names = parse_tree_type(weekday_names);
  }
  void long_weekday_names(const input_collection_type& weekday_names)
  {
    m_weekday_long_names = parse_tree_type(weekday_names);
  }

  date_type
  parse_date(const string_type& value,
             const string_type& format_str,
             const special_values_parser<date_type,charT>& sv_parser) const
  {
    stringstream_type ss(value);
    stream_itr_type sitr(ss);
    stream_itr_type stream_end;
    return parse_date(sitr, stream_end, format_str, sv_parser);
  }

  date_type
  parse_date(std::istreambuf_iterator<charT>& sitr,
             std::istreambuf_iterator<charT>& stream_end,
             const special_values_parser<date_type,charT>& sv_parser) const
  {
    return parse_date(sitr, stream_end, m_format, sv_parser);
  }

  /*! Of all the objects that the format_date_parser can parse, only a
   * date can be a special value. Therefore, only parse_date checks
   * for special_values. */
  date_type
  parse_date(std::istreambuf_iterator<charT>& sitr,
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str,
             const special_values_parser<date_type,charT>& sv_parser) const
  {
    bool use_current_char = false;

    // skip leading whitespace
    while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

    short year(0), month(0), day(0), day_of_year(0);// wkday(0);
    /* Initialized the following to their minimum values. These intermediate
     * objects are used so we get specific exceptions when part of the input
     * is unparsable.
     * Ex: "205-Jan-15" will throw a bad_year, "2005-Jsn-15"- bad_month, etc.*/
    year_type t_year(1400);
    month_type t_month(1);
    day_type t_day(1);
    day_of_week_type wkday(0);


    const_itr itr(format_str.begin());
    while (itr != format_str.end() && (sitr != stream_end)) {
      if (*itr == '%') {
        if ( ++itr == format_str.end())
          break;
        if (*itr != '%') {
          switch(*itr) {
          case 'a':
            {
              //this value is just throw away.  It could be used for
              //error checking potentially, but it isn't helpful in
              //actually constructing the date - we just need to get it
              //out of the stream
              match_results mr = m_weekday_short_names.match(sitr, stream_end);
              if(mr.current_match == match_results::PARSE_ERROR) {
                // check special_values
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              wkday = mr.current_match;
              if (mr.has_remaining()) {
                use_current_char = true;
              }
              break;
            }
          case 'A':
            {
              //this value is just throw away.  It could be used for
              //error checking potentially, but it isn't helpful in
              //actually constructing the date - we just need to get it
              //out of the stream
              match_results mr = m_weekday_long_names.match(sitr, stream_end);
              if(mr.current_match == match_results::PARSE_ERROR) {
                // check special_values
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              wkday = mr.current_match;
              if (mr.has_remaining()) {
                use_current_char = true;
              }
              break;
            }
          case 'b':
            {
              match_results mr = m_month_short_names.match(sitr, stream_end);
              if(mr.current_match == match_results::PARSE_ERROR) {
                // check special_values
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              t_month = month_type(mr.current_match);
              if (mr.has_remaining()) {
                use_current_char = true;
              }
              break;
            }
          case 'B':
            {
              match_results mr = m_month_long_names.match(sitr, stream_end);
              if(mr.current_match == match_results::PARSE_ERROR) {
                // check special_values
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              t_month = month_type(mr.current_match);
              if (mr.has_remaining()) {
                use_current_char = true;
              }
              break;
            }
          case 'd':
            {
              match_results mr;
              day = fixed_string_to_int<short, charT>(sitr, stream_end, mr, 2);
              if(day == -1) {
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              t_day = day_type(day);
              break;
            }
          case 'e':
            {
              match_results mr;
              day = fixed_string_to_int<short, charT>(sitr, stream_end, mr, 2, ' ');
              if(day == -1) {
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              t_day = day_type(day);
              break;
            }
          case 'j':
            {
              match_results mr;
              day_of_year = fixed_string_to_int<short, charT>(sitr, stream_end, mr, 3);
              if(day_of_year == -1) {
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              // these next two lines are so we get an exception with bad input
              day_of_year_type t_day_of_year(1);
              t_day_of_year = day_of_year_type(day_of_year);
              break;
            }
          case 'm':
            {
              match_results mr;
              month = fixed_string_to_int<short, charT>(sitr, stream_end, mr, 2);
              if(month == -1) {
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              t_month = month_type(month);
              break;
            }
          case 'Y':
            {
              match_results mr;
              year = fixed_string_to_int<short, charT>(sitr, stream_end, mr, 4);
              if(year == -1) {
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              t_year = year_type(year);
              break;
            }
          case 'y':
            {
              match_results mr;
              year = fixed_string_to_int<short, charT>(sitr, stream_end, mr, 2);
              if(year == -1) {
                if(sv_parser.match(sitr, stream_end, mr)) {
                  return date_type(static_cast<special_values>(mr.current_match));
                }
              }
              year += 2000; //make 2 digit years in this century
              t_year = year_type(year);
              break;
            }
          default:
            {} //ignore those we don't understand

          }//switch

        }
        else { // itr == '%', second consecutive
          sitr++;
        }

        itr++; //advance past format specifier
      }
      else {  //skip past chars in format and in buffer
        itr++;
        if (use_current_char) {
          use_current_char = false;
        }
        else {
          sitr++;
        }
      }
    }

    if (day_of_year > 0) {
      date_type d(static_cast<unsigned short>(year-1),12,31); //end of prior year
      return d + duration_type(day_of_year);
    }

    return date_type(t_year, t_month, t_day); // exceptions were thrown earlier
                                        // if input was no good
  }

  //! Throws bad_month if unable to parse
  month_type
  parse_month(std::istreambuf_iterator<charT>& sitr,
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str) const
  {
    match_results mr;
    return parse_month(sitr, stream_end, format_str, mr);
  }

  //! Throws bad_month if unable to parse
  month_type
  parse_month(std::istreambuf_iterator<charT>& sitr,
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str,
             match_results& mr) const
  {
    bool use_current_char = false;

    // skip leading whitespace
    while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

    short month(0);

    const_itr itr(format_str.begin());
    while (itr != format_str.end() && (sitr != stream_end)) {
      if (*itr == '%') {
        if ( ++itr == format_str.end())
          break;
        if (*itr != '%') {
          switch(*itr) {
          case 'b':
            {
              mr = m_month_short_names.match(sitr, stream_end);
              month = mr.current_match;
              if (mr.has_remaining()) {
                use_current_char = true;
              }
              break;
            }
          case 'B':
            {
              mr = m_month_long_names.match(sitr, stream_end);
              month = mr.current_match;
              if (mr.has_remaining()) {
                use_current_char = true;
              }
              break;
            }
          case 'm':
            {
              month = var_string_to_int<short, charT>(sitr, stream_end, 2);
              // var_string_to_int returns -1 if parse failed. That will
              // cause a bad_month exception to be thrown so we do nothing here
              break;
            }
          default:
            {} //ignore those we don't understand

          }//switch

        }
        else { // itr == '%', second consecutive
          sitr++;
        }

        itr++; //advance past format specifier
      }
      else {  //skip past chars in format and in buffer
        itr++;
        if (use_current_char) {
          use_current_char = false;
        }
        else {
          sitr++;
        }
      }
    }

    return month_type(month); // throws bad_month exception when values are zero
  }

  //! Expects 1 or 2 digits 1-31. Throws bad_day_of_month if unable to parse
  day_type
  parse_var_day_of_month(std::istreambuf_iterator<charT>& sitr,
                         std::istreambuf_iterator<charT>& stream_end) const
  {
    // skip leading whitespace
    while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

    return day_type(var_string_to_int<short, charT>(sitr, stream_end, 2));
  }
  //! Expects 2 digits 01-31. Throws bad_day_of_month if unable to parse
  day_type
  parse_day_of_month(std::istreambuf_iterator<charT>& sitr,
                     std::istreambuf_iterator<charT>& stream_end) const
  {
    // skip leading whitespace
    while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

    //return day_type(var_string_to_int<short, charT>(sitr, stream_end, 2));
    match_results mr;
    return day_type(fixed_string_to_int<short, charT>(sitr, stream_end, mr, 2));
  }

  day_of_week_type
  parse_weekday(std::istreambuf_iterator<charT>& sitr,
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str) const
  {
    match_results mr;
    return parse_weekday(sitr, stream_end, format_str, mr);
  }
  day_of_week_type
  parse_weekday(std::istreambuf_iterator<charT>& sitr,
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str,
             match_results& mr) const
  {
    bool use_current_char = false;

    // skip leading whitespace
    while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

    short wkday(0);

    const_itr itr(format_str.begin());
    while (itr != format_str.end() && (sitr != stream_end)) {
      if (*itr == '%') {
        if ( ++itr == format_str.end())
          break;
        if (*itr != '%') {
          switch(*itr) {
          case 'a':
            {
              //this value is just throw away.  It could be used for
              //error checking potentially, but it isn't helpful in
              //actually constructing the date - we just need to get it
              //out of the stream
              mr = m_weekday_short_names.match(sitr, stream_end);
              wkday = mr.current_match;
              if (mr.has_remaining()) {
                use_current_char = true;
              }
              break;
            }
          case 'A':
            {
              //this value is just throw away.  It could be used for
              //error checking potentially, but it isn't helpful in
              //actually constructing the date - we just need to get it
              //out of the stream
              mr = m_weekday_long_names.match(sitr, stream_end);
              wkday = mr.current_match;
              if (mr.has_remaining()) {
                use_current_char = true;
              }
              break;
            }
          case 'w':
            {
              // weekday as number 0-6, Sunday == 0
              wkday = var_string_to_int<short, charT>(sitr, stream_end, 2);
              break;
            }
          default:
            {} //ignore those we don't understand

          }//switch

        }
        else { // itr == '%', second consecutive
          sitr++;
        }

        itr++; //advance past format specifier
      }
      else {  //skip past chars in format and in buffer
        itr++;
        if (use_current_char) {
          use_current_char = false;
        }
        else {
          sitr++;
        }
      }
    }

    return day_of_week_type(wkday); // throws bad_day_of_month exception
                                    // when values are zero
  }

  //! throws bad_year if unable to parse
  year_type
  parse_year(std::istreambuf_iterator<charT>& sitr,
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str) const
  {
    match_results mr;
    return parse_year(sitr, stream_end, format_str, mr);
  }

  //! throws bad_year if unable to parse
  year_type
  parse_year(std::istreambuf_iterator<charT>& sitr,
             std::istreambuf_iterator<charT>& stream_end,
             string_type format_str,
             match_results& mr) const
  {
    // skip leading whitespace
    while(std::isspace(*sitr) && sitr != stream_end) { ++sitr; }

    unsigned short year(0);

    const_itr itr(format_str.begin());
    while (itr != format_str.end() && (sitr != stream_end)) {
      if (*itr == '%') {
        if ( ++itr == format_str.end())
          break;
        if (*itr != '%') {
          //match_results mr;
          switch(*itr) {
          case 'Y':
            {
              // year from 4 digit string
              year = fixed_string_to_int<short, charT>(sitr, stream_end, mr, 4);
              break;
            }
          case 'y':
            {
              // year from 2 digit string (no century)
              year = fixed_string_to_int<short, charT>(sitr, stream_end, mr, 2);
              year += 2000; //make 2 digit years in this century
              break;
            }
          default:
            {} //ignore those we don't understand

          }//switch

        }
        else { // itr == '%', second consecutive
          sitr++;
        }

        itr++; //advance past format specifier
      }
      else {  //skip past chars in format and in buffer
        itr++;
        sitr++;
      }
    }

    return year_type(year); // throws bad_year exception when values are zero
  }


 private:
  string_type m_format;
  parse_tree_type m_month_short_names;
  parse_tree_type m_month_long_names;
  parse_tree_type m_weekday_short_names;
  parse_tree_type m_weekday_long_names;

};

} } //namespace

#endif




/* format_date_parser.hpp
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
*/