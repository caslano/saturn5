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
gz2ZHz1GOg4CM6LToKakLbQnKIBt60VDl/nWV1NX+QTKrNErX4zedG0NFLpSXDyearr43ivz0PuRkZtf5Ukq6tbHQnc6qdvWjVaZbnsXyY9pUGGX+US049/5q7ga1nhxzxdqRHBHa1KTBeQ2+aZBo9XzfiUZv3rO/GK62PDtSGBMqebtzEfuSdC+4y8z3nQJ9JsiiYHZoCBFaWlqXkrx6iSQQLhPftejpC6hxKsUNUvKGWKDyWCNVvuhB6WxXbxJXbcTo8jDF5QLxEanoIkVtzYLQfmOoHk7EUHrcNoHmQ96U7K6JFHBmeWxXSxJXZZihvwZgbTcmdy9pllq6ukz8EFn0dx0Nd3OLdAjdfUkRjRIwJnRSIMXHEsmhr4uUh1eNli21J6lhu0gQi1s5uUytn0vvkUviJvfZE5hc4Hx4dY/iMos9FDJlN/EreeIyiz1vJYpj0yeaMet09hWrfYIesJ4LldhyROa2D1Msb3S0nVT6BQPmL5kOV/KhC5uHW7rFS1aN4o2Xe4p8ob1ucGykycocesTuHWVlxtl1i8CUWNBgk9rDI1tJaTKl6XLl6XKk1Im9lImBHDregBDZbEvsghSoxqKM1vpcXKHVcuUD+HWqWy9skXr1C3qZHvMitf6M2//2B6ciEyZUE+eUCeuwt7sc4Hop03d1LS96w0rdoGl8pSYskfZm4YK3qshScOZcQPXMOSd2uMF9kDp
*/