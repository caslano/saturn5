//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_STREAM_BASE_HPP
#define BOOST_BEAST_WEBSOCKET_STREAM_BASE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/websocket/detail/decorator.hpp>
#include <boost/beast/core/role.hpp>
#include <chrono>
#include <type_traits>

namespace boost {
namespace beast {
namespace websocket {

/** This class is used as a base for the @ref websocket::stream class template to group common types and constants.
*/
struct stream_base
{
    /// The type used to represent durations
    using duration =
        std::chrono::steady_clock::duration;

    /// The type used to represent time points
    using time_point =
        std::chrono::steady_clock::time_point;

    /// Returns the special time_point value meaning "never"
    static
    time_point
    never() noexcept
    {
        return (time_point::max)();
    }

    /// Returns the special duration value meaning "none"
    static
    duration
    none() noexcept
    {
        return (duration::max)();
    }

    /** Stream option used to adjust HTTP fields of WebSocket upgrade request and responses.
    */
    class decorator
    {
        detail::decorator d_;

        template<class, bool>
        friend class stream;

    public:
        // Move Constructor
        decorator(decorator&&) = default;

        /** Construct a decorator option.
            
            @param f An invocable function object. Ownership of
            the function object is transferred by decay-copy.
        */
        template<class Decorator
#ifndef BOOST_BEAST_DOXYGEN
            ,class = typename std::enable_if<
                detail::is_decorator<
                    Decorator>::value>::type
#endif
        >
        explicit
        decorator(Decorator&& f)
            : d_(std::forward<Decorator>(f))
        {
        }
    };

    /** Stream option to control the behavior of websocket timeouts.

        Timeout features are available for asynchronous operations only.
    */
    struct timeout
    {
        /** Time limit on handshake, accept, and close operations:

            This value whether or not there is a time limit, and the
            duration of that time limit, for asynchronous handshake,
            accept, and close operations. If this is equal to the
            value @ref none then there will be no time limit. Otherwise,
            if any of the applicable operations takes longer than this
            amount of time, the operation will be canceled and a
            timeout error delivered to the completion handler.
        */
        duration handshake_timeout;

        /** The time limit after which a connection is considered idle.
        */
        duration idle_timeout;

        /** Automatic ping setting.

            If the idle interval is set, this setting affects the
            behavior of the stream when no data is received for the
            timeout interval as follows:

            @li When `keep_alive_pings` is `true`, an idle ping will be
            sent automatically. If another timeout interval elapses
            with no received data then the connection will be closed.
            An outstanding read operation must be pending, which will
            complete immediately the error @ref beast::error::timeout.

            @li When `keep_alive_pings` is `false`, the connection will be closed.
            An outstanding read operation must be pending, which will
            complete immediately the error @ref beast::error::timeout.
        */
        bool keep_alive_pings;

        /** Construct timeout settings with suggested values for a role.

            This constructs the timeout settings with a predefined set
            of values which varies depending on the desired role. The
            values are selected upon construction, regardless of the
            current or actual role in use on the stream.

            @par Example
            This statement sets the timeout settings of the stream to
            the suggested values for the server role:
            @code
            @endcode

            @param role The role of the websocket stream
            (@ref role_type::client or @ref role_type::server).
        */
        static
        timeout
        suggested(role_type role) noexcept
        {
            timeout opt{};
            switch(role)
            {
            case role_type::client:
                opt.handshake_timeout = std::chrono::seconds(30);
                opt.idle_timeout = none();
                opt.keep_alive_pings = false;
                break;

            case role_type::server:
                opt.handshake_timeout = std::chrono::seconds(30);
                opt.idle_timeout = std::chrono::seconds(300);
                opt.keep_alive_pings = true;
                break;
            }
            return opt;
        }
    };

protected:
    enum class status
    {
        //none,
        handshake,
        open,
        closing,
        closed,
        failed // VFALCO Is this needed?
    };
};

} // websocket
} // beast
} // boost

#endif

/* stream_base.hpp
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
*/