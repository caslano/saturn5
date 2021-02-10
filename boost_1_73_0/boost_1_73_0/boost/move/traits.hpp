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
VzzsaWzMlv2sclakVcFi/uGM+RHHvkCJ4xuOkZENsnjEQR1cuBFWgKa6w/p1Ex7QhFvWEhHr/SfmPu5ZFryj2SmJ2i409Ww4gJnJXa4dHPpkxVr0OCuD5PcaWqkQ9tJ2NFnYRQlI7WnWMBmpXyAiaH0CRHJ9hkWJ4zvSxDX1vdAN0GAl6U2oKXKQYbJr9yd1raYGw1nDDeerX/dlleU3K1c9vy8qPgjbcS/h67cf330xRS+8ob1WJJqjT7paSxFXbiA3bD+YLRtwVLAqi12SFVzJZ78HrsniuzTWXA1qJjuRO5aLXEe5TMlN7xFH2R5gHrtoLY5gOwRPB50w8IyoITQd2ZDFbzPWCxnJUk1qyx7KtAChSR96mkzA8ruyBNfvLb6LflB45dQ771MSsN1TAr7lgKV5+Riw6m+eQhawMvuXwklpMF/MhfnnIasCr/9cksVzFPwONuHnmX06lxl6yrm+yDG2cataMo64a4/j5yb5x23/B1BLAwQKAAAACAAtZ0pSWP4fgUICAACuBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzODZVVAUAAbZIJGDlVMFum0AQva/EP4yocrONnUZRQzBqFbuN1aSmNknU3jYwmFXwLmIXJ/x9Zxfbsar+
*/