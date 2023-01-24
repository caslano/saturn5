
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
KyAzXOol1Zx8rHnjNM1t7RnfIOd+gPjifNWffCoLIu/a924ilBuxWMuPxi3OkAszMVkiEwcGENkQgXPYtLgMTqeN+qbCQQe/Zmg77qMxf1ym4OBnqt2Cl2qsJNJtwiykxfpPft0uJKFkKWOlbvPiwX6sN+wft2TDNyw+lKgPjWOqFOlFhKPLz56xe41rGkRQuQ6V1iVFNRdFakV+qnvlD+kTb5lBb+QIDnB9P9kEUW34MrDmyoU2hTWFM9URa8Cm5OcwVmLV4RQNUwqtGj5179JUZMFqSefg/t6EN2Oat5slZUEH0ir76MfdqeFP5oAqUxe1KFF+yLkpK3tmTCXnyB56vcRUl78P3+me8m/TenyguRGjLsJzpu/1t4z42Rc/gL4QO1756lRjkaxMSDdvUykkx3b7r4ScRVAcWhaGEyQECPQDgltwCBbcIbhDcHd3DQ790ODursHdtXF3d9fg0EgD3T0zi6lZTE3N4u5O3dWtW+f7T31nSQK+eYIfQWa5sCJZUwDA2BHN7Ly2/9GjW3l484iu0ml4gUTUU11MMi0A4N/++sLgOtJ3xCq6ZVqQ9wH6nF6MKahxfNaD1KYdkwH610dZpWLn1qxdSdTzmt4rIN0njPxqQI+dj4jg7XxC/a0HGvAn+x3ZD2NEMs0blfdxC9eoXi4kb6OhcFJEJ0ZjVGaV5N12Jlw6OexGqRR5HIuIu8ELCUnTWHkQ
*/