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
9fxyYTHW9KXCMqzrdwjLhRXCSmEV7Jk1wlpYHb2xFvxDv8T7U69gBI2ZRty4z3jC+LOxEHIjWkFYfnHrRus26zmMFnnANNdWlL2QvZV9mz2Wu4ZbgzX4BL6Tf5xfxz/Df8JXCE3AboqNWF/Oh45djvXlCWmT9IE0BmvwHHmZvFz+tfKw8pTylXIUNPsJ+lTvxd6wMcGqt2ZbY7Fy/dB3I5GFV3I69Si2AevGg+yb0KpfcAfx
*/