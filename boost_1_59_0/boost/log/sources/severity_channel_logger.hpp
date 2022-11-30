/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   severity_channel_logger.hpp
 * \author Andrey Semashev
 * \date   28.02.2008
 *
 * The header contains implementation of a logger with severity level and channel support.
 */

#ifndef BOOST_LOG_SOURCES_SEVERITY_CHANNEL_LOGGER_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_SEVERITY_CHANNEL_LOGGER_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/light_rw_mutex.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

#ifndef BOOST_LOG_DOXYGEN_PASS

#ifdef BOOST_LOG_USE_CHAR

//! Narrow-char logger with severity level and channel support
template< typename LevelT = int, typename ChannelT = std::string >
class severity_channel_logger :
    public basic_composite_logger<
        char,
        severity_channel_logger< LevelT, ChannelT >,
        single_thread_model,
        features<
            severity< LevelT >,
            channel< ChannelT >
        >
    >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(severity_channel_logger)
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Narrow-char thread-safe logger with severity level and channel support
template< typename LevelT = int, typename ChannelT = std::string >
class severity_channel_logger_mt :
    public basic_composite_logger<
        char,
        severity_channel_logger_mt< LevelT, ChannelT >,
        multi_thread_model< boost::log::aux::light_rw_mutex >,
        features<
            severity< LevelT >,
            channel< ChannelT >
        >
    >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(severity_channel_logger_mt)
};

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T

//! Wide-char logger with severity level and channel support
template< typename LevelT = int, typename ChannelT = std::wstring >
class wseverity_channel_logger :
    public basic_composite_logger<
        wchar_t,
        wseverity_channel_logger< LevelT, ChannelT >,
        single_thread_model,
        features<
            severity< LevelT >,
            channel< ChannelT >
        >
    >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(wseverity_channel_logger)
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Wide-char thread-safe logger with severity level and channel support
template< typename LevelT = int, typename ChannelT = std::wstring >
class wseverity_channel_logger_mt :
    public basic_composite_logger<
        wchar_t,
        wseverity_channel_logger_mt< LevelT, ChannelT >,
        multi_thread_model< boost::log::aux::light_rw_mutex >,
        features<
            severity< LevelT >,
            channel< ChannelT >
        >
    >
{
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(wseverity_channel_logger_mt)
};

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif // BOOST_LOG_USE_WCHAR_T

#else // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Narrow-char logger. Functionally equivalent to \c basic_severity_logger and \c basic_channel_logger.
 *
 * See \c severity and \c channel class templates for a more detailed description
 */
template< typename LevelT = int, typename ChannelT = std::string >
class severity_channel_logger :
    public basic_composite_logger<
        char,
        severity_channel_logger< LevelT, ChannelT >,
        single_thread_model,
        features<
            severity< LevelT >,
            channel< ChannelT >
        >
    >
{
public:
    /*!
     * Default constructor
     */
    severity_channel_logger();
    /*!
     * Copy constructor
     */
    severity_channel_logger(severity_channel_logger const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit severity_channel_logger(ArgsT... const& args);
    /*!
     * Assignment operator
     */
    severity_channel_logger& operator= (severity_channel_logger const& that)
    /*!
     * Swaps two loggers
     */
    void swap(severity_channel_logger& that);
};

/*!
 * \brief Narrow-char thread-safe logger. Functionally equivalent to \c basic_severity_logger and \c basic_channel_logger.
 *
 * See \c severity and \c channel class templates for a more detailed description
 */
template< typename LevelT = int, typename ChannelT = std::string >
class severity_channel_logger_mt :
    public basic_composite_logger<
        char,
        severity_channel_logger_mt< LevelT, ChannelT >,
        multi_thread_model< implementation_defined >,
        features<
            severity< LevelT >,
            channel< ChannelT >
        >
    >
{
public:
    /*!
     * Default constructor
     */
    severity_channel_logger_mt();
    /*!
     * Copy constructor
     */
    severity_channel_logger_mt(severity_channel_logger_mt const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit severity_channel_logger_mt(ArgsT... const& args);
    /*!
     * Assignment operator
     */
    severity_channel_logger_mt& operator= (severity_channel_logger_mt const& that)
    /*!
     * Swaps two loggers
     */
    void swap(severity_channel_logger_mt& that);
};

/*!
 * \brief Wide-char logger. Functionally equivalent to \c basic_severity_logger and \c basic_channel_logger.
 *
 * See \c severity and \c channel class templates for a more detailed description
 */
template< typename LevelT = int, typename ChannelT = std::wstring >
class wseverity_channel_logger :
    public basic_composite_logger<
        wchar_t,
        wseverity_channel_logger< LevelT, ChannelT >,
        single_thread_model,
        features<
            severity< LevelT >,
            channel< ChannelT >
        >
    >
{
public:
    /*!
     * Default constructor
     */
    wseverity_channel_logger();
    /*!
     * Copy constructor
     */
    wseverity_channel_logger(wseverity_channel_logger const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit wseverity_channel_logger(ArgsT... const& args);
    /*!
     * Assignment operator
     */
    wseverity_channel_logger& operator= (wseverity_channel_logger const& that)
    /*!
     * Swaps two loggers
     */
    void swap(wseverity_channel_logger& that);
};

/*!
 * \brief Wide-char thread-safe logger. Functionally equivalent to \c basic_severity_logger and \c basic_channel_logger.
 *
 * See \c severity and \c channel class templates for a more detailed description
 */
template< typename LevelT = int, typename ChannelT = std::wstring >
class wseverity_channel_logger_mt :
    public basic_composite_logger<
        wchar_t,
        wseverity_channel_logger_mt< LevelT, ChannelT >,
        multi_thread_model< implementation_defined >,
        features<
            severity< LevelT >,
            channel< ChannelT >
        >
    >
{
public:
    /*!
     * Default constructor
     */
    wseverity_channel_logger_mt();
    /*!
     * Copy constructor
     */
    wseverity_channel_logger_mt(wseverity_channel_logger_mt const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit wseverity_channel_logger_mt(ArgsT... const& args);
    /*!
     * Assignment operator
     */
    wseverity_channel_logger_mt& operator= (wseverity_channel_logger_mt const& that)
    /*!
     * Swaps two loggers
     */
    void swap(wseverity_channel_logger_mt& that);
};

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

//! The macro allows to put a record with a specific channel name into log
#define BOOST_LOG_STREAM_CHANNEL_SEV(logger, chan, lvl)\
    BOOST_LOG_STREAM_WITH_PARAMS((logger), (::boost::log::keywords::channel = (chan))(::boost::log::keywords::severity = (lvl)))

#ifndef BOOST_LOG_NO_SHORTHAND_NAMES

//! An equivalent to BOOST_LOG_STREAM_CHANNEL_SEV(logger, chan, lvl)
#define BOOST_LOG_CHANNEL_SEV(logger, chan, lvl) BOOST_LOG_STREAM_CHANNEL_SEV(logger, chan, lvl)

#endif // BOOST_LOG_NO_SHORTHAND_NAMES

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_SEVERITY_CHANNEL_LOGGER_HPP_INCLUDED_

/* severity_channel_logger.hpp
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
*/