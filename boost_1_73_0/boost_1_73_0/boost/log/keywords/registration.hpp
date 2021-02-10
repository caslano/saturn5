/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/registration.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c registration keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log source registration mode to a sink backend
BOOST_PARAMETER_KEYWORD(tag, registration)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_REGISTRATION_HPP_INCLUDED_

/* registration.hpp
SjDWREgKtQpDqCKyiFqdln9RryKcHg9x298NWdsiTNlrso1KClLIzC+30HFbTsgmZDhZvryC5fa76dB7ERK3VezyMKkl2KfbcJV5INjoWC5m6TfM27vZH9rNuKPJ+MpK0KmUX10QQToOFJYzZNBu+dl+0x2Ycj/xbzBJpizJoTgk+75y4zgcv74YOGwUgBnC9PuLDfRsy2zY7w8/9IedNsWTKqUF33mV19YVFFaFsTUA83My6nUm3XOv3KZWtIkwDSUJMbPHQ65x+bml9tT1ZFiYMAASi0mr6zM//7HSZwbjW3KitQ9azdJkx9s8bYA7c0OzlwaBgN/4I/6nN+5iORLLa7RrU+wKspR1edn+FSyq3kgzJtb+pwTZrbhPrOvPWxgWHn2pH6xB/vbeY+QOY5wuWE6XD2DgQQng1MDPtli6mS8aCYrgFhJdH4AJAdMfeSeT/riS2rm/d8z3Jp4/O2ZiFIwfz5qrqPWJXYX++bPndLEb34Okz04qGRMEAHRgpb0oqfCHuH+L5pHMBQ++PquCdfIgWCeVsJ4/CNbzuiYPtWrl4HYv7pPjiiBUEM1iLIdUPyDW7nS6aLAOOsPz3uBNi9mVcB6MQ5Z4O9Ao8S40JI5N4ezC4cfvbV6qCkc++xnvQB9+6J5Xy29c
*/