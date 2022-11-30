#ifndef DATE_TIME_DATE_FORMATTING_LOCALES_HPP___
#define DATE_TIME_DATE_FORMATTING_LOCALES_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/date_time/locale_config.hpp" // set BOOST_DATE_TIME_NO_LOCALE

#ifndef BOOST_DATE_TIME_NO_LOCALE

#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/date_names_put.hpp"
#include "boost/date_time/parse_format_base.hpp"
#include <boost/io/ios_state.hpp>
//#include <string>
#include <sstream>
#include <iomanip>


namespace boost {
namespace date_time {

  //! Formats a month as as string into an ostream
  template<class facet_type,
           class charT = char>
  class ostream_month_formatter
  {
  public:
    typedef typename facet_type::month_type month_type;
    typedef std::basic_ostream<charT> ostream_type;

    //! Formats a month as as string into an output iterator
    static void format_month(const month_type& month,
                             ostream_type& os,
                             const facet_type& f)
    {

      switch (f.month_format())
      {
        case month_as_short_string:
        {
          std::ostreambuf_iterator<charT> oitr(os);
          f.put_month_short(oitr, month.as_enum());
          break;
        }
        case month_as_long_string:
        {
          std::ostreambuf_iterator<charT> oitr(os);
          f.put_month_long(oitr, month.as_enum());
          break;
        }
        case month_as_integer:
        {
          boost::io::basic_ios_fill_saver<charT> ifs(os);
          os << std::setw(2) << std::setfill(os.widen('0')) << month.as_number();
          break;
        }

      }
    } // format_month

  };


  //! Formats a weekday
  template<class weekday_type,
           class facet_type,
           class charT = char>
  class ostream_weekday_formatter
  {
  public:
    typedef typename facet_type::month_type month_type;
    typedef std::basic_ostream<charT> ostream_type;

    //! Formats a month as as string into an output iterator
    static void format_weekday(const weekday_type& wd,
                               ostream_type& os,
                               const facet_type& f,
                               bool  as_long_string)
    {

      std::ostreambuf_iterator<charT> oitr(os);
      if (as_long_string) {
        f.put_weekday_long(oitr, wd.as_enum());
      }
      else {
        f.put_weekday_short(oitr, wd.as_enum());
      }

    } // format_weekday

  };


  //! Convert ymd to a standard string formatting policies
  template<class ymd_type,
           class facet_type,
           class charT = char>
  class ostream_ymd_formatter
  {
  public:
    typedef typename ymd_type::month_type month_type;
    typedef ostream_month_formatter<facet_type, charT> month_formatter_type;
    typedef std::basic_ostream<charT> ostream_type;
    typedef std::basic_string<charT> foo_type;

    //! Convert ymd to a standard string formatting policies
    /*! This is standard code for handling date formatting with
     *  year-month-day based date information.  This function
     *  uses the format_type to control whether the string will
     *  contain separator characters, and if so what the character
     *  will be.  In addtion, it can format the month as either
     *  an integer or a string as controled by the formatting
     *  policy
     */
    //     static string_type ymd_to_string(ymd_type ymd)
//     {
//       std::ostringstream ss;
//       facet_type dnp;
//       ymd_put(ymd, ss, dnp);
//       return ss.str();
//       }


    // Put ymd to ostream -- part of ostream refactor
    static void ymd_put(ymd_type ymd,
                        ostream_type& os,
                        const facet_type& f)
    {
      boost::io::basic_ios_fill_saver<charT> ifs(os);
      std::ostreambuf_iterator<charT> oitr(os);
      switch (f.date_order()) {
        case ymd_order_iso: {
          os << ymd.year;
          if (f.has_date_sep_chars()) {
            f.month_sep_char(oitr);
          }
          month_formatter_type::format_month(ymd.month, os, f);
          if (f.has_date_sep_chars()) {
            f.day_sep_char(oitr);
          }
          os  << std::setw(2) << std::setfill(os.widen('0'))
              << ymd.day;
          break;
        }
        case ymd_order_us: {
          month_formatter_type::format_month(ymd.month, os, f);
          if (f.has_date_sep_chars()) {
          f.day_sep_char(oitr);
          }
          os  << std::setw(2) << std::setfill(os.widen('0'))
            << ymd.day;
          if (f.has_date_sep_chars()) {
            f.month_sep_char(oitr);
          }
          os << ymd.year;
          break;
        }
        case ymd_order_dmy: {
          os  << std::setw(2) << std::setfill(os.widen('0'))
              << ymd.day;
          if (f.has_date_sep_chars()) {
            f.day_sep_char(oitr);
          }
          month_formatter_type::format_month(ymd.month, os, f);
          if (f.has_date_sep_chars()) {
            f.month_sep_char(oitr);
          }
          os << ymd.year;
          break;
        }
      }
    }
  };


  //! Convert a date to string using format policies
  template<class date_type,
           class facet_type,
           class charT = char>
  class ostream_date_formatter
  {
  public:
    typedef std::basic_ostream<charT> ostream_type;
    typedef typename date_type::ymd_type ymd_type;

    //! Put date into an ostream
    static void date_put(const date_type& d,
                         ostream_type& os,
                         const facet_type& f)
    {
      special_values sv = d.as_special();
      if (sv == not_special) {
        ymd_type ymd = d.year_month_day();
        ostream_ymd_formatter<ymd_type, facet_type, charT>::ymd_put(ymd, os, f);
      }
      else { // output a special value
        std::ostreambuf_iterator<charT> coi(os);
        f.put_special_value(coi, sv);
      }
    }


    //! Put date into an ostream
    static void date_put(const date_type& d,
                         ostream_type& os)
    {
      //retrieve the local from the ostream
      std::locale locale = os.getloc();
      if (std::has_facet<facet_type>(locale)) {
        const facet_type& f = std::use_facet<facet_type>(locale);
        date_put(d, os, f);
      }
      else {
        //default to something sensible if no facet installed
        facet_type default_facet;
        date_put(d, os, default_facet);
      }
    } // date_to_ostream 
  }; //class date_formatter


} } //namespace date_time

#endif

#endif


/* date_formatting_locales.hpp
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
*/