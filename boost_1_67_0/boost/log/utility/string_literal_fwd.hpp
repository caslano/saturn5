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
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
*/