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
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
*/