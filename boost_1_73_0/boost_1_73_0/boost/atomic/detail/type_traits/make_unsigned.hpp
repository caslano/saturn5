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
Txo81Ot3uv2RpfAxiVdBdOkGDp2RfIQ4b7v9k3YX5c9Z+6I7VpA4TJdShBJC4qJ+Drcuul+DwyPhIUH36MSmM0rkPXyODGBFh560xnSuT3r+lUwzPUkeEkQuAgp3oh1V/fAkZpcz2GRNKRH5Ln/45eA3qqF2mjt5nOXiMksmqP0VLEJd00coXS3FaO3hb2bRVdj8bm1vj+Y3KixK8grwQoGH2/LATRKoD/soDaU/fh8i4BGPExG3dNPpG5GhqCiJ0M3EKhfJB0+gJqUwgWMFC2sFQd+SIt2vfiJFqxHne0goj5FPJMiItd+DmrJZ+4X0FCH+e1GlaqgnG5LRpH4tzMYNfc4+Z0f4XttVpFJ1W5CrapiV9bShkdWs0/5NWNQl0wZ/cUvP7O2to6ls34cwKuA8ay1tRp1L1FBd11s5Y4QENah4N7dRaNVITiq16mIqMoybtmOEI4w903iORRzv7eWiNJPklpEj6+oUC7VO7gN8IGemnrTM9JWXOqk4S9KHZY1+pw4xWavnnRUC0IRuSePNjS36WLxWVptg5v6aJVd6fuyYcmVSkIji/PbDhrqHWznC/6TPZwNnbH0cM/4cG40nSDiYD3qDxQjUHnXxyjCjhxmhm7qSEaZQ60DjKtUwTSTt8ojY9U2lFrxK
*/