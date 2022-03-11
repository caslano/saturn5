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