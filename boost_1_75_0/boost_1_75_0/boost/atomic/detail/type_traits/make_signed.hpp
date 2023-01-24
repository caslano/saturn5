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
JMekutyF8eevZk3JjcmBLpoGY2pEvw1dkdAmWrZbAwgnKTBHEz2Bc/9N0yItvErk9vvmleh5x781nfJb09SvRPq21lSif2ta/bem835revS3pvm0ooHNsmnmvzVtHzV0XjRVcYJ3O8q2ahenWqITSrLGb+L+9hWJoyyjZ0VXPN7oJ261nbv7t3mjj4z6AKa88nsSBAgGYG0u3FUf24Uzv/TO+B73cqCPusnoQSRXdMo3X2AfjvgStEUOl3sGhGaGJqKSHFxSRu0XzrSy/hIvAG13ykMOqsIfnxE04puIoHVKb9qH4W6435CtKAJhi9ztxwnT4qvvNZeLJM0ihZEcFgRgT3DpQ/0jVXmi4WP6XlDj7LGgwgeE3Onuz1/iQUKMpKoQbWjQ62ffy1sB+AV9JpNEASzUGQdCKv/oJ2OMQABuzL7IjSVMd0z3z/tMIrRyZhEI5D9j+jpbxPDpv16k/M+nPwT+uSxu6SrvZOX8D1L7OBiM+SB+XZWzHddX66ukSUcT1pUxHBcyJPvNKsqX2iSX02hA7GREk0/YvFZElOYqUyzNeR6HJB2p2XL6UTdGz0O+2nwrl4kpj9AvrZgrt41/9ym2lYE6eXb1DWO0nXpXRgtsqmFizH6ElqwQnTMMnOvjFgD2vwkAd/NdwG7Easgee9r4nuOsvlKnyb4yF0izZTJ/QbWHq/fjKbJBh8WI7Onzg0G4ChL2Sate
*/