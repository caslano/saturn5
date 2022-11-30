#ifndef BOOST_DATE_TIME_LOCAL_TIME_IO_HPP__
#define BOOST_DATE_TIME_LOCAL_TIME_IO_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <string>
#include <locale>
#include <iostream>
#include <iterator> // i/ostreambuf_iterator
#include <boost/io/ios_state.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/time_facet.hpp>
#include <boost/date_time/string_convert.hpp>
#include <boost/date_time/local_time/local_time_types.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/local_time/posix_time_zone.hpp>
#include <boost/date_time/local_time/conversion.hpp> // to_tm will be needed in the facets

namespace boost {
namespace local_time {

  typedef boost::date_time::time_facet<local_date_time, wchar_t> wlocal_time_facet;
  typedef boost::date_time::time_facet<local_date_time, char>     local_time_facet;

  typedef boost::date_time::time_input_facet<local_date_time::utc_time_type,wchar_t> wlocal_time_input_facet;
  typedef boost::date_time::time_input_facet<local_date_time::utc_time_type,char>     local_time_input_facet;

  //! operator<< for local_date_time - see local_time docs for formatting details
  template<class CharT, class TraitsT>
  inline
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const local_date_time& ldt)
  {
    boost::io::ios_flags_saver iflags(os);
    typedef local_date_time time_type;//::utc_time_type typename 
    typedef date_time::time_facet<time_type, CharT> custom_time_facet;
    std::ostreambuf_iterator<CharT> oitr(os);

    if(std::has_facet<custom_time_facet>(os.getloc())) {
      std::use_facet<custom_time_facet>(os.getloc()).put(oitr, 
                                                         os, 
                                                         os.fill(), 
                                                         ldt);
    }
    else {
      custom_time_facet* f = new custom_time_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), ldt);
    }

    return os;
  }


  //! input operator for local_date_time
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, local_date_time& ldt)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false);
    if (strm_sentry) {
      try {
        typedef typename local_date_time::utc_time_type utc_time_type;
        typedef typename date_time::time_input_facet<utc_time_type, CharT> time_input_facet;

        // intermediate objects
        std::basic_string<CharT> tz_str;
        utc_time_type pt(not_a_date_time); 

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<time_input_facet>(is.getloc())) {
          std::use_facet<time_input_facet>(is.getloc()).get_local_time(sit, str_end, is, pt, tz_str);
        }
        else {
          time_input_facet* f = new time_input_facet();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get_local_time(sit, str_end, is, pt, tz_str);
        }
        if(tz_str.empty()) {
          time_zone_ptr null_ptr;
          // a null time_zone_ptr creates a local_date_time that is UTC
          ldt = local_date_time(pt, null_ptr);
        }
        else {
          time_zone_ptr tz_ptr(new posix_time_zone(date_time::convert_string_type<CharT,char>(tz_str)));
          // the "date & time" constructor expects the time label to *not* be utc.
          // a posix_tz_string also expects the time label to *not* be utc.
          ldt = local_date_time(pt.date(), pt.time_of_day(), tz_ptr, local_date_time::EXCEPTION_ON_ERROR);
        }
      }
      catch(...) {
        // mask tells us what exceptions are turned on
        std::ios_base::iostate exception_mask = is.exceptions();
        // if the user wants exceptions on failbit, we'll rethrow our 
        // date_time exception & set the failbit
        if(std::ios_base::failbit & exception_mask) {
          try { is.setstate(std::ios_base::failbit); }
          catch(std::ios_base::failure&) {} // ignore this one
          throw; // rethrow original exception
        }
        else {
          // if the user want's to fail quietly, we simply set the failbit
          is.setstate(std::ios_base::failbit);
        }

      }
    }
    return is;
  }

  //! output operator for local_time_period
  template <class CharT, class TraitsT>
  inline
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os,
             const boost::local_time::local_time_period& p) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::time_facet<local_date_time, CharT> custom_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_facet>(os.getloc())) {
      std::use_facet<custom_facet>(os.getloc()).put(oitr, os, os.fill(), p);
    }
    else {
      //instantiate a custom facet for dealing with periods since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the local did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      custom_facet* f = new custom_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), p);
    }
    return os;
  }

  //! input operator for local_time_period
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, boost::local_time::local_time_period& tp)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false);
    if (strm_sentry) {
      try {
        typedef typename date_time::time_input_facet<local_date_time, CharT> time_input_facet;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<time_input_facet>(is.getloc())) {
          std::use_facet<time_input_facet>(is.getloc()).get(sit, str_end, is, tp);
        }
        else {
          time_input_facet* f = new time_input_facet();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, tp);
        }
      }
      catch(...) {
        std::ios_base::iostate exception_mask = is.exceptions();
        if(std::ios_base::failbit & exception_mask) {
          try { is.setstate(std::ios_base::failbit); }
          catch(std::ios_base::failure&) {}
          throw; // rethrow original exception
        }
        else {
          is.setstate(std::ios_base::failbit);
        }

      }
    }
    return is;
  }

} } // namespaces

#endif // BOOST_DATE_TIME_LOCAL_TIME_IO_HPP__

/* local_time_io.hpp
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
*/