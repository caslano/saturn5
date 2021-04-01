/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014, 2019 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_msvc_common.hpp
 *
 * This header contains common tools for MSVC implementation of the \c operations template.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// Define compiler barriers
#if defined(__INTEL_COMPILER)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() __memory_barrier()
#elif defined(__clang__)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() __atomic_signal_fence(__ATOMIC_SEQ_CST)
#elif defined(_MSC_VER) && !defined(_WIN32_WCE)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER() _ReadWriteBarrier()
#endif

#ifndef BOOST_ATOMIC_DETAIL_COMPILER_BARRIER
#define BOOST_ATOMIC_DETAIL_COMPILER_BARRIER()
#endif

#endif // BOOST_ATOMIC_DETAIL_OPS_MSVC_COMMON_HPP_INCLUDED_

/* ops_msvc_common.hpp
dmFEmeosYbAY++Ek6Jml4646K7F2q+HkNBDwfBQAcgvbJL6L5Gl+0lI9xJh0ZYxLWR5d2WCgbKZw7zUa9boNYBFXANd/2mi7oZuxaL79hBCzyg0gh5W/Y/nvffWq3XI7I5CG4xyEOv24tLxgi1MrupbwKx14d/8iH4yaR2K90EJea+T0tarq6OiBfuDDurqVbADbw938ZTWx9HLH5QmrFNFE1hBdatKP2CKVWhV5JDCVe8/Ubv7bMTgcDKps3AwoTaXIT2qXOM/Mvk9f9pkG/JFWuZVJbb8P5JaNhuI3DmNEr7axMbHT9ALN1AQOftR6zeVIDps3X4SGdAZQc1qKMGAaIL16e7aMreO/d0cIgVI5hfX6+2fe0d+EJUWgGarXen4rFLP30G73uHQJnZ4D1G0f2SZ+SbjgtxGz9Gt7N2es7NN+ZqaQAXL/w07x+v1gEhtbgWD21SzfGDpCm9vz6F2QvQEPbwFgBMli1AffyvQcBUyaDYCfPdQLfburaBcaOdaYP0tUyrsAeiputSVrubJqHtyBuW08ToW82qDpNm3PtzLZt9FAmkN7nA==
*/