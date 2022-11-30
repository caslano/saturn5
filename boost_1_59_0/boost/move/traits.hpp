//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_TRAITS_HPP
#define BOOST_MOVE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
#include <boost/move/core.hpp>
#endif
#include <boost/move/detail/meta_utils.hpp>
#include <boost/move/detail/type_traits.hpp>

namespace boost {

//! If this trait yields to true
//! (<i>has_trivial_destructor_after_move &lt;T&gt;::value == true</i>)
//! means that if T is used as argument of a move construction/assignment,
//! there is no need to call T's destructor.
//! This optimization tipically is used to improve containers' performance.
//!
//! By default this trait is true if the type has trivial destructor,
//! every class should specialize this trait if it wants to improve performance
//! when inserted in containers.
template <class T>
struct has_trivial_destructor_after_move
   : ::boost::move_detail::is_trivially_destructible<T>
{};

//! By default this traits returns
//! <pre>boost::is_nothrow_move_constructible<T>::value && boost::is_nothrow_move_assignable<T>::value </pre>.
//! Classes with non-throwing move constructor
//! and assignment can specialize this trait to obtain some performance improvements.
template <class T>
struct has_nothrow_move
{
   static const bool value = boost::move_detail::is_nothrow_move_constructible<T>::value &&
                             boost::move_detail::is_nothrow_move_assignable<T>::value;
};

namespace move_detail {

template <class T>
struct is_nothrow_move_constructible_or_uncopyable
{
   //The standard requires is_nothrow_move_constructible for move_if_noexcept
   //but a user (usually in C++03) might specialize has_nothrow_move which includes it
   static const bool value = is_nothrow_move_constructible<T>::value ||
                             has_nothrow_move<T>::value ||
                            !is_copy_constructible<T>::value;
};

}  //move_detail {
}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_TRAITS_HPP

/* traits.hpp
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
*/