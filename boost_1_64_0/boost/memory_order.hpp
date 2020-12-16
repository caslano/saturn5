//  boost/memory_order.hpp
//
//  Defines enum boost::memory_order per the C++0x working draft
//
//  Copyright (c) 2008, 2009 Peter Dimov
//  Copyright (c) 2018 Andrey Semashev
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MEMORY_ORDER_HPP_INCLUDED
#define BOOST_MEMORY_ORDER_HPP_INCLUDED

#include <boost/config.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

namespace boost
{

//
// Enum values are chosen so that code that needs to insert
// a trailing fence for acquire semantics can use a single
// test such as:
//
// if( mo & memory_order_acquire ) { ...fence... }
//
// For leading fences one can use:
//
// if( mo & memory_order_release ) { ...fence... }
//
// Architectures such as Alpha that need a fence on consume
// can use:
//
// if( mo & ( memory_order_acquire | memory_order_consume ) ) { ...fence... }
//
// The values are also in the order of increasing "strength"
// of the fences so that success/failure orders can be checked
// efficiently in compare_exchange methods.
//

#if !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

enum class memory_order : unsigned int
{
    relaxed = 0,
    consume = 1,
    acquire = 2,
    release = 4,
    acq_rel = 6, // acquire | release
    seq_cst = 14 // acq_rel | 8
};

BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_relaxed = memory_order::relaxed;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_consume = memory_order::consume;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_acquire = memory_order::acquire;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_release = memory_order::release;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_acq_rel = memory_order::acq_rel;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_seq_cst = memory_order::seq_cst;

#undef BOOST_MEMORY_ORDER_INLINE_VARIABLE

#else // !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

enum memory_order
{
    memory_order_relaxed = 0,
    memory_order_consume = 1,
    memory_order_acquire = 2,
    memory_order_release = 4,
    memory_order_acq_rel = 6, // acquire | release
    memory_order_seq_cst = 14 // acq_rel | 8
};

#endif // !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

} // namespace boost

#endif // #ifndef BOOST_MEMORY_ORDER_HPP_INCLUDED

/* memory_order.hpp
k9mm7pVWW899a4Jn1gEYyMGukNQTOeRiyMFY66nGs+pf02nnYNH1FWggyfxBNhxZQnvNS3OQ5EDcpAhyIEpOkoG3P/v6LsoCb4m8ex4R9dzKkqn30Y5MgVoysI+bBSRVS8ZkULavDQnGT4B6SW1hOWgXNt1+0vamCKHfYIO4UrSLN5N28aWUPUv6GWUezti+vcl6JjednhFtknpKDadpkx5G3wmGT5h2AextXnJHm7eftFO1ag72A2iCvI/0SBf0qYdzoN2zVqUu7HMXDrJSq3LgUpqV6UKtmiXOs2nblvVQM0lozk5gmZJiXUqJ2zxlHJ4LuedQ35m1C1QsR25gK127EPwntj8pSqZ9ICPWcnD+ZKbt7bXc/dFsmWn7bNo5aNRsaNp2aieVugWwUhACuVRztcswnQOAPjey9DIncQLicudmtunI/FLL0VjWLdj7I/iwcjzsP95V3KWpY4NuzAhSprQSBehDj0Livda63Y8OdEvLTNvblxFCrzSpekgBtCm5NPrWQNWynUAY5HNvab5+ltvTD7utNAvaafaqq0sVpzVqwd6SzPZqWRa0e+tJbT669qR39rmRp5Ptfjbh9VBkaRmLIASSaN3gxyRMfjJYEmSAVWBZE9lbEbb11Dez0ZeFLZFOvHszMkewZ0M3uUGnmIhgXJSN9BLc5aJZi7Kh35ty62u5s1CsmWiX2rSzMiMSvQlFxqCP0n4yUNbXwmdBF4Zrea8+N9LPcmI0e9rplut4BTzAejXNifYUcwKNLGFNZO8P6K/l2p/+1JcF7Uy9aF/9XqVZ0M7aF5Gj36usn7QT/elAOb5AkwSkL0IjiymOL9t86J/nq78tPAtfRJ/RZvtZu9en/fR89dcfUNoPX0R/O5WyLKfqs0QbxJWiV6dTPAOuVzPWd+ZWVprZz9pnu1VS712PCkks6Yvnq7/6JaFhB9IFZPs6Z5HFrH2d+7M0JUzaFL3l+coV6aWZ9Uuf8ZaZellfZ1KyoZsSlcJaRcubk+CGUhM89MH31V+0lcrwDE6atnO2NAcbIgvKwNv8THgrMwNEMloUDJXIXvT2dO1CEZzRNXBi6tKTgRMnPyc/Jz8nPyc/Jz//ox+1tj49Xs4+euA6FeFnRwNiwRjWMWBJkfuzl/IoDIbTGW9o0Te8Ia480u0YZXsd0aP4Za5fHIXIN8a5yaUmWObYhHC3Tbh2hbAUzw8DbsOHeHCju0K6fZWouQpmh14z3VxqQnMGayHyNBg3kVM04woXguhCNVdx0cm2SsNa44D1xlzmsA7XFjt8blrN6Akwbbba5tBBJt0kzaHGsL+R5hCOuRyp++v0CBcmXc9sd4OKxwzVA4X+5v4urHBD7lj7cjUW7cxwBiENviYDACvtnHeR0LSagok9hf/J3Gckct96RU0BeG/SIx8q4uIcLsvhQkYuCap+Pb9jvVwOtIjLgd6quidUciT5fIaQwc0CUpcDbcGiObLBeroCwdd2PUmrshWsbLXqKGQvB0JxGKqNOmrWI9ec0aljTRBeqMXKusVfpQ8VBQVu5JmlDKkemAW8J/jT7fkk18jg0WEhLHbFUNA4rBMkYqliFNcGXNtooT9ntQtU3FmowzNhp8tgzVBkJFaO6oCaZmDdKOBmQs1uLGI0lRQbCkycnYIJgsHEBUNCiQmZNzGh10w6XfcfY+0wOSHh36thcFG93aG+pvlbjE1YHasrx5BIj6xwicpTMPb4hBNrJLk+r9IguA4F5CoecNAMKrUsndjC4WVRHjKESFWAr0ZjZWPst1v3706MoK7DPPwpGMFg+IICcls0LKIW3uC6HmJgWc6esN9NOZU9OsJsa65wJhVV0gM7G83HkdkeFhA=
*/