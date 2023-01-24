/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_trivially_copyable.hpp
 *
 * This header defines \c is_trivially_copyable type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
// For std::is_trivially_copyable we require a genuine support from the compiler.
// Fallback to is_pod or a false negative result in Boost.TypeTraits is not acceptable
// as this trait will be used in a static assert and may deny valid uses of boost::atomic/atomic_ref.
#define BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)

namespace boost {
namespace atomics {
namespace detail {

using std::is_trivially_copyable;

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP_INCLUDED_

/* is_trivially_copyable.hpp
WUsi9Q4bPjhsgJE6+aZl3zXP1wI8eu+500ju+MvQhfOXwf389+OeJ7sB/LebOUf6PUJn7h7As594KQaM+5pp5Sd8c7zk5xDvyTlIgLVTtq9s7cLV4mU5aMbh8JMjknZdwZnBXzzdsM43sQVk3gpi3gYzN7Td+FSi05cHeFc13neQ0a/YHwnqIb3qeGFdyRNspafYkpk3wzuP/bboBYBDQr8ihIRnM74Zhb4hr9ANrxvItvrJ74vdWppYbs1A9gxG3Fa3SpCzpLPoE1m5PkAYk6KsAEAx29CvwS7sgtXedMSPHQy08sdOKRnrSh18oCj+40Ps/AfZilIvcebJ35w2D+an/RIhHJ1DEsdFVdZD2nJRCnR/NVqFPE3if6Otnj9Kx60bf+XqerB5MbJpNxsAUYSIKsw92cZRFDYl7aMs2ztL95FA38E4fSu5TiMPQYfCZUcgyyNT6AcYegAqjP5ygTiz7Jmh9Nnxx6MQ5I809uVgGUPagG8UZWOW30NEJVR+ZIBngvhMvqlItc6YWAel5BeLFQLmBpuWJIJQq8WmZwycnHjNtOBf4fjzTI61c5YFeyG31z7QQRqYv9pu86zxH+ApvdIzIdfGQHDheQ2kDSJs16dEhvdMHpAOz++VNQYEFQZJK2LB8KzC/DZj6hR8Ja7vqALCjJDjFSGfoNa+2fBweDp8ym06CE3QNkSLac4L73AdpZayGPG1um4g
*/