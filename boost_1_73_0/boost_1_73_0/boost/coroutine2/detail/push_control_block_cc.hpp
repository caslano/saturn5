
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
9dkxKXOB9uflDfQbOKxQLxxl87I0D7jATKayg19MtotxMpqFcRpGUycmOBFifWxNoqY7oWwI71CcZYuqW1Eu7jzTEkc1QSXuYEcekxL9nOWPriEDe3X1lO0T1uHanrEoEBuM1SyguEiu2IagtHwrPPwVNd86rMYEVCpdDSthWYa7tubJOMPgwcnBsowNhF5oZMJ3nFhIyfRWo7/pVrvYDj45fhgbbrAEXVR2Mb4M5pPUCTjf60NvDs1ZobfiWQBmddJ2u99TyVqp7KbqsnWpqsIjpcTjBbf1f2dNx0tAtO4BGsreC6iz+/0kbRuvtabfx7MojUYRptopbfxn8DWejB2/Lh0rHdP5r3vCYjVTA5QKKwfaeAD/OPBSd9rwqDe8eOCWqsGjlN4TXG/q52I9NEeMulcu4r0NYqdrDfiA91k6W5jQoT7h6nqLw25RQsiS/BtKYbW0onhHzY4dDt/Os78cz2ZscrW4yfuE4AGM+GvLxtM+ck5J3TW7V/86fskMz8G3IJwEX8JJmC6coCjsP7pT/+jYPzYOs3E6n03hWzCZj50ZVXh8S1PNOIuu7ehpf/ZoocuuaUSLu2L1YR3n0+tpdDPNIrPLOqgWyirDTcZjCCZJhOfWl9lzisHFFcKB7VOi7dloNNq9c/4D
*/