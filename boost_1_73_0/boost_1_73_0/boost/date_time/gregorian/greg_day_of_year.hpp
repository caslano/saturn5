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
ecbcP7Faku+aSdt3FIkE6ZA/l42+I4EPCz5GgjgpSJ55y19GiQmaSC3YKkvbdxLx4wV//AB+TsDOE9hP22pMmf2EmD4/rZVcP+ZbDueOYZeg+NmdSFPEiHDaE4fTn9+RLLaLBFGrHeVc35e294JdKR3l7E7LmHv4u7UNiToNYD9jiW52J6LuK2In2y35VL6Lj03RKb+Lj07RKXYQEgrWye/IsY8AOwEYOw0Qv6mzEZ/WfKqzW/G6uRWvCDB2stg=
*/