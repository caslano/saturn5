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
ZfXDJxS+bcIRB+2kCAVpJlFKkuqINO0WdgpHULQxYo6ylCxL0WmGPpwg9kfodIpUI9ryCKluEDAj5Bipj2k1Av78n/9PCYL2HPd3doK9vT3iOM6Nl0mSIKWUt2/f/jyLCUAF8auDf5/h/lLuvg4hq3IiTzatG6c6GA6HNJpNw+2EyL0fQgiyLOPW7ohMdderbGlHnToQVBDyjJATI6+dNfuktZGiskyQJJrpDGaxmfROzHYIuMrpICoXublB23hHz/zgd91XjuokCD+vTwzy/B5x8NUOTYH8Ts3xbRVV46UvUeTqBlY1UqH9gzjtEqeXSDKYJbA/VUynKQAlLNrTk1lCPD3mQfFdPrp9ndAaks1YFNzfpTnPhO9RSNNUSym9JakFhPng1c2ZXBKoK3pvwpmRH8qM3s6QdRHfwfDoiKbbZ8+LBJRSMhkfc/sgI1Gt9St0fckNcD43Pw34kobP0ddH9BLx8fqYG+0y47+fJTCNIY6NiKwsxyw5JpZBzfOqAbGaRdpydRLEQqmi8mxOenC/FUnClyCchON7NXxi4Z5n7rm1kzgPhSMAo5lkHDcYThscDLt0xA5PPB4RRVFuG6h6FNI0JY7jkifBqQFRFNXu21FjBKwZ1Htc/F8HsU+ymKSQfOo9AOvUdDweGw9ABQIpuXnzhucBqHMB+gjp7k+ImHNpZwwuyomDHYClxEejtLCTWXM8VhyPBcdT
*/