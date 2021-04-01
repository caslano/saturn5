#ifndef _BOOST_DATE_TIME_FIND_MATCH_HPP___
#define _BOOST_DATE_TIME_FIND_MATCH_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <string>

namespace boost {
namespace date_time {


    //! Find index of a string in either of 2 arrays
    /*! find_match searches both arrays for a match to 's'. Both arrays
     * must contain 'size' elements. The index of the match is returned.
     * If no match is found, 'size' is returned.
     * Ex. "Jan" returns 0, "Dec" returns 11, "Tue" returns 2.
     * 'size' can be sent in with: (greg_month::max)() (which 12),
     * (greg_weekday::max)() + 1 (which is 7) or date_time::NumSpecialValues */
    template<class charT>
    short find_match(const charT* const* short_names,
                     const charT* const* long_names,
                     short size,
                     const std::basic_string<charT>& s) {
      for(short i = 0; i < size; ++i){
        if(short_names[i] == s || long_names[i] == s){
          return i;
        }
      }
      return size; // not-found, return a value out of range
    }


} } //namespace date_time


#endif

/* find_match.hpp
DKAJNATw035PAp4n+IithZDgg9Qfrf9YNqfO7EBktCtCHq9QO9pQP+VetU2IwkdCLv6DWoaLgEHrpjFcB6UAm3Cr1Kv6MJUKN+xzK8Buaio5iiKh+NwUHu9H+H934zjmrdvaKD93/lXgO5MwUylQkrzRcmjk3pTX+iYlI/0dJ8VvbrjkDimxS08u9MKtfjUlYw9orwjW3fpmAyheVJTIkqzyIGjvRfATxHKFa4XElvtDgN817rkVJJEG+u/sul2r/8R1zwXpvW8qF7cJgYpPMeTENb0uK26UDdkUL6zyzueD1TSRDH1o1tVeBlhW86HndpfUQswJFzCr/KXfbKlop80O6hmJO0B4ur2IhAr3+rP4uiEFtDzGA6LiS7j6ZzyQzZGxEyeuWOEFdk+AEoX7jeuayaTJoYzYykHb7jqd5x4z18WsEyy8ct4B4VWBzWqeU0co6U8tgO4Ax8b6DXCAOoulSFSH7rJ5Vs7gUbY/j+o22ribTq0lNgbTDdq8MOp3nlJcyoA5EO5zCt4iF+V4eKPmnnOxSFoF6DEs8PQpsKiSgKJHF866hxl5XQ==
*/