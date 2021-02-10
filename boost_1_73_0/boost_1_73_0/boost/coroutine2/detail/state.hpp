
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
qtvfEbHLMrDcUf6GZE+1FyAFVQVukMA8cWHDNNceXM3T82iVwlUQx0GYriE6gyBcD3gX8/CUvMEpqwK8bxRqqkIB3zY1x+JZ8u866Y6fnsN0FS+iZZqdpcssmE6jVZjCIbgHx/BHK6y1f3LBrfnGag9H/uGRv08L9l+GTD9kGo1Vmb5kKE2YyTmEweXMeQ34eo9kpSHIc9kKQ64uJZTUKu3pApN1GC2TeeL8wEVetwXCic3UG6/66HSguaT1lwWM7Bv4UJElanLGK8nJgRVT8GFIPv61y3g6S6bxfJnOo9BZMiKeQSO5MNYSNAUg2rres8bggll9rdLiBkZUdLhaLDofcW0HZezDVYWd/LYdjeqWQJj+qrsW3V3TBTPMBVbaFDQYCgTbYm9lyn8nlZ1gDRskrEbJW15g4Tn97FKoNZxGYQe6pHhbjLUrNZnSnGy3BOQ7jp1r1pB/cmZ1Ia/T/Ahp+sOBiv6K2HSBQ0NMUXHFUBZRanpgmpxeWX9g6yxYLVLHtt4tLOMojabRInF2Es7+DC6Xi5nji9LpNemc89s3inHBzYj45+XILo7hbwf+L6hdeBKSbh64pWnoGMJ7RqOBPrU7KaX0N1y4BPc2yDM3uFVLZO3RtMlW5agHCEX+/LZYOlhIvm1f6Ysk
*/