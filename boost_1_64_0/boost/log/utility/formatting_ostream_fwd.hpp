/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatting_ostream_fwd.hpp
 * \author Andrey Semashev
 * \date   11.07.2012
 *
 * The header contains forward declaration of a string stream used for log record formatting.
 */

#ifndef BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_

#include <string>
#include <memory>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Stream for log records formatting
 */
template<
    typename CharT,
    typename TraitsT = std::char_traits< CharT >,
    typename AllocatorT = std::allocator< CharT >
>
class basic_formatting_ostream;

#ifdef BOOST_LOG_USE_CHAR
typedef basic_formatting_ostream< char > formatting_ostream;
#endif
#ifdef BOOST_LOG_USE_WCHAR_T
typedef basic_formatting_ostream< wchar_t > wformatting_ostream;
#endif

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_UTILITY_FORMATTING_OSTREAM_FWD_HPP_INCLUDED_

/* formatting_ostream_fwd.hpp
UD2Suf9QABnFxithZphrp5YBUxeHPWNBkZc+KBI7EXMSCp0XADDUrt6TjD2dvFaMth2tx0bq6LmkM0F3XaL9d/hM6ssO0kKbZz70gPBezv0fSADUMBhO+02TW3CZ11Ushb9hS4us2Udt6WfxFuUSn2mEmyaBuKF320wofptSN+1N98xQbB08dCCQXj3o5mEie45W2KIEM2NTB/+QpQOyNHbHwsmC8rq4ILg694+AyTvJhK6NliBRwZaks6MB0JPGuHGVkdOrJIsRE8wt6aSZYxBS5g6zKAeGVUsQuyHeMfx41N0ABrP/kJ5gHO+VVLBWuIcsoJjKo1iYZObSi2hyHuX+bA8ohj+QvvI5/vadUEmghEh5hylBrx8+nxicIKCNy4f9ac8FfkCErP1344Hr6SUuauUM9ZX8sqKW4RjKTmfaqZcnsmmi3JAFc64BDC3LCL9yjkEqhV0LYc5lbFdQl3LGG7NV8hVfegZQfeOmVUOp+qO8BemO3Xo355H8Y47NxZhhcGrs6AKIreEXUXum5IxsZNujJ68irOrfPis7HpmDsKOijLDtD/gT5Q==
*/