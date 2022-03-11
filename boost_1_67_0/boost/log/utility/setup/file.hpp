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
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
*/