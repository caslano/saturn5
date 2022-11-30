//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BIND_CONTINUATION_HPP
#define BOOST_BEAST_DETAIL_BIND_CONTINUATION_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/remap_post_to_defer.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/core/empty_value.hpp>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

#if 0
/** Mark a completion handler as a continuation.

    This function wraps a completion handler to associate it with an
    executor whose `post` operation is remapped to the `defer` operation.
    It is used by composed asynchronous operation implementations to
    indicate that a completion handler submitted to an initiating
    function represents a continuation of the current asynchronous
    flow of control.

    @param handler The handler to wrap.
    The implementation takes ownership of the handler by performing a decay-copy.

    @see

    @li <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4242.html">[N4242] Executors and Asynchronous Operations, Revision 1</a>
*/
template<class CompletionHandler>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
net::executor_binder<
    typename std::decay<CompletionHandler>::type,
    detail::remap_post_to_defer<
        net::associated_executor_t<CompletionHandler>>>
#endif
bind_continuation(CompletionHandler&& handler)
{
    return net::bind_executor(
        detail::remap_post_to_defer<
            net::associated_executor_t<CompletionHandler>>(
                net::get_associated_executor(handler)),
        std::forward<CompletionHandler>(handler));
}

/** Mark a completion handler as a continuation.

    This function wraps a completion handler to associate it with an
    executor whose `post` operation is remapped to the `defer` operation.
    It is used by composed asynchronous operation implementations to
    indicate that a completion handler submitted to an initiating
    function represents a continuation of the current asynchronous
    flow of control.

    @param ex The executor to use

    @param handler The handler to wrap
    The implementation takes ownership of the handler by performing a decay-copy.

    @see

    @li <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4242.html">[N4242] Executors and Asynchronous Operations, Revision 1</a>
*/
template<class Executor, class CompletionHandler>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
net::executor_binder<typename
    std::decay<CompletionHandler>::type,
    detail::remap_post_to_defer<Executor>>
#endif
bind_continuation(
    Executor const& ex, CompletionHandler&& handler)
{
    return net::bind_executor(
        detail::remap_post_to_defer<Executor>(ex),
        std::forward<CompletionHandler>(handler));
}
#else
// VFALCO I turned these off at the last minute because they cause
//        the completion handler to be moved before the initiating
//        function is invoked rather than after, which is a foot-gun.
//
// REMINDER: Uncomment the tests when this is put back
template<class F>
F&&
bind_continuation(F&& f)
{
    return std::forward<F>(f);
}
#endif

} // detail
} // beast
} // boost

#endif

/* bind_continuation.hpp
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
*/