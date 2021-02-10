#ifndef DATE_TIME_GREGORIAN_CALENDAR_HPP__
#define DATE_TIME_GREGORIAN_CALENDAR_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>

namespace boost {
namespace date_time {


  //! An implementation of the Gregorian calendar
  /*! This is a parameterized implementation of a proleptic Gregorian Calendar that
      can be used in the creation of date systems or just to perform calculations.
      All the methods of this class are static functions, so the intent is to
      never create instances of this class.
    @tparam ymd_type_ Struct type representing the year, month, day.  The ymd_type must
           define a of types for the year, month, and day.  These types need to be
           arithmetic types.
    @tparam date_int_type_ Underlying type for the date count.  Must be an arithmetic type.
  */
  template<typename ymd_type_, typename date_int_type_>
  class BOOST_SYMBOL_VISIBLE gregorian_calendar_base {
  public:
    //! define a type a date split into components
    typedef ymd_type_  ymd_type;
    //! define a type for representing months
    typedef typename ymd_type::month_type  month_type;
    //! define a type for representing days
    typedef typename ymd_type::day_type  day_type;
    //! Type to hold a stand alone year value (eg: 2002)
    typedef typename ymd_type::year_type  year_type;
    //! Define the integer type to use for internal calculations
    typedef date_int_type_ date_int_type;


    static BOOST_CXX14_CONSTEXPR unsigned short day_of_week(const ymd_type& ymd);
    static BOOST_CXX14_CONSTEXPR int week_number(const ymd_type&ymd);
    static BOOST_CXX14_CONSTEXPR date_int_type day_number(const ymd_type& ymd);
    static BOOST_CXX14_CONSTEXPR date_int_type julian_day_number(const ymd_type& ymd);
    static BOOST_CXX14_CONSTEXPR date_int_type modjulian_day_number(const ymd_type& ymd);
    static BOOST_CXX14_CONSTEXPR ymd_type from_day_number(date_int_type);
    static BOOST_CXX14_CONSTEXPR ymd_type from_julian_day_number(date_int_type);
    static BOOST_CXX14_CONSTEXPR ymd_type from_modjulian_day_number(date_int_type);
    static BOOST_CXX14_CONSTEXPR bool is_leap_year(year_type);
    static BOOST_CXX14_CONSTEXPR unsigned short end_of_month_day(year_type y, month_type m);
    static BOOST_CXX14_CONSTEXPR ymd_type epoch();
    static BOOST_CXX14_CONSTEXPR unsigned short days_in_week();

  };



} } //namespace

#include "boost/date_time/gregorian_calendar.ipp"




#endif



/* gregorian_calendar.hpp
wXA4i+fRXUiU47sZnEHnBG5wRTo/eduBjuArKwT42T+/9Ps0Yd9iZHobazR2y+lP6tLkYHYLo+Au9F72sjyGHFkK2li1Zjb+8uHCDXJWllvALa6YENqBzhaj8WQWzbyfuExEnSJcWRaNQvP3nnOYKJr/ltyB/QJHOWlHkIReJNYFoeQaDC9Q1ebwnXN/Hc4G02gyj8Yj73aPndUDCYCJtapoR60QqYCYMViUxskzUVLaNknDlTI5RJOHN07JNLjwWJra/Se128jTmoljykjyBXKlDUmJ1JFhVXGiZNeTPCvdpGuZRS3JZTbxCi6osJCcpdqHqNG0s2g9QMKkVAZWuGPUVMWGWLtuQ7QtnjWUHtst4lbgTTQ21IJRismqRX/zLzpBUNuhjKBouowj6n2FYuNHQIrOtQDb5LTDURIb9/ROnYMKwLMAFZNrtNWp6/WazMiAvma1gAcm6jZhe0lo2il1B8IAt01euNum6c0ALs7Pz0GzrYZO5LxNw8H47i4cXYfXDYPvg9aWdMkSTL2T8/7x6XkfqGcw12JtREwwmSDkdUEqyFhiVEWf14xL2iaJZqOqL6QolvodaAvJo1uF0ogtNfyM1aLRyWnfQvtww2nL1aOTyCCvVOE0vW9g158161t93gT3w7mrgvg2
*/