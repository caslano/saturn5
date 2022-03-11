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