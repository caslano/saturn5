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
80N6xVO2IUMlYeTbT6US8/Rke2++uVFV4unuM+zc9FjttEZ8GqoWIVsd0zwdIqYB13Cxpx3p/FuumVJJ33uzmMOyPBvGUz3Qv375C7vqDKY9dkHJd5qFysrVmss6nlnMHrIywzIQSkL6LSH9dy4qPEKWdajHAjOJl8acw6U47SFJ2c3fUmpIF+wM7hbycvC8RDZLGiR+KdRnD9UPT9sPpCpf7qs3RFPpHeMx5gmykvsCjb93C5lhZg85eTHRVCN7cS1OANMF683Y2U6EydJKxUnGDvzAYfKff8A5TYveZWssZl8I8VBKlfTG92oGECKt9Ol+ALzd6xaTf/a4PtZtEnvCeLwnUbqW8lO+oRArHvPVjCF0QxjRVqP5d30NaEaReV983leOV72LGhB4dekW74WXvasOJDW5R9Szl61ak4ytCn42mH4+M1oF+LOd8GcF+POd8OcF+O93wn+v33TTf1fi6sLWH6lLS2Sg8bO+XBXk2zitGv3Q+tQAnELJGle2VqGspxWh3U8vc9rd7HLbBr2t9S13+CuKXnD9Rxfw31BLAwQKAAAACAAtZ0pSmL+AIx8DAADICAAAHwAJAGN1cmwtbWFzdGVyL3NyYy90b29sX3BhcmFtaGxwLmhVVAUAAbZIJGCtVm1v2jAQ
*/