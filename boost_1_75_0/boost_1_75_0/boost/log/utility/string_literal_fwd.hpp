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
4lR2o9HpylY9qFBVCaUTdSl1yEy64ncZSY22SGJWJY1084Z9TEIIMXoJKBVK1laBt12oLDGSIQj2cFQtfsc6OubqgjDUtA217p3Xsh0jeoTgyzCxfmllOLHo19uP3kspIbkU54iwiih1XkkTiNqPoRdZhGg2B/RuvuCPEq9YZaHaZuEugzzag6TUwZf5QqT+2WM38Kg5tRI1XkuoRIc4kpT/pyz8ULgtJavJZNZM3IziXetX5PyLDYeN//ReeCyrfPFvrJBPaYjqEbzluXqHnZPKzzoZMirIndTmpkYOWJYDwpW1BNQEJ9MEhu0DpUp++3ZNmCX+8b9wIOjRLKnkwbfUf/3BqGw0h17TWlf9FfpH9WpNUTPjRFfL6lt1tpsNdtIKNlW4bHdPD+Umr0w7AR41PO4SxetNE7UAkkl1Iu1xOKMq9dFXzJJiIH1ZTSJexN4qfkEEwjcn3c7QFvEL8e5Yoi2GbQrJYiBc5Y2YCWzapYV8sX5JVSLr/JK4wXE8fU8Py/AYu7VfvLmAOCVTe5v0bW2qXAFPeqO+j01DMLO9IhljLvK2ZXU4V87iEPqA7F9+fFbceiWlk2KIeJk+roh4f713AWFiO9zoDIpLq0u8+lW/Qeu2XCJ+rkDA0hw8E8Hfm3/vK8M0JhiRgMKVYuBtiKTlCy9LEduEfgltPHej44Ke+yaVMqKjUZyARNHd+q6kwP8WuKbs5rTk
*/