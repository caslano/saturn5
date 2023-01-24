/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_integral.hpp
 *
 * This header defines \c is_integral type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/is_integral.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::is_integral;
#else
using boost::is_integral;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_INTEGRAL_HPP_INCLUDED_

/* is_integral.hpp
H3QN8heIVkRbgL8ETcM0/Gq4kgQ73ieasboRxAxBjBifv1aSuxOU1yvdxNZAr2x7J/FeAS70Mf38/8xqYMzxX1ht7/F482dWX/yF1e3xHap1BU4ocUw80nCqdDGJh4nZ7XBRusvtU7aGuMC6yR6GK0y4SiZSAoy000SETTI4MOGlHB4ok7HEcXOQA5RTSkYarP0aGMxCBIxrO6j1mABamas8IDWzD/hTMb4PKr56WtHraBL3+WNHvEJHGnYMkotq2Ooh/LaNht2w2MYgAcsI5/YE5wVflyJwEeO1t+wrrv1Z1Yn9BUW6wtTvFMF5oardcrBSZP6ZuWnwC0oXdbLnbjSxt/te4478EYMyVoOZU74moml8k9azBZ72nQ6dWDbpQXbZM2kOSkI2rd0O4mJ5AXbgd5MRg4DzlMzS1+czLG/VQ+q5fmVoMN+80ypw4x/4Xmn2Yktz0Efwq519TqhMJu5J9hLfqFzbIkoMWQyfBlawUy9PXYR06KWZZGdcMafN8im5EmuppgYzRtOEm06M/gvGute+TBeZnGR4ssnlL0mXJ8nNcyzbsF+PuC0mCsWpFGpbaqU46KGXrYb3iacdemmgKkNrvjG4DhwVqG830OP2E9drf349luyEwmx5tc8cH0DrrSFsKAwXzZNTlLoc0Qhxd/V0c3dreG/oErZ6x8FrW8HJ/6w0It9mCiL1P6ucgjnyDLKTq4yUWlt6
*/