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