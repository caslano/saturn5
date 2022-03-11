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