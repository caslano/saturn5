
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_ASYMMETRIC_COROUTINE_HPP
#define BOOST_COROUTINES2_DETAIL_ASYMMETRIC_COROUTINE_HPP

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine2/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

enum class state_t : unsigned int {
    none       = 0,
    complete   = 1 << 1,
    unwind     = 1 << 2,
    destroy    = 1 << 3
};


inline
constexpr state_t
operator&( state_t l, state_t r) {
    return static_cast< state_t >(
            static_cast< unsigned int >( l) & static_cast< unsigned int >( r) );
}

inline
constexpr state_t
operator|( state_t l, state_t r) {
    return static_cast< state_t >(
            static_cast< unsigned int >( l) | static_cast< unsigned int >( r) );
}

inline
constexpr state_t
operator^( state_t l, state_t r) {
    return static_cast< state_t >(
            static_cast< unsigned int >( l) ^ static_cast< unsigned int >( r) );
}

inline
constexpr state_t
operator~( state_t l) {
    return static_cast< state_t >( ~static_cast< unsigned int >( l) );
}

inline
state_t &
operator&=( state_t & l, state_t r) {
    l = l & r;
    return l;
}

inline
state_t &
operator|=( state_t & l, state_t r) {
    l = l | r;
    return l;
}

inline
state_t &
operator^=( state_t & l, state_t r) {
    l = l ^ r;
    return l;
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_ASYMMETRIC_COROUTINE_HPP

/* state.hpp
jCnm98oZVFF8nyfF7QzQK+RgcMP2gPJxFvEkuQdX0HMVoWeOblWIPN8F2cvxR2Ksozs3Sr1sc+cJZPA4xUctbeNaaQs2I74L9h0YFCmHWdQ5kdVatSv3fZFPAnX6Uy072bqcA3Hq0R/r2jdK1bRv7ScW1V3bJqWmOI96N6IJN67mA7ezNtJ+f9gPOjKa0Yt5n82UZF694tx8ZNQ9zkgjuwE2hlXegkVt0GwpMLOzIkTTstLTf9Cr5/gWSODEpzfNiVZSR7ciwPBAy8kws+ZSM0+o8BD/rcRez8t7nk77eWJdu65VYnq+q8bTtU8wb9TLMnL0vdTvcnOMrT+hnpPpiBeWKLC70K6DV1VJng+J0AGlb6Jeur48Wn0x1vrzPRYriCOJuAvWpCR6GrolA9WwNYIby5fSdvQxlOnSBxwOpTdtrQCjNT2S48w03yi+ZF9VXDgDs22QYO0SGqqV+F/A3UYsIXctS/DegKWCRE0yRxgugix4hf1DtK9tEl8ofKmW9QNiii9o1NtODH/9k5cnQ63sZZNc0cz2FTgyjxVAAegvmmvMnglAr7NK+w==
*/