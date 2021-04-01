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
eaUBvadHIj+NbUVFT8fFf7qSSe9aEfmqWCM5aZHKNVbc7DSQ/TuEQu2M107DwzFEG8cEJYfgo8tXpG6icZ/VHkGehQ4cQD/QLgHnB3Hz/Z2STth2a6sUeIg2gN75Evvs9Ao5zxWUAUCLA7uA68/+T6Uas3EkAPs53J/ENwHoGP+NTdJiC8D6GK9Tkf9igREHbnnBzeF65E9ckhkeIR6o24eOwzIs3AtgbdklyCYH7rhxCc55ID/zwXFXJG1d+Z68tbSEOfLmlY8ZgLfaBIX1zonHgdntcENZKliVIfAb1uicMUzgcD6Xm4uHJcV2Gn7VHt1uRpZS9hfjTvvX737iqveGeBwRVlFjhVdsYtbGmtbl8U6oZbHUGUuIV2NFuEP1VgRs8sIXfIIa84LEwN+AzNTPUVFbo9b2APJf86eR/dXQFfGJzRHfT9O5xk/FCHKrfBi/akbvS8z1gbhgvLineBWWuz5J8Th0XS5aKgyv7AireXVKRQe5IYQ+9tRz01/AIWGsCjezu7hNrDzh9GKUXwxl5cx2BgVjNW7YbhXWh9tz48wP1TOxTAL65g==
*/