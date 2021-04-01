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
+4jToN3HNIW83JPtNIgdqCUztQR01LFPyjWLlf8iTVgg2ccw1a4sWJGc1GgqfZtmqbfUUS8s0q6XnTz6WqKMkDDnfKLlIPvv5+oUirF2mq4oCQnEyn+wau+lW8YLPWoATEjL4Ix/Ci0NdbUmoFM62CfgYKQf0BHzQJzRgta2BJStZPBFfV/PWfEZk7B8MdU4d7O+vFDw9tXRdkFDkmRjCHX/E6YsxG0YLXPQQansZKvr+ewupxcrxsasfH/Wrf/DUCXL3jGxoKUId2hf3cCaoVPnuUgS2F3au5wtxkJvQNvX9jp3dagdri+vu9DkXUys0jAm8wOpUNlNw3IYsqXVrik3IS4DqkKir+0SsawMQuJ4shw5z0HW4GpCUFYQLyrzfREHk07lzyf3m1sRg7SdBpII5bGt7mI+5g/Ez52KZz1+dIcXHat1qeSiy5MUe/mqQTd0ulAB87FuBcXaB0kJT/xfZaklAdO1+DjjJlhvmbr1TmrntGtPPKGAoZ0apWgXvlcBLgFna+DDd6NArPbTCitt3mWs+8oa+VQ/u156NfLgitTPAIUSofNFNw==
*/