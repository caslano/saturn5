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
hwdB0ZdXVqhyNV7HKsBcTTqqjnlFwDo7BGLqwzGcF2r6J/P1uDPSg9PWsYYyUMerW1HaPjUVvFOr3vHSb6jwCGsmz4k5MDjPLS6cjfN7MJjseuvuWVW6DPnLIEa39n2XUuEChASvnhodw4PNsdCtNTECs1YTD109RxIbWSno5LyW42Pt/K9OPHX9QFzbe+d7gTHghe8J1yBQ1SVbHQy6SU4MwJZ86alCxySPEhwHmg5WaCpTdndTTZZi8P7Ab5C4AVCL9Gizot0gHzoiqVcCMcmtUmwajByI6gZOS+Ai8MEbg5FLglEO/E+pcZ7w0GcyE8L+YSWzuU5l2vyZ6/OzWHoJjPjYQCaY661CwFSMcXvt3cVRXg2rxXQmoya7KquxhCjTr+Ee6MthLnDbB291LPb7+cE2Nv4qTxpoOO9IvvMCKrDethrCHU1m5uIVkq/45wBbz3K5KlL3vwcG3Gyvw0C21ANt3oBABPPASjfISlt/nxnAzkJyfWGWTgQsdjTJzOgXNConXXf2sJIF0ECtlu7jq/a3PLux09w+fG6CmF5MFU5kdVZ8LM5g8Q==
*/