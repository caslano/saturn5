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
agACA1MRGBgs928hICKYEaGMiGITQBjMBwEjYhY4xkCDUxioCiBQ8BQGiv81DPyDtt1/BXjOyg43gvGGcFjVHc6FtBnkfS5b4EzImUXnlwWtuO0W8u4vbw0E2AtQ878gxq24bCnq5hCx5txvV/fqPEHSNpqrKI385PtkccFSZ4G8bHUt/8nXumLnaX2MokASnhKX3dh0d3KA+deuxeHjVxn3wyZ2JsDjJmvvPC3Hh0vQkbDy5e9kbB7Agrnvc11rPcP+ZjZsipotPy4isXkKg6J/zZKslGtsHdPHS/0mOpRaRD3jZbjLO8wBX+eLEonvrznOdBLrUnPoC5vUyeVnJ3Zsc6S8FO5+2ob2jHu3maXeFm+cwFeaMuZFVK2Bwx2cSztvKuejysr52N1QjPwz5OHJhU8EPT1uAXC0GgTgZZ4AHrYZHyvlsViD/IxzJsfwgY11jzX0/hq3JYiCFAXR8RCKI9l4qhLr23OBgAGuE2Bg/g4MRwui6WUQD+pk3YwVvdQ1d1vno0U7x2gGAMJ8ECgUIsIHRaAZ9Lci9Kj4TwLtn0FYmau+EQVgWU+TaEpPL53goXlFnGrQuavz04LDQRwp4cT4OfdAykreVOjS4btGaVWmAVekEQFd7NCOInqljVXbAhXlyKxab+WrSQoYw/ss4w+uhXQ/cpP1fwMbWa9dE8xsN5IbLS4Um2C3jaPMyXJ10/lEFj2zLxDt
*/