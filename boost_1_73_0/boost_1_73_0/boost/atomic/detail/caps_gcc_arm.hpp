/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2009 Phil Endecott
 * Copyright (c) 2013 Tim Blechmann
 * ARM Code by Phil Endecott, based on other architectures.
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_arm.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(BOOST_ATOMIC_DETAIL_ARM_HAS_LDREXD_STREXD)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_ARM_HPP_INCLUDED_

/* caps_gcc_arm.hpp
Xrr1PvUvXlc/djqXAUrv8SKqVmMNWkp0ZeSdgmZhWzMvmaAFmEBmOyXXEP7h6uryaHJMNQuqj/xxz/XnUfHfqpfxoNAKsq4Xb4uWiOB6cZkCM0KlXF/aTSy6nhxCTanag20MwmUP+bcBZ8uOchdonL3bHseISN3i7NPFxbuzq5JCe+y93GcPBHvqrgSDFnhe2IHowlpTBZLzocTXz3sx8MVD0in/efLpgtvZFxzLLRKVcFcUbuXWd1xoC7OnqokAzi+JP9joS/7FzxQ2ZSEGsJM1Qg145taQkyOTBHqcCymTimoFBK5/pGTA/98MQ/fvPdgJQ4PxJKJIOunPXV9/gu4Hxa9kWNr5juH0d+Sy+LYnOUZi8d6w6rzsCQWyEkKeXXQw0csKJiQ70rdoyMLvr2cIi1cDySnzfQnOLLwLvvz5PvQdcGwOwlEJRxxJUS8Zvs0VtoXjil/YkOOcBGBnaD2PXfh8Qi0NkZ2U7BXeV3sUFJF9Drq1HMPUMxZWY8DYEf5QduxogHeplUQKyJYSBLm7l3JNaW5yb+rYzRMD2Y6RxIx/k86mzsQebCMxkafea0pJtdjCNI8eUvTjZ0FAATJJ+1HRJ5OPvJE0KksXMCnV1HOiCPrZz2TWddWKP499xqdhrb+ZMt63NUYA
*/