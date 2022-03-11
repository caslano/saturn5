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