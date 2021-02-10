/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/conditional.hpp
 *
 * This header defines \c conditional type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/conditional.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::conditional;
#else
using boost::conditional;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_CONDITIONAL_HPP_INCLUDED_

/* conditional.hpp
fQ8J1Fp+8Y9UWtAlGn+Luc0uf7uG710qc8TWALHLBvzsTCzlz2vtP/0qr6mf0g31tv38wdnhYXxfqJfiblvRQk6x2pJXkdbLXygTF8pJltAdgqtiXqt3Tvgvgev8SHenevHceVcXPrXDLNa2UFzsZdSEtANe5ib1PDoqYPKwm00Fes1bpddqgVIalFUuSrdsLRRSuW1qYyPzb1BLAwQKAAAACAAtZ0pSk/ysrlcEAADBCwAAIwAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvY3VybGd0ay5jVVQFAAG2SCRgrVZtb9pIEP7Or5hySs+23EAj3SfSSjSQHKoDEZDLSZfTarEX48SsrfUaxDX97zezaxO4Ro2rKwne9e48z7zszCwd72d+WuDBqx9mvgw/OBrEjcoeRKhflmbsCewfou5xfE1JB54hT8yF1yFP4BgIq7Sc05yx1xTdk2306BDyntEUVxBGyIss36kkXmlwQhfOut0uvMPhrAsDvkkimESJBIc/chgkEud/urDMFFxzGSn+KGbZUiNNp9Xx4HwwnF18JNKyEKBXAtJkEZYqBaTgEOvHd3qlBI9EBDzP0yTkOskkAc47NbbTav2SyDAtIwHnhY6S7HT18WAJWTr4pcWDVdLSoYdZv9KP
*/