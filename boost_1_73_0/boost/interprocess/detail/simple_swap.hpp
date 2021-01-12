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
uRaCsy76js1Z33xS0VX4yo/ALs1XOXC//+7IsjU3rV62ZKlrAH6ivCpw9TOC73f9rb8E0E0mRUnFBLkBEM0w/EE9ncqpfjI/3o11uaXTuGKWDnQBgRmPp8JnbMNsEiWE/r7MzFVRwKVbSoO1JZwCzRmWWz9bkGOM4STGaT1gzlekwZcfX2Pj3VjTm848PouaBwehwR9+Cc0AUUNBSUFmW7HwOL0+t+7wmfqNHPLjwDyoFl0D
*/