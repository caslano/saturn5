//  (C) Copyright Jessica Hamilton 2014.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Haiku specific config options:

#define BOOST_PLATFORM "Haiku"

#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_STDINT_H

#ifndef BOOST_DISABLE_THREADS
#  define BOOST_HAS_THREADS
#endif

#define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#define BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_NO_CXX11_VARIADIC_MACROS

//
// thread API's not auto detected:
//
#define BOOST_HAS_SCHED_YIELD
#define BOOST_HAS_GETTIMEOFDAY

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>

/* haiku.hpp
wB6wLjwVZsLhsAE8F2bDGbARnAmbweUwB14G28FrYDK8A7aB98P28FHYAT4Lu8B3YFf4EewBv4U9oZ/2eRKsCXvBDNgb1od9YXN4MmwJ+8MhcAAcBQfCXDgIToVD4Bzo91mLL4dOuq6Co+B6eAbcpOa3wbPgw/Bs+Ec4Fr4Bz4H74HlwPzwffgkvgEfheFiT9jwZpsIpsCEsgK3gNNgVFsEecCYcBK+HF8AbYCHcABfAG+Ea
*/