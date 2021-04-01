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
QcQTs869FB52UEZkK1G3Ta4ZEWM+yFfKbDSC9Ac5A5X5zG0bXprLokNBj3E4D9nnPkNa1J+4NOfJArHlrMqOMSqF2BC8BUUJ5jGDfvKAEP+BCDol91K/TckEhcMmBLluBt4ifFnfOFwnm89AGonHeg1vISDczJO6Hj1bt2XC+JCzq0adZzRo6LzgNrPX87XqkZqhpGGbOdaWTeKply5AZxC0R+KOsaA44xn5cP8DTLezzmNS3gfVbZ65Bb3qcqb9LzI0+MBqntoNQWRdt3NWEYeaZI96z2J5pcZ97fttM/8Fyo/MLqBjZe4rhBXc+4JTKUSYfG5AkAfGFfgxCgh9GeVxBYt7HW2jyXomuV5167JuOkXgJ2UsqMLHyf6nXRN9lTymucYEYQAuBZM5w2PRtE3v4JJYbNtKDTJ6PFDha6TqZhGCp1jG3J+KiwvrC66kLG5qU27p3YkDWnr0xmMH+9KawX+9xCsKqEEkvasnn/Si33pMwR3lq5DsTL1IUHx2IKT6kOY4zhGRek7JdREKmUOaLdlNZhneyPlOyuSwsaUOYQJi9M2WKHckeQ==
*/