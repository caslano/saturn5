/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/atomic.hpp
 *
 * This header contains definition of \c atomic template and \c atomic_flag.
 */

#ifndef BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_
#define BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_

#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/atomic_template.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

using atomics::atomic;

using atomics::atomic_char;
using atomics::atomic_uchar;
using atomics::atomic_schar;
using atomics::atomic_uint8_t;
using atomics::atomic_int8_t;
using atomics::atomic_ushort;
using atomics::atomic_short;
using atomics::atomic_uint16_t;
using atomics::atomic_int16_t;
using atomics::atomic_uint;
using atomics::atomic_int;
using atomics::atomic_uint32_t;
using atomics::atomic_int32_t;
using atomics::atomic_ulong;
using atomics::atomic_long;
using atomics::atomic_uint64_t;
using atomics::atomic_int64_t;
#ifdef BOOST_HAS_LONG_LONG
using atomics::atomic_ullong;
using atomics::atomic_llong;
#endif
using atomics::atomic_address;
using atomics::atomic_bool;
using atomics::atomic_wchar_t;
#if !defined(BOOST_NO_CXX11_CHAR16_T)
using atomics::atomic_char16_t;
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
using atomics::atomic_char32_t;
#endif

using atomics::atomic_int_least8_t;
using atomics::atomic_uint_least8_t;
using atomics::atomic_int_least16_t;
using atomics::atomic_uint_least16_t;
using atomics::atomic_int_least32_t;
using atomics::atomic_uint_least32_t;
using atomics::atomic_int_least64_t;
using atomics::atomic_uint_least64_t;
using atomics::atomic_int_fast8_t;
using atomics::atomic_uint_fast8_t;
using atomics::atomic_int_fast16_t;
using atomics::atomic_uint_fast16_t;
using atomics::atomic_int_fast32_t;
using atomics::atomic_uint_fast32_t;
using atomics::atomic_int_fast64_t;
using atomics::atomic_uint_fast64_t;
using atomics::atomic_intmax_t;
using atomics::atomic_uintmax_t;

#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
using atomics::atomic_float_t;
using atomics::atomic_double_t;
using atomics::atomic_long_double_t;
#endif

using atomics::atomic_size_t;
using atomics::atomic_ptrdiff_t;

#if defined(BOOST_HAS_INTPTR_T)
using atomics::atomic_intptr_t;
using atomics::atomic_uintptr_t;
#endif

} // namespace boost

#endif // BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_

/* atomic.hpp
tn8/OQ27bDfpfYj3dJE4daAJB3LPycbHkQM9uTcKSwcfiZUAwVNfprsKVOD1fDm5a1H6It/BSqmXTHe6xTwwuxdUmiR9/7KubVt3itgHynZwLCHs93yZF5AR0BCOg8wcJ8DoQYpOUhePik3lQvG2O095SLwor2ToKGlGZYlNjaY3gsmIWO1LUah1jvBu+Q7tATBvQMR5K3LDlVy17OJMUSue1Ruy2x7+tcFfmzMbpXR07jwazRlkqcHAppLJm86+gVacZ8rNdiFgVpBI8MnWv6dNeHQ/UEsDBAoAAAAIAC1nSlIs4VJCjQAAAMoAAAArAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvdW5peC1zb2NrZXQuZFVUBQABtkgkYI2MQQrCMBBF93OKOYApXQiFIIJ004WLLuoBQjKmoXWmJFPU2xsQ964+PP57V+Focef0MkX8QgqXXMFpczqfYaB1s9gLM3lFnbPsca6bCt6qgkEeLjH+zBAoWOyaY9u0MGZR8bIWi8M0jdA7pSj5bdF/e0kYjDHwZ/6AiYuSCyh33EviWJ+ETPqUvDTwAVBLAwQKAAAACAAtZ0pS6aErywoDAAD0BQAAKwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1v
*/