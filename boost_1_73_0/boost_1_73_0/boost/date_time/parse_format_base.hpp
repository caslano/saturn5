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
sDBgEY9kBYpnWesOTQVXzRY4LFu2bNKEEtELTYuShaJou1TmjxSR1tZRUlcFhkNaUC+WSLwNdRHzyugbIrooLcuG8mdSdo89BlkgKui5S/CXPdgyJZQNV35wOVsFcOUuFu40WMPsAtzpuvX3wZ+eY20IjFoBvykrrhBFBSIvM8HjR8G/a6dbTnAJ49ViMpsH4aXnnnuLczdw4Rh6RyfwR11QZf/cg14mtpR6OHGOT5zXKKC3kDO1DxXXlGS8sZ4UulxewtT96FlP+N28glKKQhPdEqtSmXSlnFECIpZlWxZ9MR6W6+lsvvSX1g+iiLI65nBGIZsCTN9ZxnskUX6IpE9fYJhiaWRYIf9GYcO1FDEMWySDUxPw3FuOF/488GdTa07AGGwSv9XZJHMCuuVUyKZ0dpXAQqUyadHft9iD1ouZZpaWjmX5CbnrwFwt/MC7WE3HFK5/PCD/mO8HGg3cAxWsNIpvW4+R7USWETbis50UssWhSpzHCOUbuQ2Uoq01g1cq3mXPdD/SaB/sPa+VpggMrlmG3F34E49mRRFb2HldfMPNdo9aZcYQRWJI6g/u+Wq4oqQ7LekX7moSWNPVZGIE88UsmI1nk6XlUu+jxPvT/TifeJZTJBY2WY3HS74PRZFI+GoBblbT1ONK
*/