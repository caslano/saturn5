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
mvuxAnNGK79mhchEBa6hadtOLpRvSci3MFLtc3DCCm0eGuSO3xqzZhop8Zzl9MHW2LvO0J4Qv0uc07DVdkh9nbr1d/+7SnKfOo+n14H4eA/A34ZCLS+RQmq87V8v7vrJE9T0l6Zlj2Q8DjjX3FfHX3VQoc+DgyYdiKhJtQU9D7U8D4m7Fdb6IozgeZ1ZZ/yV2BWQ1jbOENTZqJH0ka6USxxpetTXRzrE9KZbhLWKjY7kHSusDaSztDFmDBY8x8xYxbhu7qs+LOHPdeJp7emos1Dy3qVx9CGOJTiM9UZ/rmdswPnEfrrf5C9k1K+zeLYVBZehzCys6S0St5NIb4yTihqOspQpYTbvmStrfjKGx8Z/tZccsiDtUp8BeTjQz94e95s81BQXrqou1mYpawbp+NmDYvwmtb7xOzmkdYt4+FKRab915R9Cm/WnNXNA/Xu+jIKou5JpN8UBaS2tvUDHGzNeTDNjZQdxm2Of1xQHjzMzTLrPE7uoRvf41K/tG87iv1TsY8zzt1b0Xte4T9rFC/1Y+0qauJmDq1jZt0lBDUDpXiFhNO+dqG48mhY0Ps0IGBfWDnR05CT/qNU6nm91lbGIuDr29ZQnxV0We0JhtjImnNDG8mB3lKCZT9wndrNpRV6X/flmbnij2K+UuhoXEMYKUx+/FjfJZq3r7tTQ99IbG+fd5Zg9qOE6zIkhtOFlphwD1mEiG1+HwU9oZZa5rMkxIjAfIazDDB9c57G7BpCm+ch258O8JAe0CVPWU8Rtsl0GoEHeCqx5w515V5pA2R5DyTgeHuM0Zxy3111BQJ4P6kvi5aho1EbUVNZzqlx5tq89cQ+I6/shtcsaXdchrOB3ExEpN35vxh5bS1nY/IpIu/H7mPq1yJhY/AZ+8+SXYt/Vem5a/TY5HwpcL5MyCZxbSl6D5E40DwnuvSdNm7tfHRnS8M6iAhKYttzUja612cenDHF3mtPZPtfUcDyuZ/UaMw+fJHadrXWCP7NOfIj2s5t0/qYH/d4T0485TAxhm7HmDcylzX7OeSXpMu/3Zr9jWJ3HCzQ9a1HTfG3WlIvslAf2Tx0vV4mbGt0H9/tJMvkzZkH72D20zVwtdkuIN1L2h7ugMlAT7e3XhJVoxmUZB32y2nkF2o4T4fXi7sygd6MiLhWq3xe7TNycru9Gxo3Z47tY7Asafb9KghvETWGQG8Y01zvYteJmhDXN+a6+d6G4izPp+57oO5qy3VSXns/9rEHfYLyaNsKc45ZfN/1+VlyJ1j35dX0SpMl7iuJKQrsPA3cn/X5SstiH28Yh/IZ+X4O6Nf1ne0rosob63vqFvnPl72NzdAF9rJ7rzRZZImjKeZUIE7nKzbTDKeKmnf0Z2KC8C0z7mSB2ibbyN/6CvtFk4lwg9tGqp4drfdj2u2eIXWvzPjxP9P153nvNnHW1mKEXN0ZvlTlqD4vFviv2EWpGzjQ/YZg2Jm+0XNwkyX1WYmb8dcAk1pXfgir3HvkizYMlrmbvL1r2ls0z6DVtB5F1kLYwIIP1a9MOVueXrSr2LYM32U4TnVhZMz7yqEMcRfm1+T5vYi7fizwq5iLvJBYB52BGN9zX+Rnp2GfSsaa0tkQnmQHfzCsqrpF+qvJk4n6wfQ/Q1ja1jTwsdt1sbRN/wfMMSYZtLMBtaPPWwG8oSR6C6ylwTqFxuutu3+ggWXLdK3ZKtcxkETyveK1jn8uGlzbajwkjtHxY92/1W3o5+iK+VcoRqnxzWl366oXBLbILiZj1EndXOeeRouVOhC2dhNW4jHM8vE/svUYeYrroC51hzOHzMLfOf0qtss/mnWyo2H/FOYd/86zyzyYM9/hk1gnHiV2FM4Y8TXU=
*/