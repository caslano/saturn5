//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP
#define BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/container/detail/allocation_type.hpp>

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
typedef int allocation_type;
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
static const allocation_type allocate_new       = boost::container::allocate_new;
static const allocation_type expand_fwd         = boost::container::expand_fwd;
static const allocation_type expand_bwd         = boost::container::expand_bwd;
static const allocation_type shrink_in_place    = boost::container::shrink_in_place;
static const allocation_type try_shrink_in_place= boost::container::try_shrink_in_place;
static const allocation_type nothrow_allocation = boost::container::nothrow_allocation;
static const allocation_type zero_memory        = boost::container::zero_memory;

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif //   #ifndef  BOOST_INTERPROCESS_CONTAINERS_ALLOCATION_TYPE_HPP

/* allocation_type.hpp
TeyB1rOGPx0e4B8cmvPD4tZdBSnM4vXaj+awQG5I/NmDv2Qp5AlkK/zN43k+y4BkQBBlMfiQsr9zFmWBH5KMRczXfgYPQVYI7cXJEw+WqwzOTk7eQwe/zk5U+BivIhj64XrK+LIgHTO+DtI0iCNAyXnKVESTPKmwjufBAr8R15uYwzxIMx5M84whKIScxovsq88ZKUeaJ5KV5DyJUwZfg2wF+Ji+4zyDBWOALCvG2fQJltyPMjZXaWOPwZzNUSCip6360/iRkaRZtYEozoIZIxRSb1LjLZeShPkcLQN+GBJnwFKttO6NAY515f6p2waYDqBPbs2+0QdFd/C3AvqoL4j0iXtj2dA3nd5AN4cO6IMBIJetj1zTcEjWn6Z7A7ZxrdvIYiEXyqtlj3qDSd8cXQtGczgemKilFgDWFckYGnbvBp/oH8yB6X4W6q9Md2Q4joYyYGSBcWuMXHBuSE4D2QcDBqb+YWDAlWWTKH30GZyx0TP1gYq4baPnqiiivEOWnjVyjD8mKA5poK8P9WsCYgvW4qfY2I3uOhbqtXF7zmTg0jaubGsIA8sh5DBxDNShuzpxow0RsqMin4EAbcKtjwSknmtaI2JA1a6tE46RcT0wr41RzyBeSzC4lo2EE6dgUEG3TYeUWhOX5KAA
*/