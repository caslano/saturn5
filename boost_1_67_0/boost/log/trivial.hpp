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
 * This tag can be used to acquire the logger that is used with lrivial logging macros.
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