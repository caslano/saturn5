/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unique_identifier_name.hpp
 * \author Andrey Semashev
 * \date   30.04.2008
 *
 * The header contains \c BOOST_LOG_UNIQUE_IDENTIFIER_NAME macro definition.
 */

#ifndef BOOST_LOG_UTILITY_UNIQUE_IDENTIFIER_NAME_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_UNIQUE_IDENTIFIER_NAME_HPP_INCLUDED_

#include <boost/preprocessor/cat.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL_(prefix, postfix)\
    BOOST_PP_CAT(prefix, postfix)
#define BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL(prefix, postfix)\
    BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL_(prefix, postfix)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \def BOOST_LOG_UNIQUE_IDENTIFIER_NAME(prefix)
 *
 * Constructs a unique (in the current file scope) token that can be used as a variable name.
 * The name will contain a prefix passed in the \a prefix argument. This allows to use the
 * macro multiple times on a single line.
 */

// In VC 7.0 and later when compiling with /ZI option __LINE__ macro is corrupted
#ifdef BOOST_MSVC
#  define BOOST_LOG_UNIQUE_IDENTIFIER_NAME(prefix)\
    BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL(prefix, __COUNTER__)
#else
#  define BOOST_LOG_UNIQUE_IDENTIFIER_NAME(prefix)\
    BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL(prefix, __LINE__)
#endif // BOOST_MSVC

#endif // BOOST_LOG_UTILITY_UNIQUE_IDENTIFIER_NAME_HPP_INCLUDED_

/* unique_identifier_name.hpp
5DQYGLs7qQLC17u364Dv1pLNaaQArhyXgytH5uBnas3oXqotrd8u6EwCzG7nUmvr3X4raycp+Ki/HgOXWsAoBz7byDsQ9vWe2Wq18rwnkIJ5p0ADRde7n6ugSstIgE9jbKSrQCXPFG8tMCSajeFVSSsoyBhqvRKI0uttx1tF9AUakALmeeStSFz7Yp6pSjYYCmhfM4fqZ+2TWg4bKEOIlL3WhdLtl2DwrkAc4qPa6WjD0iEUVL7ZUp5n033VGBaMgrea3fO+NlSztsghPCVWeiWgofpfo27SK2bnCHcPNuTIC2u5hAwtZJDuY35ESRlsIiDpn1i4jzgAHm3cIFCq6jqwNM38wwklcdQE+zdrMXeX0Aar1bY5lKGVZBOGxs1jyyWU92h3W5mZ4K2dbk8taS0kaLwxn4VB67k2uFCHxfaSJE+0lhDpXiolyNhagtxrlyFjawnyQBu8K28tQR4aegllvVXWWKoi/fKstLFkLP2ynECpfgy1B3Za0p5wUTRZMCTaZVAlwfO9g3/aAWyf7Zm1cuUuh7YRYQQ2M2FbmSREt7+pQ00ssunc8YT4QufG8AVLV7dzNVDVYZPJZa8MA7PYKgyxZe0P+hswlF45itEaQMBqqz3lqgws0umN3ObxKnnmiTlmdgkY5kVO
*/