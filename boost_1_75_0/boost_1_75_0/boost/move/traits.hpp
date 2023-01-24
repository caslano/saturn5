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
ynC/Aejqqf4XgD8tIXpbgqmZYZVuxbhbaCJnrHT9amhku3P9Jq+yfin/dzfXCd8EQNXdhFbNKQPc4im0RMAHYa8X2Dq+wNYSsUClZ7YwJnQX63PSg1VcNz8C6jFivUUTN5vf2QHAHvodWntxNUi1eDvlVwKJPBS4MPQ8YfGg84SzULz5Y4Kjjo/JGGtM+tmYkHLd6fMDOa2HpvzPP3P6PAGA5D+bdakQF6FKMhJsfoyF+eF3zA86/+H1vaTsPADu/2dznIE6kz8u9mcS+zOg9ghFYpU0RRT96TGmtMlD9xKCb5+9Ls9DEs5jXMp1ifWMV37D/s4ZSGI7jqEXcV4I5jmMjZfQWF4/YakHrSbvZgMQWGrOFT4DpS60QlhEdUmjBBAvGD9O+ipF6jYS5v37rO/mcLlRPeWkdS1L+Zn5PADWQ1JY31H8Kds877LN/ObgC7hYKBaLpfVypTJfnqPMkV+VJotlIBVFzPmUm3E+dZF1rjl1HXk3ZN88Ftb9aFj3o8h8/y7XHPUJvZiPfY1JH856gEYAoWxJn9UM2NZJ/5Bzq8gw5G25Dvo1H/rVQMP53tVP8IUUFAI+NQSyfwjqEioODgT6/X2+Xr0tb0zWuBHAMwy/DkYN6tAFfUXs8r5f6kIPQYqPlujf8ek56TzTIntUDj0vsc7lj9/jQbHX4PEWJKwehJ+EMtiGmM0E8PYg0+etd9pMCMs8aDId
*/