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
e9/t5bgcjr75iu07xgvXjdO8qf+Vifm6Qxx/pu4Pjue4PiHViLZen+NdepLXZ9qxXnGf6w3fx/ET0p0zSP4YsfN5zLdY6Tx7/6N6fdOoi9zQztEuHbx69Ts9pxf7B4dDmohKyYJCI6uVbC6G9Ca1K3/m4vra1fLtkKQhUbj3Aka50qTrzFyJRhLuC5XISsuUhKZU6qRRK3xRFZlcUqYKSUfB/Gzq/zWkq1wleR/npm5J53VbpJSLS0mNTKS67MKsRWOozhAB8VOlDWK2RtWVi/SSjGxK3YdhEKLQNYlLoQqxQjphKDdmrV+PRknbFKhklNaJHiUbKtzclA+qOgOaUtxQvTZkamq1HBLbD6msU5XxFRRhcd2uCqXz4RYWElbpqG5Iy6Low8FVSd2VICns2RqyJa2BXhm+6LrSnO0qr8t7hqC1D5S1TYV0oAV2aQ3ih9RWqWysvSVik6Vn2VL+jS3bYk+proCKBuOQpuGAVkIrPaSP0+gkWEb0cbxYjP3ojIJjGvtnfbz3U38CbShkbUherxupgaIhVa4LJdN7yb9rpztudEJHy8UsmEfxSRTN50EY0UsaHBzS323Fuv5lQINCrXjj6dB9eejuY4G/xVLom1hLw1uMN9SkETA8IX986jlfRD1/TnotE+y9
*/