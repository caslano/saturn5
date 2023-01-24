//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP
#define BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>

namespace boost {
namespace container {
namespace dtl {

template <typename T>
BOOST_CONTAINER_FORCEINLINE T* addressof(T& obj)
{
   return static_cast<T*>(
      static_cast<void*>(
         const_cast<char*>(
            &reinterpret_cast<const volatile char&>(obj)
   )));
}

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADDRESSOF_HPP

/* addressof.hpp
t9Mu3s1j9MISQr3Mlu2oAq8KV9e2zTcPLCJL7vJRJW8qTylFNAY75P3aZpVOwCuS+yIbxYarducD/oUTj3L9cE3kjty1U63tSz/WTaYWqq7UXSJf9vtg//HbgeyV1toLAuWCStXBomO2+Qr81azyra6Bbk6SDZ217SwPGbjr7YJexz6/FP9DUX3KYBQd0j1LHMCHUWbQoYiHZwXYSo6nsjKMdr4hL4grXkfkGZM37y2uniISOl7Vs1ouVnHNy89cgz70DtuPoNlbvfq14hkDE/Pvu5iaC7I8lW0yXxi1NyvPmmQbuG2vfKPUj1dxQXpXp5MpqS7dR0WMH6BK+zrjcywLHw6ubI3PXxyBJQTGbSpOEaqvaE33BcUfc3v7gWhNCGmdnnqs8slclxNaeb1TXD7teRV/tAMwJDqvKKDw/1qTHn4xanLB6/ZLhS89HYUB0YkhiIOJU71TTm8IPvjaHs3PzMp6jaUJmSjfRo6AcDCj07zzJdZZxM5L6qOcpPTPE824nyPEWx+egC7mLYp+bUJcWNMSt9zcE90JIT8wsiGLlwQ85TbkJF8JhXbDxQ87Tg/PUiADUlVPXV0JRx1W4kKRMv9C5v95IaNAK9lc0G6gZ1CByL746mheu16Gng8W8SJtWvQlspJFFq/ekdwzalVLvmZkA6Q1lE/7F3wtfGvK3zRvzxSLrJmGYqd/d2XEu3h1fLfk6M1N+xz+
*/