//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BIND_HANDLER_HPP
#define BOOST_BEAST_BIND_HANDLER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/bind_handler.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

/** Bind parameters to a completion handler, creating a new handler.

    This function creates a new handler which, when invoked, calls
    the original handler with the list of bound arguments. Any
    parameters passed in the invocation will be substituted for
    placeholders present in the list of bound arguments. Parameters
    which are not matched to placeholders are silently discarded.

    The passed handler and arguments are forwarded into the returned
    handler, whose associated allocator and associated executor will
    will be the same as those of the original handler.

    @par Example

    This function posts the invocation of the specified completion
    handler with bound arguments:

    @code
    template <class AsyncReadStream, class ReadHandler>
    void
    signal_aborted (AsyncReadStream& stream, ReadHandler&& handler)
    {
        net::post(
            stream.get_executor(),
            bind_handler (std::forward <ReadHandler> (handler),
                net::error::operation_aborted, 0));
    }
    @endcode

    @param handler The handler to wrap.
    The implementation takes ownership of the handler by performing a decay-copy.

    @param args A list of arguments to bind to the handler.
    The arguments are forwarded into the returned object. These
    arguments may include placeholders, which will operate in
    a fashion identical to a call to `std::bind`.
*/
template<class Handler, class... Args>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::bind_wrapper<
    typename std::decay<Handler>::type,
    typename std::decay<Args>::type...>
#endif
bind_handler(Handler&& handler, Args&&... args)
{
    return detail::bind_wrapper<
        typename std::decay<Handler>::type,
        typename std::decay<Args>::type...>(
            std::forward<Handler>(handler),
            std::forward<Args>(args)...);
}

/** Bind parameters to a completion handler, creating a new handler.

    This function creates a new handler which, when invoked, calls
    the original handler with the list of bound arguments. Any
    parameters passed in the invocation will be forwarded in
    the parameter list after the bound arguments.

    The passed handler and arguments are forwarded into the returned
    handler, whose associated allocator and associated executor will
    will be the same as those of the original handler.

    @par Example

    This function posts the invocation of the specified completion
    handler with bound arguments:

    @code
    template <class AsyncReadStream, class ReadHandler>
    void
    signal_eof (AsyncReadStream& stream, ReadHandler&& handler)
    {
        net::post(
            stream.get_executor(),
            bind_front_handler (std::forward<ReadHandler> (handler),
                net::error::eof, 0));
    }
    @endcode

    @param handler The handler to wrap.
    The implementation takes ownership of the handler by performing a decay-copy.

    @param args A list of arguments to bind to the handler.
    The arguments are forwarded into the returned object.
*/
template<class Handler, class... Args>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
auto
#endif
bind_front_handler(
    Handler&& handler,
    Args&&... args) ->
    detail::bind_front_wrapper<
        typename std::decay<Handler>::type,
        typename std::decay<Args>::type...>
{
    return detail::bind_front_wrapper<
        typename std::decay<Handler>::type,
        typename std::decay<Args>::type...>(
            std::forward<Handler>(handler),
            std::forward<Args>(args)...);
}

} // beast
} // boost

#endif

/* bind_handler.hpp
ow3v+fTwbuhxyn7mS4J58ZldS8QXsN/nPVcK/r6Tr+x2kjgJtMi+L7bubE0KQlHQvti8qEd6xfAQFTx2tIscmBSJYAsFEXzQdlM0eGTxmFi/lt9/0TZf41q14eP0qRdes3rdOe6Yra9U1m7cKxJAbn1I8c3RWao3a5B/ZBOHdTNK165/soae/OBEhB+4GXLjwKp3+ay8Gj5PZ7Pj1CnX4ocBIyMv93N54SxXwGYn00cBZYg3oXu4QXW/loLiwkhhb92uf4sx1fXw3mP5q6yzSYQ+ozCFKCAPO5HPYtD2zIENb/rrGGzXg0GRQeRiRnWp4MrapydImO98v8O6BWv7KtrTaalAtisugbBNA3tN/EYnRZgfkx+N3xD1gjGYA+kCTZPrF68aQZXFJVdbaHpT0/A2io93xR8ocL+8f0VZlOdAtIZUMfhtUJrWDL2xPmfCJ+nu5iR1SwP5HWh/2p3e4hft4wJw20VkijbdNbKI6GdG/qtdYgr65qJTt+Htm/oAp4ACAFFtKDthP+XBtqLPgwaS5eQFdGNhOadB9ovRT4U/kDxxpVxmBvexBdcZolk6MM0O878hRNFCWmqwdGC8tPplvSZtS6wf35a7/MZTxN5SdIlOwf5yPXi8wjx3hXBpsLVREO0ke8ER87RLMy1rwr78OjvF3reYst0QY3k4Z1lWleGuXxKcqnOYbHm+cK2IvSB5ve+AZlGHEY7u
*/