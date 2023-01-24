/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   logger.hpp
 * \author Andrey Semashev
 * \date   08.03.2007
 *
 * The header contains implementation of a simplistic logger with no features.
 */

#ifndef BOOST_LOG_SOURCES_LOGGER_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_LOGGER_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/threading_models.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/light_rw_mutex.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

#ifdef BOOST_LOG_USE_CHAR

/*!
 * \brief Narrow-char logger. Functionally equivalent to \c basic_logger.
 *
 * See \c basic_logger class template for a more detailed description.
 */
class logger :
    public basic_composite_logger< char, logger, single_thread_model, features< > >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(logger)
};

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 * \brief Narrow-char thread-safe logger. Functionally equivalent to \c basic_logger.
 *
 * See \c basic_logger class template for a more detailed description.
 */
class logger_mt :
    public basic_composite_logger< char, logger_mt, multi_thread_model< boost::log::aux::light_rw_mutex >, features< > >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(logger_mt)
};

#endif // !defined(BOOST_LOG_NO_THREADS)
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T

/*!
 * \brief Wide-char logger. Functionally equivalent to \c basic_logger.
 *
 * See \c basic_logger class template for a more detailed description.
 */
class wlogger :
    public basic_composite_logger< wchar_t, wlogger, single_thread_model, features< > >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(wlogger)
};

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 * \brief Wide-char thread-safe logger. Functionally equivalent to \c basic_logger.
 *
 * See \c basic_logger class template for a more detailed description.
 */
class wlogger_mt :
    public basic_composite_logger< wchar_t, wlogger_mt, multi_thread_model< boost::log::aux::light_rw_mutex >, features< > >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS(wlogger_mt)
};

#endif // !defined(BOOST_LOG_NO_THREADS)
#endif // BOOST_LOG_USE_WCHAR_T

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_LOGGER_HPP_INCLUDED_

/* logger.hpp
YZcqBGMrCkKYX/GiO7iGVSa/M2l9+viVm+2JIadxfJoRuMAFnSn3q02MCHGLwU62VT24O0+vRWyJGYgDdrHBd3mLGX1i1QRAwtHtjiKOE8o5z2YjTUufG52iazHiglR+ZK/VxJY9f14hi/c9Ypgvu0WXQfWOLv8ibOR6cvoz8Oll8bmYLZ9pHM1lrEDm5vVuIxrdei7wsFDhPY0ohdY6Qxn3Wy4jG6llDQAIpDKxsxPnE66tRv5+3vsfyz35e8XoujMYWuhC6LGtAuKbyjnhyQa5TaHV1vCHR3ru+SOzjFBBZtFLIS0dxtwlx17BbZyjYybyZPpyc8krsxMhRfGc2CfiJxkqM9nIsorkcxehEpa1j0JjVbPak3cdEmZUCAqVuPnhZ2agwP7AaSIMbNoUGkzXJ84tyA0kaRMk5LGzaAhfwCX+4vD6WjRdEw0nVqse3c0uc7KfrMVKkLB4YtnovOnPmQiSG4Pbwy6npUStvz6I/OOQy559ab9Gd8vj9zJTAc/HJV/+fL1G9Cwf6OqZ4eE7gCUoJsCFOX06OiiaVzB7yr68tmB9KOZsdFpSBpMvQGx8kXM99eLo56BT9oeZ0CtZrlqFQP42Pqrk3wl/SGUcmpJTh0Pa9pFgZqhLRdY57GQLv4TvvnhL8ZL7krkbHYmDxEBGnQF2sKcau3E39/vEGrEFB7sureF+cX3v4NiPJKEY2VsS/lIXBU8o
*/