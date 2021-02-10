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
zOvV0o/mti96Xt6WXg/HH7tD68rod++GJqffUS1UwyxgqmOunKAsgtXT46xkQ2OZYxMkyTYFlJo11Hj967xuxjOzyurvw7wtpCEOfynBsGt1IFCI/Wh7Pp8IoUK+91ycBJHfZDAxrFswfDAZGve/ogRSDgcj3j5ucwJV3uOE6kqNgFfKaxrhIz3hI33RrP7CHSheCejCXh4e6TK1fOoylWnleFxOvqpPLsNS5vm+lWRhKJBPcGMNSRDllLcgSt9tjdzqIiOnMAtcJ5U5tzBpbXubHhQFu42NbRu+DwSlvkUK9xhKRbBBfVDRS3iAe3hGKVlFa8JWlDCoFqmLb3HW+CJITrj86NIlBDYRN1KIFOZqwWaIuxGkbtvZlJ+7Wi8lMkhF0JXAFmYiLmd2bV1Bc1OgbA2gQMCbR9UAKrS8EytApU6thJe3n0vKUN1K/zkY9cfFzHSgxqy9SY1+H2/WZ0MMoAflYqPsdWxmH6sWR9htWONPZZsJ8SMIH0CyIHBZlp6VtvZQAxr3CdxuA676FdpRMNLLnECfYgd16bTbVTWUX3mSPatuvK0GJBoTRhfL/DpBLUT+rnJR70++fXC+81cFqAPRPqT6KfmQPoT1Rn4DG0Sm+qpTpSF5URFFAm5eMbhjxdgyjFOpC39e
*/