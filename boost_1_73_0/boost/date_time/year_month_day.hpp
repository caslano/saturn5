#ifndef YearMonthDayBase_HPP__
#define YearMonthDayBase_HPP__

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

  //! Allow rapid creation of ymd triples of different types
  template<typename YearType, typename MonthType, typename DayType>
  struct BOOST_SYMBOL_VISIBLE year_month_day_base {
    BOOST_CXX14_CONSTEXPR
    year_month_day_base(YearType  year,
                        MonthType month,
                        DayType   day);

    YearType year;
    MonthType month;
    DayType day;
    typedef YearType  year_type;
    typedef MonthType month_type;
    typedef DayType   day_type;
  };


  //! A basic constructor
  template<typename YearType, typename MonthType, typename DayType>
  inline BOOST_CXX14_CONSTEXPR
  year_month_day_base<YearType,MonthType,DayType>::year_month_day_base(YearType y, 
                                                                       MonthType m,
                                                                       DayType d) :
    year(y),
    month(m),
    day(d)
  {}

} }//namespace date_time


#endif


/* year_month_day.hpp
h1mPqc0Iv/oFu+Lfh9Rwyd2hsPUTsTcZb0I+WOSzOdvVCD2oIdsiaqlx+9Imi1p7Uauv/i4WtdFxb0ZeKWqN495i3CxqATXLHiCrlqRmKZVWLVJ9PsB9i0PkN9h3Juu6u3Ol6M32uqvhCEXv4JQ83IGIel77gk3383xoXecg8/WuW3ePcNBUzig8u2TqFLXn87g8Ft9GJc/a8z7xEF92Vecn97QSb+xW10fZ9sySq+beSeZ7
*/