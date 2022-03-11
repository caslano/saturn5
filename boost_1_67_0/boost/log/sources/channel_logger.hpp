/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   channel_logger.hpp
 * \author Andrey Semashev
 * \date   28.02.2008
 *
 * The header contains implementation of a logger with channel support.
 */

#ifndef BOOST_LOG_SOURCES_CHANNEL_LOGGER_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_CHANNEL_LOGGER_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/detail/light_rw_mutex.hpp>
#endif // !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/keywords/channel.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

#ifndef BOOST_LOG_DOXYGEN_PASS

#ifdef BOOST_LOG_USE_CHAR

//! Narrow-char logger with channel support
template< typename ChannelT = std::string >
class channel_logger :
    public basic_composite_logger<
        char,
        channel_logger< ChannelT >,
        single_thread_model,
        features< channel< ChannelT > >
    >
{
    typedef typename channel_logger::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(channel_logger)

    explicit channel_logger(ChannelT const& channel) : base_type(keywords::channel = channel)
    {
    }
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Narrow-char thread-safe logger with channel support
template< typename ChannelT = std::string >
class channel_logger_mt :
    public basic_composite_logger<
        char,
        channel_logger_mt< ChannelT >,
        multi_thread_model< boost::log::aux::light_rw_mutex >,
        features< channel< ChannelT > >
    >
{
    typedef typename channel_logger_mt::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(channel_logger_mt)

    explicit channel_logger_mt(ChannelT const& channel) : base_type(keywords::channel = channel)
    {
    }
};

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T

//! Wide-char logger with channel support
template< typename ChannelT = std::wstring >
class wchannel_logger :
    public basic_composite_logger<
        wchar_t,
        wchannel_logger< ChannelT >,
        single_thread_model,
        features< channel< ChannelT > >
    >
{
    typedef typename wchannel_logger::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(wchannel_logger)

    explicit wchannel_logger(ChannelT const& channel) : base_type(keywords::channel = channel)
    {
    }
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Wide-char thread-safe logger with channel support
template< typename ChannelT = std::wstring >
class wchannel_logger_mt :
    public basic_composite_logger<
        wchar_t,
        wchannel_logger< ChannelT >,
        multi_thread_model< boost::log::aux::light_rw_mutex >,
        features< channel< ChannelT > >
    >
{
    typedef typename wchannel_logger_mt::logger_base base_type;

public:
    BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(wchannel_logger_mt)

    explicit wchannel_logger_mt(ChannelT const& channel) : base_type(keywords::channel = channel)
    {
    }
};

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif // BOOST_LOG_USE_WCHAR_T

#else // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Narrow-char logger. Functionally equivalent to \c basic_channel_logger.
 *
 * See \c channel class template for a more detailed description
 */
template< typename ChannelT = std::string >
class channel_logger :
    public basic_composite_logger<
        char,
        channel_logger< ChannelT >,
        single_thread_model,
        features< channel< ChannelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    channel_logger();
    /*!
     * Copy constructor
     */
    channel_logger(channel_logger const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit channel_logger(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified channel name
     *
     * \param channel The channel name
     */
    explicit channel_logger(ChannelT const& channel);
    /*!
     * Assignment operator
     */
    channel_logger& operator= (channel_logger const& that)
    /*!
     * Swaps two loggers
     */
    void swap(channel_logger& that);
};

/*!
 * \brief Narrow-char thread-safe logger. Functionally equivalent to \c basic_channel_logger.
 *
 * See \c channel class template for a more detailed description
 */
template< typename ChannelT = std::string >
class channel_logger_mt :
    public basic_composite_logger<
        char,
        channel_logger_mt< ChannelT >,
        multi_thread_model< implementation_defined >,
        features< channel< ChannelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    channel_logger_mt();
    /*!
     * Copy constructor
     */
    channel_logger_mt(channel_logger_mt const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit channel_logger_mt(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified channel name
     *
     * \param channel The channel name
     */
    explicit channel_logger_mt(ChannelT const& channel);
    /*!
     * Assignment operator
     */
    channel_logger_mt& operator= (channel_logger_mt const& that)
    /*!
     * Swaps two loggers
     */
    void swap(channel_logger_mt& that);
};

/*!
 * \brief Wide-char logger. Functionally equivalent to \c basic_channel_logger.
 *
 * See \c channel class template for a more detailed description
 */
template< typename ChannelT = std::wstring >
class wchannel_logger :
    public basic_composite_logger<
        wchar_t,
        wchannel_logger< ChannelT >,
        single_thread_model,
        features< channel< ChannelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    wchannel_logger();
    /*!
     * Copy constructor
     */
    wchannel_logger(wchannel_logger const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit wchannel_logger(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified channel name
     *
     * \param channel The channel name
     */
    explicit wchannel_logger(ChannelT const& channel);
    /*!
     * Assignment operator
     */
    wchannel_logger& operator= (wchannel_logger const& that)
    /*!
     * Swaps two loggers
     */
    void swap(wchannel_logger& that);
};

/*!
 * \brief Wide-char thread-safe logger. Functionally equivalent to \c basic_channel_logger.
 *
 * See \c channel class template for a more detailed description
 */
template< typename ChannelT = std::wstring >
class wchannel_logger_mt :
    public basic_composite_logger<
        wchar_t,
        wchannel_logger< ChannelT >,
        multi_thread_model< implementation_defined >,
        features< channel< ChannelT > >
    >
{
public:
    /*!
     * Default constructor
     */
    wchannel_logger_mt();
    /*!
     * Copy constructor
     */
    wchannel_logger_mt(wchannel_logger_mt const& that);
    /*!
     * Constructor with named arguments
     */
    template< typename... ArgsT >
    explicit wchannel_logger_mt(ArgsT... const& args);
    /*!
     * The constructor creates the logger with the specified channel name
     *
     * \param channel The channel name
     */
    explicit wchannel_logger_mt(ChannelT const& channel);
    /*!
     * Assignment operator
     */
    wchannel_logger_mt& operator= (wchannel_logger_mt const& that)
    /*!
     * Swaps two loggers
     */
    void swap(wchannel_logger_mt& that);
};

#endif // BOOST_LOG_DOXYGEN_PASS

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_CHANNEL_LOGGER_HPP_INCLUDED_

/* channel_logger.hpp
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
*/