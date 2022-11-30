#ifndef _DATE_TIME_TIME_PARSING_HPP___
#define _DATE_TIME_TIME_PARSING_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/tokenizer.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/date_time/date_parsing.hpp"
#include "boost/date_time/special_values_parser.hpp"
#include "boost/cstdint.hpp"
#include <iostream>

namespace boost {
namespace date_time {

  //! computes exponential math like 2^8 => 256, only works with positive integers
  //Not general purpose, but needed b/c std::pow is not available 
  //everywhere. Hasn't been tested with negatives and zeros
  template<class int_type>
  inline
  int_type power(int_type base, int_type exponent)
  {
    int_type result = 1;
    for(int i = 0; i < exponent; ++i){
      result *= base;
    }
    return result;
  }
  
  //! Creates a time_duration object from a delimited string
  /*! Expected format for string is "[-]h[h][:mm][:ss][.fff]".
   * If the number of fractional digits provided is greater than the 
   * precision of the time duration type then the extra digits are 
   * truncated.
   *
   * A negative duration will be created if the first character in
   * string is a '-', all other '-' will be treated as delimiters.
   * Accepted delimiters are "-:,.". 
   */
  template<class time_duration, class char_type>
  inline
  time_duration
  str_from_delimited_time_duration(const std::basic_string<char_type>& s)
  {
    unsigned short min=0, sec =0;
    int hour =0; 
    bool is_neg = (s.at(0) == '-');
    boost::int64_t fs=0;
    int pos = 0;
      
    typedef typename std::basic_string<char_type>::traits_type traits_type;
    typedef boost::char_separator<char_type, traits_type> char_separator_type;
    typedef boost::tokenizer<char_separator_type,
                             typename std::basic_string<char_type>::const_iterator,
                             std::basic_string<char_type> > tokenizer;
    typedef typename boost::tokenizer<char_separator_type,
                             typename std::basic_string<char_type>::const_iterator,
                             typename std::basic_string<char_type> >::iterator tokenizer_iterator;
   
    char_type sep_chars[5] = {'-',':',',','.'};
    char_separator_type sep(sep_chars);
    tokenizer tok(s,sep);
    for(tokenizer_iterator beg=tok.begin(); beg!=tok.end();++beg){
      switch(pos) {
      case 0: {
        hour = boost::lexical_cast<int>(*beg);
        break;
      }
      case 1: {
        min = boost::lexical_cast<unsigned short>(*beg);
        break;
      }
      case 2: {
        sec = boost::lexical_cast<unsigned short>(*beg);
        break;
      }
      case 3: {
        int digits = static_cast<int>(beg->length());
        //Works around a bug in MSVC 6 library that does not support
        //operator>> thus meaning lexical_cast will fail to compile.
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
        // msvc wouldn't compile 'time_duration::num_fractional_digits()' 
        // (required template argument list) as a workaround a temp 
        // time_duration object was used
        time_duration td(hour,min,sec,fs);
        int precision = td.num_fractional_digits();
        // _atoi64 is an MS specific function
        if(digits >= precision) {
          // drop excess digits
          fs = _atoi64(beg->substr(0, precision).c_str());
        }
        else {
          fs = _atoi64(beg->c_str());
        }
#else
        int precision = time_duration::num_fractional_digits();
        if(digits >= precision) {
          // drop excess digits
          fs = boost::lexical_cast<boost::int64_t>(beg->substr(0, precision));
        }
        else {
          fs = boost::lexical_cast<boost::int64_t>(*beg);
        }
#endif
        if(digits < precision){
          // trailing zeros get dropped from the string, 
          // "1:01:01.1" would yield .000001 instead of .100000
          // the power() compensates for the missing decimal places
          fs *= power(10, precision - digits); 
        }
        
        break;
      }
      default: break;
      }//switch
      pos++;
    }
    if(is_neg) {
      return -time_duration(hour, min, sec, fs);
    }
    else {
      return time_duration(hour, min, sec, fs);
    }
  }
  
  //! Creates a time_duration object from a delimited string
  /*! Expected format for string is "[-]h[h][:mm][:ss][.fff]".
   * If the number of fractional digits provided is greater than the 
   * precision of the time duration type then the extra digits are 
   * truncated.
   *
   * A negative duration will be created if the first character in
   * string is a '-', all other '-' will be treated as delimiters.
   * Accepted delimiters are "-:,.". 
   */
  template<class time_duration>
  inline
  time_duration
  parse_delimited_time_duration(const std::string& s)
  {
    return str_from_delimited_time_duration<time_duration,char>(s);
  }

  //! Utility function to split appart string
  inline
  bool 
  split(const std::string& s,
        char sep,
        std::string& first,
        std::string& second)
  {
    std::string::size_type sep_pos = s.find(sep);
    first = s.substr(0,sep_pos);
    if (sep_pos!=std::string::npos)
        second = s.substr(sep_pos+1);
    return true;
  }


  template<class time_type>
  inline
  time_type
  parse_delimited_time(const std::string& s, char sep)
  {
    typedef typename time_type::time_duration_type time_duration;
    typedef typename time_type::date_type date_type;

    //split date/time on a unique delimiter char such as ' ' or 'T'
    std::string date_string, tod_string;
    split(s, sep, date_string, tod_string);
    //call parse_date with first string
    date_type d = parse_date<date_type>(date_string);
    //call parse_time_duration with remaining string
    time_duration td = parse_delimited_time_duration<time_duration>(tod_string);
    //construct a time
    return time_type(d, td);

  }

  //! Parse time duration part of an iso time of form: [-]hhmmss[.fff...] (eg: 120259.123 is 12 hours, 2 min, 59 seconds, 123000 microseconds)
  template<class time_duration>
  inline
  time_duration
  parse_undelimited_time_duration(const std::string& s)
  {
    int precision = 0;
    {
      // msvc wouldn't compile 'time_duration::num_fractional_digits()' 
      // (required template argument list) as a workaround, a temp 
      // time_duration object was used
      time_duration tmp(0,0,0,1);
      precision = tmp.num_fractional_digits();
    }
    // 'precision+1' is so we grab all digits, plus the decimal
    int offsets[] = {2,2,2, precision+1};
    int pos = 0, sign = 0;
    int hours = 0;
    short min=0, sec=0;
    boost::int64_t fs=0;
    // increment one position if the string was "signed"
    if(s.at(sign) == '-')
    {
      ++sign;
    }
    // stlport choked when passing s.substr() to tokenizer
    // using a new string fixed the error
    std::string remain = s.substr(sign);
    /* We do not want the offset_separator to wrap the offsets, we 
     * will never want to  process more than: 
     * 2 char, 2 char, 2 char, frac_sec length.
     * We *do* want the offset_separator to give us a partial for the
     * last characters if there were not enough provided in the input string. */
    bool wrap_off = false;
    bool ret_part = true;
    boost::offset_separator osf(offsets, offsets+4, wrap_off, ret_part); 
    typedef boost::tokenizer<boost::offset_separator,
                             std::basic_string<char>::const_iterator,
                             std::basic_string<char> > tokenizer;
    typedef boost::tokenizer<boost::offset_separator,
                             std::basic_string<char>::const_iterator,
                             std::basic_string<char> >::iterator tokenizer_iterator;
    tokenizer tok(remain, osf);
    for(tokenizer_iterator ti=tok.begin(); ti!=tok.end();++ti){
      switch(pos) {
        case 0: 
          {
            hours = boost::lexical_cast<int>(*ti); 
            break;
          }
        case 1: 
          {
            min = boost::lexical_cast<short>(*ti); 
            break;
          }
        case 2: 
          {
            sec = boost::lexical_cast<short>(*ti); 
            break;
          }
        case 3:
          {
            std::string char_digits(ti->substr(1)); // digits w/no decimal
            int digits = static_cast<int>(char_digits.length());
            
            //Works around a bug in MSVC 6 library that does not support
            //operator>> thus meaning lexical_cast will fail to compile.
#if (defined(BOOST_MSVC) && (_MSC_VER <= 1200))  // 1200 == VC++ 6.0
            // _atoi64 is an MS specific function
            if(digits >= precision) {
              // drop excess digits
              fs = _atoi64(char_digits.substr(0, precision).c_str());
            }
            else if(digits == 0) {
              fs = 0; // just in case _atoi64 doesn't like an empty string
            }
            else {
              fs = _atoi64(char_digits.c_str());
            }
#else
            if(digits >= precision) {
              // drop excess digits
              fs = boost::lexical_cast<boost::int64_t>(char_digits.substr(0, precision));
            }
            else if(digits == 0) {
              fs = 0; // lexical_cast doesn't like empty strings
            }
            else {
              fs = boost::lexical_cast<boost::int64_t>(char_digits);
            }
#endif
            if(digits < precision){
              // trailing zeros get dropped from the string, 
              // "1:01:01.1" would yield .000001 instead of .100000
              // the power() compensates for the missing decimal places
              fs *= power(10, precision - digits); 
            }
            
            break;
          }
          default: break;
      }
      pos++;
    }
    if(sign) {
      return -time_duration(hours, min, sec, fs);
    }
    else {
      return time_duration(hours, min, sec, fs);
    }
  }

  //! Parse time string of form YYYYMMDDThhmmss where T is delimeter between date and time
  template<class time_type>
  inline
  time_type
  parse_iso_time(const std::string& s, char sep)
  {
    typedef typename time_type::time_duration_type time_duration;
    typedef typename time_type::date_type date_type;
    typedef special_values_parser<date_type, std::string::value_type> svp_type;

    // given to_iso_string can produce a special value string
    // then from_iso_string should be able to read a special value string
    // the special_values_parser is expensive to set up and not thread-safe
    // so it cannot be static, so we need to be careful about when we use it
    if (svp_type::likely(s)) {
        typedef typename svp_type::stringstream_type ss_type;
        typedef typename svp_type::stream_itr_type itr_type;
        typedef typename svp_type::match_results mr_type;
        svp_type p; // expensive
        mr_type mr;
        ss_type ss(s);
        itr_type itr(ss);
        itr_type end;
        if (p.match(itr, end, mr)) {
            return time_type(static_cast<special_values>(mr.current_match));
        }
    }

    //split date/time on a unique delimiter char such as ' ' or 'T'
    std::string date_string, tod_string;
    split(s, sep, date_string, tod_string);
    //call parse_date with first string
    date_type d = parse_undelimited_date<date_type>(date_string);
    //call parse_time_duration with remaining string
    time_duration td = parse_undelimited_time_duration<time_duration>(tod_string);
    //construct a time
    return time_type(d, td);
  }

} }//namespace date_time

#endif

/* time_parsing.hpp
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
*/