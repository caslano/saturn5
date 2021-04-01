/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_debugger_present.hpp
 * \author Andrey Semashev
 * \date   05.12.2012
 *
 * The header contains implementation of the \c is_debugger_present predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_IS_DEBUGGER_PRESENT_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_IS_DEBUGGER_PRESENT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_WINDOWS)

#include <boost/phoenix/core/terminal.hpp> // this is needed to be able to include this header alone, Boost.Phoenix blows up without it
#include <boost/phoenix/function/adapt_callable.hpp>
#include <boost/log/detail/header.hpp>

#if defined(BOOST_USE_WINDOWS_H)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>

#else // defined(BOOST_USE_WINDOWS_H)

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

extern "C" {

__declspec(dllimport) int __stdcall IsDebuggerPresent();

} // extern "C"

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_USE_WINDOWS_H

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

struct is_debugger_present
{
    typedef bool result_type;

    result_type operator() () const
    {
        return IsDebuggerPresent() != 0;
    }
};

} // namespace aux

#ifndef BOOST_LOG_DOXYGEN_PASS

BOOST_PHOENIX_ADAPT_CALLABLE_NULLARY(is_debugger_present, aux::is_debugger_present)

#else

/*!
 * The function generates a filter that will check whether the logger is attached to the process
 */
unspecified is_debugger_present();

#endif

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_WINDOWS

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_IS_DEBUGGER_PRESENT_HPP_INCLUDED_

/* is_debugger_present.hpp
gJsfKsG45JQdYYo49ZEk6mJni7SVzsTkQEF8xXchp7krGhOyCB7B/fZKYCenWPR1VEVW6c5Zcs5/6F/aroVabm0k5FXA4S/ARgG4Q9HKfLOWxrwXGCw9zxM7871ZFShZ3OtLNdAVSS5xi3CF2CNA/2a+Apxd1QpdRdRm1RWY+co1bRHd385HzO6xQuw7KqEiWvZJ97oJltb2/a5pM+K61Nh7L2JFdLr8DV/lO1XUXYAmwCW5aeC0GxR7DGyCXKtZvNx9CXweDyWNm97eEEXIts3MvSPsXV92m52PbZV8Kv2EKI0ECbtENLYHI+74dO9HI+7FWzTTnpdYe92aY24jwCfaXs7wqLN36yelowGmnh6/W/yBMMQqSayWqjIXWAdVoiW/PJd1KGJX06YjabXUW7WVdNvPyYZl4Qphc1tn2Y9saWdxqGF/bJCP+8jkDuBjc4VVZ7G2vI2C8ivYaxoM4IxYSu/E/+TiCHhFKFEEYwUb6BTbP+2+9uXZH1qhXda+J4jhiyL9yTlzfXFF3sEC6VNO4YgfQDcNtBoK8rcwB57591MfnANHLWCJ7A==
*/