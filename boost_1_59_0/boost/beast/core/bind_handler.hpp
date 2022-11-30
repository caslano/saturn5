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
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
*/