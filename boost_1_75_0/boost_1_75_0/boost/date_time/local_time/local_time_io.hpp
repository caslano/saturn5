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
Ne2Ye7W6ornEUzorS2BzRLxZvoIgcEPoo0o1+VnXq2WIcetjvlh2QjH4RuRUbf7lVyLeCldk/jJlfcHB627XlL934uW+69czu6SKAX+Yp2yan8hSGGgXAVmWzdq5DdUDhokaj77pN66ITREEuW/vlOx9dq+gEdyo/B1Baeen7GZQrUPDy80H2qwukwcc4rZmAmZpNjKhI85+0h8fpw+5GZD2SOk3QE1iUlDpGdxqKgz+usD9E3HgeCDxRbMO1VLFz2sA7c0Ue910CIQ16ZMybC/cH1fUtBWgiLsC3LBdGDwZaLcQjqx0G+tmD+E5Hw3KibHVEFScpC4TcdygnsEoN0mkxqqkUcSo1qimUc7vAGm2QjsdejQpV4kx841einJ0lcpz7GVT98NBHpVqVzaUp2hD42EefK8NcazCujy/MW/Hf/Dsd8WLPBZ+VjSMerko8D0FZF4F+LCRFiFfPAb4RfMWOgpKGoXeAhNjzIa8AVbLAiRLJhfkc7hE+dA86G/e9y8b2/lCku94HRL5Lbta0V/GgqfoSxmkTpVreHBkmUrv05Vpk+4PKlRSlH2WEvOr6PZH73yUWHNdc16Ok1zzN+gNGM9lfrFSrQtb4yZZdc+kOIyPJUwsck0XG02au65G27EcGEi5rlCCoiCM/DfSsEKMO1lo5MWMoLjNHllVhHGzFmNiax6eqOIq7BfsLvcivoK4CuN7HW4my/sV
*/