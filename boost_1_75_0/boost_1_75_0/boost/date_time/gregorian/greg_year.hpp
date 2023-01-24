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
dl67517jVOL6IKXcZfNyritPU+DBuVPvZu8csZkYlkh0C6uVfVR/7E1xuuRLeO+RNa/Rz0Do4yz3jXLwm6vmz3VbqW0cMFFZPs7F+8mI5mm47so5wu8sn6u9X/JBlnUZAbrd2huF1vHPh97wtZZ9MjdOE9QzLCSyUdQO/lWT3RP040yq1W3b+1uPu2PD8Mn1PnwYG1dol2/WMqBIVTzkRVW3InBOrxao0lD/MPOidHVzcVZ/s6X41JytdJUwfiDcfQv4lv5wz/c7nOE+2Kr8bT8E+RiqJ8YxO0e0VTpnelPO83hz1xbuxm2tfI8GJETwEje22cA7dYV6dOfWBrs39YjYVmP0NadPS1cHYj3CQEKn89Npr6bxz7RZWEqaS7qkuh2dW1xkVWnO0q/9rfV3lm11riZ9rljyqhMNxu2yXPQmCZGt4JXBj/vsGprVWmRIP6DfVG947Lgr/BiqXXh9O1C+vbzoj5cX+/H4atXdlfO06sVfahdq1Vs3a65LgKLo6PspScyjo1RsZcI7YPVznwwcqVuu90Pk0Smit8Gmz6XL3Vq+z8lo/th8/iuN/+HrsXwakd6NvKXux8/bEhDe8bHX6zsVO2S+73voQfoaX0DIv+TleDLP0lB4Az2gs7yt/3vIA12PSejxr4f1TqAjsd/Rxj+fZVFbSbeyfm3TMOA+qLie8GMbfse37u3Q9i5i3kfJgN/9mnfH2ifB
*/