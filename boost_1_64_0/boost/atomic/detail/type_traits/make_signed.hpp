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
MHZMrTQaMEX6AxK92HK/9NDdw/KB5NZlXrgcbT3Eg752jTsSl/uw2YDUBZbFM5tGjt3lfUecix5+4xttxByY/5wQ1iwno3ntGuBX49ABQYAiXpYyqg4hP3Th0StDWcT8azqqQ73ylqZ/3hOCxlcPWsv+dwj5xoZ5eXDtfnRcxcJJ1O/bb9NnJtpfYIktv8RYBxwX8px3+x1muX/eFZUuyj5tHaMv4hPeR7dEz9oIFsvxBwNtYNGMVPcxVfe4il8UBDS+JZMMzBB7NftTp4BqhK46ymE/Bm6oBxm2DBDHJhOW4FXd7oIbe2hgCDfanSm/BNqwKGzkhmGclk32XOK/DL2coq8NtUUC4l9revoXou4hIZbKDqVkeQ7jvQf2sTAwXsrmjUgw1OTbOFURy3OXGrBWnb4OHXt2K1y8x2AjHB5mNMb7XGxF3COumNuLtb3w0ccCQGUo6Lx9/NPy7FY3xX5aSvAaIzZeyHplurUz7qqeOuR7pMY+P8XhzpT0zRetVUY+6hFT1FF2iacsV9jnPvi3lPpulzkJ7JU+b57Np/hf3XcUHOMiGqkeiQ==
*/