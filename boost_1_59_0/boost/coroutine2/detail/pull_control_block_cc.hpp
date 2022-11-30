
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
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
*/