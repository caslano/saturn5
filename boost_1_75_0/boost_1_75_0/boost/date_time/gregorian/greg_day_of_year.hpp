#ifndef GREG_DAY_OF_YEAR_HPP___
#define GREG_DAY_OF_YEAR_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <boost/date_time/constrained_value.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace gregorian {

  //! Exception type for day of year (1..366)
  struct BOOST_SYMBOL_VISIBLE bad_day_of_year : public std::out_of_range
  {
    bad_day_of_year() : 
      std::out_of_range(std::string("Day of year value is out of range 1..366")) 
    {}
  };

  //! A day of the year range (1..366)
  typedef CV::simple_exception_policy<unsigned short,1,366,bad_day_of_year> greg_day_of_year_policies;

  //! Define a range representation type for the day of the year 1..366
  typedef CV::constrained_value<greg_day_of_year_policies> greg_day_of_year_rep;


} } //namespace gregorian



#endif

/* greg_day_of_year.hpp
5eyZAln8EkQywu8mArE1Pv75Cs9hxFPonJnU6S9/EKUlPzuikc/lkacI3t3Kv9kwV50O1QI4IWhUSGmksX9+7Czu8riwcVTPpAdf+La7peJkKBRrqSmxsTN1NF39hPvh8xnJbg8787+OHNnaJPA/xaBq39adox09ce5LbmTmiYF4XUx6TlbFHjr5mMYNkkk2FrsHXQuc0Q6VkNaUM93M/HZ25rTMOfrlbGSZ2zjrxsDex0Euq7VJ9vew04urjnYk3ZH1SjWA919bct+08nHaxc+6zDShABrzjtOaHHyhNbpZgs/dI5nX519ds5FjCsXwnH9jNG3v5XNCu1kiZ3Qm7ds58S95+ky4HucZCf9useKbqEpGJXVXcD1ZNgUuNXUOj7V7i3/FtdreibqDjbf8HLEPeggaT30XskYf82OtJ43OAjzETuUhbnDLK5kBDsgEklesxY7XK6OnV/QaltXeJPso89vCmx5S2yrRfYmeCvSISr6ggejTARf6GBgoEEoMkRUh30Y6KOykVaeJojT93Ay7JKquOfXIySihWXDQzqTvaYiNQbCo5P2chCUJcWDvYabO3DxI+TJvAgDw4VGZZc6t9jITa+Az7fJjrmesBR7ndczEKdRNjd/Tw2QUauE7IB/tGDUUDh8ERgcakiSES81YM7MBDkTr+cf4jQ5/4I9akdtfjS6NrX9K01dS+A366eCP0CEeYCflgiRD
*/