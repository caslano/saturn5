#ifndef GREG_YEAR_HPP___
#define GREG_YEAR_HPP___

/* Copyright (c) 2002,2003, 2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/constrained_value.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace gregorian {

  //! Exception type for gregorian year
  struct BOOST_SYMBOL_VISIBLE bad_year : public std::out_of_range
  {
    bad_year() : 
      std::out_of_range(std::string("Year is out of valid range: 1400..9999")) 
    {}
  };
  //! Policy class that declares error handling gregorian year type
  typedef CV::simple_exception_policy<unsigned short, 1400, 9999, bad_year> greg_year_policies;

  //! Generated representation for gregorian year
  typedef CV::constrained_value<greg_year_policies> greg_year_rep;

  //! Represent a year (range 1400 - 9999) 
  /*! This small class allows for simple conversion an integer value into
      a year for the gregorian calendar.  This currently only allows a
      range of 1400 to 9999.  Both ends of the range are a bit arbitrary
      at the moment, but they are the limits of current testing of the 
      library.  As such they may be increased in the future.
  */
  class BOOST_SYMBOL_VISIBLE greg_year : public greg_year_rep {
  public:
    BOOST_CXX14_CONSTEXPR greg_year(value_type year) : greg_year_rep(year) {}
    BOOST_CXX14_CONSTEXPR operator value_type()  const {return value_;}
  };



} } //namespace gregorian



#endif

/* greg_year.hpp
56SUG3378B0Apz8fJ+KC9WJdQ1n8eVwIxI8kXW7o0fvdhVP44yOnwr8CTqBKGLlRXqrnQdu0Td3m7XQ7BDPAugFPwDfGKBdtMB2dP2GKVgXXvitWMo7Yi6bwCMy4UxSl3LYyirMmTmXlpkfnmGkVwMYQ1GDXnY+f8y1cMUC9VW7ZHzRFVKwlraq1ocbSQXO74xvuzVzdSGhS60JDdT1rhT2I083mrYxV6ujc5SBVpZMtuEqoR93XdMKViFThaoBzG2kznXC6K4efiN4Gc54Ok3A2P+XJhgzt68nFB1z42Uo2GOEe8fpaXPUoLKCtzro0ItV5ru8aq7U3T5x/POVaAPWTpFXlfWuDcM8cBwAqTewuT5pt+RS6jmyCRR0MQMI0oApPVl7OEY8AjTRUPljM5uH7afDvRTCbHxBJ5oq0TxSye5nJ4qiFlHHs7Id+Q02H08Op67Y4ci5zBnljER7ILUdh8Lt61vhkP26k3AJgyJOumI9wOHdn0FdA/Rpl8eBBsWDeTykWZI6PiIFmUhxayZQR5DseLnyWRXUhGspFzPXAGi9GI9+5++jxK1CNsbuK4hv+jbvdT+CmqB6RDsxoi42rVgudppBuq+xgxpQ2rqzpNE1bT/6jYoXhu2HQpPXgxWIWTPtvg3FTQWTi
*/