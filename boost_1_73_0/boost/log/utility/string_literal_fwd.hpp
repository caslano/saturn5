/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   string_literal_fwd.hpp
 * \author Andrey Semashev
 * \date   24.06.2007
 *
 * The header contains forward declaration of a constant string literal wrapper.
 */

#ifndef BOOST_LOG_UTILITY_STRING_LITERAL_FWD_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_STRING_LITERAL_FWD_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief String literal wrapper
 *
 * The \c basic_string_literal is a thin wrapper around a constant string literal.
 * It provides interface similar to STL strings, but because of read-only nature
 * of string literals, lacks ability to modify string contents. However,
 * \c basic_string_literal objects can be assigned to and cleared.
 *
 * The main advantage of this class comparing to other string classes is that
 * it doesn't dynamically allocate memory and therefore is fast, thin and exception safe.
 */
template< typename CharT, typename TraitsT = std::char_traits< CharT > >
class basic_string_literal;

//  Convenience typedefs
#ifdef BOOST_LOG_USE_CHAR
typedef basic_string_literal< char > string_literal;        //!< String literal type for narrow characters
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_string_literal< wchar_t > wstring_literal;    //!< String literal type for wide characters
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_UTILITY_STRING_LITERAL_FWD_HPP_INCLUDED_

/* string_literal_fwd.hpp
fIl8m/xz+R75Hfll5UB1pvoIRnULGVX9JMyjKuPnxv3GSLPCnGB+YV5gNfmYpTn5n8st45Zzq7i1sDqC/GWwEg4ST4Bm7RDni2ug93vLR8sr5HUYtU9g6xhajRbUhpt1kPthWKEPz+vyX/te9H3oY5aXMCIdkzL2Uv4urGmP8YYYl7zyG/Iw7TGtnz5VV4wzjMeMa839rRrr++Apszo3Z45jR7MzMWbr+X2EicI8Yb6wQFiI
*/