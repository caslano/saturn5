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
jx7x/WaItnneMqTlx5QVLVNh5SdNzbxlyNirU2oWZo94Y8ZzGf+MGW69Z1z9emcv2c9YKv+sLPsZVOWfyTRIzsrqvOfhzt8XVXVueTP/vtjqt88o/4wu+9lXx35m1bGe6WU/4+rYz9ayn2X1650N9mudcfV9abspcwxb4bcovZtX9xTK+xiy8Lt5o2jQpJ7AKFgHpsFmMB0mwT6wHhwPG8CpsCGUdUtwEWwCz4BN4TnqPnSGzw4NP1vD957h81CAM3zgYzAWPg5T4E7YSfU94NMwCz4D+8Mn4CDVfw1zQnvW9P1za8RdshcTn/rwcpgBr4A94FVwGLwGngTX6/OgF3+3urqfSvaNoYcZh+Xy66B3r2fCOrALbAaPh63hGtgB9oLdYW84XM1HwSw4AfaFs2F/mA8Hw9PhEHgFHApvhsPgrXA4vA+OgA/D0XAvHAtfhyfCD+AE6BLXiTAKToK14WjYAubCTDgNngDzYBacCrPhdDgKDoEnwVNgIZwDz4Bz4dlwHrwQLoCXw0J4JVwIb4SL4FZYDLfBxXAnXA5fhKfCP8HT4EfwdHgAngF/VPvVfIQPE+BqmAzPhq3gGlPedI8LnG4pbz/oneg+P+UN+mEDGIDJsArMhNXgWBgLJ8M4mAfj4ddwQmgfBRin4VRFDdNwFmHPB5drOKeq/6fBTnAlHARXwxx4NjwRrvHcCV6o/m9Q/82d4HqXvB8+DmvBXTAdPgOz4LNwMHwBToe74enwJXgJfBmuh3s1vAdC67t1PfxW7au3obx30K+HKXAD7AzvhsfBq2BfuBFOVPOT4TXwFPg7uBxer+HfBK+Bm+ANcDO8E26BT8Kt8A8qfwtugwfhnfAQvAtWcwlH41/Pp2uIpVHDPeiDitE94ul6l3lX2Ah2h8fBnnAI7AXzYB+4HPaDl8MBcDPMhvfDQrgTLoTPwyL4IiyBf4FL4XdwCYwOlm9YDZ4Km8DTYCt4OuwIz4Cd4UqYBVfB/vBMOAmeDWfDNTAfngNL4Fq4El4Ir4aXwevg5fANeAX8E1wPP4BXwZo+8ge2g7+DXeG1cCS8EE6EN8Ap8EY4G26CC+FWuAxuh6fBO+AqeA+8Cd4Ln4L3wz/AB+FMP3r4MHwgaA6D5s0CmMMcGDSfCIPmRfBhuBI+Ci+Ej8Nr4E54A3wCboFPwSfgLvgC3A0/h6/Db+Hv4U+QuGh91bVmcLSlvu7TduEjGAs/hsnwE9gJfg77wb/BYXA/HAW/glpfdb2Tvb5ynqHU13dgLfi+9q8fwiz4ERwMP4XT4cfa/n8BL4FfwvXwr9rO9XFD608k7yW8Fof7Iflt0n57M8yG27V/2wvnwh2wAN4Jz4T3wIvgvfB6+CC8HT4EX1H9m6r/XvUELvpY+AjsDR+FA+BjcAx8HBbBJ+Bq+CR8Rs2fg7vgHjV/TfVvqP4j1X+m+r+q/ivV/6j6aB96WAsG9Z3gI3Aw3A1HQsKScvwSXA73Qs03nXenrljy7dQA+QZPg7XgKpgOz9L3kdVwMFwL8+DZ8DR4PlwHL4BXwAv1PeVNV+dvdX57K+yK2qP5Vht7NWB92BQ2hB1hI5gJF8JusAkcAFPgUNgUngibwVkwFebDlvAc2AZugG3hZtgObocF8G5YCB9T/5+EneALMB3ug53hd5AuSdqzLrAx7Appv0SeDXPhyXAaLIDT4Wo4A14HCyBlUsLbARfCe2Av+BDsDXfBPvD3MAvug/3hD3AgjCf/smF9OBh2hENhHzgMjoUjYD7MgRfA0fBGOBY+pvafhxPgZ3Ai/BFOgol+4gkbwULYCi6E7eBsmK3yESqfqHJTngaWX57q+ihPMAnWgo1gOkyGWbAJHAxTYR4=
*/