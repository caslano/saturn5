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
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
*/