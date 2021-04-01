
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
Z0eE9eSGfv5A1IWPxNpTMaqC4Lt0b5XgdB2O8ZJdrISkNRCTHYfVEiS+y91uBAfPtVk5skEZm2IY/bG/0cHh2t5Cd7OcTEn6XhwoFCm6pYcA2JY7q6M+6Al3dtpBPyS/nToEoZ4ni7rLFyoSAwBB551NOmorC36ALXBMckv4C88k+D4XmrrRU94O58u/RsD/+Afvdy0cJN1EccJRo1eQsmY45wmA73kgFBtyhU2xuOCer0tZ34lbv4byjrgDDElOTr2WvpX6DBGOo+SLF+mkJ3PwaqCSubbvMa8ElzGx1JBFQ+Jc2gaCHf+BbzEFyLnbivryMa3dSbNlPVuUGIJPOUZYSBgD2XthuxQvDGyJKWD9464OA4uoeLmY9OWWOGb4kFBnV1CDq57uzbQiMkSLsviGWfbLl/ZJ9ZgoyACFaGmRbKOZAFrvXExvbe5VwTIWHu6iggddb2lWpAEN9seY/jYZZWA5Vn2ji5o9fBbb17PZ0ZnJHPTFyqjCg+F3mTUpmzhs0YZw7XPufZ91UtVGOtWZk8I/kGXkrmm39wXUeIXkqzoEnaqXofKDtw==
*/