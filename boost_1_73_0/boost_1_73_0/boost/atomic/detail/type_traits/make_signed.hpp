/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/make_signed.hpp
 *
 * This header defines \c make_signed type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_SIGNED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_SIGNED_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/make_signed.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::make_signed;
#else
using boost::make_signed;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_SIGNED_HPP_INCLUDED_

/* make_signed.hpp
BFV8r2sMxUmuZ1BHS8eQRY13h2bz5LOw2vuNczsm6sKg4JqrgEgYriK6jEmS49LCVsgYKAX+LG8LKigh/jIKSiT3bby282QmJ9eONh7nWm3+9D03lj+wbb4GZuv8sfDxbzpboNZfhophldaaUMoQHbJEBVIddv7aPD99Ud0AncO0FAyNnvdPLad9Me47Q2s8/KTczThBkQCoAylHQSGPBlDQRAkjqt8X5ZBvqXONMywKK8i680FK4Xio3jysq21NKnVU8FBHzhS1RxucKJiSl/fW0D775Awsa9goq7lNWRH160kDI7knJDXYbVYiETmk5fR/JtzQHMUWazjMj1XSfmraQf14fSkTZA3Hg2H/pGudU41VqVC6MXf9sMb1WHI1aejDnRKXG+XgMLRdSoteF6kgj1BVnQ8VRRUGuflTwuqqLFwZ1olO5l52VeH0WhweHJTg6i1DnCXlUFH8r6POJ1QLYGNaN8XyKtOseXdjrgDX0ppZlGZxlEBywSrLXBXr8rUUUgogkhXVfluwqUaWroKNyBiXWPLWBIulCMUY5SWqrOcjM+UHGrsz6XoySQ3iSJaXrkctHa4gMVRIkNIGVagW0lZ2hRoVtll7jhJ159eDHdii/z8yQjCps+3ErdyUgIFiTSiXzjSupRk2
*/