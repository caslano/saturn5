/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   file.hpp
 * \author Andrey Semashev
 * \date   16.05.2008
 *
 * The header contains implementation of convenience functions for enabling logging to a file.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_FILE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_FILE_HPP_INCLUDED_

#include <boost/type_traits/is_void.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/parameter/parameters.hpp> // for is_named_argument
#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/comparison/greater.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/sink_init_helpers.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/core/core.hpp>
#ifndef BOOST_LOG_NO_THREADS
#include <boost/log/sinks/sync_frontend.hpp>
#else
#include <boost/log/sinks/unlocked_frontend.hpp>
#endif
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/keywords/filter.hpp>
#include <boost/log/keywords/scan_method.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_DOXYGEN_PASS
#ifndef BOOST_LOG_NO_THREADS
#define BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL sinks::synchronous_sink
#else
#define BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL sinks::unlocked_sink
#endif
#endif // BOOST_LOG_DOXYGEN_PASS

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The function creates a file collector according to the specified arguments
template< typename ArgsT >
inline shared_ptr< sinks::file::collector > setup_file_collector(ArgsT const&, mpl::true_ const&)
{
    return shared_ptr< sinks::file::collector >();
}
template< typename ArgsT >
inline shared_ptr< sinks::file::collector > setup_file_collector(ArgsT const& args, mpl::false_ const&)
{
    return sinks::file::make_collector(args);
}

//! The function constructs the sink and adds it to the core
template< typename ArgsT >
shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< sinks::text_file_backend > > add_file_log(ArgsT const& args)
{
    typedef sinks::text_file_backend backend_t;
    shared_ptr< backend_t > pBackend = boost::make_shared< backend_t >(args);

    shared_ptr< sinks::file::collector > pCollector = aux::setup_file_collector(args,
        typename is_void< typename parameter::binding< ArgsT, keywords::tag::target, void >::type >::type());
    if (pCollector)
    {
        pBackend->set_file_collector(pCollector);
        pBackend->scan_for_files(args[keywords::scan_method | sinks::file::scan_matching]);
    }

    shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< backend_t > > pSink =
        boost::make_shared< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< backend_t > >(pBackend);

    aux::setup_filter(*pSink, args,
        typename is_void< typename parameter::binding< ArgsT, keywords::tag::filter, void >::type >::type());

    aux::setup_formatter(*pSink, args,
        typename is_void< typename parameter::binding< ArgsT, keywords::tag::format, void >::type >::type());

    core::get()->add_sink(pSink);

    return pSink;
}

//! The trait wraps the argument into a file_name named argument, if needed
template< typename T, bool IsNamedArgument = parameter::aux::is_named_argument< T >::value >
struct file_name_param_traits
{
    static shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< sinks::text_file_backend > > wrap_add_file_log(T const& file_name_arg)
    {
        return aux::add_file_log(file_name_arg);
    }

    template< typename ArgsT >
    static shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< sinks::text_file_backend > > wrap_add_file_log(T const& file_name_arg, ArgsT const& args)
    {
        return aux::add_file_log((args, file_name_arg));
    }
};

template< typename T >
struct file_name_param_traits< T, false >
{
    static shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< sinks::text_file_backend > > wrap_add_file_log(T const& file_name_arg)
    {
        return aux::add_file_log(keywords::file_name = file_name_arg);
    }

    template< typename ArgsT >
    static shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< sinks::text_file_backend > > wrap_add_file_log(T const& file_name_arg, ArgsT const& args)
    {
        return aux::add_file_log((args, (keywords::file_name = file_name_arg)));
    }
};

} // namespace aux

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_INIT_LOG_TO_FILE_INTERNAL(z, n, data)\
    template< BOOST_PP_ENUM_PARAMS(n, typename T) >\
    inline shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< sinks::text_file_backend > > add_file_log(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& arg))\
    {\
        return aux::file_name_param_traits< T0 >::wrap_add_file_log(\
            arg0\
            BOOST_PP_COMMA_IF(BOOST_PP_GREATER(n, 1))\
            BOOST_PP_EXPR_IF(BOOST_PP_GREATER(n, 1), (BOOST_PP_ENUM_SHIFTED_PARAMS(n, arg)))\
        );\
    }

BOOST_PP_REPEAT_FROM_TO(1, BOOST_LOG_MAX_PARAMETER_ARGS, BOOST_LOG_INIT_LOG_TO_FILE_INTERNAL, ~)

#undef BOOST_LOG_INIT_LOG_TO_FILE_INTERNAL

#else // BOOST_LOG_DOXYGEN_PASS

/*!
 * The function initializes the logging library to write logs to a file stream.
 *
 * \param args A number of named arguments. The following parameters are supported:
 *             \li \c file_name The active file name or its pattern. This parameter is mandatory.
 *             \li \c target_file_name - Specifies the target file name pattern to use to rename the log file on rotation,
 *                                       before passing it to the file collector. The pattern may contain the same
 *                                       placeholders as the \c file_name parameter. By default, no renaming is done,
 *                                       i.e. the written log file keeps its name according to \c file_name.
 *             \li \c open_mode The mask that describes the open mode for the file. See <tt>std::ios_base::openmode</tt>.
 *             \li \c rotation_size The size of the file at which rotation should occur. See <tt>basic_text_file_backend</tt>.
 *             \li \c time_based_rotation The predicate for time-based file rotations. See <tt>basic_text_file_backend</tt>.
 *             \li \c auto_flush A boolean flag that shows whether the sink should automatically flush the file
 *                               after each written record.
 *             \li \c auto_newline_mode - Specifies automatic trailing newline insertion mode. Must be a value of
 *                                        the \c auto_newline_mode enum. By default, is <tt>auto_newline_mode::insert_if_missing</tt>.
 *             \li \c target The target directory to store rotated files in. See <tt>sinks::file::make_collector</tt>.
 *             \li \c max_size The maximum total size of rotated files in the target directory. See <tt>sinks::file::make_collector</tt>.
 *             \li \c min_free_space Minimum free space in the target directory. See <tt>sinks::file::make_collector</tt>.
 *             \li \c max_files The maximum total number of rotated files in the target directory. See <tt>sinks::file::make_collector</tt>.
 *             \li \c scan_method The method of scanning the target directory for log files. See <tt>sinks::file::scan_method</tt>.
 *             \li \c filter Specifies a filter to install into the sink. May be a string that represents a filter,
 *                           or a filter lambda expression.
 *             \li \c format Specifies a formatter to install into the sink. May be a string that represents a formatter,
 *                           or a formatter lambda expression (either streaming or Boost.Format-like notation).
 * \return Pointer to the constructed sink.
 */
template< typename... ArgsT >
shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< sinks::text_file_backend > > add_file_log(ArgsT... const& args);

#endif // BOOST_LOG_DOXYGEN_PASS

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#undef BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_FILE_HPP_INCLUDED_

/* file.hpp
1CPG7T2PKm7veSTzmwjxwA4SVuNR2YLQZrbxKM9yUm4b+hy21ZhPV3YOsf1Ivq5GPl2yiY8rQHxbwzTxXZXzX+Py1uNBYCt+ayULOFD3+kgN5rhcB30fxuczfgLjJwI30PdvI7+9sgl4E/Ax+hxvBi5g+n8AtyG8iOHFwOcRfoThR4G7EH4SuBv4LPXPAd9D+B3gPuBH1H8M/Bzhzxj+whg39EE+CPyR+iP0QT4GPALUXV69G/grwgkMVwX+jnA9husDw4BtGG4LrAy8gOFewFjghcA44AjgQOA4xo8HVgNOYXgqsAZwBjANOIv6K4DpwOuBGcBbqC8BNgQuBJ4FXEb9cuA5wIeBnYAbqd8E7AF8Gnge8Fng+cB3gH2BHzLdIY6vdI63PgzHQq7leJvP+X8LMBJ4KzAaeBuwCvAOYAJwATAJuFD3rpOLOG+XcJ1YCpTvOHFvgHuAHYH3cZytAPYG3q/ms3rHLe/P7fN5KOfBCM1br4nAKPqKxgDzgAnyfspbH6ydMr/HAdsDJwCzJJ/3eHvNd8TybluOlwLZyeON/Dd7VwJeRXWFJy8LIQmYkAQisoRFkUUIiwgIiLKIshjZQTQJSVg0JGkS1qJFRQWkGi0qIJWoiFhRU8WKCxbZFdCorLKFRaSKmlrr0qL2f+f9M28mc9/LPJLa1r75vpM/79577tx97nLuOSyHLGAEMJv5ngRsCcxxeeKfCrwKmAscAMwDZgHvBWYDC4A5wEJgIXA6cBZwBsfvmcCHgLOAL5FvLXAObRHdCtwInAvcDFwI/J7h/gGc7PK04ynAJCDcjfGqlOXZTjFeDWZ5DqHtp+uADYCjgbKu4x3mUcC2dOcdbe6Lom0xXuOONnVXuHhXuhnwW8bzPevjB9rA+Qkoh1+8oxkC7AUM5d3jCOpEiOQ4VBvI9ss9PtSJov1up5jjTtoce5e2bt4Dnk+dGw1p86s58CNgCnVnXEl/9/uPA4fQxtcw6uwYRxtfGbTxlcXwum2gMqbrUkmX1TbQAt7FfhDYDPg74EXAh4BtgI8ALwEuBaYAl3N8/j3zXWbsw6BPMv4GoM2Mfyzvxt7EO97pwPq0BXM+8G5gQ+qSaAycwvfezPK+BTiA4a6mLohh1P1wI3U/TKB/JnA6MAc4A5gPnAksoA6IWcDfAG8F3g68C3gHcBHwLmAx4+H3j3sdGPMU37+xnB+M4zzgBrbv2BB9jY+6JV9TUBhlXKeyHRSwHRSxHUxjO3iN7WA27+zjJTIu3QkcJO3J8/2/BzgGOJ930O8HTiV/Lm3YzaCtJMQld8LvAD5Nm3HPAJcD/wB8DPgsEGHkDvYztAFVShtQLwLxv/T/l4Cv0zbbetpk+zNtsm3j+3fwrvu78ps22fS1LfADlktD0CFd9o/tMA4YRx0KnYH12Q8b8a50E+B4YFPW+3Ws95bAqdQpcBvdfwNsw+9/B9ZvN+DDvLP9e9pqWsG7208Ar6Stor7Adbyr/SbwWn7/BwM30xbSTr7nXWAC8H3+jkRGVh+OkrvYfUB+7mv/ou9n1/Td7Jq8l626k70ZdXYGlHQEdoNAWaA5oCWgtaAy0GmQdjRKSwZ1A40A5YDmgUpAb4D2gypAkeU1e2f7Z5L/z8jML6ox/f9li03y/4g6Mzsf6v89dwA+bKEZ5/klHB/nc7/3HtDDPWShq8ujXdm3b/9Uqv+XPazFlfT/h0vYO9TyoeIXQlkjm/5/C5U4lFHQdcEtttgEoA51rncuJENL0CMIV2rLD47HJS7Jj00m8E0J38DpubfNJsBZHzYByr3pQAJYMZozmwDg9WsT4PPj/x6bALrs4ggfNgFSThh50puao7LS9d73YUK6cF8=
*/