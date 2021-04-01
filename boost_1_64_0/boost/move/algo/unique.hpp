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
b2GtM5NoCf5m1/Fc1hDlK/GjzWGrhvx0r00xd1N/6kX1S/wlLSX8Ikbsh3FX3R5TvnxVlIU5jpw22zPf+CnsSIvYvzIJ4fD52e/ZJtpx3zqzfmMVx5gyuGphK+PPS/MjHfuT9gKDBQRZtisBvsSAhNG8+JUuKDA9xcKpVy0pxmiJy5KT0zqyffGDsLWUQ7XhgElGbNaXeGyyiWI5FS7OpNLOaRGNZpIPRPzBNlGnoGNbw3QNhxVEcVk2Emi6o1vv1Spr2i9drl0+59tL3VY0bXekagodckzuzxS4BoOmaG6tORgfYGwyPAeuoSh9jUT32iZpWg1j6TPf8Bam2wbASwJWwiMgPTvzAWy1+wAtJDF+GuT5yLZ2Q/6ObU7W6Dl8qFMptfpwTZLiR3BVLEhFxz99mC9lgQ2Hsj1WDRbLCSTJfovzIVaxkut2qSZ3O9NzYNrqFhg/pvjV+6MbJYAB1PPL0aLnLW2Eqr4LoBwifqQw/njGHBW6oeEIEVTSgxxckZv0yvRHB5R3rJa/sS/dlNGo/qPob4V7UBW3/U5BlPGjepLNlsF15PkweQ==
*/