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
QYrZjQEoeWouhCebIxJ075alkB3mNJCLDoRUFtbQuM2RQ/MBT0H3FTKDn2I5cGXx5GJ8u7cG7cgkTXIcmX9IAL07LSXTi1FyRi0yFPh1i+a01o+WG5eXfzxzfWE4+T7Ll8bQFLEOmQmdimtcAHmEyghc+xZu6aC6eD976kLQ7DyUh5IKPIdgY24x2PKLl0ugJKwQZ7lGUj3JYj46ZUq2GB1TgF+YeabC7TbraELYqdbNyvyQ+19MGj/3/klxznWa7XLj4IFFKfYUqbAfG18ICPm+eHeYPfkx4F41w8JkUqn2uYP14suOxDg5PziB2FMbpbku3yDI7T+RQXuFd1/0VadYNVFV6IpVBupCbMiF98urcqSkQ9+1Z0SOdfu/FA9wmljWhTAY9Ia9AfU1yXdcn5Efi0HVTaiLq1+9m+k/yxn1dvyv+QJgcIJqOiOq4XGqu/Fqck2yjpP9drVYArRaR/B0YDjApw3fw+fXnPvwgjAH2wl7vagjtrXPzjD2XMtjtXp7+YN3Of1wtVwh02J8u/z38D+jV/Atr8fD/5fx7Q9/a2CtJo33RX70i0Uv/KlIpolKpTVuCitTMR9364nfc8lE57hPDB6VgfcsiVuNJRNH9ElN1J2yAY84Nrg6zQk+x+ZHnMmSq9U8GLmW
*/