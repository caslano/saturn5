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
kbq1l6MEmNRF1puad4PWoq9i9q9ni/tvPHvCS0wZvE5kV4Z/92p6PCeyXNXjr4bTnfJWU9cP8w7BfnHZO27aI745pCxugU8guxluOoY94m26/OtlsaLt0tb6pYunaoCfCOyx4LtJlzJlcU5+Rd5NulSsHJa1V2jeZ5t0lXTnXXKgyadfxH6B/f2ly5H7pOtFPsVaLtWtt2yY8vyayB4y/vws8Uow5SO2m4wvmPfn2T2Cer8pL/1E7pNy+Anl8E/i382B8srxeNybcmz8ixH3X+B+g7j/NFAa1+nm3fbr47XMa1yTJOzo0rIs8iTVq98at734/aT4/ZjH7zzjtyt+NTfv9DeIXx3Nt9eFon/LX4cTycukBf7vwf/t4v9rHv8XG/8PatxDcf0cu3rPMHJqgqR7PzfVuZ39Cpi4vcxzzJFwXAnnbcL5WtxeFPDcyz6j0JPGfcSvJHMX8E0S9o3+M2n3LvTN4qzNbib9x4vdqNLvye6yLt6t6qS5wfB2E94Wcf9Hv23cbK7IEk25zhT/fkeOnmTavTkaRujZB0han+mG9iysET9qmbuG48T+c4zYdOU2whJ5jnomjeb6M/H/O26qqe4/Xr553ySOIuN06Kq+9WZ9KOkv6ZKscT1Xwm3i+mkFGmDaA+YQTuhb7EeJR46/LmYz3fVue38Ns6/ia0mXAK68cZzhj3XuwvbT7qW+HOdjX5Hk0QOH+Ilfq/yl9aBELuFM1jTpI/I2gVf55r/EDXCvyJ2cYd1G3O/C+QCR9yitR7retpmWz3dFvsDflxGxB1kDHu+7w/mA00la+luV3iMudlY4naj5+VpPanvqnK2ePELY4zVupWEvJu6l62a/k2cfQbql2doBGScaI3508JTREsmLRK27C0T+o3+dm8KZqGdqnQ7FpY74sw9/Foq9WI8/040/8bCFhHsOcQlw7uYQU+Y+FfMepszt0zLWLKy++f3e+taPnUg3+nLMuMxfD6effw6roqq4w3zBOO0kTh+K+TV+z33D6Y7nDJozxe94x8c/j500773BqWLnakZf23rslKR5950liJ2nGOGoyfnzjdSe2RNl2vAWh5/F60+6917LSSJv5JXP994/H9dD283SsiqFLZR2NUXemtSdhH19B4hQDVMPvyts0n1GKMYdjJJ7z/aivO8I2Ud5R5jX4599RyjUu7DLfz8tbujIb7R+t45CvRwcr+xpeSeo4Hcrbm3fotZ3A+xGvmPa+n3sHbnff0bkQ2z9Pm6P/C36hsi7lvstulvkg63foknHMB7hP6Gi36KSXp5xJkteWt7vVja2f3emnVAmLxeUzD96PqadULH3u7QTKvbdmXZCxb47006o+Hcndo/43dnthCN/dw494cjfnZNEbv3u5F3/2L47bz/hn63Hx/7duauZrnv1secLLofB78791rJQpl6b/iulV9D+dF+ova4m+nGM3NS139NctsyY98Lm4jbX10DTvpHoJ/k60EfcwYzFMHerpXzZ/Mwz77KtxY+TTPz8vWVcyW1CT5YQej8WO6eyrj7OWi7xP7INMv1ue3E73hd6r6sp+tG0FnWtZXe/veya74I0cT/GF3qfThD9iewsjrWWb69/n7UkPXSeJcHpR3x07bA8c6yY1dZ8eFHMqopZkqbjfWJWU8zq6bP/rbfZdybfHeV9r4zsE/69MrWP3u+s70pd5TmG+l5xxrul/evSNMdT12ZLWLmR39/yzANE9r6pt5eKf8u9czJmvjZK7J7k9lH7dUx8XPPuVi1oh7iUfoMsMu8Jp4jf8b7SZ10um3FDcTld5OeU9ds81zLzXPEwvbd+0+h3Qorop3vTId275zZf5JnU14DXT2MnHvY=
*/