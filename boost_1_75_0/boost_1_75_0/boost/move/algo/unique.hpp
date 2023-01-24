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
SgnFmWnO3McG8cZLHqP+kdey1+22lyF+yE+SMluomawvTQ+cdpWv2sucgcxfHuPtf8zZ/jyMp+PMfWj6bw/2QSnabLc5hkz9Zm7/tNmJeyd+2RpfNa3batts69d7IPPQZsZzrdzs7M6ZWD4C3dkM1InIQ5T2duSgXNiLc4H+5e7NobqKXhPfCQB+B+nKZmJvLan/CAWSNQIWxA/hFxi6P29O78gfYPuXHnRL/UKd+BzZkhkPUW/ZOFC7vUHn0UWPE/9neBA/crYm2ix7IXYWT/mGvQ4pma6Ptsdttof3QOZfH2d8w5rHKd/wyOPpWj7tqOVNovi6sMSNnzJ9BnKBvniH2Db22fG/Axn3Fob/HMP/uYU/V7Djn0D4ktvdZFUxnmcks5m2yWPxLTbcN0Lmf3HcNVso7ilb0ri3OkwmH8wS+4RxbnyfzZ51r0XRqf2jHfcjkPkVx72d4X7Swp3j6Jdbs8RXhYv4XWTi9g7BfdaO+1PI+H7OcKOfU9zSz9O4L9tR3yOIJ4WbMO5A1+7zqp/b8E+BzF0cfzPDf6eF/3uOPn+N9PkON95/9T7vtuN+EjK/5bgPMtxHLdynHX1+lPT59Gv2+WU7bk+3B0W7HX3u73YuyacF6OoBUttr90dDN5fbCd6ZkPkpx9vWTfEu6U7X+Qa3Xc4aI4rvCz34U3xt/PtM/IcA+A2kT7vZmp+TXvNvdtM1/3vrS89g
*/