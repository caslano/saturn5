#ifndef LOCAL_TIME_LOCAL_TIME_TYPES_HPP__
#define LOCAL_TIME_LOCAL_TIME_TYPES_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/local_time/local_date_time.hpp"
#include "boost/date_time/period.hpp"
#include "boost/date_time/time_iterator.hpp"
#include "boost/date_time/compiler_config.hpp"
#if defined(BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES)
#include "boost/date_time/local_time/date_duration_operators.hpp"
#endif //BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES
#include "boost/date_time/local_time/custom_time_zone.hpp"

namespace boost {
namespace local_time {

  typedef boost::date_time::period<local_date_time, 
                                   boost::posix_time::time_duration> local_time_period;

  typedef date_time::time_itr<local_date_time> local_time_iterator;

  typedef date_time::second_clock<local_date_time> local_sec_clock; 
  typedef date_time::microsec_clock<local_date_time> local_microsec_clock;
  
  typedef date_time::time_zone_base<posix_time::ptime, char> time_zone;
  typedef date_time::time_zone_base<posix_time::ptime, wchar_t> wtime_zone;

  //! Shared Pointer for custom_time_zone and posix_time_zone objects
  typedef boost::shared_ptr<time_zone> time_zone_ptr;
  typedef boost::shared_ptr<wtime_zone> wtime_zone_ptr;
 
  typedef date_time::time_zone_names_base<char> time_zone_names;
  typedef date_time::time_zone_names_base<wchar_t> wtime_zone_names;

  //bring special enum values into the namespace
  using date_time::special_values;
  using date_time::not_special;
  using date_time::neg_infin;
  using date_time::pos_infin;
  using date_time::not_a_date_time;
  using date_time::max_date_time;
  using date_time::min_date_time;

}} // namespaces

#endif // LOCAL_TIME_LOCAL_TIME_TYPES_HPP__

/* local_time_types.hpp
lqmEBcukzvjAkh3164+UX1bbJp6vhl+WXYx7xOol+QJZnSekOomUrxoKUqtfmykXTl5qIsUi0Gd2m1vFUshzJjCpy2SS4z2B30wAOKAY/d4JUj2qZLQT5DK3ElPp0QFizO2i6/Qw7ZckUt75550yw522GVJkx6taod2JxcZDJe5ZJGlZj9mLJZAgeRdDgQor7nFo3MM84J2TveICQkyNySNP5TTlaoOrvy63jZ0IJDB26PFbXv3mthGardj3XAJXhj9wmQThM9W1w/UuPr781Gj4yPcROCGDXZ5ezqCfknC1vP+lZpKBiBXupp/napLL7/pzFtng4QSNgd9HTvh+eKde1PY2oMeCzHBXyNN/sLqoNIqiSiIM9Vo4JbLLsHazL0PU5JvUq/qQpJTO5X9iZYbso53OVUj99kPciFjxzDQyN8I1XQclJPrXf0SGspSByg60glUUxUUeqH2wQsQV9+W5JngzENWx8nAOFmEHJWuXtFudx/cCq44qkPzviEFOedPEVMsv0+dgQOToCa+Jly4sVOHYmVrJ1b5a+Mi5eOXUgRvaAEmp7d3oBg==
*/