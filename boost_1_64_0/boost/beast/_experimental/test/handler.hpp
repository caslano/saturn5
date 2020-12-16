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
4clBz3zzYSycBJvK3A5Ohe3hNNgBToZpMst/tVXIJw//Z6BXC86CSXA2HCnzZJgPp8ICOAueDAtl1ni/2gGEyfgfOt7fCT1zzgFsCHvAVrAXbCtzCuwNB8MUOA52gxNhup7zsv3emu+3eU4GskvthuvrsxcHvAEmwJvgEHgXHA7vhlNhffwrkHkZvAeeC++F18D74I3wAXgLfAR25Rk7YBrcCdPhE3AJfAqeDXfBNfAZeCF8Fm6Cu+E2+Bx8DL4M98BX4BvwL/Cf8HX4JdwLW/A++DtMgm/BBfBdeC58D14L34e3wI/gXrgffg4/hfEk+GewNfwCdodfwuHwAJwHv4IL4MfwF3AfXAffhrfDf8K74Xb4KvwB/gMGSL+3YST8CEbBL2A0jCJfasFYWBsmwjqwI4yBPWFdOBDWg6NhfXgr7hMa1w1kIoXIWuRWZDfyGdIirm5gIJKPrEE2IruQfUjTJnUDGcgsZDVyHbIT+QCJbVo3kI5MR8qR9chm5GXkWySpWd1ANrIAWYdsQl5ADiAJ8YQHKUTWIrcih5r3sRP7fOzehBthTPO6gR5IDlKOXIZsRfYi0S3qBrog45BSZD2yBXkNCbSsG+iAjEJKkApkM7Ib+QCJaYW/SA5SjlyGbEX2ItGt8RcZh5S2rlszD6VmHkrIPJT1retWey7Krbh5GTmAtEigHiI1V81Vc/33Xz/N+H/w7ImjH/8P9sOucJ3/vzpS5/tF0LaGL8KLg+ftfx3aD2sej73XWUujcfO40d8coT4bue/ke34h9iHnMGw35u06ryV0vnc8PPnboH0tmfHNmBN8z8B4yvi3NSLO9g2Z2fA2DFPReUI6XmcsTMN+9zdB+1/TOzyDPq+qfoAz7e94e1aG6QOYyP87dF/nZrjOyDiSeea1GhOv0LMXQs+XOuzc8n/3b7t/d99AdX+7+/UZtFgevN/99g/Xf3basmtafrL6d6kT9477z83Z/k/1JVR3jcD+AGnn1E+9F2KQJP5vAAOmnOo3OzS/2WEGbAEHwZZwFGwFx8PWcBFMgGWwHTwHJsOrYXt4A+wM74Bd4HOwK/wz7A7fgj1gHcLQEzaAqTAJ9oEpMB32h8fD4bAfnA8zYDEcANfCQfBSOBjeB4fA++EwuB0Oh0/BEfB5OBK+CEdBfiMedl76xpq56TW/CY5ybvrmmvZ/zVVz1Vw1V81Vc/1XXz/J7//gkeLBn/9Huf4/OA/5BBrqsWz6HMn+ftmThuZNGj2S02JPzSsvZxwJ+znYrzb2mg85fMLkoRNOHD966DhHz/izrSn+zDXzVgl/XvlpS/IKi+YZ60Av7HsG5xgb+6q51EOzJg/PZXbY6Ky8ydNOzCsonFM+pySor+fuPaS+fbx9fmlhUH9ecVFJ4ehsPd6Zj9qL51cUVvk3YvTwcdlo6aHoKC2KDtbRg9BRerh0sqbkTh1uNTRHrg3+zKtM0xyCPX444Z5klaw/gfnSGevSmrvAPusqdCqkE5whOXXo5OGcoOp4ZPpvBrr6b9Kj1IGANBFziHfmc+q/UQYz0abImTs33/TfLC2e71pPP9Xod9d8Dcd9vJ2/cY4xR9g5bpwPbaSgGufDzTf9GDw37Cy7HtrPoIUcNUdyicOG8Dgw7SpFcVgSFgfCLP0Wxv7F9pVnX9t5VN72dp5VTpX9YedEOfPHljjxcZ2Djr/c47m616Lqnp0nlaZ5Ulco3jHyvA6yhTTdFh7v4vJDhWlM0LN4ys5O3OaYeluyZG5BCc5C07lLLc3L0pzLE5FJpPPu8OfRVRZwlZVAWFn50uj3tOdff3yEZ0y6wzKrtuYIKt+nI1OC5XZPWFiWkuce5TZOYSkw+gMDPew=
*/