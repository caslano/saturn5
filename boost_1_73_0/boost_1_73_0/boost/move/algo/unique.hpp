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
YEWSUW+CMBSF35vwH25cfHQF3ZZhGrJFWeaDkQlqtrcKl8AGraGdzv36XcFpAqG999xzvgLCorGpNBgwUapc0+MLjwfdZCZgL0nElmGyZINfJvi1LngnvYEYmz02A1NmyESDu+pI3UxaGTBblAboyssKIdXKorKGRruuqDNbB2zojWDouiP3zvU9d/hw75Oiawl+9qOYSVXS9DkmbTckMG14wHK7I/X/DoSSNbbwkOmDqrTMQILCAzYdzKG0BdCRQPBOCiLVdS1V1nqNOe+/LuJkFo37ZBItlgnfVrKim3sjnyah58GnVOD5j36Poi/TtDzDEfQamzI/wum8IHNL6bZAOL1vKKSBLaKCnim0JYt9qyWDXaOtTnUVsFUcLkEqrY61/jYOi57jGAjvCX9kvavwllKpupk6bLKZwpnQYfNpMgfidFgYxWuHJe9RCDOHxbOPsKufPmm3elvNEoeor6mCX1D49df4A1BLAwQKAAAACAAtZ0pSh0yi4mYDAADHBgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzOTBVVAUAAbZIJGDlVeFu2zYQ/k9A73DTGsAuItOSuxZxFWNb7K7umsa11QYbjBmMRMVEZFIQqaRC0nffkZIdo8CeYDIsk3en
*/