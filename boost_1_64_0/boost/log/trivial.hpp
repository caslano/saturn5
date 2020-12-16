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
+TKzUuenu25tr+xkMlOXby3mM4xx9/vVrfgbVLeeNU3Gml3xahlV+fz+aygn213xKk7xT7ALdY7J9mnVqy/dc0z0PvqG8HWx6/5K4VMT/STtQwvj7tMUxrnRlcPYN5WwG8KoJhzaQQwxHUu/ZxgD+RxRp3IY/2C3Me4w0s4sWZU7b+nyxSGF79BpCt9OQ/gesudcVgpfwZI5/lY+pPCVfc/wBfpV6TGu8Em/qtwdvmqErfw0hW2fNJYpVsXc6NJU/pvuDBv2UmevnOcud475MBFKv54xrLil26j+/vnNFBHDXEGX7ldqrlcRHhvnCKIb+nkRoqvn57yeEHp9SHwr9ceIB/dUPPTZfISXeyq8xnMgnG1my7p6frD61UGyUykrQemuFhPoMMeHcEaBqltcc/vHSrs8BnkEPzLcfuTOXuM/2jJ3Sf7iAkefdknhXHP5w42q+x3TlXm6lcT/8ZwZl0h8DyN/TSDvavtiw6Od8Qo+U/2dBLtvcuo2ukFQm0xYpQ93ufKb8WrXeQiPn2FJr8GS/aK4Z7cHQemxdE5xKnlteA+ID5w3pPTnqPOlRnmdNeRIn2OqHFMsHP26D5R5Mm6Gmd8ZprvP1VALbM1rm6rxHGhdx/n1ryacuh9Y1bsJ8eOeip88C7IuWMJsehac+RIrc+YH+8H4LGGyz7af4c4Xu5mu1DfSc5aHKf0epvzALWN+mNIe3dDTXnSlLH/3flaoaWmX7wuUn6x3c50b9E39yudmPIVOiTMdg86hYG5oiO+7uGEqY+Y1PK40adq6umniLF/e5eYbmex+QN0nrsjT9vMcHF/KjGq8TN8r1LN4n9IvtdKI6S7zexZumtolY/zRde8hgKrznWymbV7A/I5auoxZkr+B9nS+0qmvz+r4XLm5jLkezfSc09FKJ050fNZRpbOG8M4ivcdjmXqasDYj/cPnx4yPDIttUScyKjaql+Usr6ruDeivF/2YsMiI8PoBG7GJLn1dV1/H9bZqvIOT/u4y72w3Vfk+LuX7GXmvKpgp1676fFjjyvXGYftMuZmV8p/KQ+d/pXpjz0zPegO3nHlZZb2Bbuj1xu6Z1ao3xpwqDRMjTl1vfKzTMbj/nBLvmk8u38isWe552fkrlvRUndSQ6gzsG76RmdNOdHV6vFuN/lnV38tcazll7jxJqL/DHkzl2hVX17sMca3c522v7NQxxR333H3eObZb+ryuJGXeFPNo894FrvRo/j3rUNVflTA40yOxaeX1as/ZfURXejjenULKe+y7ngXP76PoVu9dxhS/la7vo7qNcMdPynaeO37ViFverNC//eadhrgVe8Qttrns1YoEzq+YSj4XueMmn1+81lKsVPr9KY3Gvqy453OfrWWKr9aV9kF9dytLCL0vb4q/++zhjbN0/z54DVyLyv376aRHqTs99Oeeqvv5Tyh7c0hXTskypw1uVzrHG7eVw7qv/6bSGWa19zhTtDQ4zdQ3yo/jv1ufXNa+yflzOiwq3d6VdHte2tUv9HVwOha31HsE6rmUuaRjxjmudAz+JOVZviYrewO9ype46zPtG2VKL9GX9JIzoVq0/m5lTNLLvTeSSp85yh/yw3XGdcvW+qwkVa8chi+is7uK9DEcautZ7kqVO4/5BtM/3O6rJd/FxX18Xcsu8s70477+Lh4pZ9LaaR9vP3/KbKOvransGe2u0XtlTcu1zVIJZ2tzH+acqs+g+1KZz/PVwnY9cZ/S5S8rxOkke0r1UX5091WcUbd0oZirPacOKDdKffqs88D5qdIvbqzsj/ZVuK+CoMcFuirz/r4G2v1ijjuUbwUSz/G2DjE6h/IUL2fgdWnifzfuChE1JnUzYuf9I3A=
*/