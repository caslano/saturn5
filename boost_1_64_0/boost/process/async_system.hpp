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
5SYgs9NSRFpei/fiyUaibh7rOzrEyQqfo1VSOXmSs85WKidTdRdIu3vYf7TJNxebVv7wdlUZSDQDAsWBBCnzPVZdZ0exXV1cyWTUwjL7PaJ/Ef3GvkdNH9Nc8xC0MblGKvI9vlxzAmV6d6CHb3F8a/NYfDPr3Jngzs1/VtIZ517v1jt+bCYjy9LyqYNkk8gzkdaOcrxnzOvIPzGdTfC4T/gXx59jPe8pKykon6pr+rAH7xV7zkz7VqZN2DEmxdXmKK2o0zM5X683Dc2zJsccNMeY43y1WdP0pP/YuA60Ib1ux43WPvbYU04Z3bYjf53Fx27+HpB22ZC89E+f7bxLabgxpxAQmD+9hj+QVsOfUjMltGfBdH23pnOP/1HWqU7WefGnoq/3TiPnw4vsNMJPx+kaFMJwGvY07ow64X50RPYlPBPOhV+58+pjz6f/XNmlTtB1xb2FvxvsjuuhrifuLNwxNMReEf4/6V5ZT+LaI7sm9rpaDdNwTXdv4uh3OXYe/j64a2Pa0TB1fbWcusIoNl3egFtm+e3vC6Gtfx28XL/3s2xlha33CdtP2D2nz6122ketn1wjMI+2Hloj0Mp3aGtvQ/dbb5hKXBjyz43wz4jwF4lf78VW6+9D6x7S3VWuzP2de5HK7HtIZ6vMvl9Upfbs+ydfT1GZdf9khydzjzuvUmSF40LrDJDtcuz9E9Y/IJcxAWMF5DpWUPle5KUid69t+ltV5Xp9ytB9iA/I3r10Azp+7jM5WJ7zG4aP3ZYUGfk0SzbmaBiAsl5Kyn82Gz7/eL1Ups6V3yc6HyWVxDf0Vyfu94XW3e8S+Qa3n9430/G/YuabVu7czYrzHVk+Y4srzEumR/Q9F6Ye+nhNdWOuwWoAXxadpr6oa7Cm/vRYzR53Ha/nxMbpTrzHEuswPt9hUn1/xrrP38yc5G9ihvm71biLkNCc47UXyvhAx600IimD9+LPpOR9vmtMmn9AIDQvarmEfRCfZp6LD80FGHOBIzvPHGeah13HMtX+PglfKleTSZSg1ofGG+iWw7aLHH+Ve91/XPzf0S6Qad3ulzjvxM3wve1HJu1spMjOj6/lf9sve2AGx2NuPU+U8Jt9XUyiL2y8Zo23Fk2Tdpj0fNxAMyV+srs3w6LZMobHH5yHv1T0uiRFW3OWDl+SNPtNSy3L/VJ/LyZVxp1pdsd9x1yBGeatxCTzVWKyObVmkjm7ZrLZWXOBO777i+i/keSNs4omO2yq9r+eQThv3uzA39NM67gH4+qbt3C14+sae+yXofpvSnq4O0DthOpwp8jGkMo+JtbaOCP53JIUZW2cW18tpY3NM6F6yJA4jyb1piYixolu+Xwh51yUNXNq81ux0cbEGuelyTETou13IvGTfumE/0L9zKaR+psh+l9kyfEm2mO1vAskD5RvF7f/GCCyS+NvMUtMQ21TOhfHPc6OYDu09lWZNLPCsjtDzpMrTAtzNDK7b3nJ0LdY+dO5Mnrscy+U9PqjrRm8T/LWgX4h203HNyJ72hftnPFsFLvp+lzaT434rrSdyDLKZBx22qjguwr7O/M9fPOuc3bY0zkW3t56qmcKjRng6CXMWxu5t94XjNFmRV27aI/ZYqxjtMdeh7GmMbRG8a2fWKeI4/ju+Ev8Z8G9GV5Yd/xG5xLYbpOlo34Yvq/IQOJ9gH8QxO/G3Re2J6oX90P4Z9z11t4mdvx3M6CE6dhQ5e+pbAZM1Xkh4eklPArPruN9n6hxNE+u3mDkpM8rT5U9De01nddJmLeeMyNsXKfvZdD2u0ja3jD6ojT6x7SfHNctne6N6xof4rgu03neN5t4JKuytLrYWf092ekfkM8Rubc+dNHsn3c=
*/