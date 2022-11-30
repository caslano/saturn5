
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_PUSH_CONTROL_BLOCK_HPP
#define BOOST_COROUTINES2_DETAIL_PUSH_CONTROL_BLOCK_HPP

#include <exception>

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
struct push_coroutine< T >::control_block {
    boost::context::fiber                           c;
    typename pull_coroutine< T >::control_block *   other;
    state_t                                         state;
    std::exception_ptr                              except;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( typename pull_coroutine< T >::control_block *, boost::context::fiber &) noexcept;

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume( T const&);

    void resume( T &&);

    bool valid() const noexcept;
};

template< typename T >
struct push_coroutine< T & >::control_block {
    boost::context::fiber                               c;
    typename pull_coroutine< T & >::control_block   *   other;
    state_t                                             state;
    std::exception_ptr                                  except;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( typename pull_coroutine< T & >::control_block *, boost::context::fiber &) noexcept;

    control_block( control_block &) = delete;
    control_block & operator=( control_block &) = delete;

    void deallocate() noexcept;

    void resume( T &);

    bool valid() const noexcept;
};

struct push_coroutine< void >::control_block {
    boost::context::fiber                       c;
    pull_coroutine< void >::control_block  *    other;
    state_t                                     state;
    std::exception_ptr                          except;

    static void destroy( control_block * cb) noexcept;

    template< typename StackAllocator, typename Fn >
    control_block( context::preallocated, StackAllocator &&, Fn &&);

    control_block( pull_coroutine< void >::control_block *, boost::context::fiber &) noexcept;

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

#endif // BOOST_COROUTINES2_DETAIL_PUSH_CONTROL_BLOCK_HPP

/* push_control_block_cc.hpp
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
*/