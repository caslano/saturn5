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
vxNbSzP9s5/TX/MH6omk/7JG1xVYF/ezuaamHwJhFkUBH12fL2lFt97bCP0SSB6iSrC1ukbsxWeos/cvGvDZwMfZqeIZ/PmEaEqpZEHGqrXZ3XbRswSYVIVIOTY6dAMxwmHYex1GjSmHvRwdgZor5dMrF88djYm7DTGFk54GC/2i4pbSineA6JeT8lqMVInT5tg5J9csU2Sstf0N9UtDrxlLwunU283GVaVz/QQAj0I+TGUUYuN4JbylMf0vYgKzznnlAJ3hDIZWcY4fY6ygZNw64YvezWuf7aDjofgMUKNWgs+j9akiX0QLpd6dJEOAiFcfQO/VRh1SbkUIamZTDYH+jYTEAnrMYmTo7HNJoF6SmRTauh+eLK2dzuYQc7U1aLgpSctnlbarO9ywN0yFkr2RQ9/yb1B1f1yaHFxUGbw/u+JJeUSzBiUqG62beqsZXzh7WtT0ODgmPPIEIaouFlhKfZFHxi/fhabMBBX/2RuONL13SbuzjyPxglDkdJK0/jUj3+NQIGKiEhxaUNPuyDILLWyj7gdSwqZBUcHqRrQuib5RZ8NTmHG8Wg==
*/