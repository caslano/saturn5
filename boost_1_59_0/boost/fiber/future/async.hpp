
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_ASYNC_HPP
#define BOOST_FIBERS_ASYNC_HPP

#include <algorithm>
#include <memory>
#include <type_traits>
#include <utility>

#include <boost/config.hpp>

#include <boost/fiber/future/future.hpp>
#include <boost/fiber/future/packaged_task.hpp>
#include <boost/fiber/policy.hpp>

namespace boost {
namespace fibers {

#if defined(BOOST_MSVC) && (_MSC_VER >= 1911 && _MSVC_LANG >= 201703)
template <typename>
struct result_of;
template <typename F, typename... Args>
struct result_of<F(Args...)> : std::invoke_result<F, Args...> {};
#else
using std::result_of;
#endif


template< typename Fn, typename ... Args >
future<
    typename result_of<
        typename std::enable_if<
            ! detail::is_launch_policy< typename std::decay< Fn >::type >::value,
            typename std::decay< Fn >::type
        >::type( typename std::decay< Args >::type ... )
    >::type
>
async( Fn && fn, Args ... args) {
    typedef typename result_of<
        typename std::decay< Fn >::type( typename std::decay< Args >::type ... )
    >::type     result_type;

    packaged_task< result_type( typename std::decay< Args >::type ... ) > pt{
        std::forward< Fn >( fn) };
    future< result_type > f{ pt.get_future() };
    fiber{ std::move( pt), std::forward< Args >( args) ... }.detach();
    return f;
}

template< typename Policy, typename Fn, typename ... Args >
future<
    typename result_of<
        typename std::enable_if<
            detail::is_launch_policy< Policy >::value,
            typename std::decay< Fn >::type
        >::type( typename std::decay< Args >::type ...)
    >::type
>
async( Policy policy, Fn && fn, Args ... args) {
    typedef typename result_of<
        typename std::decay< Fn >::type( typename std::decay< Args >::type ... )
    >::type     result_type;

    packaged_task< result_type( typename std::decay< Args >::type ... ) > pt{
        std::forward< Fn >( fn) };
    future< result_type > f{ pt.get_future() };
    fiber{ policy, std::move( pt), std::forward< Args >( args) ... }.detach();
    return f;
}

template< typename Policy, typename StackAllocator, typename Fn, typename ... Args >
future<
    typename result_of<
        typename std::enable_if<
            detail::is_launch_policy< Policy >::value,
            typename std::decay< Fn >::type
        >::type( typename std::decay< Args >::type ... )
    >::type
>
async( Policy policy, std::allocator_arg_t, StackAllocator salloc, Fn && fn, Args ... args) {
    typedef typename result_of<
        typename std::decay< Fn >::type( typename std::decay< Args >::type ... )
    >::type     result_type;

    packaged_task< result_type( typename std::decay< Args >::type ... ) > pt{
        std::forward< Fn >( fn) };
    future< result_type > f{ pt.get_future() };
    fiber{ policy, std::allocator_arg, salloc,
        std::move( pt), std::forward< Args >( args) ... }.detach();
    return f;
}

template< typename Policy, typename StackAllocator, typename Allocator, typename Fn, typename ... Args >
future<
    typename result_of<
        typename std::enable_if<
            detail::is_launch_policy< Policy >::value,
            typename std::decay< Fn >::type
        >::type( typename std::decay< Args >::type ... )
    >::type
>
async( Policy policy, std::allocator_arg_t, StackAllocator salloc, Allocator alloc, Fn && fn, Args ... args) {
    typedef typename result_of<
        typename std::decay< Fn >::type( typename std::decay< Args >::type ... )
    >::type     result_type;

    packaged_task< result_type( typename std::decay< Args >::type ... ) > pt{
        std::allocator_arg, alloc, std::forward< Fn >( fn) };
    future< result_type > f{ pt.get_future() };
    fiber{ policy, std::allocator_arg, salloc,
        std::move( pt), std::forward< Args >( args) ... }.detach();
    return f;
}

}}

#endif // BOOST_FIBERS_ASYNC_HPP

/* async.hpp
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
*/