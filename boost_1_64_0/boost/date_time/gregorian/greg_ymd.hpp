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
PZ1SEpshQpo5EUSwi5HRqFyVFsparGdsrLDpcNbBvjnWyTilUwIOH1qRgbBHMOm+6EHaLQIiL376KFSc+E6eKMzlR3pPtqCb0xuIYPAZIg//7WkncDxnAakarmH7Nq/7+0PTiX9FZ9S4G5pxboGqeqkXhBVKcPjtppM+yWFua/2EpX+x8VxRHJc53Jsu5BLKY7GmPGErF2tKNKEGoONpjDOUZakvIXfPkgWMFk+K+qeVcTXo9kocbEc2nRu10iOPtUJ1b3jnRrLQVlBzCKdLIwUXQgzBkvM8JqLa3AcMQKSr96uGiHgQ6i23L25fvUlCYy1sDSCxGv0hvo8TmPnVO3pM6X/9ZJs/g4zN6IFCpPBuL9tWEzduPqvCDY/C7zjEpAWe+D+iHASHb3qeur95VShRjqQX7N4J7lrFonRSIkKbYgYA08XEjurNRnEoIjE6XKlYK9tdxtcHe7n7bHGICMEv2TdyypaH5TtYb65Vxi+Uc7VgslG+piWowrlkmTeC4EDWGU00j1891hqKH0X8Ehm8Qe5Q7D8t2AB6xijmSNWJXW5C7XYsbH4oaA==
*/