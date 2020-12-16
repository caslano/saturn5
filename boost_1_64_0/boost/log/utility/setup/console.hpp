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
D/Qhcw0ag4eaooKZ8swQ0He1rqQ/z2GNUWW5LPNLXfcaSFx3pJdy1VyQwpX/TFNJ07nc+dJa0px9UtdL/zUZjzDy68JMWXzuK/3KbI+xRbbnUj8etqRLdGwHKcPeDtJ+v0lcS9MvfIf4Ggbnb28/J2sfz5UFVDhUsg6nAD31sX74+nhK7qR86WDbPTtGbSqfff4u6au6cvD/Q5DDjvdQqlyXtZxMzfSHvVHiY1xDUMvVkO8htuuNtRzVXjKHUnm9uUXiI1wDcNR7IK9q6f5pMyUt2/c2SRvmysYaugzykexNPTTeuJYvlLWUGKR/ha3NW3BO+usyrWOrmzGY/bhhjTi21vvGFp7Pg3t/gDwB59R2iUsLdm+EcseQ8pmA0vzOh871Yh6Ou/9HVffAz3zKJ+EbSZvldD4oJ/h7Q/+009V9SI7jfbektd53I63funVQ4v2/qZQ7I3fC5NzRk/PNOX1c0sSa1+KGh41wwOu39EGCpKnGsMoTbvbJy0Fcn4O9V5V1Xz2zS1tY+25tss3fRe7tsw+rvgv8TJmsnpskbZaWiP87QOg/zTLy8dwQbulP0dv702zTVRIfY+9fM6+9zxJ4PZjOuqTIMe19kMA+KJJ05+B5JNzsh0dEFyZlF0rZY6ZPmTLT/L7AzewnPleIv8trFferLLev5L5b+kqObemr4SneQltznrXiPNtl9pXtGdc2z96XtPWd5hnKCX6e7Toc/DxD2nLn2ccSX9eyXqmx8Bvnk5pf2hEVVmVNK8zN883H7yV9rC29mluv/olzq7S6t9BbObdKOLfSj1j6y/7c7Hdtqitp82RudYGMcL6uoszy59Q9El/F3pdl8k536J+5Et/A0j/JnEcdJW4SnrQiMc8rm3NprejDkU6VKWeaUzB2LF6K++7frpN0jXhvo3wZg/MhC7af/K+z+1MD+Hd/r/pE3LuDus4iT/m+3d8H9u1WedW4fP0U1xGff7b1fI/RSPEGRI6jvv/ztTpfMVDYx5/al0DSvSzjbzykSOvv1BZSntVXW9re9KmdJvH3az3l+dttbxOWYX3fMG3C5fk59jWFaS1jVtL63sXPk/hztOaaTp1Le0l0g7QemscvX5HXLsN8Md8gjYxj/zw97NcSv+vfTEmzHPMzTFsE8ZWdN3761Enm2vuapLuAYVV2hP/1BOP+JO4vRaf8xQO915O2tKxPrc7wFvomrye76es66htzbPByEnh9Gitpd2jDUMKlkBu1jo7jQ8o054p9fFwl8eu0ruI967KPjzJlFJd7zVFp7WuasvXcJPH5mCdR6JEo0xe2VPRZGKHtA46R7yRNB+t6yD6+U+Ju1xqihO4Q21hgu4XJM3x9htVxE8tbL6XeP0q6ukGtlxUZN+iTwO+Dc4Lzq3X26wzkV3v6/Gf3id9rm20TF7buWjLw83U3fHjb0nFtA/mxVtxv1NnvNZAfcSB/4Yr7yTr7q1bcX9jZz7fi/rbOfsSB/ZHFR1TxBmjjLynjI/oBfaD2AZOAH/r5lmaXk+8d5nuX+fb65StkvjSHfPuZ7xNgDeA/mW+7sg3TRl7Cx9qNzLcW6YxyHgEa9XkUmGrE02d2E31lNwNbA58AdgduAZ4P3AbsD3wKOBr4NHAs8DngpcDngX8D7gJeC3wTeCvwLeBtwFeAdwF3Apcz3QNM95iko4+bsmPSFlZSxsftV/r+/gb0AI8DM4C/8zwi3Nrss4A68FygG9gDGAbsAwwHZks6+twqOyDtQyVlfG6/YXt/R9/d74G1NVkTxCftZ/q8HQJ2kDDPQ+xigc+jOo4vfQz0AGsCM4C13N7zqMvzOJPnUZvnkcHzqCPnIel8PsnlnEdlpDMwGmg=
*/