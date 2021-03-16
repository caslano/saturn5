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
5W5Q5ou68gUR35U6dF2EEKzyAtcHU7GgYqy91fgXyXVBUepP/l/+zBu3BJX5jzO3bFmanN2wroUv84ytxne8tQ56aAFvO4RiHiiethT4SDgfFPNBMa1KxQJQLADF7CoVL4DiBVDMr1JRAYoKUCyqUrEQFAtB8YpQsPa7jWi/VQePffaAYg8oXhOKvBCSlx1KOlwJI1FZQSWe4ULNrslSn32g3gfq1VzdoHUdEu9KIWG361yqfaJWSdBwT7K7n1A=
*/