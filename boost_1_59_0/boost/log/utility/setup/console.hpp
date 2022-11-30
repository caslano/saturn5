/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   console.hpp
 * \author Andrey Semashev
 * \date   16.05.2008
 *
 * The header contains implementation of convenience functions for enabling logging to console.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_CONSOLE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_CONSOLE_HPP_INCLUDED_

#include <iostream>
#include <boost/type_traits/is_void.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/detail/sink_init_helpers.hpp>
#ifndef BOOST_LOG_NO_THREADS
#include <boost/log/sinks/sync_frontend.hpp>
#else
#include <boost/log/sinks/unlocked_frontend.hpp>
#endif
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/keywords/filter.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif


#ifndef BOOST_LOG_DOXYGEN_PASS
#ifndef BOOST_LOG_NO_THREADS
#define BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL sinks::synchronous_sink
#else
#define BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL sinks::unlocked_sink
#endif
#endif // BOOST_LOG_DOXYGEN_PASS

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

// The function creates and initializes the sink
template< typename CharT, typename ArgsT >
shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log(std::basic_ostream< CharT >& strm, ArgsT const& args)
{
    shared_ptr< std::basic_ostream< CharT > > pStream(&strm, boost::null_deleter());

    typedef sinks::basic_text_ostream_backend< CharT > backend_t;
    shared_ptr< backend_t > pBackend = boost::make_shared< backend_t >(args);

    pBackend->add_stream(pStream);

    typedef BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL< backend_t > sink_t;
    shared_ptr< sink_t > pSink = boost::make_shared< sink_t >(pBackend);

    aux::setup_filter(*pSink, args,
        typename is_void< typename parameter::binding< ArgsT, keywords::tag::filter, void >::type >::type());

    aux::setup_formatter(*pSink, args,
        typename is_void< typename parameter::binding< ArgsT, keywords::tag::format, void >::type >::type());

    core::get()->add_sink(pSink);

    return pSink;
}

template< typename CharT >
struct default_console_stream;

#ifdef BOOST_LOG_USE_CHAR
template< >
struct default_console_stream< char >
{
    static std::ostream& get() { return std::clog; }
};
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T
template< >
struct default_console_stream< wchar_t >
{
    static std::wostream& get() { return std::wclog; }
};
#endif // BOOST_LOG_USE_WCHAR_T

} // namespace aux

#ifndef BOOST_LOG_DOXYGEN_PASS

template< typename CharT >
inline shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log()
{
    return aux::add_console_log(
        aux::default_console_stream< CharT >::get(), log::aux::empty_arg_list());
}


template< typename CharT >
inline shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log(std::basic_ostream< CharT >& strm)
{
    return aux::add_console_log(strm, log::aux::empty_arg_list());
}

template< typename CharT, typename ArgT1 >
inline shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log(std::basic_ostream< CharT >& strm, ArgT1 const& arg1)
{
    return aux::add_console_log(strm, arg1);
}

template< typename CharT, typename ArgT1, typename ArgT2 >
inline shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log(std::basic_ostream< CharT >& strm, ArgT1 const& arg1, ArgT2 const& arg2)
{
    return aux::add_console_log(strm, (arg1, arg2));
}

template< typename CharT, typename ArgT1, typename ArgT2, typename ArgT3 >
inline shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log(std::basic_ostream< CharT >& strm, ArgT1 const& arg1, ArgT2 const& arg2, ArgT3 const& arg3)
{
    return aux::add_console_log(strm, (arg1, arg2, arg3));
}

template< typename CharT, typename ArgT1, typename ArgT2, typename ArgT3, typename ArgT4 >
inline shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log(std::basic_ostream< CharT >& strm, ArgT1 const& arg1, ArgT2 const& arg2, ArgT3 const& arg3, ArgT3 const& arg4)
{
    return aux::add_console_log(strm, (arg1, arg2, arg3, arg4));
}

#else // BOOST_LOG_DOXYGEN_PASS

/*!
 * The function constructs sink for the specified console stream and adds it to the core
 *
 * \param strm One of the standard console streams: <tt>std::cout</tt>, <tt>std::cerr</tt> or <tt>std::clog</tt>
 *             (or the corresponding wide-character analogues).
 * \param args Optional additional named arguments for the sink initialization. The following arguments are supported:
 *             \li \c filter Specifies a filter to install into the sink. May be a string that represents a filter,
 *                           or a filter lambda expression.
 *             \li \c format Specifies a formatter to install into the sink. May be a string that represents a formatter,
 *                           or a formatter lambda expression (either streaming or Boost.Format-like notation).
 *             \li \c auto_flush A boolean flag that shows whether the sink should automatically flush the stream
 *                               after each written record.
 *             \li \c auto_newline_mode - Specifies automatic trailing newline insertion mode. Must be a value of
 *                                        the \c auto_newline_mode enum. By default, is <tt>auto_newline_mode::insert_if_missing</tt>.
 * \return Pointer to the constructed sink.
 */
template< typename CharT, typename... ArgsT >
shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log(std::basic_ostream< CharT >& strm, ArgsT... const& args);

/*!
 * Equivalent to: <tt>add_console_log(std::clog);</tt> or <tt>add_console_log(std::wclog);</tt>,
 * depending on the \c CharT type.
 *
 * \overload
 */
template< typename CharT, typename... ArgsT >
shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::basic_text_ostream_backend< CharT >
    >
> add_console_log(ArgsT... const& args);

#endif // BOOST_LOG_DOXYGEN_PASS

#ifdef BOOST_LOG_USE_CHAR

/*!
 * The function constructs sink for the <tt>std::clog</tt> stream and adds it to the core
 *
 * \overload
 *
 * \return Pointer to the constructed sink.
 */
inline shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::text_ostream_backend
    >
> add_console_log()
{
    return add_console_log(std::clog);
}

#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T

/*!
 * The function constructs sink for the <tt>std::wclog</tt> stream and adds it to the core
 *
 * \return Pointer to the constructed sink.
 */
inline shared_ptr<
    BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL<
        sinks::wtext_ostream_backend
    >
> wadd_console_log()
{
    return add_console_log(std::wclog);
}

#endif // BOOST_LOG_USE_WCHAR_T

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#undef BOOST_LOG_CONSOLE_SINK_FRONTEND_INTERNAL

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_CONSOLE_HPP_INCLUDED_

/* console.hpp
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
*/