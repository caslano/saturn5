
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