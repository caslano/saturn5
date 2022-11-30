//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_ALGO_MOVE_HPP
#define BOOST_MOVE_ALGO_MOVE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/iterator_to_raw_pointer.hpp>
#include <boost/move/detail/addressof.hpp>
#include <boost/core/no_exceptions_support.hpp>
#if defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)
#include <algorithm>
#endif

namespace boost {

//////////////////////////////////////////////////////////////////////////////
//
//                               move
//
//////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

   //! <b>Effects</b>: Moves elements in the range [first,last) into the range [result,result + (last -
   //!   first)) starting from first and proceeding to last. For each non-negative integer n < (last-first),
   //!   performs *(result + n) = ::boost::move (*(first + n)).
   //!
   //! <b>Effects</b>: result + (last - first).
   //!
   //! <b>Requires</b>: result shall not be in the range [first,last).
   //!
   //! <b>Complexity</b>: Exactly last - first move assignments.
   template <typename I, // I models InputIterator
            typename O> // O models OutputIterator
   O move(I f, I l, O result)
   {
      while (f != l) {
         *result = ::boost::move(*f);
         ++f; ++result;
      }
      return result;
   }

   //////////////////////////////////////////////////////////////////////////////
   //
   //                               move_backward
   //
   //////////////////////////////////////////////////////////////////////////////

   //! <b>Effects</b>: Moves elements in the range [first,last) into the range
   //!   [result - (last-first),result) starting from last - 1 and proceeding to
   //!   first. For each positive integer n <= (last - first),
   //!   performs *(result - n) = ::boost::move(*(last - n)).
   //!
   //! <b>Requires</b>: result shall not be in the range [first,last).
   //!
   //! <b>Returns</b>: result - (last - first).
   //!
   //! <b>Complexity</b>: Exactly last - first assignments.
   template <typename I, // I models BidirectionalIterator
   typename O> // O models BidirectionalIterator
   O move_backward(I f, I l, O result)
   {
      while (f != l) {
         --l; --result;
         *result = ::boost::move(*l);
      }
      return result;
   }

#else

   using ::std::move_backward;

#endif   //!defined(BOOST_MOVE_USE_STANDARD_LIBRARY_MOVE)

//////////////////////////////////////////////////////////////////////////////
//
//                               uninitialized_move
//
//////////////////////////////////////////////////////////////////////////////

//! <b>Effects</b>:
//!   \code
//!   for (; first != last; ++result, ++first)
//!      new (static_cast<void*>(&*result))
//!         typename iterator_traits<ForwardIterator>::value_type(boost::move(*first));
//!   \endcode
//!
//! <b>Returns</b>: result
template
   <typename I, // I models InputIterator
    typename F> // F models ForwardIterator
F uninitialized_move(I f, I l, F r
   /// @cond
//   ,typename ::boost::move_detail::enable_if<has_move_emulation_enabled<typename boost::movelib::iterator_traits<I>::value_type> >::type* = 0
   /// @endcond
   )
{
   typedef typename boost::movelib::iterator_traits<I>::value_type input_value_type;

   F back = r;
   BOOST_TRY{
      while (f != l) {
         void * const addr = static_cast<void*>(::boost::move_detail::addressof(*r));
         ::new(addr) input_value_type(::boost::move(*f));
         ++f; ++r;
      }
   }
   BOOST_CATCH(...){
      for (; back != r; ++back){
         boost::movelib::iterator_to_raw_pointer(back)->~input_value_type();
      }
      BOOST_RETHROW;
   }
   BOOST_CATCH_END
   return r;
}

/// @cond
/*
template
   <typename I,   // I models InputIterator
    typename F>   // F models ForwardIterator
F uninitialized_move(I f, I l, F r,
   typename ::boost::move_detail::disable_if<has_move_emulation_enabled<typename boost::movelib::iterator_traits<I>::value_type> >::type* = 0)
{
   return std::uninitialized_copy(f, l, r);
}
*/

/// @endcond

}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_ALGO_MOVE_HPP

/* move.hpp
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
*/