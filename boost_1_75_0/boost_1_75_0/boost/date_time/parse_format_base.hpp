#ifndef DATE_TIME_PARSE_FORMAT_BASE__
#define DATE_TIME_PARSE_FORMAT_BASE__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

namespace boost {
namespace date_time {

  //! Enum for distinguishing parsing and formatting options
  enum month_format_spec {month_as_integer, month_as_short_string, 
                          month_as_long_string};

  //! Enum for distinguishing the order of Month, Day, & Year.
  /*! Enum for distinguishing the order in which Month, Day, & Year
   * will appear in a date string */
  enum ymd_order_spec {ymd_order_iso,  //order is year-month-day
                       ymd_order_dmy,  //day-month-year
                       ymd_order_us};  //order is month-day-year


} }//namespace date_time

#endif

/* parse_format_base.hpp
e0raZA+hU+/Vq9NH59004fodz8dX54V04itWJ5sKqKAKjFC8dM+PUQpHjXQF0sjfp9Wdj794nrnW8TxNvK/fcZmQ5vAM6ZR4HltnrmU7j73o699YIMTy/ZBOjIBkT4whSWCJzPFMRnP1cXyHVKsQ0CjHjqgH4x7hxTwVlLzJCC+W+lPUI2G39l0zm75D6FP61es7G2uSqkwdgJToS+Tm78fOYbdS9JWgjnmF3PQFCgo52m9c5zTcvjK2Rcli2vDbagggziXmob8DKMmZOeTDTYy5G7fYlkkxIkB3n/r7TTFrTy6Wl47qHVFQsu/EbZ/XaKkKbg8WqL6LWPE67+qnkpI32/mv4YGYxxgANSNKKpXoxrC3GrXZ/6D1cKB/AxheWoDF2z5QbHmMVoe3zq+E3a7arV+LfiLg+S3uVITY0hbnv2Fvpya/vy8/0Z+i8v8wcqxH1phDsd0u5Oa/aX7/SzyyVvJm+QfmB2IhlnJ+qJOHtfafG9ubqQim1H+ryYV20b/N/X7wV/0x9/GwmspF+5Wl1UWMZbZB9ro6jjQB4sp7AIP6/VWbUcuxlNhzsWLOVFmqtx5x77XMSoLPlq3ssLEDo+8s1RmLPxKb7DwMxhL/umePlubYvSULiS297hARQ9Ell+KLjyGroYqEdNoYWCsWtXLRulEzoGMcSjqDTV49AC2Q84twMlq8JSttfABq22VAX883tlbkdwKA
*/