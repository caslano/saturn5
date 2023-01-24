
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_PULL_CONTROL_BLOCK_HPP
#define BOOST_COROUTINES2_DETAIL_PULL_CONTROL_BLOCK_HPP

#include <exception>
#include <type_traits>

#include <boost/config.hpp>
#include <boost/context/fiber.hpp>

#include <boost/coroutine2/detail/state.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
struct pull_coroutine< T >::control_block {
    boost::context::fiber                                           c;
    typename push_coroutine< T >::control_block                 *   other;
    state_t                                                         state;
    std::exception_ptr                                              except;
    bool                                                            bvalid;
    typename std::aligned_storage< sizeof( T), alignof( T) >::type  storage;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( typename push_coroutine< T >::control_block *, boost::context::fiber &) noexcept;

    ~control_block();

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume();

    void set( T const&);
    void set( T &&);

    T & get() noexcept;

    bool valid() const noexcept;
};

template< typename T >
struct pull_coroutine< T & >::control_block {
    struct holder {
        T   &   t;

        holder( T & t_) :
            t{ t_ } {
        }
    };

    boost::context::fiber                                                       c;
    typename push_coroutine< T & >::control_block                           *   other;
    state_t                                                                     state;
    std::exception_ptr                                                          except;
    bool                                                                        bvalid;
    typename std::aligned_storage< sizeof( holder), alignof( holder) >::type    storage;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( typename push_coroutine< T & >::control_block *, boost::context::fiber &) noexcept;

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume();

    void set( T &);

    T & get() noexcept;

    bool valid() const noexcept;
};

struct pull_coroutine< void >::control_block {
    boost::context::fiber                       c;
    push_coroutine< void >::control_block  *    other;
    state_t                                     state;
    std::exception_ptr                          except;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( push_coroutine< void >::control_block *, boost::context::fiber &) noexcept;

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume();

    bool valid() const noexcept;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_PULL_CONTROL_BLOCK_HPP

/* pull_control_block_cc.hpp
bbv2dwZXEP2AvD3HF5IHsaCRWFJk7XkgTPXJxvJbMJbAzx700tTo+C2XFdDpxL4Ajeygv037lXc59+QoKtzxc+7idelRgmODpewTUact/qwJ+/51NTk5Q0/WL6C261WqL/2FwV3ODQVrVqkL9h3R/ujRkbAnVkCKK7WKJypHlQmTeM9Q5ur5FwzlZ731Qh+7k8SL9MJi2yXBckBRQhvNfdsmwXaHfLuqd+37Qq/Q4BJgRmwb1nvbS9BLtS33jbuWUKcGvh5iyewk4IRfi7v8xzpeJ8Yy+nqeF9tAx8j8ddkyVidpq/wCbMiV/oJnO0BW/LslzsU2JgLVWeIv1+M9LUIFuJeTvqw9boh2ajza3v5+HPNjD0GSQ3naXIU2Eim32uH9O0buIznvWUsBRjHsj03fLaDWr2OCDC3VmrnfIs3ugr/T6oIPFdi+UamsAzp+10sX28v6SGgN1uKIxzjRdN0TyTBbDB7btPjuIt7+hTW1k3Of3D/F3kNczbfWtkW0dcvJJy/IVH5AfYHndrGJCD3Ywut9V4fP4cnCHIjGIFK5mchH7dWqe3tRcAopwBWGnkLr6sIreZ1GQtRRY8g8az/Gc0+FgWF1QvU+ZoNWtnKu0fSLZRzJcQQ18JCO89Arn61oQb51/4knx+dOJt8DeeOmAySZOUdjNpMFOo9EyPlp2THY/REZEUIgBu6rpeRr/6wCrVW5jIheDTqp
*/