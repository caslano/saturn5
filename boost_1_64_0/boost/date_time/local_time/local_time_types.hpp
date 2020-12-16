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
3fzoXK/a2qZlCAB98aae/yfv7M6fTMkFu8Vu1avJhY5V692m0BKU+v/EVylmySaLk6GY1pbSG1LmyO6pj1JiG1+4hOMP5/gMa9Y93GtJ24jLnlmkRJAWbY5Ut7ZcLKRw/5QiFfBFiq/1BaEliykPRykx64T2ysG0r9zoh3ZxuiL1p4tZrxuU7E9I5HsGFlL6vmYWF9wL+SfMRLQi8uuFg98aC03L/wtuAfb/8ez/VlP/d7vt/9pNWF1RqDqZ1t2lY9mMIO+dkXMVs6/bpi57la3L76XY1oMaeFpfevbA7oZv3mFW767m6056EPN5dEoSeMcS6XElZl+OSdiYMRzTaGO2d4h7V2Ke5pgWG/Mox2RszIYO7x73p6Pc8BrucY/PA0+cORRNQXcPI1wDo1SP2+hM6JEeN+Psbn5zGbARvupa6VWxNxSwvLXg51lYI2AlPW5C97hE65drqMfd35Y6Uqh985u2yDlLQ05ujbR1dtBC1148GVQV+aQheUQgahw9F9wbFJm/f4dra25QxwqoRydo14XE5VjxDsjgdMsC3tXPuqAePJstBxWwF1bFnygerUYTX7ychrwL3zITlFW2rryYsQ6qKJUHpfjqilJ5+ApcD3m4xW+SAwaPRwbFP3Qhx+cjHvJI+x8v8nyTU3P1zCCq82eI+ZVcfky4nRTZuc6uv4GBs8DyMIAblUQTJO07OW1CCXKapN0Drs/Ua6apfTgslfjr29xKTIZF3V4w6HR7j6AUTATfvXJ4T9thVqebnA/ey5TvCGu2PMG6XfKPK09OCgr9C136yy39RSaiP284LCcOVUsxWuK883bMF69hWh/hhQ8Ty+T+eD2Zdy3WjeKUiXmI9aXbGBiGWN9jqwR6CunDgvTrEFNgpszhC9JV3m23opMwza4wE7Dqz6hvE2G+jiPGh2K9nyFRgZwlTHj0CQl6bmXg8UhGjsMePWJNiIYgAai9JluMp8iwnOcfoKuGqwhSgkO+Qor/Nq2HmBp0CaGngqaAXjRMVW4+cQsleovC//hqcQ0D/yruGhj/IBc/Vt8NGipV/sucaj5OEp8xcFPZBxTSih/YeYjB8rikDIfUgVi1SPQf1LTlAylUD6H9eB2j4bZ/m+9mF3ixAJ8FGxkitMiIFbgoT16czNJ4PNt3+ys0AMjyeDyjTXfGCd0id61Yfb2zncfjwJbxuE4z8Yd2PA5ymIosu1LG48dw5lRnqvCeFcffQcV9PTtu8smPA+t2ufFILjfiofgaGYqD3gnfU51w3QIE3EQjz/WPfO4fcrzp4Qp693U01KTmzq8WResy0QV72cYVd2Hk2x8vvxGrp8VxfvPaHMK/e2Bv2x1ltjupXSqxBUnakIbEcd5o4k6kZ+UCR+bG99LGp2kb6SF3skRygdWaUopxoVjrTbHRULS7VzZlEEM4JsedGZb+vHN485FPH9ZwPqXzxTuvpaKXMeh5xunlWViSmVTHjMX9rZMGwjm8boKkt3Xap8hHF+/1+76J59PfB1wrW1X2vIG3quDifPs67Chy6WAQJ0OBirPd2yBdL+FofI1aGEdOLnFvRZw9Dd6Hk9APdVjvwwNmMGbEndiAl0yshybrbPqmulsSVYK1j0+age3wH372vOr1g9dQ/rojquvKdswImkdX+AEoJ7iedaDvlogcMjZ61dLaSj02NJ3wPn3ngKZ3RspresvOetmi9bK5RC/BDziilxR2N5IOFtvsB3KfltiwYxTWzgYu0gdrrG3RnsLzcdaZWctOQow/VBS9LFJJYlPa4kYFpMcXKHtT7RLyVMreVGBN5SJcbN6ZgIvIyogmOxVVm0Uus/W5ymW5SGjKBnk8SD2LAYPSTU9jmB8=
*/