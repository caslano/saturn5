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