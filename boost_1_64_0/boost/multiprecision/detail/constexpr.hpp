///////////////////////////////////////////////////////////////
//  Copyright 2019 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CONSTEXPR_HPP
#define BOOST_MP_CONSTEXPR_HPP

#include <boost/config.hpp>

namespace boost {

namespace multiprecision {

namespace std_constexpr {

template <class T>
inline BOOST_CXX14_CONSTEXPR void swap(T& a, T& b)
{
   T t(a);
   a = b;
   b = t;
}

template <class InputIterator, class OutputIterator>
inline BOOST_CXX14_CONSTEXPR OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
   while (first != last)
   {
      *result = *first;
      ++first;
      ++result;
   }
   return result;
}

template <class I>
inline BOOST_CXX14_CONSTEXPR bool equal(const I* first, const I* last, const I* other)
{
   while (first != last)
   {
      if (*first != *other)
         return false;
      ++first;
      ++other;
   }
   return true;
}

}

}

} // namespace boost::multiprecision::std_constexpr

#endif

/* constexpr.hpp
bffjSN0xdLYKwi5luHlc5InLaT3zXW2r2nZ9w9OUhNppjB24g6TnUQOrjgQtx4n/XFCt24cQoHcHtvqrV3v8DNcA2h9XSRtaVWF/nnuJnn/fUPBrfVNXjalzfjt7U36Y4432MRib0oU1WR97jpn/+LsLno3izkYrVvdx7XkDT7S/5/gXRGV43cTlnIYVn/bvowUvFVretral/ZvywvmS468aoaJrlOi7hzvBmV3MX0HHozY66iYuj917B0lLjvb676vjgcfPCY9F9n7Q10V/upc6N/G7+DOVcRulgz1HI49xNRl5nHtsvg6qCni0cphDmBBpzMf1MKAnMa9EzTvR8pHJm2Ybi035JiQuRs3AeXXxsXRe8cZ5Fz2rHG/VpRtXSj1kBb+O67qutD+FH0oK7yIov9DVvAmNYDd2N9406/mRnJ6U3odOmao1+RgOst0ZeLyDYqRsG8Hb2PdpfulKEa/r3aRPDatVp11r6pHJm0/AOx2eBSV+s6Nsgh1gfEHKUwUtjPZV368pz08VPG0dJG9sezpPHMoDPegwqSMw2AS14m1Hz2Xw52A/ZYMSB7u7s01MVoPvwWCxpDJVMeqq6bJB3jiGO4kbJ8ezvi20HY8j+MBsJ7yIYdKOpMQK0nPtwu3YFjoPjXGnGKmnZUk1glTZmCT/Z3ABB5EnDTs+2DzYLb6/35DXsVbX3FVNPyKpCbf3dgv9yuk9U1y0Lub6lR44FDnf//zzYu2Qdde0dsRsvWVzXvhTnfvFPYgPow+cey2JHl+6ePHikJcev8lyXGA+Whu58SnF2t4MhLKZcswX+eWfTXm1upUKFntWDZgXXxlRGS8GOOIz6zvnPHvzZvLim+31GYroe65IeQkbTGxqWHg3k7zhQYfaP+6fWRJeWyUvpWAZsAscpMoCZ3+4A+v1Y5Dt8S/ovHZ11VWNYhsbAjT86GB3Xrz9AnryThEWxpRckc1v3AIN2jnkW1tHFbhsvYmuce8nuJqFRplGtrzHgRof7B/sHZzM1982773OSI7Ejxb4RjRN5bnt8UcHJ8fJhxDGM83vI8TjXkb7aVzXRWgCO4anft14ZzD6yxe61Vba8wifwYfz2aba34Jmgvjovczvi7FpUupjK2DyxvUZKIhKqQ1zYObjd+6XVP+9N1obu+R3/WR/f7Y7yaP4qBzTMdVKG2qH7HIU3t0+85dkLgfTtEHrJZuXznHgcL+9nNM7BkovYTvUA48eQuMgyRxzuWmsaFwF2JeJ9QmtI7Q63VY2tWRptiMt5ufLaSvF6oYLGzvZf13BfN+IsIKp/c3p+4RdwNIcm0J1uuKITe87wLc6buwcJT/2eXEmuIvga6ZbC6MtHeIhbdkUPuI/VPBvdBWiFAbxh2Dng6d+M9CsvT14Y1Lw/1zBP/BWmehE1ndgv/T0zRYijnkcflnMW9NWdaPrEX8CzGFDu+Ymc+/XBe8qujZ95iM2e4MXrJyXcWbP/4ruQb6tBfyx49if3JhDzInFiwV85UDreDapwzFTRVNpF1bXQZ4XYD8cqaNmrm5kzeM4Bm9aCnCRKwXaUcpwu8C3sHHoyplT8IelDN5F8IrpEIKIfsSDh3qEXISH20cb8yIewgcK3r6VRjSt7rHjQR6W7Zs7R3tl2z9etl1UpvO2HeW/xL18Y+e49+Ql+G8TvGbCwQJc61GGB3D/GVvr+1ec5bn91zneMS3rtuZdYp+6fUscH+2W73sARDBVbXxjQhww+X47H8b4QYAhcTalb2GRUIRR+st1eAuwT8+PzyTYhumqbZ1rI8WmE1faZjKn5CyXqiF1BFY3bYwuOloHfHwtM80srvOyjrChnl1ST8dC1xrPQ5zUw5eRU8I=
*/