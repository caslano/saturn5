
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
ZZ6udG+VpXlOgmWewrKjJ1lCBAPLYIqRZYGR5Xu9JHDKoit9eSep1HLGgmWuwjIgs8wzsqyKYJlvZHmmyrJAV1qgsjTP59Yj20Mh/YD22sXnSJnlcjY1Z8hW9OiQNu3MyqTEppWenCbzuC5Vq92oNo7u6+G6HJtllX4anDZGW6XO1YpvH6MtT+dyeeLaNZG7lFPvHKU768UvMIp/qF58s49k6MWP8JT2PmHxbRZwzr/gytGa+OVa8aLRmvjlBvELXXpPm9JHL3++Uf6r++jkNztcWR+d/BFul6/Ib7NXcDEM9tXJP0wr9ujkH2aU3613288y9PLnGeV/LUMnv9l7p2bo5I/w4etZR/mttyVF0KLgkFGa/CO04pJRmvwjjPInIWwZ28WwRZCg6PHrmYd1NX7dVY5fr9pNil+X7sb4dfq8TuPX2pE28etlI7cpfs0eaRe/Zozcpvh1eYVd/DqvYpvi1wkVdvHr5RV/Rfya9ovXIrLr2Oy1i19X/O61iOzeC3mjxa95+vh1+kavRWQXAEub+HUkWJojuzND3i7FrweApTlKzwBLm/j1t61eiyj9uw5vtPi1QB+/vv6z1yJKf2KT1y5+nQCW5ih9dId3e+NXdb/1QSxzZLcDxLKJ7Nb/5rWI7L78w9ul+PXFn7wW8esDv3rt4tfrwdIcv14EltHjVy2oOwIszVF6FljaROkJYGmO0je2e7sUv36wwWsRv76K6WUTv96zxWsRv1a3ezuNX9UBPR0QQN8LbUPmCOrgdtQmTRq3ErUOqxgqbYPSAEWmKGoT5w1rWdJpJPvFRZaR7DsXdSmSnbRZU8QUymL+GxQxO8yJ6w2KRDjO/npFOo1pky+yjGnbh9vFtJr3NW7SNDFfUzy61aCJ2Q/H/WjQJMIfh/6s06TT6Pbo4ZbR7UHDuxbdbvpV08Qc3i77zaCJ2b1fW2fQJMLN7/tJp0mnce41wyzj3BHDRJwr6K8nKd6NODm++EAp3JVOgrWD4IX9QiEuH9hx+ztuSGCk01qOXwdXD/uzF2BnRn+5RA7EmppjUONrS+f2XdPokjZvFNQEmfQxORBFKfVZTvQbiiSZZWMucsllgc8/tBilDKQoUHZhwFVd55okV7Etg4+6tHFkEGr0T9X3JzzLUJQZavIPfc8Eo7SIQIKoMWYoFBILtU0x0cDQxgot1gotVkGLjY4Wa0RrfaUjFKKdYS5HW6KsNI2qs7ls0Hm8EiEcgiYMLhIN8sLT6AhL4lRWvy1r5dWP65NU0IK9do7ceokjLFOax7jjz0Mn7vi6opntuiBAv4eCW1KiccmsRXcsirqSKxzmY0L20zU5xdTpcJdFpzpXoqKrM1LXpEhdf9+s6eqMouvSNpOu83+30NVprevUtkixJxjjeaeFrkNNnU6NNR5qRuoaE6lrZluErik6XWOi6Nq2xqTrsq0WusZY6zpjTaTY9xuj+hgLXa82dRoeYzxNjdQ1NlLX3DURuno3abrGRtE11GrSde1vFrrGWuva2Bop9vPGuD3WQteAqdM1TvMxLnVt3R0hcE5jN26+CdpuitgPy7gfDs6S9sMF2PGQdfCas9xR6eb3aEdVYkMI1FqLf/QwDvfOq3kotDtTjUylMeVwIpXY0MF256KddstV6VGVKpUtkBbwRK7t+0kQkVVJrErRFeyAP0SJ4U0XR0kDz1biR+2oBWE8zpH2OlsLIbPN50jwOA2IB0jrz9KQcjUknh59dZYGlWs8PTJD4djocR1UngbFM6PbdVB5xjMjMxQOi87SQeVrUDwpKtJB5ZtPigClmDtl/H1OBw7larY4U2pvQ9KwrmRiXeEurRRKl3fGS4J3lFnMKwags08MIn8=
*/