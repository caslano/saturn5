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
cyPkB3aCR8KecAQcD4+Bs+CxcC4cBZfCMfAWOA7eCk+Et8EJcAM8Hj4CT4CPwWL4HJwIX4Inw1fhVPgmnAT/CifDT+EpsD/lUwKPhTPhWFgKJ8NZ8GRYBs+A5fAiOAeugnPhNfBUeDOcAdfAha4+cBH8BayEZl8eb/wPLg7Zl+cK1fOVsAO8ChZof5kh8Gp4vPaZOQXWwUXwa3b/Ko2TwdSQ/au6aP+qApgCe0BvrYY6hft9yFoNv5I+T8De2s/pBPgMLIbPwkrtS1QF39IaCc/DK+CL8Fq10/XwdfgA3A5/q32Wtiic8sE4T+J8ZPv2YUvx7cN2rh1LMWM6JtwA/q9Qu18Vqc/HtbCHW26wL/w6dP1dBwfCL+DR8BvwOHi97ofVcCb8JqyEN8NL4C1wHVwD18O18B74bXg/XAefgnfAV+Fd8Au4Hqaj290wCn8Mu8H7YSF8APaFP4MD4WNwBPwFnA1/Bc+AT6t9vwDfhi/CVArmNRiF22Av+AYcAt+EU+Gf4OPwLfgCfAduhTvgW/Bd+C78CLalPD+BOfAz2An+A/aGX6j8tzka89BYSzHSReOrjvYrKoQ3yT73ZtnnroHHwrVwNvw2PAPeCqvhOniu9iVaDW/T2rHfgz+Cd8AH3XLVGrLr4cvwbq1pcQ9MQZd7YQb8IWwNCWvK/SewE3wI5sOH4f7Q7M/llj8cDjfatUS8sQrChKwl8o7Watmh/vkvyveH8Fb4N3gb/Ez3w8fKxyfwPp1Xf6FxBvrOkP7iH0rnC6XzT5gPI269wAy16zbwYBiDQ+X29hnbqPh7huwztkTPmfNgZ9lR58tNeOrL+11OnhS+PbxO4asj9fqdrefNEjgEXgkPd+ODp8ELdD9dCM+HF8FVsBZ+DS6HbrldDh+DV8AtiucVeAl8E14Kd8Cl8K/murdvkH6X6n17W9y+QTc4Df6Km+mvspn+6prpb0Mz/W1uwl+R9j+quzLT2YBsQT5EWMN3t9Y56bwys1lrnXxZ65x4a5wMWZm5R2v41lZ/Oev4rq4JX+NkLPqWIfFr+i5dmbnX1zpxzkm83sl1KzP32Zon61dm/t+v8btpZWaL1jzZvjKzxeueOFexBjcyBJmJ1CLrkI3IVsRZxRrAyFikDFmKrEM2Ix8ihVdz7erkXIfkkTySR/JIHskjeSSP/7Rj39n/u+bke77/n2fff5ixzXc/9S9chNl+9eyq+fhetNCb33+Xb37/Zo3NnSZ7ganag23D37Ia1lg39v/zqzFfK5+9uKZ0VkV5mH2OwvROZMeu6510vWHN9BzZS20x1w8hhkzH2xPg+03vn3YMYZtlp+vfj+9HMoDD9pS4zdi0sfMf9Fkg39RLqD2k/PWztvTTjfsrkQR5l/8+xt0J98nGPSwSb8M/z8bd29r7TzbuUZGADb9soL6qeGTDr7A9E9rwc93av87EnWfrws0rNcyq8tU+G7b1+Hd996I+WjkBW0fz/w8KYLNtvJuuo5baUrt2Z7V/R0fOvd1Xdk6q48/5DmWIdHavI0OL3BPxdew28PB9BXsav087s+2+gl74nr49AwiuCTRuuBOsn6dYj3eZzkWca9xzaBLDJsZX79aGpsBcf8lZIBuaeTaeAv/8DWv/0s1c2+ZU81f1L//dEtU/10PrX3lYZPqJ0gq/zXQwzDyccTZAtq1Mlq45xu3l91CTX9nQcD8bwc5q99tNcC8Er+xb3na64p5n258//0EbtI36qd4upT7uDNifwhzxj7B2ZDehCG1Pp5owf408bW2rvHi6JW5P1s+fIsfzFcRrTzu+cM91IZ0szQ2xeyfYNjLNhPsospkcyUZfcXVOWPeyyZc/9gVRPzTFuD8=
*/