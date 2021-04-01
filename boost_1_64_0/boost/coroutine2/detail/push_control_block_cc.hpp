
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
Cyo8w8DNyGzGaDdnpouLvrp97401lmlFkYyu6FfVohnv+k3FKAhGt6dYD30gaQ5p/yFOz6Lp+iokVH3wLvyJwb5RXRCsmS0UAJO5Zxy7czaH5DVUK1NMnSco7DnvNEYvL/9SCMLdsN11AhYliKEoIbMGNv5tjxLqhw3AnH+TC14golIc3FHibG4N5k3D8gXocZoRaHyLydrGLdFnRU8P8Oist+GeA0DSJ45lna6fm0JG+mRLAavQ7F+PAjrYhWe9P5PhaD1xDFt25ywVgTkNoqNG4Hee7i0KRFN3Xo2kFOrTr4kptRIfZKY7cV42TQJyEu0h8CC13ejhTs5mjwdoAuKZz4T+CmQs2oxBDGurrKSmA7ggSgwq6yetize6csFjkGU1Y/VJhJGeTqCvcht3KL/KQpGerthASt7LDVTQyrEFzvuvp19d1vJ/sI35c16YIwxHAbi7m8ie+xiregOb49saV2zU/FdSNslwJYVB9lR/bvkve8FExKj7bm6mO9H87L511XjEU/oNtgS1+AmQ2z1PlhlRkMRFMHmGk/0YtDj2GQqOqh00hQDO1Q==
*/