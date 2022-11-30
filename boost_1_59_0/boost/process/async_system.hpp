// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/async_system.hpp
 *
 * Defines the asynchrounous version of the system function.
 */

#ifndef BOOST_PROCESS_ASYNC_SYSTEM_HPP
#define BOOST_PROCESS_ASYNC_SYSTEM_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/async.hpp>
#include <boost/process/child.hpp>
#include <boost/process/detail/async_handler.hpp>
#include <boost/process/detail/execute_impl.hpp>
#include <type_traits>
#include <memory>
#include <boost/asio/async_result.hpp>
#include <boost/asio/post.hpp>
#include <boost/system/error_code.hpp>
#include <tuple>

#if defined(BOOST_POSIX_API)
#include <boost/process/posix.hpp>
#endif

namespace boost {
namespace process {
namespace detail
{

template<typename ExitHandler>
struct async_system_handler : ::boost::process::detail::api::async_handler
{
    boost::asio::io_context & ios;
    boost::asio::async_completion<
            ExitHandler, void(boost::system::error_code, int)> init;

#if defined(BOOST_POSIX_API)
    bool errored = false;
#endif

    template<typename ExitHandler_>
    async_system_handler(
            boost::asio::io_context & ios,
            ExitHandler_ && exit_handler) : ios(ios), init(exit_handler)
    {

    }


    template<typename Exec>
    void on_error(Exec&, const std::error_code & ec)
    {
#if defined(BOOST_POSIX_API)
        errored = true;
#endif
        auto & h = init.completion_handler;
        boost::asio::post(
            ios.get_executor(),
            [h, ec]() mutable
            {
                h(boost::system::error_code(ec.value(), boost::system::system_category()), -1);
            });
    }

    BOOST_ASIO_INITFN_RESULT_TYPE(ExitHandler, void (boost::system::error_code, int))
        get_result()
    {
        return init.result.get();
    }

    template<typename Executor>
    std::function<void(int, const std::error_code&)> on_exit_handler(Executor&)
    {
#if defined(BOOST_POSIX_API)
        if (errored)
            return [](int , const std::error_code &){};
#endif
        auto & h = init.completion_handler;
        return [h](int exit_code, const std::error_code & ec) mutable
               {
                    h(boost::system::error_code(ec.value(), boost::system::system_category()), exit_code);
               };
    }
};


template<typename ExitHandler>
struct is_error_handler<async_system_handler<ExitHandler>>    : std::true_type {};

}

/** This function provides an asynchronous interface to process launching.

It uses the same properties and parameters as the other launching function,
but is similar to the asynchronous functions in [boost.asio](http://www.boost.org/doc/libs/release/doc/html/boost_asio.html)

It uses [asio::async_result](http://www.boost.org/doc/libs/release/doc/html/boost_asio/reference/async_result.html) to determine
the return value (from the second parameter, `exit_handler`).

\param ios A reference to an [io_context](http://www.boost.org/doc/libs/release/doc/html/boost_asio/reference.html)
\param exit_handler The exit-handler for the signature `void(boost::system::error_code, int)`

\note This function does not allow custom error handling, since those are done through the `exit_handler`.

*/
#if defined(BOOST_PROCESS_DOXYGEN)
template<typename ExitHandler, typename ...Args>
inline boost::process::detail::dummy
    async_system(boost::asio::io_context & ios, ExitHandler && exit_handler, Args && ...args);
#endif

template<typename ExitHandler, typename ...Args>
inline BOOST_ASIO_INITFN_RESULT_TYPE(ExitHandler, void (boost::system::error_code, int))
    async_system(boost::asio::io_context & ios, ExitHandler && exit_handler, Args && ...args)
{
    detail::async_system_handler<ExitHandler> async_h{ios, std::forward<ExitHandler>(exit_handler)};

    typedef typename ::boost::process::detail::has_error_handler<boost::fusion::tuple<Args...>>::type
            has_err_handling;

    static_assert(!has_err_handling::value, "async_system cannot have custom error handling");


    child(ios, std::forward<Args>(args)..., async_h ).detach();

    return async_h.get_result();
}



}}
#endif


/* async_system.hpp
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
*/