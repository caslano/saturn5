//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP
#define BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/container_rebind.hpp>
#include <boost/container/detail/is_container.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class AllocatorOrContainer, class ToType, bool = is_container<AllocatorOrContainer>::value>
struct container_or_allocator_rebind_impl
   : container_rebind<AllocatorOrContainer, ToType>
{};

template<class AllocatorOrContainer, class ToType>
struct container_or_allocator_rebind_impl<AllocatorOrContainer, ToType, false>
   : allocator_traits<AllocatorOrContainer>::template portable_rebind_alloc<ToType>
{};

template<class ToType>
struct container_or_allocator_rebind_impl<void, ToType, false>
   : real_allocator<ToType, void>
{};

template<class AllocatorOrContainer, class ToType>
struct container_or_allocator_rebind
   : container_or_allocator_rebind_impl<AllocatorOrContainer, ToType>
{};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP

/* container_or_allocator_rebind.hpp
siY4ooXsckHEj6Gtc5TW3hIxoPQsW8q/U7Lb3HMQNWUFrp9AkLiwY4qrMZwFq+NovYIzf7n0w9UGoi/gh5s+3kkQzkgbnFAl4FUjUVEWEvi+qTjm98B/aKc73uoYpuvlIgi/RGkSz+ezdB0vIn8Gb8B9/R789tyI+zcX3IrvTPXhnff2rfeSFsxXikxdp+eoeV0IU2zSlKKwyTGE/unceTr29gWQC7RNJVgOqkHMrUuyCaM4CRLnZ15nVZsjHBmQTnXlJ8eGywStP8IemS04LEkQFeniSVzSmGiNoA8t5MFHCzqbJ9NlEK+CKHRiRsQzaASvtZEEdcHgQ/O+o6w4qMMkO8d7Z6ANahWTmrOn3FpJS4XolJUJqiXqwcGD08GCGnt3rVFNFGaipmI72yJ4Mv90NXpzsC1iozgGNV5SihKbimW4x1p38BI1SdwY7IVER9FVwk3+F0xy2836ujFyppPHy2gVTaNFYr/mf/un8WLueHXhdGTacv9xh2tecz0i2ngxMosH8J8Dd7YValKA3eoqEMWrlIYxuMP9gVfM8OARHS4FIvfJIcQoiaauYyX+26LScDihPeqDe/hNZ9iBW2/K5Cey6jKBoVa2Gh/tysMQg1xuk3xCJr8O+jARHkAANJLUUYzc9d3S/+K9
*/