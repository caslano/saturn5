
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

template< typename Fn, typename ... Args >
future<
    typename std::result_of<
        typename std::enable_if<
            ! detail::is_launch_policy< typename std::decay< Fn >::type >::value,
            typename std::decay< Fn >::type
        >::type( typename std::decay< Args >::type ... )
    >::type
>
async( Fn && fn, Args ... args) {
    typedef typename std::result_of<
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
    typename std::result_of<
        typename std::enable_if<
            detail::is_launch_policy< Policy >::value,
            typename std::decay< Fn >::type
        >::type( typename std::decay< Args >::type ...)
    >::type
>
async( Policy policy, Fn && fn, Args ... args) {
    typedef typename std::result_of<
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
    typename std::result_of<
        typename std::enable_if<
            detail::is_launch_policy< Policy >::value,
            typename std::decay< Fn >::type
        >::type( typename std::decay< Args >::type ... )
    >::type
>
async( Policy policy, std::allocator_arg_t, StackAllocator salloc, Fn && fn, Args ... args) {
    typedef typename std::result_of<
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
    typename std::result_of<
        typename std::enable_if<
            detail::is_launch_policy< Policy >::value,
            typename std::decay< Fn >::type
        >::type( typename std::decay< Args >::type ... )
    >::type
>
async( Policy policy, std::allocator_arg_t, StackAllocator salloc, Allocator alloc, Fn && fn, Args ... args) {
    typedef typename std::result_of<
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