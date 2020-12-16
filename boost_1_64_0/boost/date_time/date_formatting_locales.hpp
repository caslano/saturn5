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
MZJ5iylB1DLKGR1HLo95fHo0OMJgOYasTW1yDAy78FHMExALKiDD0s2Fjs71naT+L/IS/F98uTdF/xd5Vv8XnyTkSjj/bE3/B0qfir+Mfgn4HWik6J9j50BLeX+OJS8vrrh7OY9Z2pW+9qUXzhbibI3Zyhid7s2/mNzmZDki+dl8fqA/tfIECqOTCxfSOpK+yuaLr1n0lfqaNl5L9c0ALcTV0dk1ZSOWR0JpdACoVsemtZf9i+qvnQ9HDIpPSccQL5qHuTylv6gAz0J1YxrpntfbsNwbGMyH0HGmvBexUF1F/rDWhhybKa/dSk3cje/f3xyk+7eU2c0OTiXe10/5jd6wUKtB61vVKNfu+Lb2oP0wvpnnu+IIPdisWGVDcSw4mlt4OMj5hkOQM+9gaJceQeUeNPW/HsgtLR/QO+dtvItS53DGdznjh0OR8X57xibOeK9eAk1fQjnBzjmiYWngc+SKgU9Eh0UsVR1xK5biQ+P6I7z5RAykY/PL9HBSudWI0aOsuPEe7WM6IvOo12qkNz2P6fBaMoj97qf5On5Y1LX3uSv6iaZRGkBllV1h3ilqut+yGIBRTMDmurASNaYfMBA+6Z1e6Q2hdSX0W3+CSEBs17D7iNAEa+pirH3YRxYPjsNfDISfDYhzvhWW65KGw522OFjhjF5rutXaTMtpZb0cC5WDOTKZOZ4tAHNsBHM8pJnjtnTaMANQGrfepQTrnQgtGKM25oJwHUzghsBAgEa7Waqd/KrNlCSULS8u8pv4ww5X7QP2YiSOEUg8YUdiQLoqzk3FEa+2OrlUdUvdSAeVrpyFZXiveJPiUUw57q/ZLmyyXYdLm2yBFDErF5vHxT6fj2IftRf7W7cq9mrAQz5xUzF7+ttWEW4mslaI+kWOz7V6pT2T0rdMdgI0MTU2HKeaSQfbko5xmlb85jX3DimjVVG2qTwhPfeN1XPuHgeV8LmD8zoS8kLLma2VHqtsWZuR9bF2s/bQWU+2Zb0cWRfGZcWvVKym6XwH2fKdgHzlCUXqfC6d74Ovrfl6I18W/ZG8I5rsGG6yfmITbK29yf6RpprsbfrUHtqGU1rpk3HZrULfQkttdF4/gMNZOBK7OPFr/XTiKZy4u0oM5o8uVvcG9HpnkE45Mi5lGlKeTBdncMp1Zsq0uJQupBSD9E+5YkcNSlKxfqpiSu+MObyEmOdO+v/1WKexqMhprKP/Hvp/NP3/tOgHG+/v8sT5yzcngUt7xTlugUikXvy2qSByY2+7g053S0gycx0Z0GyUR7ExlyDuVMRhpNZOnF7Jtlo8IM1YR3LlJAs4W6k8oaE8T1oIiEiCqRK8RgnUnhYFBMrDzdrFNrR8d2bRi+3M92aKAoBK7p9DCABOdZO4gKGAGBLTXY9Qr8BKLTo/OYzvjokeYAk8bzAH8sFXZ3Ru5Ge79trO7jujp4sZqmQPh7OW1Dx9DYUQUo0V4UIUUIsiv15vmyF8JEa1BfWoZ1lB+ZeDZFeMrCM8KWAF4cE4enpxXf26AZoKKAkgpiQz788nThz+uKfSnAdIc86NPezLGEgeoOV/d2hlV7i35o40uae/lXvc91IUzW7ZlOpWemX92O7D5k+guFUUQBSFYBISp3QD5s6sez4yhj2xXof8UgxsWRR2lsiQRbdT3CwGrW+hTYsTjdegkhlcSd3j6LfUgYihn+5NdN820SmG0y/66Y3pR/Rwun3vXsi8F6ZzD1wreqCXCHX0v9m7Evgoiyu+u9kkCwE23OFOQoDIZdCI4ZKNRrto1IiIQVCjoAZBRdhAVAgiVzCgeCFWVPAq1dqqVUzwCocQFQS0qLUeeFQ3rletB6hh+/7zZuabb3chG6rWtuY=
*/