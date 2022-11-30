#ifndef DATE_TIME_GREGORIAN_IO_HPP__
#define DATE_TIME_GREGORIAN_IO_HPP__

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
#include <boost/date_time/date_facet.hpp>
#include <boost/date_time/period_parser.hpp>
#include <boost/date_time/period_formatter.hpp>
#include <boost/date_time/special_values_parser.hpp>
#include <boost/date_time/special_values_formatter.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/gregorian/conversion.hpp> // to_tm will be needed in the facets

namespace boost {
namespace gregorian {


  typedef boost::date_time::period_formatter<wchar_t> wperiod_formatter;
  typedef boost::date_time::period_formatter<char>    period_formatter;
  
  typedef boost::date_time::date_facet<date,wchar_t> wdate_facet;
  typedef boost::date_time::date_facet<date,char>    date_facet;

  typedef boost::date_time::period_parser<date,char>       period_parser;
  typedef boost::date_time::period_parser<date,wchar_t>    wperiod_parser;
    
  typedef boost::date_time::special_values_formatter<char> special_values_formatter; 
  typedef boost::date_time::special_values_formatter<wchar_t> wspecial_values_formatter; 
  
  typedef boost::date_time::special_values_parser<date,char> special_values_parser; 
  typedef boost::date_time::special_values_parser<date,wchar_t> wspecial_values_parser; 
  
  typedef boost::date_time::date_input_facet<date,char>    date_input_facet;
  typedef boost::date_time::date_input_facet<date,wchar_t> wdate_input_facet;

  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::date& d) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), d);
    else {
      //instantiate a custom facet for dealing with dates since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every date
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues at some later point.  With the default settings
      //for the facet the resulting format will be the same as the
      //std::time_facet settings.
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), d);
    }
    return os;
  }

  //! input operator for date
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, date& d)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;
        
        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, d);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, d);
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
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::date_duration& dd) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), dd);
    else {
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), dd);

    }
    return os;
  }

  //! input operator for date_duration
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, date_duration& dd)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;
        
        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, dd);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, dd);
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

  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::date_period& dp) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), dp);
    else {
      //instantiate a custom facet for dealing with date periods since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the local did not already exist.  Of course this will be overridden
      //if the user imbues at some later point.  With the default settings
      //for the facet the resulting format will be the same as the
      //std::time_facet settings.
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), dp);

    }
    return os;
  }

  //! input operator for date_period 
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, date_period& dp)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, dp);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, dp);
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

  /********** small gregorian types **********/
  
  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::greg_month& gm) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), gm);
    else {
      custom_date_facet* f = new custom_date_facet();//-> 10/1074199752/32 because year & day not initialized in put(...)
      //custom_date_facet* f = new custom_date_facet("%B");
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), gm);
    }
    return os;
  }

  //! input operator for greg_month
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, greg_month& m)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, m);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, m);
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


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::greg_weekday& gw) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), gw);
    else {
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), gw);
    }
    return os;
  }
 
  //! input operator for greg_weekday
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, greg_weekday& wd)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, wd);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, wd);
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

  //NOTE: output operator for greg_day was not necessary

  //! input operator for greg_day
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, greg_day& gd)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, gd);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, gd);
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

  //NOTE: output operator for greg_year was not necessary

  //! input operator for greg_year
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, greg_year& gy)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, gy);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, gy);
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

  /********** date generator types **********/
  
  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::partial_date& pd) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), pd);
    else {
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), pd);
    }
    return os;
  }

  //! input operator for partial_date
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, partial_date& pd)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, pd);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, pd);
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

  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::nth_day_of_the_week_in_month& nkd) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), nkd);
    else {
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), nkd);
    }
    return os;
  }

  //! input operator for nth_day_of_the_week_in_month
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, 
             nth_day_of_the_week_in_month& nday)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, nday);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, nday);
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


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_in_month& fkd) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), fkd);
    else {
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), fkd);
    }
    return os;
  }

  //! input operator for first_day_of_the_week_in_month
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, 
             first_day_of_the_week_in_month& fkd)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, fkd);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, fkd);
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


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::last_day_of_the_week_in_month& lkd) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), lkd);
    else {
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), lkd);
    }
    return os;
  }

  //! input operator for last_day_of_the_week_in_month
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, 
             last_day_of_the_week_in_month& lkd)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, lkd);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, lkd);
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


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_after& fda) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc())) {
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), fda);
    } 
    else {
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), fda);
    }
    return os;
  }

  //! input operator for first_day_of_the_week_after
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, 
             first_day_of_the_week_after& fka)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, fka);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, fka);
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


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_before& fdb) {
    boost::io::ios_flags_saver iflags(os);
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    std::ostreambuf_iterator<CharT> output_itr(os);
    if (std::has_facet<custom_date_facet>(os.getloc())) {
      std::use_facet<custom_date_facet>(os.getloc()).put(output_itr, os, os.fill(), fdb);
    }
    else {
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(output_itr, os, os.fill(), fdb);
    }
    return os;
  }

  //! input operator for first_day_of_the_week_before
  template <class CharT, class Traits>
  inline
  std::basic_istream<CharT, Traits>&
  operator>>(std::basic_istream<CharT, Traits>& is, 
             first_day_of_the_week_before& fkb)
  {
    boost::io::ios_flags_saver iflags(is);
    typename std::basic_istream<CharT, Traits>::sentry strm_sentry(is, false); 
    if (strm_sentry) {
      try {
        typedef typename date_time::date_input_facet<date, CharT> date_input_facet_local;

        std::istreambuf_iterator<CharT,Traits> sit(is), str_end;
        if(std::has_facet<date_input_facet_local>(is.getloc())) {
          std::use_facet<date_input_facet_local>(is.getloc()).get(sit, str_end, is, fkb);
        }
        else {
          date_input_facet_local* f = new date_input_facet_local();
          std::locale l = std::locale(is.getloc(), f);
          is.imbue(l);
          f->get(sit, str_end, is, fkb);
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

#endif // DATE_TIME_GREGORIAN_IO_HPP__

/* gregorian_io.hpp
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
*/