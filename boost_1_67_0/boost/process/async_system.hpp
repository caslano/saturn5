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