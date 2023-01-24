//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_HANDLER_HPP
#define BOOST_BEAST_TEST_HANDLER_HPP

#include <boost/beast/_experimental/unit_test/suite.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/core/exchange.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace test {

/** A CompletionHandler used for testing.

    This completion handler is used by tests to ensure correctness
    of behavior. It is designed as a single type to reduce template
    instantiations, with configurable settings through constructor
    arguments. Typically this type will be used in type lists and
    not instantiated directly; instances of this class are returned
    by the helper functions listed below.

    @see success_handler, @ref fail_handler, @ref any_handler
*/
class handler
{
    boost::optional<error_code> ec_;
    bool pass_ = false;

public:
    handler() = default;

    explicit
    handler(error_code ec)
        : ec_(ec)
    {
    }

    explicit
    handler(boost::none_t)
    {
    }

    handler(handler&& other)
        : ec_(other.ec_)
        , pass_(boost::exchange(other.pass_, true))
    {
    }

    ~handler()
    {
        BEAST_EXPECT(pass_);
    }

    template<class... Args>
    void
    operator()(error_code ec, Args&&...)
    {
        BEAST_EXPECT(! pass_); // can't call twice
        BEAST_EXPECTS(! ec_ || ec == *ec_,
            ec.message());
        pass_ = true;
    }

    void
    operator()()
    {
        BEAST_EXPECT(! pass_); // can't call twice
        BEAST_EXPECT(! ec_);
        pass_ = true;
    }

    template<class Arg0, class... Args,
        class = typename std::enable_if<
            ! std::is_convertible<Arg0, error_code>::value>::type>
    void
    operator()(Arg0&&, Args&&...)
    {
        BEAST_EXPECT(! pass_); // can't call twice
        BEAST_EXPECT(! ec_);
        pass_ = true;
    }
};

/** Return a test CompletionHandler which requires success.
    
    The returned handler can be invoked with any signature whose
    first parameter is an `error_code`. The handler fails the test
    if:

    @li The handler is destroyed without being invoked, or

    @li The handler is invoked with a non-successful error code.
*/
inline
handler
success_handler() noexcept
{
    return handler(error_code{});
}

/** Return a test CompletionHandler which requires invocation.

    The returned handler can be invoked with any signature.
    The handler fails the test if:

    @li The handler is destroyed without being invoked.
*/
inline
handler
any_handler() noexcept
{
    return handler(boost::none);
}

/** Return a test CompletionHandler which requires a specific error code.

    This handler can be invoked with any signature whose first
    parameter is an `error_code`. The handler fails the test if:

    @li The handler is destroyed without being invoked.

    @li The handler is invoked with an error code different from
    what is specified.

    @param ec The error code to specify.
*/
inline
handler
fail_handler(error_code ec) noexcept
{
    return handler(ec);
}

/** Run an I/O context.
    
    This function runs and dispatches handlers on the specified
    I/O context, until one of the following conditions is true:
        
    @li The I/O context runs out of work.

    @param ioc The I/O context to run
*/
inline
void
run(net::io_context& ioc)
{
    ioc.run();
    ioc.restart();
}

/** Run an I/O context for a certain amount of time.
    
    This function runs and dispatches handlers on the specified
    I/O context, until one of the following conditions is true:
        
    @li The I/O context runs out of work.

    @li No completions occur and the specified amount of time has elapsed.

    @param ioc The I/O context to run

    @param elapsed The maximum amount of time to run for.
*/
template<class Rep, class Period>
void
run_for(
    net::io_context& ioc,
    std::chrono::duration<Rep, Period> elapsed)
{
    ioc.run_for(elapsed);
    ioc.restart();
}

} // test
} // beast
} // boost

#endif

/* handler.hpp
7tPqKpsOVNZ1C18AfRAPPhVbC4LIyKWi/FrhzomoKffImXFUXcYv1MWBHT78ArObwPlVu/2W18GYSSCxSJJ5Ddcl0Mub4JVTzNXBQixS4w2tQdgQVdZDlV4CuSy7LQXzYjXVJSqC2aq+ErKoigobZIVVXGEtV+jLFT6RFVZyhQVc4XgLVdgoK6zgClO4wjdcoV5WqOMKo7nCKq7QICvUc4VcrvA85kFKzag4vBmqnClWZystTBd1eh5EDhWT6nBvO/h1+GFRNVThPq7nhs2td0yHNFWhioHHYV/ETbwAMGI2Y8QtBlzhDt+qzf4dISs8hn1iiD+bXUtzq4u+UQmIRq3/itedyItN8jOSwI1cJCVwa7i9+YYEjlx2nHkL0J5Kd6WWcpZzjOqGAG4+C+CK5UN1G7jsFsebNJFlejRZAdFlUedPryJzFI+KCYvLn0bOd8NjNo545x/8jkmoIwWDDn1apCUe7Jt3FrVExZnmFQiUWf2LY+aXcXSoyV5LHjj1ZiFWthbddzxaI8dgeUoToD3/y3Fw0bG8lqWV/gzcCPo0swyq+mDgUqA6aYhltsgopv7TdUkF7qvPYId1oXHSGS2LhitdQ7J0aZbVwZpMovS0UzQ7ob/9ydmpeZUQ0eNiMqrEkQ88SSvCqyHUaRUYrFeGbY6qjfTD37fysM1R/R0Bnr6pIbVGGNgesEYk4zWYF1fVlf5JNACg4JVr
*/