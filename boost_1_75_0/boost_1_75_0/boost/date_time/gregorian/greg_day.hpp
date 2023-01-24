#ifndef GREG_DAY_HPP___
#define GREG_DAY_HPP___

/* Copyright (c) 2002,2003,2020 CrystalClear Software, Inc.
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

  //! Exception type for gregorian day of month (1..31)
  struct BOOST_SYMBOL_VISIBLE bad_day_of_month : public std::out_of_range
  {
    bad_day_of_month() : 
      std::out_of_range(std::string("Day of month value is out of range 1..31")) 
    {}
    //! Allow other classes to throw with unique string for bad day like Feb 29
    bad_day_of_month(const std::string& s) : 
      std::out_of_range(s) 
    {}
  };
  //! Policy class that declares error handling and day of month ranges
  typedef CV::simple_exception_policy<unsigned short, 1, 31, bad_day_of_month> greg_day_policies;

  //! Generated represetation for gregorian day of month
  typedef CV::constrained_value<greg_day_policies> greg_day_rep;

  //! Represent a day of the month (range 1 - 31) 
  /*! This small class allows for simple conversion an integer value into
      a day of the month for a standard gregorian calendar.  The type 
      is automatically range checked so values outside of the range 1-31
      will cause a bad_day_of_month exception
  */
  class BOOST_SYMBOL_VISIBLE greg_day : public greg_day_rep {
  public:
    BOOST_CXX14_CONSTEXPR greg_day(value_type day_of_month) : greg_day_rep(day_of_month) {}
    BOOST_CXX14_CONSTEXPR value_type as_number() const {return value_;}
    BOOST_CXX14_CONSTEXPR operator value_type()  const {return value_;}
  private:
    
  };



} } //namespace gregorian



#endif

/* greg_day.hpp
mZWtodG48VUAauLnKgjbgDJ8aTlv6/naoSflXerB4Sa+Kt8bF/6LOvP13cLyZ7Sf/Wpw8z51Sw+t13vEtj1OspPJvILutnxifC/wJM6nfHAqNELPt3qydY31tkBpX9B9/M07rCfWrRs1xlsqqIbHtLqAf234aKU1wunm7UmVTr0+Ri7C9jHlkl8hxvTWiWI2StW8t67gLhYr891og4n++Gi4RclX8CPex+hQipq+ScDSFMfYzYIIz2Gp6SqeUVmBrhyiPCTvL0jCtNxkUd9Lhd2xhwo3rzoPnxMfG0itHJ1oi5iNNJ+x1bsY9PWDfc3bUadVFnHos6yCQ/Vqxl3tcNqEVIkGvUZ8PfgYi2lgfGKo/l/L6OEG5sWPzACjLe9xv3ggU5+C8N+rk7zlS72yaIiC+COTTEjpJFqNY14GdU28uEfKVwp/fjONm2r9tUxXPKkzLNARNSbGwuTp6+lnG8fBmGR/b66lPy9tCl9pLR57qLd/mnfae1q6djq3mpmpWRPfpla4GiffO2D58zoX7UF77ZKleomyZJTlW/vtrY+V1kRmLAbyGxlNWt5aLS00h7pWxNbQ+12cmHiMcBSn6/M3ZFngbEqtd4TcUUflqK1Bijy8GCzwcCoi5Eihbe042uN5CNsZDOtyDvsGdLoC2zEhwdClpYN+9UNEWrNWSCSddfYCIWXQUhKuW8OEu51+uYOUkUL2pSq+qmjb
*/