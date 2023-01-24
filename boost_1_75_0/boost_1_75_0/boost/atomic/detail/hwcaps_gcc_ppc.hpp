/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/hwcaps_gcc_ppc.hpp
 *
 * This header defines hardware capabilities macros for PowerPC
 */

#ifndef BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__POWERPC__) || defined(__PPC__)

#if defined(_ARCH_PWR8)
// Power8 and later architectures have 8 and 16-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LBARX_STBCX
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LHARX_STHCX
#endif

#if defined(__powerpc64__) || defined(__PPC64__)
// Power7 and later architectures in 64-bit mode have 64-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX
#if defined(_ARCH_PWR8)
// Power8 also has 128-bit instructions
#define BOOST_ATOMIC_DETAIL_PPC_HAS_LQARX_STQCX
#endif
#endif

#endif // defined(__POWERPC__) || defined(__PPC__)

#endif // BOOST_ATOMIC_DETAIL_HWCAPS_GCC_PPC_HPP_INCLUDED_

/* hwcaps_gcc_ppc.hpp
e+hi82IQVK1Z6NVnsDMr6YUEvSvmilBmGLXAo2UnRoMp0ceLie8O+i70V6FBTxltraEtQtuny/FSbWyhD8D6pfAkj/KHT3yyfg5+ctGI4YaggQg7sViR7W1s4SrLpwte0nFV9MVSPDWS3D6byy+MuYVLxT/DX22jW1LxehhQnLyVPfMjKDc05tWe6g1Cc9jPTqR39MNYzR6WlwxfyKjjXHsVqiMAhvocOZCyx6kvUB5Uhtapp9vaQ+hJ5bBvGpwhVc4BwRtb+T0DTFHDSPv6nkZnfi7yXZDh68agwrhud5FeHkCmBxujw8blRG5XTMfeibwAXwHL+9fMsiuZpccaebZ0IdstAhl8I83Lxx43R3P8B0SeavIKeTN0x1h6k5M0Ia8K3cJITwjoprOJ+n5a92lR08Xi0+XwDmZg9XHM8gCuwKyoJTr+d4DMwXEk2x7rc6Lz8zXnOBJycBMLLbeMsvpbxv0KFkqAaYH+m28gtF4KnnaEPDnN39AiT9Zobe7KVlco4K3ZW8QNlQ33bEuiYDIb/iNlVbKBtWg1VrM+V7v+p4Mb1YC7vETRu8aVSAlj8s0P/GXKyXpyYcyqogmke7RZtxFuVFX+udrZzdrZfQZ2kauUwHiF6Du+kBhFov0DBa4EhTH8Oe3vPBz7cj5padHxv4Xr5DLIm7UGDuhGRhpop2bplCevLkm16gClwVpN1wQnXxUtkhK1cXcO
*/