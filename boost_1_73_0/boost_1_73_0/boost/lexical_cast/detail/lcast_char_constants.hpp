// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_DETAIL_LCAST_CHAR_CONSTANTS_HPP
#define BOOST_LEXICAL_CAST_DETAIL_LCAST_CHAR_CONSTANTS_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

namespace boost 
{
    namespace detail // '0', '-', '+', 'e', 'E' and '.' constants
    {
        template < typename Char >
        struct lcast_char_constants {
            // We check in tests assumption that static casted character is
            // equal to correctly written C++ literal: U'0' == static_cast<char32_t>('0')
            BOOST_STATIC_CONSTANT(Char, zero  = static_cast<Char>('0'));
            BOOST_STATIC_CONSTANT(Char, minus = static_cast<Char>('-'));
            BOOST_STATIC_CONSTANT(Char, plus = static_cast<Char>('+'));
            BOOST_STATIC_CONSTANT(Char, lowercase_e = static_cast<Char>('e'));
            BOOST_STATIC_CONSTANT(Char, capital_e = static_cast<Char>('E'));
            BOOST_STATIC_CONSTANT(Char, c_decimal_separator = static_cast<Char>('.'));
        };
    }
} // namespace boost


#endif // BOOST_LEXICAL_CAST_DETAIL_LCAST_CHAR_CONSTANTS_HPP


/* lcast_char_constants.hpp
Ez9TnBdWnssFrlkucNww9QhqsFOmy6RDhTvNQplG/67XM7GKycWBXGCycE5T4jILJD7U449aKbQGjlX4vVlngbbZcXzmTEXs7FAOVbXlXbvf71wRUOGQTEaUKAm5BRECW+n0mvibp5CZV/oYYS4I22OAWRiWDLN6uIc+pQSdMpmJMM1aeQgTUKP83mxAfbd15J7kXwe7rX9g6ayvgxn1Qe/NLKysGL3Z3YyHxQ1q2AAjiMKJqZeNEHCUA8hCLBBMeycFU+sLLrB1mgJkp4IQSyeQzE24ZoR5qILbnuOVm62QZiKtgxmr/rbegCoXymSmma5kmwDUQEgX40S7h3SssNx9niXqdTNt6Kyq6uOMLX3qFDATYbEtHAOcsiA2DMmMhVQyaSXk4nQZT2q3FrlKpD21SWscyqYrvb89z8kjCxqbi2nA9c1tp299HHRHnVHn95F5upWRmo+an8NocNcpkP+4LcIz/ymqjTRUJsn9r6kyj2ObEWY8EaPX2Ibp1sXBSZI1FRz0lHqqcIxFPQ4JUU8opXL6OenfvuxYt712t18ATK85bXTwv+qKVBUKomiKt+hWcjGfYUMY604LhwI+ppqBzd6UerQQHS0yVpgrDtLrZjlvlXNveiPyovOZoiJzZX0f8Vc/o68L+vpG
*/