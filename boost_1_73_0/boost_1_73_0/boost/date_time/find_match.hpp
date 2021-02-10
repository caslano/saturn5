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
TIzVGk9SUnMFEitDsSmHB9axBbABvMWKsd/EN/Un7njxAuYmIEUq8zWwdhr8m6EdDDs7x0g5udNwdAO71SRpdY+rCxSLv7fSmEja7pyUElW3syLrshSVnhTMAO2MTd8122mORWhz1aOtmvRTVjTV0oOJytG4hf8SOTwQaexsrFjkJQ7uULFcT2/T00t7PgmNn5fB8z2nUZvO/NAf+5PAuA7DaSNyvtlfphM8LlKj5VQzBX++YJyG2EfysLSvhQP41wB4ZmZF1Sm+vyKoFmyJiTcTeptVSx+JLoiFiYx6A20+2tu2BrsivpN1W8VS4DdjDXuj92O8Jr/x5ufwXb40qDC3nUrgHk5FlbdlODX+M6yUGU0Z7a+2O7HP3YkbLgw7SdqvGtL20NpvFGZOOJ958NWezB1jRpExuM81CifybzZEbDfMDpPa70CrOPduPP/Wi/xmeLVRIVRLgF7gOGBPAh+30/nsuSS6zfYcF2GvfzTABjwfIBO+LV6eGP8DUEsDBAoAAAAIAC1nSlLrWpTSfwQAAJ4JAABBAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9IQVBQWV9FWUVCQUxMU19USU1FT1VUX01TLjNVVAUAAbZIJGCtVVFv2zYQ
*/