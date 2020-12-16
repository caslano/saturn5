//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_ALGO_UNIQUE_HPP
#define BOOST_MOVE_ALGO_UNIQUE_HPP

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace movelib {

//! <b>Requires</b>: The comparison function shall be an equivalence relation. The type of *first shall satisfy
//! the MoveAssignable requirements
//!
//! <b>Effects</b>: For a nonempty range, eliminates all but the first element from every consecutive group
//!   of equivalent elements referred to by the iterator i in the range [first + 1, last) for which the
//!   following conditions hold: pred(*(i - 1), *i) != false.
//!
//! <b>Returns</b>: The end of the resulting range.
//!
//! <b>Complexity</b>: For nonempty ranges, exactly (last - first) - 1 applications of the corresponding predicate.
template<class ForwardIterator, class BinaryPredicate>
ForwardIterator unique(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
{
    if (first != last) {
      ForwardIterator next(first);
      ++next;
      for (; next != last; ++next, ++first) {
         if (pred(*first, *next)) { //Find first equal element
            while (++next != last)
               if (!pred(*first, *next))
                  *++first = ::boost::move(*next);
            break;
         }
      }
      ++first;
   }
   return first;
}

}  //namespace movelib {
}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif   //#define BOOST_MOVE_ALGO_UNIQUE_HPP

/* unique.hpp
NP6BcdlBMzpJA6uXI22OXcfUWV+oM3VP/ApV0SH+9IZ9oKnNhp3natWwuZn2km5m261qjRT5+eJDVVd8Nkvml9wDLDWUAtn+vpEJIobXWG4NzD6prvuI/MwHrCE47EfG130KWJ+U7+/i9BeJG5pKBebRC4SILNjf9ezf3KEv6Pvnv7tDIxvdodfp+9rf/zdtZn6ZD99nBT/v8q10fr5HD2FTv6HR5cxJ6uYfiW0ac/5NC/YibhN6KP58BnZr/poYg+hytLGTfakbVKrGCMb/AQ3rVpolL5epMxruqvQE438AqznOShoianDotJgPssg65ODQGEvu+OGyJAtrUbx5L7mr+SVV5uQnnvipUmkERUS3u8KjxkAvOofiHL5VKm+xp0Yof5lszi2VxaiSQIs5AVN71JVML95zVEWukimKhzLRGnSOKJ1LasTERklNHTkizTq3LoYsoLk9ooqBVaZZ0A/ykmeu4kCnLo6gbyUKQ//4urREbh4tVGWt/lXr9nC2vaRKi6oqkFJpwUrAY/fYzRA7Ip3uqlSfHSFEarCAo7IZKkqqhu5fv/XfId1W9ioCw9u1V2G+SUtNRDjh77ugY/sWVRce2H7GixMPHP/JeQeOXzCsffsb687vuHx/uODA+Pt3UL7yDsr3x6Htl++ITpTvGx2Ub+6EA8c/O639/P9wXsf5x1X6tvYf20od9jFuZJyzTOaQwm58c6KcRDv6tihf1fJfN0XYnCkirlBCHGtgvI+4NApBHBAdQwlo/ULorEHB1SXpS1w/wdJy0MpAtM+671B2Y6r+e1xiAjcLmps1IZzyiI9oPPOOiURU+gJ2E6VNTgk141K084fVXd99FTehE/SE9n8RbVUXdqsup/oWYZEch9ia915HYuOOPTC5A2YtvC50ZEwLugEVPuspK1fAd4l56G7OfTQDEP5Et0PQH7HlPxHlTwO79CZlsV63Bhj0RFGEgfH+toNkksiF3aQI6BfnIFZ/aqXDg6uLmiO6abAoplhqkgcPukmofGQK1xMyNuBRTKJLM3Rp6/1Ya3lJCaksR0cI2eiE3VQOvZ3EJacAKoeTrUZrgr3JpfJTw1CTsClgnjJ6UUXZnpI/ravlasv/1gfqCIfVmP54RZr0I0vqfSDf4PyX6U3QuIZvwJelodQHSYSSxCQp292yk5R8gZ5uYvBwuIXiuVvts97SN6ejFxthohOBFXA7lpqJ0jRpEFJOxKVGEuyg8CztuG0PBmdABFNH2uQL4TiOuBzZUVNSE5MiSOT5Fcm+O/Oh9kQ2reWB36HbZzxSt/eQ5YMsWGir1IxgxqTOOPpH85kixqPYez8u9X8m6gMTZRc7W5OQ9SCXu+RR3r6Ks7R3GaAAau4mUOHhEzdMZth2YHFC2Q0V2a10ZHeZzi7LWvIV0k/xq+OndsyvXylrk18brkwaWiE8FmN8rbqog/E1nPnfmQ555M5m+tBRmvhTh8B0Lxq2iIn2Rt3TvE8G+fjz2B5pgRl8Y0zcgyrmGNu0/ZVuLQJFkzVwkzVwk633yCZrCCah1qW9O/7RowRKxjKqozIgvP+DPLmiPDoqTrUR4S9zWHjbSYJCISLNSH2MVe7v+byMkCjrz8+nIaEjVY7wRxxIdtFJK/MUQvIIkPwESFYQEmWBOqaRDIBzCwSjV00cKPWMYpnSiv01dDC6ypF7oU54mrFGVY3INkiHZ1NTeIQzhg0EoFB70gDEcY8Vom8gRabY0bYIY5Hqt6MzjWno0b9FsX8vevSPTuEeLSwuySobW2ziGjvoPeozTy9gOIuunSoAXB7ZJWKPlLEnw0Op7awDKjb1JFgv4Vgl2s2jI0qUIzpRFaKrKITx929K6/w=
*/