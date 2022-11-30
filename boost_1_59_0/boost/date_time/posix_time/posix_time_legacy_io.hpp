#ifndef POSIX_TIME_PRE133_OPERATORS_HPP___
#define POSIX_TIME_PRE133_OPERATORS_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst 
 * $Date$
 */

/*! @file posix_time_pre133_operators.hpp
 * These input and output operators are for use with the 
 * pre 1.33 version of the date_time libraries io facet code. 
 * The operators used in version 1.33 and later can be found 
 * in posix_time_io.hpp */

#include <iostream>
#include <string>
#include <sstream>
#include "boost/date_time/compiler_config.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include "boost/date_time/posix_time/ptime.hpp"
#include "boost/date_time/posix_time/time_period.hpp"
#include "boost/date_time/time_parsing.hpp"

namespace boost {
namespace posix_time {


//The following code is removed for configurations with poor std::locale support (eg: MSVC6, gcc 2.9x)
#ifndef BOOST_DATE_TIME_NO_LOCALE
#if defined(USE_DATE_TIME_PRE_1_33_FACET_IO)
  //! ostream operator for posix_time::time_duration
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const time_duration& td)
  {
    typedef boost::date_time::ostream_time_duration_formatter<time_duration, charT> duration_formatter;
    duration_formatter::duration_put(td, os);
    return os;
  }

  //! ostream operator for posix_time::ptime
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const ptime& t)
  {
    typedef boost::date_time::ostream_time_formatter<ptime, charT> time_formatter;
    time_formatter::time_put(t, os);
    return os;
  }

  //! ostream operator for posix_time::time_period
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const time_period& tp)
  {
    typedef boost::date_time::ostream_time_period_formatter<time_period, charT> period_formatter;
    period_formatter::period_put(tp, os);
    return os;
  }
#endif // USE_DATE_TIME_PRE_1_33_FACET_IO
/******** input streaming ********/
  template<class charT>
  inline
  std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is, time_duration& td)
  {
    // need to create a std::string and parse it
    std::basic_string<charT> inp_s;
    std::stringstream out_ss;
    is >> inp_s;
    typename std::basic_string<charT>::iterator b = inp_s.begin();
    // need to use both iterators because there is no requirement
    // for the data held by a std::basic_string<> be terminated with
    // any marker (such as '\0').
    typename std::basic_string<charT>::iterator e = inp_s.end();
    while(b != e){
      out_ss << is.narrow(*b, 0);
      ++b;
    }

    td = date_time::parse_delimited_time_duration<time_duration>(out_ss.str());
    return is;
  }

  template<class charT>
  inline
  std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is, ptime& pt)
  {
    gregorian::date d(not_a_date_time);
    time_duration td(0,0,0);
    is >> d >> td;
    pt = ptime(d, td);

    return is;
  }

  /** operator>> for time_period. time_period must be in 
   * "[date time_duration/date time_duration]" format. */
  template<class charT>
  inline
  std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is, time_period& tp)
  {
    gregorian::date d(not_a_date_time);
    time_duration td(0,0,0);
    ptime beg(d, td);
    ptime end(beg);
    std::basic_string<charT> s;
    // get first date string and remove leading '['
    is >> s;
    {
      std::basic_stringstream<charT> ss;
      ss << s.substr(s.find('[')+1);
      ss >> d;
    }
    // get first time_duration & second date string, remove the '/'
    // and split into 2 strings
    is >> s; 
    {
      std::basic_stringstream<charT> ss;
      ss << s.substr(0, s.find('/'));
      ss >> td;
    }
    beg = ptime(d, td);
    {
      std::basic_stringstream<charT> ss;
      ss << s.substr(s.find('/')+1);
      ss >> d;
    }
    // get last time_duration and remove the trailing ']'
    is >> s;
    {
      std::basic_stringstream<charT> ss;
      ss << s.substr(0, s.find(']'));
      ss >> td;
    }
    end = ptime(d, td);

    tp = time_period(beg,end);
    return is;
  }


#endif //BOOST_DATE_TIME_NO_LOCALE

} } // namespaces

#endif // POSIX_TIME_PRE133_OPERATORS_HPP___

/* posix_time_legacy_io.hpp
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
*/