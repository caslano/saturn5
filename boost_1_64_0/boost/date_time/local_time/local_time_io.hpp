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
VvfQZCaDiGpEfKNHtqFj/eoAdzj1Vjv83ArZX/w1cHiP+clj3H2xeF9n4TjoEh8YLO6GaA7weUITupUpxcBtf/R6EiheZgKySCiRP7tM3JoSs+mykmlUr8a/aidoUK0ItibY/xkfNN8ChdI5GNJh/PvZqJs+HrYLePEwr7eZBby/PQj59PXW06M0EoQ4GAlyVWFn5u0P8vh6jyhNtTI01RpnDhsvMbRpttWK6OcDHA17WoHoo1EdRyOODGIEce9A3N4Uh3uQwlTkHKAOz/3JBzTZuIolxxdC4IwQvtAVyo5zIrtSS9VgpVqhpWpwpVqupWpwpVqmpEJApFoGXkiCEL4QWoEQvhACZ4TwBXcpuaFDasc/F+pyinXOv5f2Gn1M6o+1QY3Ogd7ARExyVDgOi33xp1whi0aVbPwHAvXtuOwB6TjonjWadb9MpW2b+I2ZXdv9/gdrcg0sjOzxpaVyYuC8dSXzRzHz1vsxZbfeg4jdxp5qYCkNxLaA1SB69n1M9IcVg7feu4MmNaIqwDVdZt42jzfgS7v6yCVu48zrDfh53oBP/HnEWjox9pScJMXEmCW/n4pjQw9L/kKEN+Cj7KNhr4pHrHPxPX4rHuhU8UGq+Da5HOPcSGnFB3XFI52u+Nlbdqr4Z55QFZ+MDF3xmMUdcBHzHx2hij9luBUf5IoPqor/6mYmenPYPegxUPFrbMWvGW7Fz1kpV6foY9tS8UFeGR1+xQe54lEcPT9myXeEuOKl91Oz4xn8neXvVnw7X/rJtv6Sgu5110Q2rmCi36cZB3U87MRAjtmhQdPtquXHhqgemnnHQIyrneXm/fD4B8r7iLhHhnhNvGrp1QH2xEjPevD33M0D5wOApR+e83NBY4gtqKMIta1yoB6Kv2HfRlbcLFbiBNdXD9dXFvU1fwo5JlwHiSb9w++Swo4FmEgnixvgq9MSS9d/DnBZYqiPh8SCOhuo3hK3oqp2KXGrlXgGSTxjEOm/rmKJ4QPLAwyJsZQ/m3M7ve3Dyg2j2jvrGBsVW10nyZGqb4pCqXMjVBitx0AsIv0h8C1LGmqrSVdtYsfO+1lBmS7cqa/2lyomkonZWLLJ60BFPGx3GKScv96lBkcnXmgPVGCYSH6fj/eS38cJ/R/NiEY+/82f8uejN/xom3qPjJ36o7BIRL8e6pLddxTMczCu99vFMfq+Q7f9hPPnW2WTwncY0AxA3HnCApbKdfzqRsy4/IbbxKUUpK5/wX5291GSEFkouXtPJdiKrRrA41vAQsX91Fns48DfGoBY0Ob5zC5q6LHX8RS1n/Kvv1sdtih7zDt3M1+Z5hZ7LUTvcKecN30QU85TMOX8op1yvnwNKtDg+8yNp3w9oPTduwbvh83ISAAG0QHGE7gaRQJX5GRaJjFdHJO0MWdzTLON+QLHtNuYj3NMi41Jc0zCxkxDDE+sZCsoVPHukBvupXCl8+Bm3utJQ0uKHrz1syuEhR578H+5WeuU67YXmd98eQ3f71Zzsyjwx0K86G7vbHjlJoEdJns+lXInaTT9Zt6DB1qzumkcPSvTxcd3Oy/FlvWIvNNp41+7HKMt5Fs6ta6VgLBMu8uw+h53ITdjnzh1JvwIoKqlvwdyF/v13qbZgBjHf8OwQRGBjVXGZEMX5rDqsot253oZiR0b5Hza12KT6jFPVLuIbVW63e3CPyYkqoK831D17/sL8M9iJFgZDA31dC0vaGa2Pw5fSt9Yk2vynyyIMUGpHFTlRXczze/Y+jpqCY15mokD1c47B6e57nYyPjXsmkVTrFkjBuQ4bGWUzMk1dRbvK7080DikeACa66fcA3GhD9jmmrPN9SiziIqrR/gd4iy/vLSnaLE=
*/