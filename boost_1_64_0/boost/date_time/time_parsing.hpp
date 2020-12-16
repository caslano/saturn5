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
lKAoE0QNGjWugHFBNwpi8GQl4VAIuByCAcVzQUDxwAVPVJQQAQMooKBEEC9QAa+J44Enbjxm/9FVXd3TYcKQZi/nvU66q34d//+6/q/6v0oRHK8CYMrm6uCH24NPR00lprhLTxEXrYDpszhFaCizdIBhvXBZd8WuqTwH/7nL2+C/DDim3RlJEU9nrfHNQ81CGGSZiWX7dh5zKJBJsAGVX6Gu8hy3P9SF8uQYX6i9aFmUKjFiqitZm5ql3Rv2aH+DIWUWPPfDswiedfB8BOGjXF7tMXh+g2cvfPd1wzfEVcOzAR4thX50CjEuxZlffIsUX4IakEh/k/gjueWmP36O/5Spc8+ZPHVG2oSSDaBqHxocAAOS1QLp6EhTo2ycu2Q2mTFYHSn1Kz7Tag97kdkeVrfHz4TDBDyTZOFMx8dyIAM7y9ds5b19LJavijy35AzVHsqLW8x04Q5NSksfUKfQSYNwvirT9/mUqPbBMogyZvjdiQh4FQOOUABLgr0pj6s5aoASVRrMoahrOOpkI2raNNL+Uuy1HJupxJKPyCActjTNfJP6I/j1DP7V/UJGrUW4ppwQ3b8fs/qKvrpYN4iLHQXFLl9A1/CnRpq+HSZdyLmkyTYNrk2Q7NT2fzoLAccU8AWWT+dHFnWc3PAaJQ9bLAM53jjdlMyB50Jgt9roDQnsS46ab2+vXHr6QTgvrOLfh8qL7FPZsKMTLi/gwoYEsmvc4tKc2zbmajKYQpI5RLJAGUGi7qVb1vNjyOFDn4j7ULtDVvLiXeGlooo88WJhtN4O4CDhTb3lR93zdAD9v/zYEIZFdtvW+iJbJGW15LXykxSFl+KEeh9rjn6ei5qj21EyGmr4/zz2F1m4WDFnA3DcvGxNhBeBCgNarwZByz2YqBt0GvRTDdkt5JY9b64BTt267CIjXxisSjQaRf7B0NeZoUuDJ5uhSxl6MUMHFGjR+RNMCSbiP07zOKdJVtKIIWHbQFMaCKOfCFqvYXuov9tL3OmrRvESiFaUnvLz8V98efLN8A97anlhqLhbLV0NjekycJ1zFJJ9FZP95vuQ7HeYyf7nY4CCx3kB9FRM5MZE3ahYmfxVTt6Hkt9pTn4oJv/GY9QQxBa/ciUua2j70rVVCh2K24t3Gr7rOunnIhYqOfERJKrBm1yD2jlYg9vMNZiTCzW41qPmPkP/389P86YkaxyS9VQFlJaj20+j5WiRkg7U960psNgUuOgocSN2Ed+IXUw3Yv81V7llPnXKFLJmGbc+l1TrO7nq3jnW+4V2HW3f3tvMiWjvaXNEez8dWhvm+gnn+vRsupTITJBpkHH94DgDSxJ6CrPxc6L89BtkwZzru8RZyOJBWU96mkEHpHUyw8Ls4OAz+FJHNezFw6Dk3W5TY6C99lI62t9tiwo8JyMygxsxgwctGciNn/wBRo1wT8AWqFd/E1CpgabXMtqR1FZChTFh+JRAGyNFPEK0VJxdE1gwx4NFcBp22KzWt0whWrKFaK8ns9siclY0vhv6Fwqe34Vmuy41yWoZdwZMZVDLfQJqzClbos6cDjiXQxjhTnmdR+o7uVcMHaq/S8l0WrghjDXiW8ETAFbE7M78xYiZi6d8JELVdEdpeT8RIpYxLjeXRVszJVhWkGL7i9sXj0Z1PPXqzRQBoFQ3ApEleyTUYgsdJUsDF6osvXlaY3AFfzLB4bBq5qWc9OQlm4NNvK9IM7eWUFsJ2A3feEisf4/uHGF3okyxJWfDSag04s24BOLEkkPkPbtj1v6S6NXOS/ZqC1t6tRUpXu25VK/2dCuvtumP3//dT1kf1uXTUkz6HX7mLhjmKSbFE7lS1k8yoYjV1+owaT+ELFX+y7c=
*/