//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_ALLOCATOR_HPP
#define BOOST_BEAST_DETAIL_ALLOCATOR_HPP

#include <boost/config.hpp>
#ifdef BOOST_NO_CXX11_ALLOCATOR
#include <boost/container/allocator_traits.hpp>
#else
#include <memory>
#endif

namespace boost {
namespace beast {
namespace detail {

// This is a workaround for allocator_traits
// implementations which falsely claim C++11
// compatibility.

#ifdef BOOST_NO_CXX11_ALLOCATOR
template<class Alloc>
using allocator_traits = boost::container::allocator_traits<Alloc>;

#else
template<class Alloc>
using allocator_traits = std::allocator_traits<Alloc>;

#endif

} // detail
} // beast
} // boost

#endif

/* allocator.hpp
aaDZ/7zD3j9repFi0CPx2y6EoMjMZ7vFQuNsjPgjoJJwl9S9AeEkJacbLxWV3Nny68rv+fLbJL/N8tsmvxcr5Z38Bof42ye/YfndKr+vkN/r5Pf58nut/F4tv3n5TcpvXH7rRfF3F7pH0aotau1WdcXkVVfWf6TagX0LPB+FpxBe9r6dp4CcQ8ef+I6r8k98Zy2GLL4n/gLHAcN6Z3UVWPAF76yvlcAXqUBfvby9RL25Pt77
*/