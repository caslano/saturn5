/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/alignment_of.hpp
 *
 * This header defines \c alignment_of type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) ||\
    (defined(BOOST_GCC) && (BOOST_GCC+0) < 80100) ||\
    (defined(BOOST_CLANG) && !defined(__apple_build_version__) && (__clang_major__+0) < 8) ||\
    (defined(BOOST_CLANG) && defined(__apple_build_version__) && (__clang_major__+0) < 9)
// For some compilers std::alignment_of gives the wrong result for 64-bit types on 32-bit targets
#define BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF)
#include <type_traits>
#else
#include <boost/type_traits/alignment_of.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF)
using std::alignment_of;
#else
using boost::alignment_of;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_

/* alignment_of.hpp
v4HDlFZwM1e45QQHKOspPQf2/QrG42xq0/1ixpVtTFmu3HMVOf3Uo9HduaLHKEIMJj0hSpmtacvvlCqq+BfPJqhHBNzdf/86Tb9aWujxWHg/Ic+dNj3oRfcYSOIqEBn7+CC5AVBYwxH/eEi44abpgwNm8gKfC2j64HpJrzE34Xr5vCQ7RGzkq/t8uMP1groalz9GyH/9HaJY/hg9Jr2mKM4214XBf9HICeIpf9iuguK5+KVn7ESTnMQRAMa7pjEmL1+JqR6uh52REorFFJPydqxZg0n4w2/VmQR/0pdXEPbY+pyFStiz+XfXTdkTxqnq46ykaRiGKU1f5A4FlwnRKverttvacUq+1trMqLV7/o3zFQuH48OyZBA8tyeEHhR/t8dY8zGxiVJkxnFboWqayiFXy/u8534mFm5n9nKVCBylN91/9s54V3mRsVSMz35QVZ5m5TgV3h8ZJmwDMPbw3Z75YdXxisMxU/iPRrs4QwkERrvqT9VrdqIzX3TPKuyEjhC+nMvZ2YYtbhSS1yrj0ilvrjv0a96IrnFnxBhq8MxbRX4OraP6vhcHuKRe9jBaxE1yMWHyGa94Rk6Fpk6N/mYu2v/K1hyesYvzyMRwankBFM5xJxYxza5rrpCH1QS6AGqXpm3XSQFak148ubhna3pxpfnnlqV1N6dNs5ulK+mAd22mYxXCKgvOhc6iywcH+oUHK5PG/DfRxi5b
*/