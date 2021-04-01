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
+/IEb+G0rlFTQ0lenJAX+xdxHB3LkvWhlptiCAXaH9QOQ39SI3QL/4VIy0vITs6fkp+tqb98q6QcUxspDrP5wvwF+zmHqSQsk/m7PR6RJWrRbCYWzm5u3z8HMlAzHx5Z+8UOCOTNfGsdz4hCZxfm7+w8bQdWv/XzBhr70xRPe9X8zgSYn54L3/ya7LNTRtM6aa8CxT4jnHV13T3/PqQ/zyOlavW4wOTneoJILVSkpAJLifcsTHmbRHaHBLfKu2ypyG3WbdKGXTVHzG7g7CmyEhys2pxo6BKJGBo3Sm3zhxecFEf7cnHXu6F2HsUBpqfBlv0d92EnG6jauBevxCmAik2IE57H9USFsod6g4WhZ+sILeSb6V4jyd6ZSnHztfumJS013qw82Erd6mQcLeqzlXtDOg0lx3tH/wJl1PkWyZmb/xI0Nq3x7KhDdC6K9dxTPjKkwIbcr9EHK9djg3Tyqpdgci4tEiJD0yLG65XKICQRClQqoTXGp7k3co4Rv0DxzoZSe6H81iJ12503eNLaJj/a1UKGWGN2zgt0zpWsDg/KHbanGGFyrlZsIQ==
*/