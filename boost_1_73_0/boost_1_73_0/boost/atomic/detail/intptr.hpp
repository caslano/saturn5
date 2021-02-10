/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/intptr.hpp
 *
 * This header defines (u)intptr_t types.
 */

#ifndef BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#if defined(BOOST_HAS_INTPTR_T)
#include <cstddef>
#endif
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_HAS_INTPTR_T)
using boost::uintptr_t;
using boost::intptr_t;
#else
typedef std::size_t uintptr_t;
typedef std::ptrdiff_t intptr_t;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

/* intptr.hpp
Vv7aqBUPWTEY12C+fflE9sK2T5FbnpGNLouaqzaJ6xErhM1KSy5HeLm+Xaz6hCF3ZiPiw77OmJoz1qVF3uJ0ifg6Wy1gpk7fEEae01HX7N9fL4979sMfY4Z+d5e42sUiGg7pEnNpOW20tGK55ZhTe+kKr4Mssd+CZ+TEdh21q+bVlpHP5kGFh0rw4NjERjlJNAullFycH8QftaUlCZCRKkZoOBpy7G5bsJon4IfzCfMNG/rmFFTYLZR7hxMd70MM9Xxn7G2G24amr904IGyCEJWAJfb0Oca87NxPUEsDBAoAAAAIAC1nSlJPSd7tEQMAAFIHAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9hZGRkb2NzcmVmLnBsVVQFAAG2SCRgrVNRb9MwEH7PrzjSPCRVqMfEE90mqsFgQurQNpgmCpGbXBojx45sp1vF4LdzTtt1G7AihKvGzvnuvu+7u/SesNYaNhWKoZpDg0YGvf7/W0EPtq6s+2e0aPcB743+irn7vXOW3cDyR0ET2rdAMNhE3GQJbI24gbiLyFYYe/6cZVtgJp6YfzAfOMn8kSxBj+IOdbMwYlY5iA8T2N3ZeQ5PadvdSeEVVwIlnDlUUzSzFPaKzvKy4tfXA4sHKaADLgddovNK
*/