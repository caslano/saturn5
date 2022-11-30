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
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T) >\
    inline shared_ptr< BOOST_LOG_FILE_SINK_FRONTEND_INTERNAL< sinks::text_file_backend > > add_file_log(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& arg))\
    {\
        return aux::file_name_param_traits< T0 >::wrap_add_file_log(\
            arg0\
            BOOST_PP_COMMA_IF(BOOST_PP_GREATER(n, 1))\
            BOOST_PP_EXPR_IF(BOOST_PP_GREATER(n, 1), (BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, n, arg)))\
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
 *             \li \c target The target directory to store rotated files in. Enables file collector and, if specified, limits associated
 *                           with the target directory. See <tt>sinks::file::make_collector</tt>.
 *             \li \c max_size The maximum total size of rotated files in the target directory. See <tt>sinks::file::make_collector</tt>.
 *             \li \c min_free_space Minimum free space in the target directory. See <tt>sinks::file::make_collector</tt>.
 *             \li \c max_files The maximum total number of rotated files in the target directory. See <tt>sinks::file::make_collector</tt>.
 *             \li \c scan_method The method of scanning the target directory for log files. See <tt>sinks::file::scan_method</tt>.
 *             \li \c filter Specifies a filter to install into the sink. May be a string that represents a filter,
 *                           or a filter lambda expression.
 *             \li \c format Specifies a formatter to install into the sink. May be a string that represents a formatter,
 *                           or a formatter lambda expression (either streaming or Boost.Format-like notation).
 *
 * \return Pointer to the constructed sink.
 *
 * \note The \c target named argument is required to enable the file collector and the limits associated with the target directory.
 *       If the parameter is not specified, the file collector will not be created and the limits will not be maintained.
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