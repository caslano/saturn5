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
aWksiv9PaLIPwdpVcaxvzJeqwMfisJvK2cwbuxQbyWlPHPLrR80bz0dYcAEdj0iB2rzG7UR3v7EmR2zbd3naP3nSiAUpI/YGkhT162BRRf+POKgPnoe1zC/yXHFO3Kibrckt2JyWA4qp4JYYh8vbQjslqcXTW1OxiCDBcGK4V0zWs3IAMpLRTZTm0Wlfx0wZ56/DmRuLmTqnGS3NsMaISVF6Vjv5YNBhnqflh1NmIhAMcRvV0MzFq5r2YyARDoNY1LFBtszFVL4ZwaORMhXELKupvZll8E4uxypLR3SOHzfsimmjLaDXiF0X2Z8a9u0PrUc4wl5tHhJSQ1s1u9l/XZyWK2cCId2aX8mlFB1Hd7/c3V0ftH1WZJbUoqxELafPPApeKDxDsev6q9OpXXsjwYPPX/NDGm/WH1cihw6xkpwg8YQIKHJnWgHscWSl/7j0ewgaaeVQavE1zCCcNyRBVeCgmcA+w8Psjl2RtlXvmLBuP8gM9OXM1zxg+1ihtZ4xJxanqd6mrYCn/5SME3cYHYuXv4JB04yQ6T/ZJlcZF2Pk8SlIOb/9MKZvkw==
*/