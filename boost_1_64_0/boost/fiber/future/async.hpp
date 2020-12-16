
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
rL6YMHZLSSTDhAQMXklIFffNLvnRj8YbF6Gd97iZs2Xn66FxLNXfIb0omSp6v3miRTpgo44j0y6lnM3NhcvVD5I7FCM5Tq4xcUeYxrhqTmOM6zX73pNK4CW2Pi6CGzEzkIwzA+Ji2ww7mxVInto5eNlttl24wZCWKRWnSSxbAEjgCW67v5d/LUU4pzFC080JthbxMiGcFIdB3QMM0sUgEyluugbgOhRXxzs1rt/se5faT9sbxoRruEcbKRr+R2w4pU2zq1ObLfgyUEMKU0UQWD+GMYJPqCX6nybj8ToMlhGtgYTpv8531f6bHeyle8H/Ck4Pj/gM1W8xefxdL9H17X3HMOdRyrkkmOOBhTKWtYSyYi8RHX3psQg7Ov8Rl0cf5KHXY4RvQzJ07FTMWbhY7di4cjYgGA2Fi5PsSpyke7HoM1zyJWI+G4ZiBMapCEzzJIs3zPQkbY8AnjrZmAMkKZrs65Re9Cqx4eVmiXwa7+3lUEI4sF4l0CSeePlukavTi14j4Hs5cJa2aLnOjnlFGOriihEvddou5g+rEeIZ25eEhnTOO8KS574nLbmFjZzkspCQlHe7xcx8p2pboO+jPjB1mIoG6WWLcP2TqcgvSwSzBDril8epY9gUxO1ScY9QcNv8nRS0zyBaMXzPT7dL7Pl5duxfcUVsibm5TMe+lbUNgdRWkk23cJve4TNm05NqxqaHyAP17fTfmDyUWQmnfENO2ekNW+ZrwJ5pFrIWrK6yVsbxZVZYOo1k2dRsvTbnb7/tei2zND/tDy5ikyIMN7Xp5DDatRVR3Kx3QkWQyd9HCcsOyR5pyfsEYnSWPNr/UoSr2Obrf0Qq2dXXl5rbVcPyRWOCCa5enP2Mw1Vc3+F9uvoOrzSH62G2P+oZguxh2B/1VVHFYwEhGE0ItMueUiBU+tx6+l5YEhE/EvcZ+HH804j5cWCvrr4DT1SCH4v3mvLj842R8uMmQqA1fLIcfqTq6VvxaET8+HmPgR+ffBIxP4r36OorfrwS/Jizx5Qff9sQKT96EgItdlU5/EjW07dgsTluI2n+3cb1PuubCmT5/Hxht4GfD34cCT/TmP3bHTRF5FqvwuTjpwMhocw8sXeTrVsTG71JFCXc+UMgIPJcPM9JWX+GLLCnV1EqDkffvCuHxgxM6m3X/o5JaPZpjZcgd/yIkLl16C1jD839Vs5Vimg8Iv9nl97/SfDMgP9wAP+0ifFFAfiVHbdR87NofOgsnvPPJPsuDr7U8tUOvsTnOtgLHz2y/FvJGZoMLZPh3xQ0+Zld4HUKr2oaVKXbI+Zitn+wZySNjYg72gpMKqx96gmnJdBgWP+6FmW7mr+tvxnMqB6CXBpZW7MDPkbyQ4e886J1o4z/saCIY21yU5oLKw7sxhL4hNvUOhTnn7E6Zt2DISLSgghT5DFR3nS4jcQiUO8WLgxGt905REqQBMeGxPj80qiS0lj+Gm1LYBSm6ChMYWhSZMOxmDX/8NUlZ2xK0dAa/2YJU6OjpDS68jWmlpyJDlsjuWnDTaorKbVFVlcKq2tntNUSijimbBYcwsLVIGVaUyovaIP+kchwFSMu/0eK2mD59jq6VFEpWqDD8VY1PO/fx890fBiznfV/tFJLN0VByg8/FmzDI1d29kiJssAfG/6xWnZGpwQ/cHBisAX/E0FaiVZfLfxn813s71Fk1d2MkoaSmgfA/jam6TaRalVK8/72OGQ6NgARLX6GUqD7UF80lElBJw8qjLb4XCjkaDAIR5Y7adWd4aCFam58UoFwK8OTfziq5DBgyEixzSg9iTh/jE4oKQfrggiw2vIPO0oO2xCrdUZpMcMaWy7WzhFghb7XvRwUp5aVjwI=
*/