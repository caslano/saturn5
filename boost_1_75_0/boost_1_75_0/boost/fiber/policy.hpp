
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_POLICY_H
#define BOOST_FIBERS_POLICY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

enum class launch {
    dispatch,
    post
};

namespace detail {

template< typename Fn >
struct is_launch_policy : public std::false_type {
};

template<>
struct is_launch_policy< boost::fibers::launch > : public std::true_type {
};

}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_POLICY_H

/* policy.hpp
Gyn1WUsGMNABWNa5tKxhIbiszq64rMtCyEgJCinucjJSolBc29dzIyXM27AwFh0No9qs51F8wpz9ewMZKZF2E1voWrBBgLeM1HfJx8blqPD/XiKZ+aCHeB6Jht/8R+HZG+9+8x0yFbTJN0xeQz7ccgFn5dlXnJcYf73AbDVt2QtAlqtcVBtDV3TNGYjRVjzCeLZZjWz8AyzyYSImThfdw78XAjP2ETBJwDnxa+iX8sEy4o7EAtFs2sJW1+WWypcukSRqY+unMZKOon2yKwbvVvKbB0GvrsZ2TzxKqC2N6mB7EpDcmBCaoXchF4YGc7BJm4NNYg7wjuzSEEBs7/GYAaobfSig6iKgj2xWplwrUy7KCJWEJkCjaVRPYb7q65mB6BTV1fEQjCZfOCavOG2gK2rbDbjcYbBdGaM/BLcaCDyWkOAjYXyCpg8A0X4wHOKnypShJPFYZlC1t0u48QkhkoxfL8IKUsclSKpLiqROHByhPgwpnglxDUEKC8ZCD1xHlYKZBnz6C1WR3HwJCWGA/KB7FpkMXbQvI1J7cEpyViI7JwGiw9ZzUwExE9295ovXx6lTaeN18axQnoVJCENPFMbqQwz9ax2vT9jOdvaaa9eR0+0d3Ok2t7byxQwP474F5DA+xwzkYbMPeZgi7F/fJGRwP3/2Roy/cRhxm7lvoo3AbTxzAr2OocdIegx/k+gAxyPk3ZFh/vBTEZrr
*/