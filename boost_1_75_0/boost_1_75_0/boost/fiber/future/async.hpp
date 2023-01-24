
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
Yb6IMlQwPpreaEuxKbK0V/dQQRTXf7fj+u923P63HRHA+RAlexMb7v57U0z1T1r+DvLYujbvjmCDZeNd8d6A2WOh7YVxBuxBVwEjMb1bbKM26+qHj2f1+7WufqlWH+2LBU/xxASVp2A8wHYIfY+WMN7u4M7psQDCfK7eyp3aHhRhdMNgyRhBZg2+2onNyTay9izNxMi0ENbFl6jyCmlc2FspEZuQjvnf3zUIurVwvaIGGYEqq9vipKljvu4eNubBca0ac6FxzIKPOgPBVGK73mczQezibe42Ulakjf3ydLTLeyV/7LFim0l5tc3fbP/Fnmb3UCYXLDHgkGakPmOZ2LGEvHQJ1zzorTRkkXwDJkjkjrMxvqpAxxaxz1Swputvifg7SONwyF8w5ix6TTtTWFlgIJy90WsAnALZrBsPs7Lo9AR9ZGRHrAR9PBeDfRwOffSxeY+9nfc2BqcvhtXgw29i/N9M0o//yCRt/Msnwfip7TWT/mfjz5sE4w9v1fh7TwoZfwz08Vw09jFpkhh/20mtH/8rRfrxLynSxj+5CMZPbZcW/c/GH1kE4w9r1fhPTAwZf81EGH8U9vHARDH+7RNbP/6xE/XjL5yojf9qaPtVajtz4v9s/J9NgPGbWzX+lRNCxj9vAow/Evv4/AQx/qcmXHT8NnZ8vRzb0VRtj0cZpc/MJsEfWRwLqoMzks8e0xCMPfUra33bc2bT
*/