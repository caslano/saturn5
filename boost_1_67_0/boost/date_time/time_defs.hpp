#ifndef DATE_TIME_TIME_PRECISION_LIMITS_HPP
#define DATE_TIME_TIME_PRECISION_LIMITS_HPP

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */



/*! \file time_defs.hpp 
  This file contains nice definitions for handling the resoluion of various time
  reprsentations.
*/

namespace boost {
namespace date_time {

  //!Defines some nice types for handling time level resolutions
  enum time_resolutions {
    sec,
    tenth,
    hundreth, // deprecated misspelled version of hundredth
    hundredth = hundreth,
    milli,
    ten_thousandth,
    micro,
    nano,
    NumResolutions
  };

  //! Flags for daylight savings or summer time
  enum dst_flags {not_dst, is_dst, calculate};


} } //namespace date_time



#endif

/* time_defs.hpp
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
*/