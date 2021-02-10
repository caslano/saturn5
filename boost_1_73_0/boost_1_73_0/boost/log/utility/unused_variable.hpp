/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unused_variable.hpp
 * \author Andrey Semashev
 * \date   10.05.2008
 *
 * The header contains definition of a macro to suppress compiler warnings about unused variables.
 */

#ifndef BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__)

//! The macro suppresses compiler warnings for \c var being unused
#define BOOST_LOG_UNUSED_VARIABLE(type, var, initializer) __attribute__((unused)) type var initializer

#else

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
BOOST_FORCEINLINE void no_unused_warnings(T const&) BOOST_NOEXCEPT {}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

//! The macro suppresses compiler warnings for \c var being unused
#define BOOST_LOG_UNUSED_VARIABLE(type, var, initializer) type var initializer; ::boost::log::aux::no_unused_warnings(var)

#endif

#endif // BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_

/* unused_variable.hpp
C2wHF1ZEEcGaTkHfU/uU/WO1WOJOy/NhL4vViAWEFn/C7CCA3SPuv8WOTWm361ZwEzawAvKNXQP1wI5A/WKPbSJNRDglmDOrA7hB3xm78eUQCH3EipNr148baeqdjeRnz6ePG02zdaG2PtWXqSGAyg/w+5sgw0dEfaqmNjJMrWNeqpfa8Oq0dBzGHrOjxcO11VbvuA7CoNbqb6QMU3viNlnYaGQQT+qzptXgKsjjIiRNVzGUMrpWZOXoAmIFXcLldNPYbxG7Oa7GB1i2xzveozlZ1wegKf5b4A0l/KMpZvlHxHL+OW6Wf8Su4j/Gz/CPPar5T/XJ8d9TlX6ZAK5teTkJELVCBI6dm9uhellCGdbuuRVMs7QBtZxyjJ3VD+BXqSfdgzSEkUINJ9bSxliMdSkw+Zb8Hj54kfX1kLGhHa0Cj/wKvIj5KyoOg2P4wQMWIVk35JWwiR8EWLjHYlc092FhuLcmtw9MPWtBSsBuVg/hXzLFpEvlN1M3ht3+udlT++e4dx0Zg5HB3h4fH8dYuArAujS87EIup7bZwclOvJCAQGxvYtokRZ2vK7wRpGgyrCOa/mxmRsy1vcYOrh8ZpFNoWMm0ltom2MShnCoobM/O4Dke9F9FQBdCyDFEXIouMAD78CHPbYOCCcFQ
*/