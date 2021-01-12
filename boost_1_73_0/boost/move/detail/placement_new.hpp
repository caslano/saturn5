#ifndef BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
#define BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP
///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

struct boost_move_new_t{};

//avoid including <new>
inline void *operator new(std::size_t, void *p, boost_move_new_t)
{  return p;  }

inline void operator delete(void *, void *, boost_move_new_t)
{}

#endif   //BOOST_MOVE_DETAIL_PLACEMENT_NEW_HPP

/* placement_new.hpp
vI8xWIJJeAin4wf4CH6IS/AoPovH8CX8GLfjP3EffoIn8Th+i59iOX6GlSpTh7AqfomeeAKb4Un0x68wEE9hH/wGh+O3mIzf4Qz8ARdjOf4Nz+JyPI/P40V8HS/hVvwJj+PPeAJ/w6/xaqUbP+tyIk5J3x1y9YOGG4rfGNW99dff3zF+asWzLv+rz7pEs14LaPAXEuuJYqKMUBr/pkQEMZEoJFYSRcRJQtkp+BGhXeRZECwg
*/