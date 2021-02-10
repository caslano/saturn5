/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_trivially_default_constructible.hpp
 *
 * This header defines \c is_trivially_default_constructible type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/has_trivial_constructor.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::is_trivially_default_constructible;
#elif !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
template< typename T >
using is_trivially_default_constructible = boost::has_trivial_constructor< T >;
#else
template< typename T >
struct is_trivially_default_constructible : public boost::has_trivial_constructor< T > {};
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE_HPP_INCLUDED_

/* is_trivially_default_constructible.hpp
wXHpG6srvRb5xrEGv6usLMrFpCbuKmsTd6uRK1y5EYE/Fx18jltCXUsgEfciZL9hlFVU54abLtR9cT3Ve15de4kQDsplunK30q2wNfKpWV6oGNcsLWFPod9F6OkW99InGiSCOl3I8EKKU0B6KVVXTqNDzTNuVYzoQtaNkOSAPYdJu3XyQMze5IxQoFlOZ/wRfpV9bgg+Q3ZxzCrvKMMZjIPCSM0cqdN5nEfB6Dq36rj5Jj8R34gjZb0IpQ4yuzDj6TymNkSVuM+vkraRicxTuUt0je2Z5hwCEquBlroOiAB4/lxgoPmGpnJLWgsnq368Se9hXRsSb8Ukw61XiS72aIgD/KfoWwsKRtgywIGmPD8QDOxThxc4arR0KMNrTd8pSa0XbnKvaEf60pBshTudlBdl0UvxA+fzwowMFY2Ojj5Huumtk8osijNCSWMNPhr7gzGctLu2tHQ/GVANa1L/REk8Hr7xQ9IyhfUNJdP+vpK5+wrHCKR784BfqGulHzymN7pWdOoYR66ICKdCnORL1nsultUVgXnNTJ1gTrHzQqy4bDYiVA7C98/kWu62WQS3KRiieT+e0SV5mum5RwIuE1PjtnWej/JNYN2MbSR2vvpUIQmQtTJ9yyOZmsu/UdjaDGxb4ppK4ASJrgiO
*/