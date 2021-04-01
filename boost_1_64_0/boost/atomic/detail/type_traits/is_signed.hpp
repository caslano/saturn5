/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_signed.hpp
 *
 * This header defines \c is_signed type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/is_signed.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::is_signed;
#else
using boost::is_signed;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_

/* is_signed.hpp
R9gsxpjEaZSyEwmA8qbbKb5clzzSGLWdBi5txUf6xKoIKmk1rA3feq/9On1CfTzlPgCb0qsneC7BypOsQm5+jYac3sm3hfE9/VRWCM80vQf7vn/t8+fAmKb30fJ9jeYBpH8l0a/yMTnLt5syb7wKD0W8NleyyuKdFUzd9Q04REcBi5dCb3jt0nPG1FzcGX2hLDnes2a9XtLP9pKHv40cUtVjP9d3cIT2Y0yFKOcPepUR5UitTz/9/xMILWuWIb0RnhM29iatwDjp/aJtM6vL1FeFKOtRYBXInmLXyzWnyoK9vrzbVGSpeuEUiI1uBTilhOmvm8KP7qD+hCOF8tlctb+KIPGKK1C2UY2BxgFDTZItw3ULvTjq4id15H05RtI1NXpyBBauzDZRBZj1cG/HtNFIJdwk/DwrNGJezxIxm7fVWWLKPwZa5sZM3hsL3TDiD4avswCEjJw5ZKzgnn99gKOCAOKVsML1u6u5tUCwx3hOZuHNW7TfRcaXspCJpBEF+0b9vyJRx1P0W46iNWQ41iExmUfvcTPEhjS89rxCSABMvyiYi4QYeIYUXA==
*/