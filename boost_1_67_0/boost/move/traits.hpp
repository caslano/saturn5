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