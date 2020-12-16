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
EtTbhB5a9HJAQjno+9dzYtTfrPH6r4iu/75z7PWPVvU3St9E8Qtl8R5UnJT5IIH1GSe6FZdKaHHQSwGvg4R3amx4Jyh4cZwvXzybQS3YD1C15jnzEgnloOWrZPnNUeV/p8ofTB/E2gOOZUC4oXOW9RB0Wmkq1ZyKDC1P54sSUuRxxi+JNu2fTWBUoY+u58O+Ho3Oh9/PjJoPt0hQ7QgU5sOx05s0H8bK4runNcQav0VT4x+/FAnqWoCy9X+fmFCMojvHc9GUS43+qO/eaH+Mi+6PhRJU7SXcH0dcLqE0cp9i0cXjJIT1w2J4VziTyZZ/pubYX7Duv34jLiyOxolEaRGVoEeLLW8VH5ewYQhWGmghLaPlHcrr4gO+97rmrGidWJ9NOTa4uLutbba78Kllum2v6baNIDXDemwF4vQCjzn04xHaItMskxatxlk3630ZWvdY0D4/nqCd6DTeS6ZsZRUjjzi3im8qlsN8zxsBVmn7rLvtWpTrOYLrWReIUc9i1INHWfLFcVcFWs7Pct6RV1ZlkHFX+VaXo9oeJ5zw8eWs1n/ClNZ2lO86nLDRPVo0BXq61NF6/k5JN67Sj2EsU2Nh+W4BHmRJYzMnAqgcOGHlYPUp7DHMl1+dam0fJcECmjTWNd2A/OpR3FkPzVCGwstpNTHUsQSVubXWOb/g+/RY7z/O5MX4j8kx6dOHF8VPn6ZIUPdPjqRPixWUA9p/k0VTRxj0aVTnRunTbdOj6NPfxzKo54Yzfbpxahz8w8Oy0MuDjPqf79Ro/c9H13+BBLV4ENffZmp89NE4I2WO1WckwaQp6+rWfal1Xdp3YrzPE2LWtxL1PXqGsqG7Zpy2oXt1pAkjv6ZwUUaNVgPKmgmG8SKbqszE6ViUU7Eof6cXZWE+kY5bXfRVMqAhwlD2BFfk+3vR1m+wylhB3hk8ahCXKtFK3CUQDABGCWCkuQzcHqVeghdY7RQ00FunrUAPrsSEVR4pl0Ev44NFRLMyda5psB6+k5POPEbSrted0Ig4LVKX5A55PNUmzyPcQ67WVPDWUwGJilxHRbSTcWl/XODM91ejuSM7X46OnG7vyAQfdeQpTOuhXxouG1i4jL0a4sVAsq7s5SyBdmrwcfqg7QA5eiSo1E5ZBrXFGPYqa6tb/02JFM94lNUrTaUraBwwJU1vigWGj084SaTotQCzvIN+FeRkADjru0KXBf94pFQv1EqF42vWoIhrFBfxcxFkqBVTojT4fh4nlUKdBkYjsNz2ZopNAfYBeBW3yjIIvoAQKkCXLuAu3XoZbxi6S5U0insloaci8Vvklz+4lEm81HaFxeFhJcLi8Mr/bWmSoB/WJmLpUE8/zX6dEPVYCFQ5co23x9L/6xGRa2e/Uy99nphY1CoC1isa5Wnul3dGlzBP07mDnFlaP9Cv6IQfFS5Tb8+V1rxH8jLpUbyMVgSru4ZoQ3fFz+jokUMlXRjSGB93glr3Xl63y9GeiuOCa05VWtr2p0G4ZwGycOWq3KlrW2X7TpHANnLnVApgo+fxF6QdgeODJ+eopafshvATrUShrqgM0N18vPBTll+dyJyQpcY8mJixoCcn0l/U6JrjUW7C8ZL/kavUp1ZpcXBuX0m0zVU6uodapa15dX2VK/0+hoZicf6VF2ffqXpx/k0vzrbD1JJ8NldxXfv6/1IeOTXhLyY/1vsUZh+ScmPyY2PPaaL84NWTGd7e7Jjwks6Jn7+rkqCmHNkQef4/Ox75wUmy/CXZkeUv0uWjz1+x/I07T1YMyxdFimHh+wGx3ORHqfooVx8l6qMIH2AGsDuBWbGUccdOwZw7DnPuIz3n7sqjPfbIhAhGyBf1IBLrU5A5BF4=
*/