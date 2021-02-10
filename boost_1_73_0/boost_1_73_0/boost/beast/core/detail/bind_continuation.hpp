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
nlwOb2cLp9NEaxZAidrU6o5xzLKBETvwyZZkq6KoxuViD10bXXi9iPDmNjm0aFv3wMz7uuCCYLWz7eq0pdprMghfh+M7F45nW4tD9QEynNcufz9m6nI6myym7yY7xvYg3kyG48nN5W0wWkzDwN2ZkJ/Bu3C0Q36+ZjrJzc7KKs6hlEKLRHA/pXG1BFFh9nQbEKrv8fDX5OZ1OG9CsjNtcNhkT+qJ+xnztapLeVrrYGWNkUkUvoXzcwNpi2z9fv2x4SyuV5K/NbvE7BeZsF+elvK3zhutHeLT4DLcqcZBW8cmSZbbt+QODmDQVfwCR8PZEgYwUtxMRiFqZmpQy5wWdNopl7hwdTbod+aeqVf423ehHS78XJqDwUFn0OnYffm5QEdhsJgEi2g2Ca4Wb6Jx+D6YhcOx27H5/nXQboEfy4rRvMBt4TjfjdKuExsl6mQQbzRV98WTgL/yV0dJuaK7bYF7N8N/SXDbdvXOGj/4ZaMSPxh9u060wOVcKXiWWjeGa2u3bW3CcZAUJJySoiq/HeLmoO3aBrq71lqNuqebtX9kNvx/UEsDBAoAAAAIAC1nSlKgLx9vVQQAAAsKAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9mdHBnZXRyZXNwLmNVVAUA
*/