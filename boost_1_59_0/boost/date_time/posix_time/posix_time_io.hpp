#ifndef DATE_TIME_POSIX_TIME_IO_HPP__
#define DATE_TIME_POSIX_TIME_IO_HPP__

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <locale>
#include <iostream>
#include <iterator> // i/ostreambuf_iterator
#include <boost/io/ios_state.hpp>
#include <boost/date_time/time_facet.hpp>
#include <boost/date_time/period_formatter.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_period.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/posix_time/conversion.hpp> // to_tm will be needed in the facets

namespace boost {
namespace posix_time {


  //! wptime_facet is depricated and will be phased out. use wtime_facet instead
  //typedef boost::date_time::time_facet<ptime, wchar_t> wptime_facet;
  //! ptime_facet is depricated and will be phased out. use time_facet instead
  //typedef boost::date_time::time_facet<ptime, char>     ptime_facet;

  //! wptime_input_facet is depricated and will be phased out. use wtime_input_facet instead
  //typedef boost::date_time::time_input_facet<ptime,wchar_t> wptime_input_facet;
  //! ptime_input_facet is depricated and will be phased out. use time_input_facet instead
  //typedef boost::date_time::time_input_facet<ptime,char>     ptime_input_facet;

  typedef boost::date_time::time_facet<ptime, wchar_t>     wtime_facet;
  typedef boost::date_time::time_facet<ptime, char>         time_facet;

  typedef boost::date_time::time_input_facet<ptime, wchar_t>     wtime_input_facet;
  typedef boost::date_time::time_input_facet<ptime, char>         time_input_facet;

  template <class CharT, class TraitsT>
  inline
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os,
             const ptime& p) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc()))
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), p);
    else {
      //instantiate a custom facet for dealing with times since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), p);
    }
    return os;
  }

  //! input operator for ptime
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, ptime& pt)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false);
    if (strm_sentry) {
      try {
        typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet_local;
        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<time_input_facet_local>(is.getloc())) {
          std::use_facet<time_input_facet_local>(is.getloc()).get(sit, str_end, is, pt);
        }
        else {
          time_input_facet_local* f = new time_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, pt);
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


  template <class CharT, class TraitsT>
  inline 
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os,
             const boost::posix_time::time_period& p) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc())) {
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), p);
    }
    else {
      //instantiate a custom facet for dealing with periods since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the local did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), p);
    }
    return os;
  }

  //! input operator for time_period
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, time_period& tp)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false);
    if (strm_sentry) {
      try {
        typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet_local;
        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<time_input_facet_local>(is.getloc())) {
          std::use_facet<time_input_facet_local>(is.getloc()).get(sit, str_end, is, tp);
        }
        else {
          time_input_facet_local* f = new time_input_facet_local();
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


  //! ostream operator for posix_time::time_duration 
  //  todo fix to use facet --  place holder for now...
  template <class CharT, class Traits>
  inline
  std::basic_ostream<CharT, Traits>&
  operator<<(std::basic_ostream<CharT, Traits>& os, const time_duration& td)
  {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc()))
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), td);
    else {
      //instantiate a custom facet for dealing with times since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), td);
    }
    return os;
  }

  //! input operator for time_duration
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, time_duration& td)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false);
    if (strm_sentry) {
      try {
        typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet_local;
        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<time_input_facet_local>(is.getloc())) {
          std::use_facet<time_input_facet_local>(is.getloc()).get(sit, str_end, is, td);
        }
        else {
          time_input_facet_local* f = new time_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, td);
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
#endif // DATE_TIME_POSIX_TIME_IO_HPP__

/* posix_time_io.hpp
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
*/