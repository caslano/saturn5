#ifndef DATE_CLOCK_DEVICE_HPP___
#define DATE_CLOCK_DEVICE_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/c_time.hpp"


namespace boost {
namespace date_time {

  //! A clock providing day level services based on C time_t capabilities
  /*! This clock uses Posix interfaces as its implementation and hence
   *  uses the timezone settings of the operating system.  Incorrect
   *  user settings will result in incorrect results for the calls
   *  to local_day.
   */
  template<class date_type> 
  class day_clock
  {
  public:
    typedef typename date_type::ymd_type ymd_type;
    //! Get the local day as a date type
    static date_type local_day() 
    {
      return date_type(local_day_ymd());
    }
    //! Get the local day as a ymd_type
    static typename date_type::ymd_type local_day_ymd() 
    {
      ::std::tm result;
      ::std::tm* curr = get_local_time(result);
      return ymd_type(static_cast<unsigned short>(curr->tm_year + 1900),
                      static_cast<unsigned short>(curr->tm_mon + 1),
                      static_cast<unsigned short>(curr->tm_mday));
    }
    //! Get the current day in universal date as a ymd_type
    static typename date_type::ymd_type universal_day_ymd() 
    {
      ::std::tm result;
      ::std::tm* curr = get_universal_time(result);
      return ymd_type(static_cast<unsigned short>(curr->tm_year + 1900),
                      static_cast<unsigned short>(curr->tm_mon + 1),
                      static_cast<unsigned short>(curr->tm_mday));
    }
    //! Get the UTC day as a date type
    static date_type universal_day() 
    {
      return date_type(universal_day_ymd());
    }

  private:
    static ::std::tm* get_local_time(std::tm& result) 
    {
      ::std::time_t t;
      ::std::time(&t);
      return c_time::localtime(&t, &result);
    }
    static ::std::tm* get_universal_time(std::tm& result) 
    {
      ::std::time_t t;
      ::std::time(&t);
      return c_time::gmtime(&t, &result);
    }

  };

} } //namespace date_time


#endif

/* date_clock_device.hpp
LoeLxXC2XEFwCsPZqo135s/GqA2BWRXwm0pxjSgUiKLKBU/uJP+hk+54y48wulhMg/kyOl3Oo1N/OjmfINYxHENn8Ab+rEtS96sOdHKxofbDiXd84r3AA/oWcaZ3keaGGo1v1JTGsOFHmA3PJ84DsdfPqbm0KhKBOjVS7cAoVK3SorxCaZhMJpAiBehoo4WrWTAP/dDxytT5SZRxXicc3hGERpTZe8dmiyWef4usS3fgWYZyyVE130flOg9vhlx+hdX71QIaT8LRwp8v/WDmzBn2izVGBkVLNezZsiMK69RvvNfpvJ0HuijO8CZrppqE4yCkbthDdhSS4TmOlVrDKyoDZaZhw2NG/loWvDW0SuEFLw2zHaApLo8Mjg0piJU0g842w0EmYWuDPDCVoIZxQtudsZXqs82H46euaoq1v7UhbHw/FqnMc7mlElmO81Jixmuu3zqeP7fEYgUNn9H5xXTpjy7Hzp6LRHLiiXpMW+xyjJVxZSHbZls2KmayZmG1K+8K45eAkT04lcpJOK8gE+in4oyWgl1qBWdYdsHKHRWN10R7zZzibya3sDgdDU6OX1PJeLavzcHaEizuYEsZE56yOjeAA90QhgVzjd85blYhsS/3i50F9yotpa2R0c7PvYMiRE4GEPp/T1xY
*/