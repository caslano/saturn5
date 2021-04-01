/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_trivially_copyable.hpp
 *
 * This header defines \c is_trivially_copyable type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
// For std::is_trivially_copyable we require a genuine support from the compiler.
// Fallback to is_pod or a false negative result in Boost.TypeTraits is not acceptable
// as this trait will be used in a static assert and may deny valid uses of boost::atomic/atomic_ref.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)

namespace boost {
namespace atomics {
namespace detail {

using std::is_trivially_copyable;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_

/* is_trivially_copyable.hpp
puEQXFthYlPY6UfY647C3GuD843HlME4k/ZjQ7EfS797T1LwpPEriSuee91vVyNCAOuYWFDiaYDSL4gp3gOEofKUS1IwL0mMDzSl8A52E1R3W7n7gZmBEVO19cXRHHIacYJg2CimJ7j9FQqapdwblvbxdFNb7/ErCxgnl5ihTwVF0To1kiOXgsnmNMAHcBaz5nIUUTIp+iQ65vVpJfE8O5bN26mcDqxSISzVRjD3cY7F6o+XEc0OSddBuyv9mLmH8SF2O7Fz5GIWAYzWzOC0m1m3uwozEDwWscPjBRwCs6iZ4L97s4AdAD9YsdurfxmvRNAM/fOgdjeTyVpTvSLndARTJfzluNqkdMJKceE1HJu7bVhkdzViWh8sUHhkN3X6Y9duXWLH5e3jRdXKCVVyjRBi3KteVipCxDISUskDiobbK66ovdCdffXlpA/Ct9+rlWkE81eJ0WipXJEc8a22uCHyf69hVPtE5Ng+3o066LMe9AmXVGBi/8/UsYw5FBTaIdMXTXIPcaicg9cC36YJeW8SxMY41su00Hj94AlzXZigMZCI8IysqeOTDw==
*/