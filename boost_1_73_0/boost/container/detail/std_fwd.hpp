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
wm20QmPRdLQGfYRqRFIW2oo+RxdQhSi30Q6NRHeix9B6tBudQhHRbqMh6o2y0Xy0HX2JWsa4jWHoTrQE3RtL3ug7VCGOcDQavYb2o3MovLzbqIf6oOfQJhQY7zZuRY+iLegYerGC29iDfkTxCW4jCfVFd6M/oLfQGRRa0W1koNyKB4ysSrQjeg59iL5FvpXdRmXUAQ1FqZUPGCOqkA/6A3oL7UdhVd1GXdQFpaP70Cq0A51A
*/