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
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
*/