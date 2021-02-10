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
GmDsMKIlSlNPNFncB4rC46x+cG/wmkzOz+Hy8mwyOYtjFyEiDLCyBKdgmrS4T1xz3tBIVG0b60ZW1LysejNdb2tkTWYOKnaQIw1b3ILOYJVhed9SgvG0IP5GYgk8Cuzb3IW/jBKHqmVIWx/PnflilszGsyh2LpNkHhs8euoHhD+ZR4GZSXbCGO7/ejR/RC30AGeKyAe0eAL/OPDleKKFz8eSO8LjCR9h4NqRRy3/1DDaRWXHGpCpFFKr/ZXz78P08q/8MPLfhlGY3Dh+ltnDoR3QZsMiSJaLKVz50TJwFhznGZKCbAjS2TvoWXRU7V3TyBbjb5u33bicvpvOrqfpzMwJEsJG15dlHATgR/EMR/7bBXzRMsHFpoluPnzxoyS+Gn+xvAjiWXQV7Ned/wBQSwMECgAAAAgALWdKUqhhiAF8BAAAwgkAADQACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0hTVFNSRUFEREFUQS4zVVQFAAG2SCRgrVXvb9s2EP2uv+LgAasdKHLbFOjaZMUUR1mEOrYhyc0MGBBoibK4yqRAUk6MZf/7jpS8/CySD3WQyKbv3j2+e3fxlj04+GkvxzNw8OIrtb8pvvC5T5pJ8TfN9PMJaXoL7Q8m
*/