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