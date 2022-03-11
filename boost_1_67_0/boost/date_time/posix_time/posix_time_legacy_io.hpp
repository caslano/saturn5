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