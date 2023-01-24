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
r7VzUwnzOfezqbLUgyeljDKCVacjlEMFczikCsO4mWMCPhpzaa+St94OI7emFkHLVd2QZS4PjrJFn05wWCqFTnXkM3lz8tPMGq5eK7b5ETIDw5ShCbrZDpt9MPDsmzCMXxwEprtlOzZqGQcH7W+SaHpIEWbR72W6uBAp4llgfSkFSSHxHoIq2zCUGlWfuk3bOwmVgShd2DG4D2xx9DOU3Y1sNkWtUfgEGeogcqTVO6l9qmEYabfQYrhFpodY2K0hX+lXKOkcYrQCyXo76jfiP++w5JCZgEzIOGNKBmhatcbv62ntQ/4BAiHWkmGM4YWWLAj46Xec0e3wWUeY+W4cYRsyGFYsaiKU04owVe2S9+/2GdXYxEIIXayDMwicUG8AaB/fxJAAmnN8jLJNLBrU5+ETKmao4451yOlyg2L4JcaIFTuhJfWoZ9ZoOEXKJbmu9WnJGSQPZ0KqhyzGJXlt1drwksgBBBISfV3ofFM98QyqGE6yrKVIGnqSxPJDrFnIKGod27bwOG32LWSp0P7Ivl8oryWWi8rtlT/rwx7qQvAlHUg3E9HEtRBYZMW2RgnkV7vTyLQEkqWL9wxsxCAPpPgrvpVr3g7npCHF4LUTErKRFftosmP0fRVWO0t6esgiTTJlTEJBlAQ1zSjQ2ErhEuAz3jXAaadinGMb7pI2l0MY6P4JMYXizKhuM7VD8IGhRs8SFsfEoPwU43Ch
*/