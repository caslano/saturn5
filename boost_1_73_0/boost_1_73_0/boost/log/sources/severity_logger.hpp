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
FD6kszLa4HcplqGYlXQUUPxbIVYqWDB4zoaXV2BOouSknyxNHsAPbtNsnYhwLtBZE/QGtKX4rcQIIjgpSMYiyyXEysEwKlB9sMaHaVZ0MMXIlQjiCG0Pa/QK8qY4jYvYTyD05WKHFa0tNb68HF3071164EB/h/7CN99Av9+/d+D4GHrHPUyGmOvM98Oe4zidjiz8Ig6Qw1QWECz8HAZlKhME/63MCtG3HyRIydXXbCHnqPaVD8OfvZPzyen4nXc2noy8s9Hk3dV76L88OBi8PHj1rWNIzVD7sHwgM3uEsX86PhvBIFq5gMFTYiVgn/GUKWDgKoiByPMsZ4pxhDQxlCZ/e2WQKhziXgQrv1g0uKaATf2lcDp/oFL5Ht1C3JHIf/n7y1e/HuF9NNs7TLsmhRIART65OWEtC3ZWOvMhC8tEnOKhCR0iN0hy4YcPmIyDBBNBSLYbwF3sK8eQHBVhhkrCJM1RBgsEEIqRPYCfML1JWSK2YoEpdS041yJgOle4iK3h5cl4DHfo/uQmmCQoDQE5AWDOkvE8RUdBP5sDsg/HT1kd9rH61KKjuuPfRRb161uOQ6qIoz5heAMH5EF0+brtKJA6WXHI/jzDkgV3fhKHtf52Ya5VipGJJT7LH1SxYZ7BeJUvC3zOX47J
*/