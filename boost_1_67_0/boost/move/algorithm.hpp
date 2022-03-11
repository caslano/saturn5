//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_ALGORITHM_HPP
#define BOOST_MOVE_ALGORITHM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/move/iterator.hpp>
#include <boost/move/algo/move.hpp>
#include <boost/core/no_exceptions_support.hpp>

#include <algorithm> //copy, copy_backward
#include <memory>    //uninitialized_copy

namespace boost {

//////////////////////////////////////////////////////////////////////////////
//
//                            uninitialized_copy_or_move
//
//////////////////////////////////////////////////////////////////////////////

namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_move_move_iterator(I f, I l, F r
//                             ,typename ::boost::move_detail::enable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0
)
{
   return ::boost::uninitialized_move(f, l, r);
}
/*
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
F uninitialized_move_move_iterator(I f, I l, F r,
                                   typename ::boost::move_detail::disable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0)
{
   return std::uninitialized_copy(f.base(), l.base(), r);
}
*/
}  //namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_copy_or_move(I f, I l, F r,
                             typename ::boost::move_detail::enable_if< move_detail::is_move_iterator<I> >::type* = 0)
{
   return ::boost::move_detail::uninitialized_move_move_iterator(f, l, r);
}

//////////////////////////////////////////////////////////////////////////////
//
//                            copy_or_move
//
//////////////////////////////////////////////////////////////////////////////

namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F move_move_iterator(I f, I l, F r
//                             ,typename ::boost::move_detail::enable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0
)
{
   return ::boost::move(f, l, r);
}
/*
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
F move_move_iterator(I f, I l, F r,
                                   typename ::boost::move_detail::disable_if< has_move_emulation_enabled<typename I::value_type> >::type* = 0)
{
   return std::copy(f.base(), l.base(), r);
}
*/

}  //namespace move_detail {

template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F copy_or_move(I f, I l, F r,
                             typename ::boost::move_detail::enable_if< move_detail::is_move_iterator<I> >::type* = 0)
{
   return ::boost::move_detail::move_move_iterator(f, l, r);
}

/// @endcond

//! <b>Effects</b>:
//!   \code
//!   for (; first != last; ++result, ++first)
//!      new (static_cast<void*>(&*result))
//!         typename iterator_traits<ForwardIterator>::value_type(*first);
//!   \endcode
//!
//! <b>Returns</b>: result
//!
//! <b>Note</b>: This function is provided because
//!   <i>std::uninitialized_copy</i> from some STL implementations
//!    is not compatible with <i>move_iterator</i>
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F uninitialized_copy_or_move(I f, I l, F r
   /// @cond
   ,typename ::boost::move_detail::disable_if< move_detail::is_move_iterator<I> >::type* = 0
   /// @endcond
   )
{
   return std::uninitialized_copy(f, l, r);
}

//! <b>Effects</b>:
//!   \code
//!   for (; first != last; ++result, ++first)
//!      *result = *first;
//!   \endcode
//!
//! <b>Returns</b>: result
//!
//! <b>Note</b>: This function is provided because
//!   <i>std::uninitialized_copy</i> from some STL implementations
//!    is not compatible with <i>move_iterator</i>
template
<typename I,   // I models InputIterator
typename F>   // F models ForwardIterator
inline F copy_or_move(I f, I l, F r
   /// @cond
   ,typename ::boost::move_detail::disable_if< move_detail::is_move_iterator<I> >::type* = 0
   /// @endcond
   )
{
   return std::copy(f, l, r);
}

}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_ALGORITHM_HPP

/* algorithm.hpp
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
*/