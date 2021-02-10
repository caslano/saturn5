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
ooe5Txe9ZwerYmYpIPYaiKNozUlGKypMy52iBnvWGlQSWdQ4G5ll/4oo5saT2da2P7Fus3m8iIfxJPFCOzlwZ/xb+H42GXuBKLxWDU7CP38iFiaY6WHhWdGzmwfwjwefHCPfqGp31Eooni1SXPrg74YivSbYqDRAMn0MhO6DQ5hRhQVqx5CifzW2pIcDPMMS3sKvW8MW3HljJt+gVZuJC5aVNPvThdLsb9rGgZ0Mc/7afd4NvOuCfeoPqf/73KJa/zuwALVCzRc9f7Tvy++Co07Yq5XwcaTvnD969vfRCwrmiA8/hNEkfBtNosWFF+Z5qwscHcGxO5+PF8v5FD6Ek+XYm3cltjmO0/gMU3GXbceJVYdu6loqVFc78lvD5fRsivdIY9ep1gmV2CrBT8ZjCCdJjKPo7fw+KeCj8rCE9wq9O3Bun1Pt/xgtZ3dM/gVQSwMECgAAAAgALWdKUkPcGSpYBAAAaQkAADgACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMSU5GT19TSVpFX0RPV05MT0FEX1QuM1VUBQABtkgkYK1UbW/bNhD+rl9x07DNCVQ5TRF0XbNiqu0sQhzJsORmHgwItERF3GhRE6k43tL/viNpz3nr2g+VYVMm757n
*/