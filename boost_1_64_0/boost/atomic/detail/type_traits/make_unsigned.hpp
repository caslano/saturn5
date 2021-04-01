/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/make_unsigned.hpp
 *
 * This header defines \c make_unsigned type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/make_unsigned.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::make_unsigned;
#else
using boost::make_unsigned;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_

/* make_unsigned.hpp
3DBvV04V0xRYJkrJNSC+dOxUJOOMdf6o/+74OZ69nuZvq6w38DdRshZaSHLOGHcM8hC9BdFObGLVfrA++dZ95a5oaWNxm6ZlljtznQ7svRA45L1J3I4vZHIbjMixvf6sqSBr+d70xNU4Yt05BCc02z5xRTOSg6xef4YCuS/GUqIj0V4Iq/fxUx02E2VKN7HKhHpxU8B3xPITkH+MIiNLyz3bXIXPY/2GP6uopZ88lfM369zm9U7j1M52ymMdxMhW7mL1obmRI5nb2JtfVKGLC6C1Ca2uUr+LTDeqls+mazUbjdu2ZCvZuGkwIsl/X03IGsRzKhgEgsGmY1mbX6XMz5ivEhxFprzQZrih7WcMwoe2Nig+hNWmr0HaszntkGmDwEtECXBr8P6x6w+MiAyCC0RuD+lf4kRRu/WZqv1BuSiFB4+41RaR2VkygTLNRYhvzOH+JBF3GnkmLVnKAS75lOWXisl9RfshoKZ8z0VnGdf/huWdpYqq28p6yyXLyQTqGN+ceNz4GMmKf1qfXLn24osIBL1pxDo+RXpL5stWqeXf3C7PiyEc7M4vhQ==
*/