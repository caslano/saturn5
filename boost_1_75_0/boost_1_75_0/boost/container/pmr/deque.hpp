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
JZ8u3iEnEEIX1y4iMHOnBptFQbPErBZMM0GoTT1SiXnMrknSUMQJ4HVVFPzLf1RCel/w8e7naKv/tjXpqwQxoLzHgD+P7PDkcQCqOES0zRhJ/RJgU5fh/kdHRyXP0zpbgTmoXQyky//WkgBOA+e1hv/cCYWjtvk/CmJYU8zVpbIMIaUnAhqkylTKO9ePgEeM7h+YvQGsAwClMzuxJGDUglZT0u9FdNoB40mGin1JpCrGMz/jigcecntW/jopoCRni+Kl88jAyuwv2RbqiIsnWdh0ra3FO9FWEpAkiV0ZqDRKCXMiDjWvo6lXBZx0UEHuqipQqzW5OqvJNm/VTjDXJ3+4asDjJbWmBaUgw1MDtA2NVpp2lNDvd3L9v245sNaaOC62DKsQiav1vSpgbjFQyQLuBs7r9tmDbFaXP9fdfU5Rxv9oPoP0M+hKgMDBwQGNZrOS0QzhbDbl7WtToI2UJvovEHZll3tXbZHHboQXRYJ+T7I9kByPzTkDWaZBhHYmOYT3Z5+btU4szyidB5ivd61w64UbhzjVwakctt6SFOCrD65eF2Rkr12ftMREBAbmDLyZYjzVjGeK2UwSJ9CIBAKNlCB89uxzdn/kPdG6ZGV338zPbK9rkRhv6CjaqZ5HMLcoyefsNfX6yc7tl4+wpc3+ycFODUjTjFY3Y7A1IEkKF58vCbg1AAvOAgB4qaZXJchVgNJ7+qNre/pu
*/