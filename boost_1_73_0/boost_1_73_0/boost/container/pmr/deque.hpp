//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_DEQUE_HPP
#define BOOST_CONTAINER_PMR_DEQUE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/deque.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using deque = boost::container::deque<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a deque
//! that uses a polymorphic allocator
template<class T>
struct deque_of
{
   typedef boost::container::deque
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_DEQUE_HPP

/* deque.hpp
u3zTnx3f4/aML6iuqZpfU1SRjC8A1SYPXZKRPqwAP5etWlybvLDMV1swKrWgrNJTXlfipeLI1JGjxqSNSxuZWlBXgXqVvpGlv6qb2tKiGm9JAZm3onKyQmfa29jUdJ4UqZwCDwIX6qgk7FfF5ZfEdXNWS5VF5QVIrp5qI8UuWAI1fNO8pafbrris6mRN+LvpFLyQ/iw/G6DAYp6NfshSeaHXF6sOT+u66XO6TQDx6bbxnLFQmq+01lfCy/SrO9I=
*/