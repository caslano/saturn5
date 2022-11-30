/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   log/trivial.hpp
 * \author Andrey Semashev
 * \date   07.11.2009
 *
 * This header defines tools for trivial logging support
 */

#ifndef BOOST_LOG_TRIVIAL_HPP_INCLUDED_
#define BOOST_LOG_TRIVIAL_HPP_INCLUDED_

#include <cstddef>
#include <iosfwd>
#include <ostream>
#include <boost/log/detail/config.hpp>
#include <boost/log/keywords/severity.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_LOG_USE_CHAR)
#error Boost.Log: Trivial logging is available for narrow-character builds only. Use advanced initialization routines to setup wide-character logging.
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace trivial {

//! Trivial severity levels
enum severity_level
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

//! Returns stringized enumeration value or \c NULL, if the value is not valid
template< typename CharT >
BOOST_LOG_API const CharT* to_string(severity_level lvl);

//! Returns stringized enumeration value or \c NULL, if the value is not valid
inline const char* to_string(severity_level lvl)
{
    return boost::log::trivial::to_string< char >(lvl);
}

//! Parses enumeration value from string and returns \c true on success and \c false otherwise
template< typename CharT >
BOOST_LOG_API bool from_string(const CharT* str, std::size_t len, severity_level& lvl);

//! Outputs stringized representation of the severity level to the stream
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    const CharT* str = boost::log::trivial::to_string< CharT >(lvl);
    if (BOOST_LIKELY(!!str))
        strm << str;
    else
        strm << static_cast< int >(lvl);
    return strm;
}

//! Reads stringized representation of the severity level from the stream
template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_istream< CharT, TraitsT >& operator>> (
    std::basic_istream< CharT, TraitsT >& strm, severity_level& lvl);

//! Trivial logger type
#if !defined(BOOST_LOG_NO_THREADS)
typedef sources::severity_logger_mt< severity_level > logger_type;
#else
typedef sources::severity_logger< severity_level > logger_type;
#endif

/*!
 * \brief Trivial logger tag
 *
 * This tag can be used to acquire the logger that is used with trivial logging macros.
 * This may be useful when the logger is used with other macros which require a logger.
 */
struct logger
{
    //! Logger type
    typedef trivial::logger_type logger_type;

    /*!
     * Returns a reference to the trivial logger instance
     */
    static BOOST_LOG_API logger_type& get();

    // Implementation details - never use these
#if !defined(BOOST_LOG_DOXYGEN_PASS)
    enum registration_line_t { registration_line = __LINE__ };
    static const char* registration_file() { return __FILE__; }
    static BOOST_LOG_API logger_type construct_logger();
#endif
};

/*!
 * The macro is used to initiate logging. The \c lvl argument of the macro specifies one of the following
 * severity levels: \c trace, \c debug, \c info, \c warning, \c error or \c fatal (see \c severity_level enum).
 * Following the macro, there may be a streaming expression that composes the record message string. For example:
 *
 * \code
 * BOOST_LOG_TRIVIAL(info) << "Hello, world!";
 * \endcode
 */
#define BOOST_LOG_TRIVIAL(lvl)\
    BOOST_LOG_STREAM_WITH_PARAMS(::boost::log::trivial::logger::get(),\
        (::boost::log::keywords::severity = ::boost::log::trivial::lvl))

} // namespace trivial

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_EXPRESSIONS_KEYWORD_HPP_INCLUDED_)
#include <boost/log/detail/trivial_keyword.hpp>
#endif

#endif // BOOST_LOG_TRIVIAL_HPP_INCLUDED_

/* trivial.hpp
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
*/