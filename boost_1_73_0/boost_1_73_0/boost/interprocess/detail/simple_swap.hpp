#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP
#define BOOST_INTERPROCESS_DETAIL_SWAP_HPP
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost { namespace interprocess {

template<class T>
void simple_swap(T&x, T&y)
{  T tmp(x); x = y; y = tmp;  }

}}  //namespace boost{ namespace interprocess {

#endif //#ifndef BOOST_INTERPROCESS_DETAIL_SWAP_HPP

/* simple_swap.hpp
gLMBguyEcEgJbLMaBzdoOLflBg1TmdTyHHePwnUr3AGF6z0+Ize+uXu0E1eHGOugVWseXfEndeQy6ULDxycSjA8tc/Bm8OxI4HdDp+HzCvyhnqybfsIkewPZNwq2/GnHMAxU8R5kMqQOg9TmuyHneRD44bbOMKkBhYROh9aBbC/I9rKraYsoetQ9JU3o6DyKAvA4yHVOoZU/W5MGPCSEP10DN3DbyC0erXB/EJL7rnLWkPU42/JVbkcmMSkDGPU=
*/