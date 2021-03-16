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
wzgDqgP9AAyPiXydsAZR70vQPnXwO0TrqlbhidTitvWEiCsxKtSXYt+mfHpAtoByb9KH3ptH09+wQxBW1B5CgnX4QU/cst3U3NXGd+7xNUt/ofkrhlx0pU0A63JCa1d0f4ILnCBE4PvfINlEWMMMC9p2DTQasAmSy5nsOiH2K8F+Ju2Z7Poh2jqqDcgMEnSQPEuPUXyNiO9IFRfUWIU9be4h2M+fXcebiV8JY4/Fs1ZEWzCd1GNaV5zWlCQR/sE=
*/