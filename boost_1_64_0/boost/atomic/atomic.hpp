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
9vl7htbBakeeGNBHFDKQVfSXN8SOBcUltdU1Sx3skLyU0EO3tU/6ySltifSRTuuw/axb+oB92dp/ic2XNb+L8/HoC6kf3j1OdZN8Qy32V0ndnNLKpG5OaaXBGHsneOzZ610VUm/2bTvmSm0+MO9LO4xE1PeKJJZoo60dCuUCrkOK6tgZsep70zPVtX7IdDZ0CbvWaz/Oba8Fx/DJ7rTwvTT7+dAkPv+ZYp+58WXTp9JuX1md+K069JXkTbL8LlSU1kH5XZD0TF2nWVw/lY3tuBZaz/8x+lqoyrefTw6++K9QD+N1Wz10+54u9QiJJUv+9p3byfZjRJVh/c1qFHsypF17IbXm9Vjbo9y4dZt0GdF2m1jrmy2OIVtRToH3wldN/zdb+VJfiVP4jvo2s1zZgnUWnTQjU3x7p6r12zxT+PdbSE+PR+IhBuf/Zcrv6zyVt84zEtuuQ1oR85uYm6l/ZXeO2YEcw/XbunRLSEiwHNPqu36jWe8pfuPzkL+lBP2HHxdf4ic4YZ6jjF3IF3u3/1z4vbKrR5t+yOb3/se/Efzef5r4JdNW9KtuK/Xb++Qbzr+9LdIXQ6Sv+yLXmdfyN3VfLC0rWVZTUXtV4fyK2qWG+/EnOkl6DuLuRPouve1jQ81BdDge9byQBBmDk3hFNyF1KNRbbAy5P3C8n2pU+au1vejruEB9UkLuF3T6WToO0SNqfaHk1/cPOu7RVkv5Xq0/UufX9xNyrN6n0q9R6wU6/2Dtk/5xosgJ3H8Frjns13bPkSfbrPcc+Wqb8z1H3WnyDSm5HixGrjCPj73Wtte/9dZ21379i1Te2cZwo6e0fUC/r8rPvq2//5I2VM8DWSb6REy15F+i/fmrVHoJ1y+PtH2gjAFyLJ54O7JuaUds1G0Yft/wpvj43ybH6dfkODV+am8r7hscj88sla9E2iigl6XrrO8jdNpZ+tg7S60XWfKW6eNspEorl7YJ6I605C3Vx/hg0gK6BSpv5x2T9rasCmlL9qmPxfB7kcpe4XHNXzPnHFrbNvRexH0uluh1a/dvpdv87vLE8HuQN8x5h1a79D2I47MpeSPfg5Auz316nk/NQkn3ir71HmV+B+5RsMXtHkWuF3r+D/u0131IUsgcXnkub7XXXZ7KHesueePcnstJb9/c3vY+lwdsLxUf/Hkyb6kA2Yvtxj6r7XIcOcVUlnO2v8o/NnjOqvX+jsfdNJ2eqc/NTLU+UefnCsuEpeC9QLpKT5Z1ouyp9e66r+9Lbvs8lN9Xazxl6W/bca3uE4bt0/cJav0SvW7v+6yU8HcyPyVPfbD9asuW6s53uvcmb+R3MpLe7r6n/Eh9r6/TB8T2C+ScHSffbmgI2r7MV1hTtsD5mJV8/R3fuzxJmvVc/HtKx8/FkHcn2hd5e4y7D/GDyje3NvPGj1YUbJi7euTsexJzux/quI+vcww+Nx/fjsfmc/YJdvddvm+QuX3T4xt+/PqLS45fk7w99cxuxy6N4EOsfKnPTvAeqhnx3J8/mPeyb9gHt4/reGzwSar884+NGD7r4+U3PHzR3IzDXW++tuOx9pxjC7r5ZLvFanTzBXfzyXaLddhxn/WOxjCvVfaseuDuve8+n5Oz4vmZdRVfv/8w9wv6W/7quUrF9aNrDe3b+6qOkU2a3ad0qPj+DYPxcDiU70fLO1H1XhU9+/ejv2rxmUuX9Uy4Eo6Gq+F48cG9BN4EZ8C1cI747FWIr94yeBv8GlwnPuW3wwZ4B1wP7xQf1LvgQ+ITvA1ugD+Ad4vP+Ua4F34LfgDvgbEenm90DER51wiHOsRA7Cvt0U/aoz9MgANgEhwIM2AW7A/PgEPgIKi/wyrlxzu0d64=
*/