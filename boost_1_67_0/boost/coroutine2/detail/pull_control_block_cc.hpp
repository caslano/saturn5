
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