#ifndef DATE_TIME_LOCAL_TIME_CONVERSION_HPP__
#define DATE_TIME_LOCAL_TIME_CONVERSION_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/date_time/posix_time/conversion.hpp"
#include "boost/date_time/c_time.hpp"
#include "boost/date_time/local_time/local_date_time.hpp"

namespace boost {
namespace local_time {

//! Function that creates a tm struct from a local_date_time
inline
std::tm to_tm(const local_date_time& lt) {
  std::tm lt_tm = posix_time::to_tm(lt.local_time());
  if(lt.is_dst()){
    lt_tm.tm_isdst = 1;
  }
  else{
    lt_tm.tm_isdst = 0;
  }
  return lt_tm;
}


}} // namespaces
#endif // DATE_TIME_LOCAL_TIME_CONVERSION_HPP__

/* conversion.hpp
v1H179RcLgGfBhvClbAxdL83hefC1qreTtU7wItgD1U/VNWpB8W+E+AKOFS/n6rfR8DZsFDVx6l6CTwTninyWD0p9+vDvj715GpNr/thOlwDc+F6mA/Xwo5wHewCH4C94IOwj+pTd/ReePKujzsb1J0/qDsb1Z3N6k4VPAg+BrvBTbA3fBz2U3223ld3Dvdx50l1Z6u687S685y684zmv23q3rOwJ/yjuoc+Ox5Zpu508hmP
*/