//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_STD_FWD_HPP
#define BOOST_CONTAINER_DETAIL_STD_FWD_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//////////////////////////////////////////////////////////////////////////////
//                        Standard predeclarations
//////////////////////////////////////////////////////////////////////////////

#include <boost/move/detail/std_ns_begin.hpp>
BOOST_MOVE_STD_NS_BEG

template<class T>
class allocator;

template<class T>
struct less;

template<class T>
struct equal_to;

template<class T1, class T2>
struct pair;

template<class T>
struct char_traits;

struct input_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;

template<class Container>
class insert_iterator;

struct allocator_arg_t;

struct piecewise_construct_t;

BOOST_MOVE_STD_NS_END
#include <boost/move/detail/std_ns_end.hpp>

#endif //#ifndef BOOST_CONTAINER_DETAIL_STD_FWD_HPP

/* std_fwd.hpp
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
*/