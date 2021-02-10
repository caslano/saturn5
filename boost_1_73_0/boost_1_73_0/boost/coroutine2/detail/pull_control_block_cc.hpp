
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
PDIaeTW2/2nAAnZUj8nL7nwwY+TFL4wno9nofDSY0pjzK72/ulfjQc8TFqawV9FvOzNaKun2cfDKbJ8WD+DfmrdHI5wWHkY3XprQyFyJPzhEqFWU6FVLF+lhGF0tfya7e9dA6O/ifTkKGodhv8H5shsk9hrqehUifAyYFIKrqty++s/XlHLvfsCG6L7tD/qzazb+0tpgq9JreY3nBYo0/HI7iTqn0QtvN+nN5pMhfOgO5j02EQ5/j9i610bvQWZ19/tK0q+MACfSZr1pPnw/HH0cxiN/gJEBlhrHkGE1yHwWjy7jq97VaHJd42EbUjh4JlRZJhMpFIpD8BK1j4M5lLsx7fWgO5iO8BB/O9nlLp5Pe3FvjMpt7B8fIIvfeDn9sH3J/gdQSwMECgAAAAgALWdKUvd5UrdGBAAAgAkAADIACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZUUFNTTEFVVEguM1VUBQABtkgkYK1VbU/jRhD+7l8xcqUqIJ9zQCXKlZ7qC6G45GIrdo5GimRt7DXeduO1vOtAVPrfO7vrlPAiwYcLBNvjmWdmnnlm8ZcuHH63j+NrOHjzk5lvhh+87oLiVvxFc/V6QJY9gP3BwCVe35FqCI9RD9kB
*/