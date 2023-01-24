
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
DnO2zaivb4SV7lhu5KmvEY1ovOm0xw4NjKmSPIGitNfwRw7va0/WpKcQ6fQu8re/ku5Yv3nnPfMmeUYqs3nXPn/IdfBieX7eRDZ6gd0zgbpUz1zjcFEllQfBBgkEhR5+JUHD58/dxqW4UcQm3QMRv6psW1JjtlBHrjKL5IusqCteJwOd3eONRM/uGKWvT6+4XjEY4nY0GNlBYF7bQQUD/dE2/cS4He+r5htm7CgyN3enRbLw8YnPGjOXwde3dYQcpsUXxKozm1DGo5jbvk0hOQyQdPneEz3XG1kJLZzsqKnpYEL+IUXDyCvwNuD5aVSOCJKTmgbZKqWr0TNZqA+rDuhmvRo0c+mG//kGuibiHDESORVyWteimtZY9S+6CJ4xkvffsgwAvXxN4jcKq5K8Me1hGceJijeSSf6U8kknaDl9NcGLxgX3s3J/UhuwzOQUKd/zNOCQzJlVLluh6sNK1eD6oN9hVF1afK/qLRN2Jy2OheJsRgX55dmSaZmw5sCfjF/MJoxrUxd4h+eDSh5Z68iR9ZGRdXSbnO8VtgOQ180wPmJieM+1tUhSumbYQuVOIh5cnTx8FLsFyNwKob+riet8Pbkq8XwHdT0EHtMBaHoBf30jr8usxko0eVJ8C3j94k9g9xN92YnGPyQA0Y71b+g1M1Nb3Byy3JzTwScYgeYt3annqecQj2ascu4URfa6crxsXqEZ+BVMPX0r
*/