
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
8waI5sdNNwA2vQ40/VDcjdtbCty4byR7j2klAVfFATfp4iTxJGj6PerCzYArfvl73Hugse3Zvnu+4ofEjh8Au/LrPK0x+W7jiBEFT+cNiNsgpKUU1XKx2frHC3Ll0jPpT48nI/oSDo/73kRavIkaZ7GfRJ82xX3D3mviNm+5zcHj0adRdDJqo2MhVHfg1Hfifp/CYRzh3ev95HtEvvQnMct0us/Qmzs7IDscjI/6k2Q4ADztqS1V/6HkPvF/AVBLAwQKAAAACAAtZ0pSjxgZHPgFAACFDQAAPAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfUFJPWFlfU1NMX1ZFUklGWUhPU1QuM1VUBQABtkgkYK1WXVPbOBR996+4m31YYFIH0iltabezbggl09TJxE4pM8x4FFuOtdhSVpKB7Hb/+15JNiGUBR4aJthWdL/OPffI/kUH9n7ax/ONO3jyk9hvgh+8tkZTKf6kqX7YIEm+g/tDwwu8PiNUDzZW35NdeJbVd9ixVkkT6725T5JnhLswSZp/PWN8kZhbXHGWjf1ArNaSLQsNO4NdOHj79g28gP7+wdsuHBPOaAmRpnxB5bIL7zO78kdBbm58RT90gWogpb/lMC6YAiVyfU0k
*/