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
7U3QskKWGR5t56sYOcPSZHaDdoagHMS2wocwmJRAQAwwsBLAxPfu7KAMsghvwtzwC3sxtcerG2hmIM2tbS+5g4DD9BTdYBITBEFxe75/uwIUZDdkM5g3MZzj3TDOEruz3BUAx9bkFu0tfFiMfZdUAQQ60MX2VgswEoGHrjK20bEtD5wmALM8TCGPwcQXVngbor9EMNxi7HgW1+7MCcKoiXbrsRA4AFcFdMDk3dFJYO4s130g2rW+1ldrfFwaIp7c/ue63WDffgTPsh9TrSd1aLkTkPpdIw1T+232rT/q9Zrs+DEJzHugBg/UAbEPhF9YwS3IO0X3Al+PaFRQGXwDF1rBetC3FvZn5Eioz/TuyMgGQ+23q9//zj6wbzsMGYwbzQvDGDSaZa3miXlcDtGLzbrW+qT/XNH+SxW+UtXBvNB0o69cqgIB9NPceTzdUlxOxFwj9b+X3ZEXOjcexLss2xe6oefZxTaTh4sX0VZGxkWeNraZEEkbzWw6sJd2DDSyQg9d6aipXpt6nCl6t5XWHbW2u+eqbhSaz3W9r55rRlcx1AKwb/QuKwiZ3XJ088tZoV3r966KyODQzzM38pbP6lCHIJ9XcgaYHqMEmnO4PPCkGvh2Xc+3Rk+vhr57povpvSqJE5DZVjvKqJeZ
*/