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
hemUFyaEt0kJRNH0C4y0mUafQ2ZobgpVdwXq49xofmqldD3V7ckuTPQv7QRy+/TLcb99+uXYLkzw7S04c8ogWQsgh9MvKFb2rpTlGB0836Q+DqlDuVN3ROqs5lEDdUchdf8g1nu6OHmro1goZ6yWOcju1aWpdQImwnbWC4zCnR41H4JF7YdgyQ8BwvuuO0TJ+/2WYh3a1FgCtDCFqrsC9XEhovkyl9K1VO/AoyEIKWsnkP1DEG9KhI2fXbPNdqRGeQvQdJnjRLwFkIOv19CM2btS+gYxXTJuUh+HeKHcnxphjhisyaLoZhs/Nf6DUI272jyUShGqdRmw8SJ/UnuR/7hT8Sy7urn2WZZ8I7xv2EKUvFvsNWEMLazmZGNlClV3BTeTndL8tVxK11ShfcY3/Us7gex8x1va5gHfkY34hm9vwQ3nG5K1AHLwtSKaMXtXSt9/ROVUjxYxdCh36Kbk22pOQ76nMd//INS/3DR13TJ3+wBMdMcL3b6Tp2mt+0pry91MJUv5D52E6979unXv4vmTFeUg3n0k7QRy+GVVte7sZrUOdZlqFJb9j1IfN8xIiFWbxUMUlMfjhjx0br3zzmvvvJuaK9N7tVemD3hlQnjf1YQo2mcAI2ScWtyvmaD3TKHqrkB9XCdhLj++V0Kqd+DRUgwpayeQ/coUb4aAjZ9ds812pEZ5C9YOGSRrAeTgi3A0Y/aulL5zRpct0jMPBqsodehOBB3/ZVE4VmqArjZUuNcnDrWpHhf3m4g8Nb771xF5UfNk+WHtk+UN8o3wvpUFUXzB7oZIPpeCeHxoCnlwBVzwQtOXq3ANEgZcMnTWd5JpJ5D9t7quW2SEpZ9viyW5RxxvzblzD8lbA7n5q3tQKrcyUQq9k+c3KQnhyqZTCVuFwb8sCqhEeUxlbah/tdck+gD8/ot9ANomhgaNo6VeYBTu/6j5hHxc+wlZ8xOC8L7jAFH86y5rYf0NFe8RpI9NIQ+ugAuOy/pyFX43SAbvwLUxCSlrJ5D9E3LdV3Rg6efbZrkdsZneGpyP1YDkrYEMnuBLPGW3UCq3MlEKvZNPb1ISYv4WPmsAc0XKNU8bZihOwxmKfxDrX201+PsMxa+/VNwklrU3iR9rHoI2tQ9B5/wILPXr6v4dtvz9J9r578x/SFI2ppAHV8AFh259ucoKjyGDd+DaoIOUtRPI9hG49lUfsPTzbbPcjryZ+Bv/yL23BnLjl8agVG5lohR6Jy8I8rIBy6VjCfMcCf+yKMAS5RGW/yBW9BPo0UcA5ZUfgcZxwKp2HICvg7XOd1zcXDnf8Q0/AghvX/5EFPvyFO3858U/JikXppAHV8AFxwh9uQq/oCWDd+DaoIOUtRPI/hG47ntSsPTzbbHkR2Bt8eLfNvfWQOaXh/kRMLdQKrcyUQq9k5d/sHct8HEWRfxeaa8lJUELhFLxagOctOpBi16g6EV7ekgqAVsNChJt1chDD0gwSFta00rDNVCwIChKVYSCPMo7LQWvpdhQeQQQBRU9UfALh1IE24pA3P98M5vJ9bvmi6L4yP1+yd3uzM7M7s7O7s6+WJHby6hlu1ZLoDMnSYlvL7VEvJdaDoOX17PWIS9eiPfXBCqG4afe5UbBxmD5jYKA6o2Cea5VjuUfRMRroyAS+NoomC9xYnBCIYCcKv1hdgKtQ9hzo6BIVxgt0kGNuLIR6dkN6/V/oEvV2ZTtnp6udr/r/2X770V+++9qP8bL8Wu8tlJBgL1+wxtc9E0/jKcf++7hOnIUQFFQgFUytYkwKQ3QPHplWqWNF0IM5WmVh/HyvtoHmDq/Q2Cy8epV/LxfGtfSIFz20CWAUrcWRT/YLHDWLeCVaqXEi1Y=
*/