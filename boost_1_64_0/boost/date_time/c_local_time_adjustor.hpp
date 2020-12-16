#ifndef DATE_TIME_C_LOCAL_TIME_ADJUSTOR_HPP__
#define DATE_TIME_C_LOCAL_TIME_ADJUSTOR_HPP__

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

/*! @file c_local_time_adjustor.hpp
  Time adjustment calculations based on machine
*/

#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/c_time.hpp>
#include <boost/numeric/conversion/cast.hpp>

namespace boost {
namespace date_time {

  //! Adjust to / from utc using the C API
  /*! Warning!!! This class assumes that timezone settings of the
   *  machine are correct.  This can be a very dangerous assumption.
   */
  template<class time_type>
  class c_local_adjustor {
  public:
    typedef typename time_type::time_duration_type time_duration_type;
    typedef typename time_type::date_type date_type;
    typedef typename date_type::duration_type date_duration_type;
    //! Convert a utc time to local time
    static time_type utc_to_local(const time_type& t)
    {
      date_type time_t_start_day(1970,1,1);
      time_type time_t_start_time(time_t_start_day,time_duration_type(0,0,0));
      if (t < time_t_start_time) {
        boost::throw_exception(std::out_of_range("Cannot convert dates prior to Jan 1, 1970"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_t_start_time); // should never reach
      }
      date_duration_type dd = t.date() - time_t_start_day;
      time_duration_type td = t.time_of_day();
      uint64_t t2 = static_cast<uint64_t>(dd.days())*86400 +
                    static_cast<uint64_t>(td.hours())*3600 +
                    static_cast<uint64_t>(td.minutes())*60 +
                    td.seconds();
      // detect y2038 issue and throw instead of proceed with bad time
      std::time_t tv = boost::numeric_cast<std::time_t>(t2);
      std::tm tms, *tms_ptr;
      tms_ptr = c_time::localtime(&tv, &tms);
      date_type d(static_cast<unsigned short>(tms_ptr->tm_year + 1900),
                  static_cast<unsigned short>(tms_ptr->tm_mon + 1),
                  static_cast<unsigned short>(tms_ptr->tm_mday));
      time_duration_type td2(tms_ptr->tm_hour,
                             tms_ptr->tm_min,
                             tms_ptr->tm_sec,
                             t.time_of_day().fractional_seconds());
      
      return time_type(d,td2);
    }
  };



} } //namespace date_time



#endif

/* c_local_time_adjustor.hpp
c0jTdPXTQk01PmG/uTgyq6XV3G8uZjlqxWesBeMUn1OH7+SueQf89M83zE1ng554xhL4mNrqyJ4It6iVhU7n6l7VpFmoSVf3js2ChZbQezJWKdKscsU2rigCS+hXsoovnlV8cayC7yLJKkVglfOYVVqfUqzS49P/DKsk5Y87X2f+2PA488fM7Un44zgm2OlPaf5o1gQLbmqTP479MJE/fvmwlT9e+tt34A+LgfnO10QtZCNj/pgtBoCw30XSs6dhd2YwozFGT/QkEd5Q7FokA44i5CBZwcrjpy8TcspQJCQTDMJGWyE22hZ3Fa+Q1+tlpAtSVYeW6h3K64AZ6ceVKGvMpC/LeshFFE+2HorL/s6rIrvk2h2cd8dOuZZKofybX01e/mqPKr/9/Ke3kd+V2WH+YlF/zq8abojhMJdyARWAyT/Yh63Ru3AbHKYW6YXWEwSNoikLOKUQxr56I5oedeEttQazVG3JKxI11Of49clpaqlK5Stx/Ghjs8im/wibxbfHcy/L9nDa2+P3rg7bQ+QPt5F/hjslfqx4OQk/9tuYOj92baN8V3pq+D/3UvL8m1PMH24jf1FGavknvtRGf0ixP3VtC39Vfir+pNj+70UByXKUaKVoDAfscMS+zCZKxte5zg2A5fAsDmBeu7An27199QZbJpBZ/XGBRoOfJSJJqAcJ3cPpRacQs0YXh5g1zliPWWMnZo2detY48gkxa0yKBuKL4+0aZSjKkLIZ0gEC0p/tkP7xBwHJ/Z22SlOfLxfs0D272rNAYPcqz46hRo3dexq7Uxi7RUhfxSPBPNNEEcKLeUCzGNof0wirhN7mj2HiN+/0BMwNUsy0VqciFN5VW+ZGf28j4D4kSyDuQNHsF6Qo5irwoBBSVYkDnfSDV1gGKyxp1IMFMgax5ojH9PBihJ5B2lS0W8TfyY6W/e153R4BKa0cxdzywTq0x9Foj7/o9tiyQbRHjZpTIB3ARCcocv6Yc94jcr5nz3kV5xxlm41QyQAdfSkPb6sg+iMqEK708BQ0Z08Kh9g6W99//tGsrxRnZzLWXz6q6/s3jfVr64U4ey29J6/yLM7cKDK/Z8/8C5E5OsVSZQwYnPF8zrhYZHzfnrGaMw6gjCAPTiPF0Wbtd6RNMvoERIW3q63rp3eIrWvT3l1ovgIu7or1h/KYVUVTE8/KB0GzpeSNSkGoiIc3UstcLFtUccov9iSk3KVTNqIvADIfraYcWYXlqP+LLABveJAQROfEVuvnb7ameJgz5fo/p+v/QvL6WypyiKpIR0i7rUiP/5ZIJ8V3qMKXEDSZs5p57AvmsX6PaOb8q+axPesEjwUxqVVx9mxzA/7R1UnMqv/F4LY/DHCz7ODuY3BDGJLJ694NDm1fffJrrZ02Au8sPXo/q/o35otsoRY7UJnbkA0faqsniWILSxdLs4UXuJIfPoRKHoFKfqAruY1swVpQZ27VL0nAoirm89er2/EV6iUAEwW6OQmSPN/l4iSvky6goSnDdjKS6evBnEbp+VwTa3eKI8/fJ0AOBV7vMF6TBF5ldrx8hFd0EpdxgkAjmGvbwC7G+Z0tJDiJzRl8YiBB8txneD2pyOFTB65ymVSYRdURqqKbWvfnJQlJz/sdvs1iVGSec9tG2OIIBSnGyJ4B2x5WxRcktJykBwEPjpy5NfEgYIQAq0NqTiPhUCDayK/a6JB7QW/SXsyNRwVaFJ95Dm4vAeJT1TkiUI2QikOQm00B0xz8u8LRxuk4tM9PwBQlzBRHPKCZYqNmin6PdHAibuaa/Xsirm17zGlbdKetk5PyTSwUVt+Pmv0JNXtf16zsYTEpZ1DT2Li8FifUhHW80ljVyMaugdI=
*/