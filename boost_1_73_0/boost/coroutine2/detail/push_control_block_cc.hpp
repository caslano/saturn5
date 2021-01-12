
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
IOQm1oRAuNo407xhTHR15+0g/BOs8TJ+LmeQuIbGcLXeu1a6xM7f4B43seZW3SexG/TX5xWrs4v9exsUyjjiKOf6770fEqbUB3WFfWxd4UfKUvy4ZSzyj29JXfCU2fDXKf84TPRxnbb82utP3N6p3nFtlixM+HpIg/h8klf+8ZPoc6q+CyyD2ZhN2ug3ivwj57A+fAc2g+/CVvBb2A5mOPvbwd2cHw6/g4Ph9/AkuAeOU3cT
*/