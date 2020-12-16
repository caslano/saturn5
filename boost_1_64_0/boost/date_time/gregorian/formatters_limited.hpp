#ifndef GREGORIAN_FORMATTERS_LIMITED_HPP___
#define GREGORIAN_FORMATTERS_LIMITED_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/date_formatting_limited.hpp"
#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/date_format_simple.hpp"
#include "boost/date_time/compiler_config.hpp"

namespace boost {
namespace gregorian {

  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date& d) {
    return date_time::date_formatter<date,date_time::simple_format<char> >::date_to_string(d);
  }

  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date_period& d) {
    std::string s("[");
    std::string d1(date_time::date_formatter<date,date_time::simple_format<char> >::date_to_string(d.begin()));
    std::string d2(date_time::date_formatter<date,date_time::simple_format<char> >::date_to_string(d.last()));
    return std::string("[" + d1 + "/" + d2 + "]");
  }

  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date_period& d) {
    std::string s(date_time::date_formatter<date,date_time::iso_format<char> >::date_to_string(d.begin()));
    return s + "/" + date_time::date_formatter<date,date_time::iso_format<char> >::date_to_string(d.last());
  }


  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::string to_iso_extended_string(const date& d) {
    return date_time::date_formatter<date,date_time::iso_extended_format<char> >::date_to_string(d);
  }

  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date& d) {
    return date_time::date_formatter<date,date_time::iso_format<char> >::date_to_string(d);
  }
  
  

  inline std::string to_sql_string(const date& d) 
  {
    date::ymd_type ymd = d.year_month_day();
    std::ostringstream ss;
    ss << ymd.year << "-"
       << std::setw(2) << std::setfill('0') 
       << ymd.month.as_number() //solves problem with gcc 3.1 hanging
       << "-"
       << std::setw(2) << std::setfill('0') 
       << ymd.day;
    return ss.str();
  }


} } //namespace gregorian


#endif


/* formatters_limited.hpp
F09LWd4N7zVj4oD8encEEx9+Dx4yy/uSe/gzN4lT3OYmI5h4Zhs8LWV5X9bGjIkD8psvIJh4UWs8ZJb3da359dzGKW6ruyGYeHErPC1led/QyoyJA/LWrggmPuNuPGSWd8u7+fXczilu27sgmPhrLfG0lOXduqUZEwfkj59HMPGld+Ehs7wfuotfzx0cOdn3HIKJr7gTT0tZ3u3vNGPigPz9swgmvjEWD5nl/XRsXUx8d4IHcpAqw3zkVVVFIfmZO9IT5crs4u1JXvsSye/bXN6e73p7dvJEJfryPCnkPrT3Nd1LLvsBueJ75Mo74cpecmycfBDZQl4VJpLuwK/jyEEwqk7Q3XRbZSk5xhMN/UOh37HH6yOH58m/KZuy4Jeb2Cb5t9zN8r9SRH5Ou6oq2CkJumM/8GfbzlZ5s3f2Jr/u+MBqVrOa1axmNatZzWpWs5rVrGY1q1nNalazmtWsZjWrWc1qVrOa1axmNatZzWpWs5rVrGY1q1nNalazmtWsZjWr1buRlQEeVzlZcSX5pZ1nqrw3HYwv95PfYvfJCwf8rU41l2pflxAVWFNQ3DgkuoVEFyXAwgOfc1v7Qufeyo+9uTtb7dC/fidPpGoQI3bIg4CFB15YxBAdGMZTVWSJgTIOsv4GLltVQfYg/8pjSW1DOuXdYUDOPbDsYjTZWT6erHaApQ/hn3hjYQ2Dqq/Q+UnlKu4og+4XW/Yhn9xFxmVLqiJtR637ewFt9nYZDSjkdRNbyIv8ijRPvHw6GE6StzjRE+3fcrJ5YOXFEVjVcuR98qPcprpiUsQ6p22DTVm11gl6wsO8235weRttYxvs6g2Rqg0O9YZmqg1O9YYo1YYQ9YZo1YYG6g0xqg2h6g2tyAZIKgagYsjN9tbxZtehKY8POXVkxLo95BIkkU/9G+LIQG5KJBvJQEjHj2TREBlGjQsHPX7nK1hGHpaRh2R0aXy5E8CKO3m8gQfy8hPNpcoEuFqc/JjW9h5xZraAjm0HHWRw5BUZmrcneURhWNFjnWGVew08fBrvl0dqHbDr/wPu8ycZ8EP8Absyr6oecOBtGDzkjwwMOXi8M7fK44Uxef3fb5Ek+RJyWt6bvCmBNyeMuT15TQZP3hFhMYm+ith9/hXH5bcF6cutiJH3SvTFk732Bk421yHpVKqr5UrFOMg9KA4vki/ga5rjL9tKDvlw41ByZOBc5SVnquS3nAFSvXrRWX7/b6HoIRO2R5OFUjvlRVq7yLCiyI+rJPLjahv5cY0tdh8UAo+/ityfwOto/zwyRrLxVvhxmxSIN7Atxl/6R/P/9bTyZ5MeEn5g+Veyf9fmQAkJVENYo/Xt+2eqCFxno3CJZMzN5FBVlW3X20rR7iyXZHiVpApV/fZvneBJjii4hIxG3subOzRFShsaeO2LIzsnQh1MsJHU5WNkiD3+Jb83DxwA6ceXy+cORJ/kX6ScbHdcigRbAoeSsAPr2eRBKZ3JbCUbGQl8eCTHRRQU0M880hUY9+njXt92+Z0Cu0RLaeFySYaeVpUN4bOoVWAM5IW8m7w5+PSJcEKZITDSf+ghyVqDi1aNKOPK+PJfyc7w/YGeFuSfxldf20KquvjQgzdKsRW13K1k5W6NOBa4W4GdHGRTYM/C+BT5ORBbhA204OfnS3h+Cjaxd0b6VvrOyPNUSIFFhn+Qf+MGt4Rw8uRf1PmQUkduVHrgRknXyDeqzzVwozYlwI1STpAawQ6vNcEYzgTjCtIZWEB5kOwj32pf+KTCxLy4yr26h0amXg8Xh2kVm56MhZAiN9KOwrxxWXDsznKn8jEfuIovwRYF8cVscCpfSjBZ3lKYEBalvfs9ZPfUMDKgaBuc1AU=
*/