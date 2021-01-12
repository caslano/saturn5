#ifndef DATE_TIME_GREG_YMD_HPP__
#define DATE_TIME_GREG_YMD_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include "boost/date_time/year_month_day.hpp"
#include "boost/date_time/special_defs.hpp"
#include "boost/date_time/gregorian/greg_day.hpp"
#include "boost/date_time/gregorian/greg_year.hpp"
#include "boost/date_time/gregorian/greg_month.hpp"

namespace boost {
namespace gregorian {
  
  typedef date_time::year_month_day_base<greg_year, 
                                         greg_month, 
                                         greg_day> greg_year_month_day;
  
  
  
} } //namespace gregorian




#endif
  

/* greg_ymd.hpp
ZXA9nAufh1fCnXAefANeo/ltPvwILoSfiDux9kjeToAH+rRHaQnV8Z4Om8JM6JqrwsACNbdNw9sdsVbr42cCxCPcARvAP8Me8BV4BHwDHgvfgifDt+FIOIp8PAq+i3ws/AucAT+E58BP4IXwC7gIfg2vhd/A5fBbeDv8Ht4Nf4b3wATsfRRG4OMwHf4RZsHXYQ58B+bDD2E9+AUsgD/BxtDN581hA9gaNoNtYXvYHvaDfeBY
*/