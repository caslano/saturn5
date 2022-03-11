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