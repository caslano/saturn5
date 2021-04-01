#ifndef POSIX_TIME_SYSTEM_HPP___
#define POSIX_TIME_SYSTEM_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */


#include "boost/date_time/posix_time/posix_time_config.hpp"
#include "boost/date_time/time_system_split.hpp"
#include "boost/date_time/time_system_counted.hpp"
#include "boost/date_time/compiler_config.hpp"


namespace boost {
namespace posix_time { 

#ifdef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG

#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT)) //help bad compilers 
  typedef date_time::split_timedate_system<posix_time_system_config, 1000000000> posix_time_system;
#else
  typedef date_time::split_timedate_system<posix_time_system_config> posix_time_system;
#endif

#else

  typedef date_time::counted_time_rep<millisec_posix_time_system_config> int64_time_rep;
  typedef date_time::counted_time_system<int64_time_rep> posix_time_system;

#endif

} }//namespace posix_time


#endif





























/* posix_time_system.hpp
u80ibXzVUd5xny9I80rRW5VUmFDahhvY1Q/k8EKOYRZpvlfWT9P4DKrD7K1G6IGoG46eYSfdLH4ZPYERu5qMzq8CY8GzfFmGoGukdoNRXL6iEYzRRpQsSvKaXs4CdEDGp25MOgdxS0IklhdxHiPMgojp+YHKD/j5WsiKZSzkWiOHLHcT4a09jUW9QkguwTDPCVNrH25FG8z1thT5ajHI8BVb3zVHN06jSWK+PlOqTXEqcUeqJ320JtSVYFQ1AAPHDy3IzuWSoaTP29+VYfYq3a4QdUw/BUAxI5o5liJK/+0LWfjIMzC6IeCAa8cy2RGEfh54Ikv5NKuIKlGdbcDDdqFGHABQAh4Y/rlBga3ouj7DW9qC5w/5YbxgR8pIyurZUiZwDxzx+MM9RTRJETBu0ziGXZwqbJdo9e0cLyJHGrHklmX3DEWIugvUrJVwcoAQHA/i3F4eDASzqU2+mQZSj6RztETrUmKOr9NYZ2m9KIZAMugWcXeSPdVxFHpqntxH2ZScaSGF9OkvhwsHDacbs+xEMjjAz7bGUKjNiFVs3gvgLsJMhQ4+vPYPcw==
*/