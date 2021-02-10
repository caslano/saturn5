/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ident.hpp
 * \author Andrey Semashev
 * \date   22.10.2012
 *
 * The header contains the \c ident keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing process identification string to the \c openlog call
BOOST_PARAMETER_KEYWORD(tag, ident)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

/* ident.hpp
gX6p9R9/SO8tuwWMF/BPFN81mmJi6GOQzknWZL9IVnNCenr87NmzPpi6kksCwEIts1F3MvrNGwxbxt/tfp/L0rH5fNK77A6vJ+ZDUG2DUfcC6Hluvng7mVyZTy7sB5RySCksGc/TE/L9M58F4B6J4Fmu74GtNnGUBnLjnEdLxDq56o7ItCRczzG8++KFFNg5UZn4vDO87p8PJt6oOx7233e9t8PxwxpcjYa//lbZAsbstTudLjjUgnza53LxHD0VA8YZwyQTf3Xn3xvqTieHAHRmiDBz9jHPLgkWRFTJa+6h4Px1OwZWij2I3uBWoS2Zk7uGvTMcIwMBX7HHornuH3Q1nsF+5ScKTXO42tcu2d1QItI5D3zMkjqY5hhH0t0yhbQAhHwLEzy5Hg26IhalE8ewXXoL9E25lwuUHr47ZF6ceEzvBk1XkJvTlYhxh1nerWo531KKA1jPSzKNsWWLp1GQQ4xIcUM7BCMpB8AVEs8pQprhKRbFNTR9lMI/i1cPmj/g68mwM+zD/Mn2+gQ2cqBcQ9H3RDkKU1a8Hzf16OGROFSCNMK3jXEzR78GnrAOr4aDMXLzeReQlbKhKaJx+CMi3eqVHrxEo//7Zz+dMtrT/fs2SDM2EWtQx4O+O/mZvpvEMbv0o3vZIGWN
*/