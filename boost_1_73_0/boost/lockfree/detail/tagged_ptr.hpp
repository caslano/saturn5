//  tagged pointer, for aba prevention
//
//  Copyright (C) 2008, 2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED
#define BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/lockfree/detail/prefix.hpp>

#ifndef BOOST_LOCKFREE_PTR_COMPRESSION
#include <boost/lockfree/detail/tagged_ptr_dcas.hpp>
#else
#include <boost/lockfree/detail/tagged_ptr_ptrcompression.hpp>
#endif

#endif /* BOOST_LOCKFREE_TAGGED_PTR_HPP_INCLUDED */

/* tagged_ptr.hpp
MqA2K+mO6+1oitYWTifxtQUax7bejzlWoB+4T2BC6xyzIIpmQXjALCyajvWde81CIccCuAO/FG4Y3HwDc3tPwv5NU5nwZ6B/PvzAzY3CnvcPShf1deJ+s/AS9/cGJdw1s5jwGryD/iKFUbi1sO8EWBvCblPCdQPXh5v0qtHfT/nHxfmH7bUw8euzerR5Vi8+ntE6HfPaMzB3DqyaiblwIEZrq9ehUrbadotWnyfgtouyQxKb
*/