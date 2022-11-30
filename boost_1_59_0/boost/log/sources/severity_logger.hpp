/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   severity_logger.hpp
 * \author Andrey Semashev
 * \date   08.03.2007
 *
 * The header contains implementation of a logger with severity level support.
 */

#ifndef BOOST_LOG_SOURCES_SEVERITY_LOGGER_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_SEVERITY_LOGGER_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/light_rw_mutex.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/keywords/severity.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

#ifndef BOOST_LOG_DOXYGEN_PASS

#ifdef BOOST_LOG_USE_CHAR

//! Narrow-char logger with severity level support
template< typename LevelT = int >
class severity_logger :
    public basic_composite_logger<
        char,
        severity_logger< LevelT >,
        single_thread_model,
        features< severity< LevelT > >
    >
{
    typedef typename severity_logger::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(severity_logger)

    explicit severity_logger(LevelT level) : base_type(keywords::severity = level)
    {
    }
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Narrow-char thread-safe logger with severity level support
template< typename LevelT = int >
class severity_logger_mt :
    public basic_composite_logger<
        char,
        severity_logger_mt< LevelT >,
        multi_thread_model< boost::log::aux::light_rw_mutex >,
        features< severity< LevelT > >
    >
{
    typedef typename severity_logger_mt::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(severity_logger_mt)

    explicit severity_logger_mt(LevelT level) : base_type(keywords::severity = level)
    {
    }
};

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif

#ifdef BOOST_LOG_USE_WCHAR_T

//! Wide-char logger with severity level support
template< typename LevelT = int >
class wseverity_logger :
    public basic_composite_logger<
        wchar_t,
        wseverity_logger< LevelT >,
        single_thread_model,
        features< severity< LevelT > >
    >
{
    typedef typename wseverity_logger::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(wseverity_logger)

    explicit wseverity_logger(LevelT level) : base_type(keywords::severity = level)
    {
    }
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Wide-char thread-safe logger with severity level support
template< typename LevelT = int >
class wseverity_logger_mt :
    public basic_composite_logger<
        wchar_t,
        wseverity_logger_mt< LevelT >,
        multi_thread_model< boost::log::aux::light_rw_mutex >,
        features< severity< LevelT > >
    >
{
    typedef typename wseverity_logger_mt::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(wseverity_logger_mt)

    explicit wseverity_logger_mt(LevelT level) : base_type(keywords::severity = level)
    {
    }
};

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif

#else // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Narrow-char logger. Functionally equivalent to \c basic_severity_logger.
 *
 * See \c severity class template for a more detailed description
 */
template< typename LevelT = int >
class severity_logger :
    public basic_composite_logger<
        char,
        severity_logger< LevelT >,
        single_thread_model,
        features< severity< LevelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    severity_logger();
    /*!
     * Copy constructor
     */
    severity_logger(severity_logger const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit severity_logger(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified default severity level
     *
     * \param level The default severity level
     */
    explicit severity_logger(LevelT level);
    /*!
     * Assignment operator
     */
    severity_logger& operator= (severity_logger const& that)
    /*!
     * Swaps two loggers
     */
    void swap(severity_logger& that);
};

/*!
 * \brief Narrow-char thread-safe logger. Functionally equivalent to \c basic_severity_logger.
 *
 * See \c severity class template for a more detailed description
 */
template< typename LevelT = int >
class severity_logger_mt :
    public basic_composite_logger<
        char,
        severity_logger_mt< LevelT >,
        multi_thread_model< implementation_defined >,
        features< severity< LevelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    severity_logger_mt();
    /*!
     * Copy constructor
     */
    severity_logger_mt(severity_logger_mt const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit severity_logger_mt(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified default severity level
     *
     * \param level The default severity level
     */
    explicit severity_logger_mt(LevelT level);
    /*!
     * Assignment operator
     */
    severity_logger_mt& operator= (severity_logger_mt const& that)
    /*!
     * Swaps two loggers
     */
    void swap(severity_logger_mt& that);
};

/*!
 * \brief Wide-char logger. Functionally equivalent to \c basic_severity_logger.
 *
 * See \c severity class template for a more detailed description
 */
template< typename LevelT = int >
class wseverity_logger :
    public basic_composite_logger<
        wchar_t,
        wseverity_logger< LevelT >,
        single_thread_model,
        features< severity< LevelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    wseverity_logger();
    /*!
     * Copy constructor
     */
    wseverity_logger(wseverity_logger const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit wseverity_logger(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified default severity level
     *
     * \param level The default severity level
     */
    explicit wseverity_logger(LevelT level);
    /*!
     * Assignment operator
     */
    wseverity_logger& operator= (wseverity_logger const& that)
    /*!
     * Swaps two loggers
     */
    void swap(wseverity_logger& that);
};

/*!
 * \brief Wide-char thread-safe logger. Functionally equivalent to \c basic_severity_logger.
 *
 * See \c severity class template for a more detailed description
 */
template< typename LevelT = int >
class wseverity_logger_mt :
    public basic_composite_logger<
        wchar_t,
        wseverity_logger_mt< LevelT >,
        multi_thread_model< implementation_defined >,
        features< severity< LevelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    wseverity_logger_mt();
    /*!
     * Copy constructor
     */
    wseverity_logger_mt(wseverity_logger_mt const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit wseverity_logger_mt(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified default severity level
     *
     * \param level The default severity level
     */
    explicit wseverity_logger_mt(LevelT level);
    /*!
     * Assignment operator
     */
    wseverity_logger_mt& operator= (wseverity_logger_mt const& that)
    /*!
     * Swaps two loggers
     */
    void swap(wseverity_logger_mt& that);
};

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_SEVERITY_LOGGER_HPP_INCLUDED_

/* severity_logger.hpp
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
*/