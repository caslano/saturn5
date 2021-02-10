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
20punhliW3ugslMNhsO2oF0hsfFj6JqCK2tvG7GP0nfZtvwnI3vMvQDZYFYw8BMIkwGsmRZ6DFdhehpfpHDlL5d+lF5D/A386LrHOwujE+SGwKgK+H2ruMYsFIhNWwtePAv+W1fcm6anMLtYzuNFmp0maZLN0uUcPsDgIyS8tbwewKAWaxo8fJp++jilA/qWcaZ3meaGRoy/yCaNgMkpRP554L1GXU1wjI1RsgY6hDVHngqprE9yHcWLJEy8aVN6b0ST113B4YgCOdJVXz3vTcFL0XCbscUNIv94HvRrO3x3dHQ4em20DPyTOJpffwvRlIzejTybXi4xxMtShvQE3lbIrBoJ9qqMMdSyuYG1MBumb0dfvGkpbAXB34tgGZ4HUerPvSuGNGtuPruNKzkznWMKZ6regY1M3MWTDVO3bktx8lyJDW8MagSEBnIkkmzqnbfmwBvaxQLWO7JDjRAGgQyuCMahxpbihmJskUWwKo8nE+cxqbTRq3IxtSuJfPVYcSe0W4BGGtQM0bo0UWJaJYsup1nieEqJeLQJTxMD1AQUOVwoxTfyzrITqz8JktkyXKRhHHl2usPTNF2gFiqBb4JUsUa3EkUo4dhwYXYj3H9G21qhumCZZJ3gxqs7XAGqWzS4UpiKRwnkuAaN
*/