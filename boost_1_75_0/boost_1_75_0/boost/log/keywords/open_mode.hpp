/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/open_mode.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c open_mode keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass log file opening parameters to the rotating file stream methods
BOOST_PARAMETER_KEYWORD(tag, open_mode)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_OPEN_MODE_HPP_INCLUDED_

/* open_mode.hpp
WyW4/EslWpuOrEolNH5mhGUoySkyBZSbRpWQlZCW+AL7J86/0eW+0VykTk8YdkM8+lnns2bVkJ6dWzbtctIYfRd+SfcO2o95UUMU50LZQ11wJv9wOt1knUiennS2q7UQetnu6YDjn3BhQrYs0xLpaL62QlOVyH8BnkVgMj9b0TbpjmhtYNJukABi8RSmaNWF632m2b/jUKwdVhFYqvd04GM2xa1j/WZdJ2xM9y7+B5uV/YqkAxGz2YED11r5Eztf2IFGesavT/nqx24lIBe5WiLBJgz92WDdko0l1rqX6usPlGlZ3Np9D40hVZkL9VZe2TkWooQm1F5ROaZHemLMf0hbkqDPL0drfGkj8zNGf8Pe1NgTqaLeSFBWusxkGRrB+lX9Trhy5rDMx+txOlnRDiQmooR3nSGmrux5zmBvssESc4b3QCs0PsXBLrXZ37GMX0XJXIyBoeYnJnOea09x3PVDS8zeInxFepHeBb2ara70K9Hy0cdNiXTaSN9cy/OUa9vu3/bygHsa6nT/8as5vT+C80KDxXhA1+sQWTERIcObRcXPHi5bVzARMfatmlF3f2AuXHiU6409WbgflLPfGuScDKW8ph51Rsz6ASWcHtlfAUWM3sGd6MBv7F+ec7Y5k7fQjC2S4JXfgCo+IaPOmADr206JdjrwJrMxwODmgqpnfP0kx47lqNpnnlKlLFBlwkMOyLe9heJXLTUW
*/