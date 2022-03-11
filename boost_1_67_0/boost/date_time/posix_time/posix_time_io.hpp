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