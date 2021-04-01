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
kt/iYtE8EP30gFDmKsKA1yE+u9s93SDdVednjyJNUZQTB8apd0Lf8IKzLzg9FMzhp/u4uK8xC1/w2zDcm7P32tKhamzhyr/x12oe61UqpraB8VJECnq0uzMzVO3gvUNo+odbhf2B4cQvsgkj4t5O8IlS2Yz9jspJLu+r44rSaeuV2/YFmo66WWTWgBwgL0s0hAWg5ARiLrwY+1UdLvVKb9m/Gc/LnsJeZXMGXpOy+w4Ln6iF2T0JsR9vd+lRIQqy2h86dvUV3a2fYvsN9G6EK1XvfR2A+k54kvmIHpb+pFq/se0VfrsaRNGnzvZrvwbD8mAy/TnqNKSHSnK7efapEA9eSjxKhfwJsWkSFuzkuiJf+gzkK8PEd2MkkDYwKzXb1ZucbHtu0MVG9ETSLEvXzS0Cps5VszM4G53AAVFNqp9bxQ7aTUj6owlxRZFyINNTaIvbufVceq5msMSarjK9xwRpxhbECGpUUUDWZ4naIEOQcCAfHXpdxzSeCn8raI6M3slJA7TBNRTOKMbSea2HgZs7jrALNRfFjH0MxeroxDsAk/0RLcb1qwGYmA==
*/