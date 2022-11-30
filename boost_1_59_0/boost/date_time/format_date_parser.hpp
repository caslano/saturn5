
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
9rrv1PKTYGeSIgL2cJ/a6TG7+wme8NxkN36C4LjiqDgGBoY++xKwYUJk0wWgiwsx0j0LRyPEydsTGyDekAi8DBDnUiGSBff4lUi+XhIhHiOXfBUXyLU2WTSkBmwcfmDeae1rSBb67nd2ERwBu6oEZ7cM5eZOC20mdsjTM5hrLCgzxGCBfOIlDYAFwW4zIQKy0nA/Wmi0NMmyIvgbZPnlje2wGcCPAluVJZmpFOTWKAWtKzy2Q+zSgQKsbhFb4J4yQLrGQFNXVkzP1CNYMAGLdrk//WG4Yu3k7gZAj3W19THgjdUuFkQi3zdt7oTYscpwAwaAuXR14WoG04j17jrl9nSdlu3RXnZdML3X2mE0vjhj9xj7qAH/CFyilNheVXsOFnMM9kg/68oP94VKytwTNKGBDS9HuP4CJSqiKpZrBLjtoecG30zwAcB7eQZYLwaxfhHwPW1GCOF9rgLqbv/pTVCYNE8ADnqROJpkwLd22mfc3mgma+4OsusmojqOJqh0rEBohm+4Tf0JwXjGB/t5BoQdpprpsgwVO13gt2N1u5Xu6RYFfivjHdEHPqlmuxyx2a7wZGnHhLvtASinnfdiAok5gM2b5W2vJ4hpilHQRQPYyTvOEAr7JNxPYIQtl480AGCj4eMpDLhDO4HNiAaGXDliY4LdMP5SsX2BUCOmjOo9Anw7b3gGWDEKTLLc5Y6AOCmAbRECOFCkXnEShR952JyymJ4wyYgJM/t6FbuJmZve9i0NZjOWzIwzk7mbwP093GxCLeoDS7GBn5bY1z8QwzUJ5kackszcKCtAb6LlbQAPQuHurlC3CjRRttMWb6d12nN4pfZBYwsMpmzEDYAMhBaJwENtuvdjvJ8WyNhl33nIi+ZzH2Hach9hjL2/Yzu6125KqGAjEW0xgEasZWw9zv0qK+83J7w6TZhq6u0rTEHVYBzAM4IruMXOVsaIElgR2FBX+xm7qJrnUTVNRusI3VVdIKdgC5QBDOkVO4j1bQvnvsJ7V6g+K2/RB0hD1NrtEFDMzyU4QeLF+hyi/G1qfy5B2aEPrAbmAKfpgxiQ61NqZuy42Hoc1ibFj4z3jHm5EWjctvQ6HEbV4E7CVINOGBvcQXMC4T6dx5T8F5ZFQtyP3zOG0ZTxmFZUzCw4tW13UL4aguZKKb8igHLooZKpCvJ/Qq8rzGruPr3/rk3tq0MojPuYQmJO3LFaszG1Aqhmz7zGIZwmCuv9A1+yY/XaujQWswz1fECH/g1I5Hgh5aBWjANqO1ulQoQVUVCayTWqxNTBGL7FmjsZ8tkTHHHYJ4izVrG7ByhnH5wVMGITSBC2wsSOEdaYrY45po8Kr8F+lRVZh/MBvE5k2gAjt7HD871a/93s7f3kKDK5GdJzlNpbksVguJdbQDaftwWAxL80A2YOyzn8YNkm9u8CjbjmeUkjk6J0/Cq2fHEqaqZ8fWLUCN+2USbCL8NxcveyVPh8QvD1qvLen37g1z+6BGAy3UzoIb4CSLsojzEBXO0+cCb3+EiDwOMDc5Gt610iHrNhRq7ix7DX2Fi8jktThex+i2tDNsqtIrclmOHI2WS3TKFtOet+c3vbdJDWcQKicpu1iUQRcrkxdzh2voruPReFI/hIgo+NCGkxmtT+SIQdeXzhclmKu8mvO4/Hx+6DCU0qKHpTqsjyHWvmMnVRjQngi5bqp8jX5XlEr/rmhanLft3IY+Odsfd9NVuerawEpoT6SSaiyOpGaEp51yAtGYT4X3D+7O5YLQuCcxElJlYkeLWxTSgzDlsxXCNNhwSwXWTFWPA44ErzwvbuNUYaHk1WMeDcpDmIOaXBmVcMuGGjF7Ou8sDXxoTC6HJNRhrL8Mb3krRE8jnwcDyGaUTLIEX5zpOQlmFDOqYxlLYpEgncCtoWCu/fpAQL9LIGq4bFDIZaUF6zeTAaRU89n+hhXXBBQwfpi5l4WEcBZFToQS56HVelTZ8M/1/hQTgkYrCe6wcsU8UiY0v4nk6yml31Vi4C4vv7/M20TLd/XGIzhjM2gXieJUQc2zCMTX9BttkvADbhFeNmqjKwOagEzn6E8X6dkRsKhgQ/do02sFmha7A91AheOlyb+5GiSsdVbN46CgUESwczQusBfYgZ3j0v3kHGznbqWvj31OETxPMU7lg1hj0Jzwyv54rW6JSAy/9lBMNGZZzhKksZsxJvw/5SxksNQeSxqbj8BwIff8aDAkwlaLKt8vNQwbNSRYWYKjYxFvfKWBEFfg9cZy8hdsjXtupyV/r2NrcMZ5edqctGJeTdrZtboC4EtPhObw8SBLyjGUe1gr4haFl16/Yc9R6jAZg2LKHqvTTjg/9qT/QbluttdP0Q5cYSMtizKBG5QNiFyPTeib2CwYk1uf3mj6aTxrYPmwgUMmvwnmB7j3Ur7Tne94z3NhPs4TuHHQSFca+n8J7u/wFt264fgiAAgENLfV3JluM4dv2k/AZXteuc7kV3nZNlt9s7KoOS2OLUIBnKjJ/NTWz8A7HSwnjzfVDYi8zAvYBAAAQxvuGG8jZ6rIsZJOlVPujF/OkwN+FHEy/YuyYT9H1NH88Ti0c+jcwek3wszrePaRrVJJ1RckRm5eUjZCiP4ihPXh/xmXLCTXvSsTJiPlj+jIgnMINDSmXO2NGPCr8giJSM3lIb8dE1PFCxP09OrSNBSHmN71uEklonE6OYz3EjejVAdwrcjmOW0XA5MdS1mvED4P4Pphpm6f4QW1J2aSE+dumyXWGO3rLGm5GobizcqwjtQGdylQPLfrPKkGbQ6qm2ZAbI7AnWgcMRCL8TXsvjDJYgmDvm7oTrK+LqdrMA3lNhjjCpqmhF5C2ow54BPkB6+Pqy8RtuGCE+tYc3l2T7BHkl+0vabQm+wC95aVmiBXpeQFxSUfq0WVYYb7cX7yi19zzK2eWJ+VoDfzXAhC7Ii1EBuQefw1QVkVN66LA/QygDXwiqqkjUvuSCl7kZfOTiRF8K2UaSZYhcocAvFcfzkkyNoq8YmVp9yM1udi0ppF+uC+Vk6csxC0i7wM74gMdP7/QSo3Gn/O1PWeFo6saECjpyM5xhs3xhmTnI4Se+Cb6osTfLAJIKzGnX8ziA2gNz2HgTS8pBHgwhDxP2YjQkZSOFkdikfkgbp7TVWlrjtpVaCh9BLiV9nFP9Nv8SYXziEftWukuKGL5ZeoJeNMY46TjhEveVscUaB221VgcsdpRqOTFMyyC+u4Jnd1ddz1EoOo4ge36XbWpWIoxBznTnFQcJhGRVYuhpqTD3t7Z1g4pW6L+HNXZCOGMITAtioba1LuugGkZ2oPo288GstNci/8/f4DeEfLoj1BZ2eSo++oAI0hxq1eA4wi4goNsoBM5bYAFNgSXUyuclLJrMy9TZMQMFQTWRfar8m4Wygv3fncYtw7Je6fp4QsOD81LCPsHMt5bReRRGgSvGfruUCx5SkX8kbZC1S4MZ3XG67NmaZTYV+kMI12nq5d65+j9z+GDDaRVjpJ4wcZvRRSo+6yynYPIx8cUqqDALlmlBblnTT5WIgg4zNtYqF4qGPtJKkG9fvZkZ9Sl2TouutYhRDh3qDMaj6bo2uytIHFLpOaHmV7egIGFICDpwQP8E6BIYskLFPte1oLthTNMNaJ/VcYb6SlH1DzX/RPHPO4/cH8OuyAhvGyawszhxErFTP2l3T9Dwyx1+Bp8nA4iASqYlmSAoyyWX5CKefycrwEX2TYOZoRIZ/JQhX1F9QsBDmMkPGppMQA2DOxOk3HJK1JIq+dSHYOtYjUk6PMXFNXPDfuRtALPq7DCTrQsvZl8X9p7Y0veh3PKzprSNzJqfpVFdK7HyAyUfEgbAaoeKLV2S4s+X9OEK9OMW0hb1oUdAmhjVBKb/OosTl4PO1P8SlY0dRTng7J4Arpq2d9O93eru0BZXyZvtLDIJ8awtHXgQwjXE1ql27ibOTiLdmA5KRYIB4wVDgnBkIUArRGFe7Ghhu5BCpzA+UwygWB4sF4HRRsQzmcGvQaQnMmqyOD7BKcdjjG/UMR6yM9k8Fe8lBcZbNKGN9Nyslc3L8VP+SUXSMRn8zJGpE5NUx7vpcYjIBxSN0PoV02qP+M/AWBXayPgg/KTZxUS+EspKXkm5i+1/XCDmuEAY9/lGQDkqhCsklVTJjTYlwzazSqtAJnOeflV8RQ69HeToo2X87MmJpzyHfc/vg5mvLeHvMzWXHW2LNEyESal8jhxIMgZqRjCXgpX5xP1i83ogpv/S0FizRh1QmJxiiHKTqEBUqQxwlUWCOSfM5zj5UQCO6CbAkytiFH6WJNaTU919qgvGXowT09QkGbLdDqI+xjEqRcI/CvowQyBhrw+h7bUvdKGZmro3W7Qi8mc4TQ1bXqiSEFGGaWDo06SkMBpmQHMCIlbkfYTRjVTfY3JgbmPju071uUUUwzP6l3y7z0waAIfebC5sslT2phL/IoD+2V1eviBxzyVcWDuagysZo9KXQWJR2BCKo5Rrl0aCNXXc1bstiVCldIIhnwEXFSxXldNXDCvdbf2AQoLzYEHpp2A7g4DfWYgNAQxDe6yh517Ddd3qjc6osR8kJO9dEdptNomCuXkMdgx0wbqWtrLZKAZJiuGxkuANCkTw1F8KCaTYnbvTeUmutLtsNgJu20kSLRUn375vO7Sn2Dr3D2+PBhWZNfwZLRG8BxKKKjC6kJgpK2RE1ZsIt1GV3bIbTOi/PYjPqYidwJTAZr95Zpm4VNNu3yWAxlFYPi6yFEMCv8SP1HKmd20msO8Skb5jdLdDaLgkmOc9xZi/aKz+6qjJnIzdk8RWKsIRO0NBuQ5H2gEJkbMdxGJ9vALo4iTX10T2eFQsWCcxCmO+dqAr4oBYc8FQKiLSuppEBtNPPn5C06haO8kOwhIIldtFkDDlUNKNI+EklGVEGqlZ4rD5VTZ8Y4wPESyVmNvMmExYqz1KrulRJvwgGBrKohnkq0maeO8ujVE6ZeBifJdTGfttHfjQcJ7grYHxW4b997V/SaZZLea88HE7fB0pAhctGsHmgN/h4g158GsRPLkqwQenK6f6iWtT6E7YkhHUPrmzkyOtUQ1vGAEm1hkfU77F2mm3HIWVvbP/ng/MxlR/MoUrFjuDykXu3+iA5E3O5lITXRvTh3tdr9JRLNRLGcT0euec5C0JcyhDBn7sPtCouuW6iT2BnJZJLMeyxmWiQRaBjAPoRIdkZKajbwG9XsMWehMB8pRNhJtU1wi0KyMM6fF8+etvLdcWDU2BKzWRSG/LuQ1XJbal4t9z9sS1+W/JUqZy6xUcPihJjnjxsYMK5+1Dx6Kns7/QgX0fDiEMQUx22kfUkzxm5db6qBc9DX9x9jiTj6M+Pb07yJ76/l6MOJH377p/sVP9ygxLGk2UADuRSkG2p2WkMeOeR6nhVIaMH3RxE9J8ND9106nkvSuxbiJV073000KyEJnjs95w141cKi6aVyU4bLcykMFxmUCbW/rnBK906H9KKegGPx7QT31uMyFSIfqj9od3rMDZxVs57CnP3dbYeaxcf7x0Y0ZtkgV9pQrRpXoxMbRMgUIyzikaHw6VorKRFeJU4yBTra8H+3RIBSWzcOJ2IdPzeezUX7xT/GrUnzjOiU1Uzmgbu+kTQt+muzKa46CC0pSuT5/aPx8vCdYmT2LURqVn3zxgVjlzdPYlQUzPtsQ2OCSp5FDA5D8TrZB35UYeCrxTGG4a6vZRVtIu39OUNtyWiZqwQHWcWuugkIqzkJRWUxUSZvnE9RnFgDcLgjgVMSKJ5RH6WHBBLSv2wqm79S9LGvWmrnxvijSpo4iG3Mkwa+rB5M+W3SPklGBil1GecYfpx60ZGpVJPX7mPvxUDKO35W34LPIozyzZYeV7qTHfFDRR3R6OqWpc3f+Prf8Hpvdr+rIrUZpxfO3Y9UzmWHo/PZ0oGlnmvzbU8MwVnOKEaVItY3qv2UsHE3UeLdJ6zoVrs9TZ/3V07Gr+t8QM3Z6bT8lYNQoDD624Pcpjcu+/P+UVUj2M8PrZCFhgDmwmMTVx6chhSKZ6/ZB5M5O+RolqUq/HaWzXBaV/XcYjj6jo4oQguiqZaV8wDVh6xrWjsRu+ln/6YfMygvtk61Bj1/wxCZG+JabSU0r6QTml2HEhz5zILPd/9vtnTBrHnUyl5w81fkfos2XIpx90Nr9cgz+mZv1ZqQTpPCOVPXnuFZyy3Bca62Apx0vNp5K8De3msVJrvqQ06jWlWErzI7gsBwwz0tuPG85tIx95esf9SIeAOzl02BoZnD0EPOqO8mxb4uJ3OjXoG2XaqFgIL3Z2s6FkID7z0j3fiDPZnuAEiWcZO13fS6290sV3q2bIWZ+brhRUt9Di6L7g3yEI44ncJXgQyk7ID8bETrQ1yrDvTSb7jr/cXTlnL34LtRe7g9oPEw/Z731ZcS96X8DGmSDL9s4OeUNw/agf49q9Dl1ahqqvIOwo7KNs5oNzzxq5TMGR+OvTKki0oyTEW95f/mwRI/yQ0DB/+c1hOqghk7HpPZvSpryuO9n2+92j3GPWTI7WYmC+sx8v6/x3PExlkFWc7uJGqR9SY927OV85CIENda87fnlrNXT20HP+RkUpkt20e5K2uTfCNoTxbJHUU5sDdtZYhRNKxZDFnCUdlYAc2yeIwAqIOBsptoigdZVPRtWMbHyhOt841nO+GXnJLnlPPs9AbEe4dL7NFLnkQYk2Jr3fCIAGYf/my7r658UU6WQf+aDx3pcz5AOuRgW9WFG3xihLMC0RDT0ktdN7iEfJkTRGFVOtqkEbbUhXOL9XJpKbk/n+YNMp0jsftTIRwxclEnEUOJV7e0+nvKRH7EKob91THPYdUjNO0VnHo1W9U0Vk+EE/QNkFWdZ+8v8PJFpxbmXNT4vipmcx2cgDMwcbs7fGzH+2l6koalZxaoh8p8eK04hdDPvNJK1FgRqSPC4g9aEo3dqyjjX+gL+Ur34m93aoSwgFKp5t6ADgDhoMD2qtlMKiFeFojLB5YDCcstDmUygq1Q4wpRq0VKTOBAypUIpD9g6gSB0CKFK5PUN8K+WATpYNDGFFl+AjaoQ31xWJ2XwBYspew2rBXJFJ0hjsZ0RgjVypBasEdoIJ9NcIL9dIxvdmGlR73Ipu3h5g8FYJtVhrSO3Meqx1acFmbdXQtdgvQ2mTwlFcs39q6IhUfWoTNVJqwAyUGj6axIebLq5oTGU0fQiFZhxUoa43DbH8qYMDilDcUVEyykzgGpV4YP9Cu6VvITBWgywCpmG5DzNwTeCjRDIxA6HITRkYNoMEhlkVTQFr2VtY1eodzpCOtdEVbCbOGDNbZQ/siGhcmtABOV/jmaKSbWEcNFzJWSE2hSk1G2JdZgdvGBWfmarvKviAdyEatxJWFVIFHRbbFDgVjdg7Qs3SMJbXtSUdThPCNCqZaqShBcojWpAGVAVSIesjWli1ERWKsqGBXBZTNFToeoaKj5yTKQUKdBVAhemTR5vhhOJ7wRlAlN08vOPvD6/4iJ+p6XUZGvAxqn7lCDNktSoLw1DjalMOo3gfmEEaalmXSYJTqviUZkbVWzLgeklG+MxoSkeGyg1RtNKUpjvUCFLm8M6smjwBopKmWqNIFGEUmeaEIFN/MISDtKkkKBKNBAOmdKB4
*/