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
JxKCiYIl1wtd+b4JtQftBV6Hd7jlXC60LNhVDCzYbxyY1f1xp3gtidUfVkxKtqbf7FE2pjJvtq+Gsga0iBWrfFvNpsqHBNwHmA6bWLHDzVoeoqxbHiNCWAM2rQA+a3Gyvp/JvmaXeIz7Ha/5jmDu4ScJXHeDJxbRQ8qT8mL7kojKYz/xKyGmQ3wEMRLPrqZVBAEqnzrds8PmxJG7Ux7RP/U+XSKt/qZ+/IN1qF6QpwJWiSId+d06Z+PzF1SjcPqD4H1p8nczxh9qsJrvwOnt68HrwfX8uYF/LZArOevmVIqb1+FXAIU1F76/rDj1B59bM9T3o5zynAlanAZTPiD5hwsrgEIfkx6oU3d1A5B0YSzgNyEftMylhWuq2iBhKeUFDkoNafLSE4kxus0TfvD9r9nLuDp2oTiDk7gzbLlMG0D8bF7hspUxCp8rCqoD4ocXjhc3a8bqdtESIdNPmyxAWSDXlHCe1k+iM6deoLxRPqvY3c6CyJdrpRdpH6x2I8rYPlhEjxhcwaikdk4ezEpvUwwcsr9JdRpWQ+5mGn78+fLhkTiLZaH1dAPsBL4Gk4PzvL3+4K4WY2mWf9/QozgRjX5x8cHogL0Ld5j3cCv1w+lBVV53W3bjTpubhrDz/TAvpMlCwMbm65UX/FV6D6ykcyWUXefLHXHBKaG5Ghd3XHsXr/m9qfCXt7xhI42aUF89oa7VvwKCjAN2lGqN
*/