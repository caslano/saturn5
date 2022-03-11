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
#include <boost/core/no_exceptions_support.hpp>

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