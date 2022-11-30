#ifndef GREGORIAN_FACET_HPP___
#define GREGORIAN_FACET_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/date_formatting_locales.hpp> // sets BOOST_DATE_TIME_NO_LOCALE
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/io/ios_state.hpp>

//This file is basically commented out if locales are not supported
#ifndef BOOST_DATE_TIME_NO_LOCALE

#include <string>
#include <memory>
#include <locale>
#include <iostream>
#include <exception>

namespace boost {
namespace gregorian {
  
  //! Configuration of the output facet template
  struct BOOST_SYMBOL_VISIBLE greg_facet_config
  {
    typedef boost::gregorian::greg_month month_type;
    typedef boost::date_time::special_values special_value_enum;
    typedef boost::gregorian::months_of_year month_enum;
    typedef boost::date_time::weekdays weekday_enum;
  };

#if defined(USE_DATE_TIME_PRE_1_33_FACET_IO)
  //! Create the base facet type for gregorian::date
  typedef boost::date_time::date_names_put<greg_facet_config> greg_base_facet;

  //! ostream operator for gregorian::date
  /*! Uses the date facet to determine various output parameters including:
   *  - string values for the month (eg: Jan, Feb, Mar) (default: English)
   *  - string values for special values (eg: not-a-date-time) (default: English)
   *  - selection of long, short strings, or numerical month representation (default: short string)
   *  - month day year order (default yyyy-mmm-dd)
   */
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const date& d)
  {
    typedef boost::date_time::date_names_put<greg_facet_config, charT> facet_def;
    typedef boost::date_time::ostream_date_formatter<date, facet_def, charT> greg_ostream_formatter;
    greg_ostream_formatter::date_put(d, os);
    return os;
  }

  //! operator<< for gregorian::greg_month typically streaming: Jan, Feb, Mar...
  /*! Uses the date facet to determine output string as well as selection of long or short strings.
   *  Default if no facet is installed is to output a 2 wide numeric value for the month
   *  eg: 01 == Jan, 02 == Feb, ... 12 == Dec.
   */
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const greg_month& m)
  {
    typedef boost::date_time::date_names_put<greg_facet_config, charT> facet_def;
    typedef boost::date_time::ostream_month_formatter<facet_def, charT> greg_month_formatter;
    std::locale locale = os.getloc();
    if (std::has_facet<facet_def>(locale)) {
      const facet_def& f = std::use_facet<facet_def>(locale);
      greg_month_formatter::format_month(m, os, f);

    }
    else { // default to numeric
      boost::io::basic_ios_fill_saver<charT> ifs(os);
      os  << std::setw(2) << std::setfill(os.widen('0')) << m.as_number();
    }

    return os;
  }

  //! operator<< for gregorian::greg_weekday typically streaming: Sun, Mon, Tue, ...
  /*! Uses the date facet to determine output string as well as selection of long or short string.
   *  Default if no facet is installed is to output a 3 char english string for the
   *  day of the week.
   */
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const greg_weekday& wd)
  {
    typedef boost::date_time::date_names_put<greg_facet_config, charT> facet_def;
    typedef boost::date_time::ostream_weekday_formatter<greg_weekday, facet_def, charT> greg_weekday_formatter;
    std::locale locale = os.getloc();
    if (std::has_facet<facet_def>(locale)) {
      const facet_def& f = std::use_facet<facet_def>(locale);
      greg_weekday_formatter::format_weekday(wd, os, f, true);
    }
    else { //default to short English string eg: Sun, Mon, Tue, Wed...
      os  << wd.as_short_string();
    }

    return os;
  }

  //! operator<< for gregorian::date_period typical output: [2002-Jan-01/2002-Jan-31]
  /*! Uses the date facet to determine output string as well as selection of long 
   *  or short string fr dates.
   *  Default if no facet is installed is to output a 3 char english string for the
   *  day of the week.
   */
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const date_period& dp)
  {
    os << '['; //TODO: facet or manipulator for periods?
    os << dp.begin();
    os << '/'; //TODO: facet or manipulator for periods?
    os << dp.last();
    os << ']'; 
    return os;
  }

  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const date_duration& dd)
  {
    //os << dd.days();
    os << dd.get_rep();
    return os;
  }

  //! operator<< for gregorian::partial_date. Output: "Jan 1"
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const partial_date& pd)
  {
    boost::io::basic_ios_fill_saver<charT> ifs(os);
    os << std::setw(2) << std::setfill(os.widen('0')) << pd.day() << ' ' 
       << pd.month().as_short_string() ; 
    return os;
  }

  //! operator<< for gregorian::nth_kday_of_month. Output: "first Mon of Jun"
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, 
             const nth_kday_of_month& nkd)
  {
    os << nkd.nth_week_as_str() << ' ' 
       << nkd.day_of_week() << " of "
       << nkd.month().as_short_string() ; 
    return os;
  }

  //! operator<< for gregorian::first_kday_of_month. Output: "first Mon of Jun"
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, 
             const first_kday_of_month& fkd)
  {
    os << "first " << fkd.day_of_week() << " of " 
       << fkd.month().as_short_string() ; 
    return os;
  }

  //! operator<< for gregorian::last_kday_of_month. Output: "last Mon of Jun"
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, 
             const last_kday_of_month& lkd)
  {
    os << "last " << lkd.day_of_week() << " of " 
       << lkd.month().as_short_string() ; 
    return os;
  }

  //! operator<< for gregorian::first_kday_after. Output: "first Mon after"
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, 
             const first_kday_after& fka)
  {
    os << fka.day_of_week() << " after"; 
    return os;
  }

  //! operator<< for gregorian::first_kday_before. Output: "first Mon before"
  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, 
             const first_kday_before& fkb)
  {
    os << fkb.day_of_week() << " before"; 
    return os;
  }
#endif // USE_DATE_TIME_PRE_1_33_FACET_IO
  /**************** Input Streaming ******************/
  
#if !defined(BOOST_NO_STD_ITERATOR_TRAITS)
  //! operator>> for gregorian::date
  template<class charT>
  inline 
  std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is, date& d)
  {
    std::istream_iterator<std::basic_string<charT>, charT> beg(is), eos;
    d = from_stream(beg, eos);
    return is;
  }
#endif // BOOST_NO_STD_ITERATOR_TRAITS

  //! operator>> for gregorian::date_duration
  template<class charT>
  inline
  std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is, 
                                        date_duration& dd)
  {
    long v;
    is >> v;
    dd = date_duration(v);
    return is;
  }

  //! operator>> for gregorian::date_period
  template<class charT>
  inline
  std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is,
                                        date_period& dp)
  {
    std::basic_string<charT> s;
    is >> s;
    dp = date_time::from_simple_string_type<date>(s);
    return is;
  }

  //! generates a locale with the set of gregorian name-strings of type char*
  BOOST_DATE_TIME_DECL std::locale generate_locale(std::locale& loc, char type);

  //! Returns a pointer to a facet with a default set of names (English)
  /* Necessary in the event an exception is thrown from op>> for 
   * weekday or month. See comments in those functions for more info */
  BOOST_DATE_TIME_DECL boost::date_time::all_date_names_put<greg_facet_config, char>* create_facet_def(char type);

#ifndef BOOST_NO_STD_WSTRING
  //! generates a locale with the set of gregorian name-strings of type wchar_t*
  BOOST_DATE_TIME_DECL std::locale generate_locale(std::locale& loc, wchar_t type);
  //! Returns a pointer to a facet with a default set of names (English)
  /* Necessary in the event an exception is thrown from op>> for 
   * weekday or month. See comments in those functions for more info */
  BOOST_DATE_TIME_DECL boost::date_time::all_date_names_put<greg_facet_config, wchar_t>* create_facet_def(wchar_t type);
#endif // BOOST_NO_STD_WSTRING

  //! operator>> for gregorian::greg_month - throws exception if invalid month given
  template<class charT>
  inline
  std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is,greg_month& m) 
  {
    typedef boost::date_time::all_date_names_put<greg_facet_config, charT> facet_def;

    std::basic_string<charT> s;
    is >> s;
    
    if(!std::has_facet<facet_def>(is.getloc())) {
      std::locale loc = is.getloc();
      charT a = '\0';
      is.imbue(generate_locale(loc, a));
    }

    short num = 0;

    try{
      const facet_def& f = std::use_facet<facet_def>(is.getloc());
      num = date_time::find_match(f.get_short_month_names(), 
                                  f.get_long_month_names(), 
                                  (greg_month::max)(), s); // greg_month spans 1..12, so max returns the array size,
                                                           // which is needed by find_match
    }
    /* bad_cast will be thrown if the desired facet is not accessible
     * so we can generate the facet. This has the drawback of using english
     * names as a default. */
    catch(std::bad_cast&){
      charT a = '\0';
      
#if defined(BOOST_NO_CXX11_SMART_PTR)
      
      std::auto_ptr< const facet_def > f(create_facet_def(a));
      
#else

      std::unique_ptr< const facet_def > f(create_facet_def(a));
      
#endif
      
      num = date_time::find_match(f->get_short_month_names(), 
                                  f->get_long_month_names(), 
                                  (greg_month::max)(), s); // greg_month spans 1..12, so max returns the array size,
                                                           // which is needed by find_match
    }
    
    ++num; // months numbered 1-12
    m = greg_month(num); 

    return is;
  }

  //! operator>> for gregorian::greg_weekday  - throws exception if invalid weekday given
  template<class charT>
  inline
  std::basic_istream<charT>& operator>>(std::basic_istream<charT>& is,greg_weekday& wd) 
  {
    typedef boost::date_time::all_date_names_put<greg_facet_config, charT> facet_def;

    std::basic_string<charT> s;
    is >> s;

    if(!std::has_facet<facet_def>(is.getloc())) {
      std::locale loc = is.getloc();
      charT a = '\0';
      is.imbue(generate_locale(loc, a));
    }

    short num = 0;
    try{
      const facet_def& f = std::use_facet<facet_def>(is.getloc());
      num = date_time::find_match(f.get_short_weekday_names(), 
                                  f.get_long_weekday_names(), 
                                  (greg_weekday::max)() + 1, s); // greg_weekday spans 0..6, so increment is needed
                                                                 // to form the array size which is needed by find_match
    }
    /* bad_cast will be thrown if the desired facet is not accessible
     * so we can generate the facet. This has the drawback of using english
     * names as a default. */
    catch(std::bad_cast&){
      charT a = '\0';
      
#if defined(BOOST_NO_CXX11_SMART_PTR)

      std::auto_ptr< const facet_def > f(create_facet_def(a));
      
#else 

      std::unique_ptr< const facet_def > f(create_facet_def(a));
      
#endif
      
      num = date_time::find_match(f->get_short_weekday_names(), 
                                  f->get_long_weekday_names(), 
                                  (greg_weekday::max)() + 1, s); // greg_weekday spans 0..6, so increment is needed
                                                                 // to form the array size which is needed by find_match
    }
   
    wd = greg_weekday(num); // weekdays numbered 0-6
    return is;
  }

} } //namespace gregorian

#endif

#endif


/* greg_facet.hpp
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
*/