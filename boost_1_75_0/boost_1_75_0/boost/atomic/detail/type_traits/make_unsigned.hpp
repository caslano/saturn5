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
jTm6eu8vXXHeJJQ9ZMXgsn5OE4F6yco/1GjCvHXCns3Ln4zDEYht/EdcqdLUMP+PKAtiQAIabHtGatMbAzGjSX2mn+D0RY9frRfwKz6cDUz41zJqypV3E5wV2YMLYYeEzScDIzJf8F/Tvr9+d6EoGcRnC/SflvQWxea25TTefd6Zm15Vty9z23bjjSwr5XDCW5clVOgjXZZ0gcpV0TlinDoLEX4S23/UR7I2g8sl3gl03x0k+I8Zdf6ReI81FE6xxUzMdagdL+jJkiC6C486WZA8urmMX+eHgRsuKplbeu0C1npnOjs8J1uFaNmWQkXv45nVC4NiGBrqRo+cG0WsKT0MXEtl82ymqPbAdsUz9861L/zZDzgN4hDGMq6IqCdES/9uv6CJSP+nAOp6zGUl9fs2ZMF67B8YrShCwXniSPWx7Y54BMgqSesaMUmEKLTijKroOsGuJuyqSKcoTCGwfqStd1/+WIGMg7I4XOAYlYDMI15DshaxgPOFa0/5RD6YXUbky0v+2lWeCkipggBb1rXVN4lH3S3iQmx+DOGq1c6kfIz1414UW3qTPxCF1BKbwxslS7rGbFyML0mw4dP1oHq/daMgbcWgOtMbvyER0S7c0z96+0pR9NW1hhk7BhoDIq1zkOFG1K+PxdzumgFcC2fcwoYbRauqDFsdr3GIBwh31Sumv0QOIg15cM7aogr3slWNHeBA2jp7TOM2
*/