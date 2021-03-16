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
0TkQC1YYNS5DLh0O/LjTwPJ+0V0H0BljoIbL0rWdaT0tKf7LzVe01OAA+F2Eemw5zfeXHiA0AI4CecHgLHpglq8fynpxpmRws2JsMC8wHZbSVxak0c+Yt0uPLk7B3PG7a4bAV+LOnIles/6aFYtGvBkKtr/2y+78OkSM8extc7KON17x1D3r2xx6a90Ddfxj/THGgbnv7zt3+v5Ts6u6ddi0/I7G/NPAMUZCwlOZRw781HHCx3O7THi0y14hviY=
*/