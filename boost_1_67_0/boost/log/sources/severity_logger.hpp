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