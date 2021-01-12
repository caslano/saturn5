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
mICJDTtGHiZ6vzN9qSle8113tvZJnh0oIaq0eXa3fMt2zUm74Nc/qY/sTtE3V8pXcr6uE02fWq5LRbatLbThyzA7EDqnwJ+MIcWdj6V+j9kzjRjy1u8bxI5cu5a0WuRtTQLlzrsfNkIA0xCJiOhYoc0/UHc29pY1nzinXypxRBzyvdK1Q8LiHSN7y+QlB+85Bzk2H7Fij3zDWtQeeca/nltR674Fv7RHf517DvzHDyvq2Cfg
*/