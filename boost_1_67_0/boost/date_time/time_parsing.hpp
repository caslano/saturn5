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
  //everywehere. Hasn't been tested with negatives and zeros
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
      };
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
      };
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