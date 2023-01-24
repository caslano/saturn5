//
// detail/memory.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MEMORY_HPP
#define BOOST_ASIO_DETAIL_MEMORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <memory>

#if !defined(BOOST_ASIO_HAS_STD_SHARED_PTR)
# include <boost/shared_ptr.hpp>
# include <boost/weak_ptr.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_SHARED_PTR)

#if !defined(BOOST_ASIO_HAS_STD_ADDRESSOF)
# include <boost/utility/addressof.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_ADDRESSOF)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_SHARED_PTR)
using std::shared_ptr;
using std::weak_ptr;
#else // defined(BOOST_ASIO_HAS_STD_SHARED_PTR)
using boost::shared_ptr;
using boost::weak_ptr;
#endif // defined(BOOST_ASIO_HAS_STD_SHARED_PTR)

#if defined(BOOST_ASIO_HAS_STD_ADDRESSOF)
using std::addressof;
#else // defined(BOOST_ASIO_HAS_STD_ADDRESSOF)
using boost::addressof;
#endif // defined(BOOST_ASIO_HAS_STD_ADDRESSOF)

} // namespace detail

#if defined(BOOST_ASIO_HAS_CXX11_ALLOCATORS)
using std::allocator_arg_t;
# define BOOST_ASIO_USES_ALLOCATOR(t) \
  namespace std { \
    template <typename Allocator> \
    struct uses_allocator<t, Allocator> : true_type {}; \
  } \
  /**/
# define BOOST_ASIO_REBIND_ALLOC(alloc, t) \
  typename std::allocator_traits<alloc>::template rebind_alloc<t>
  /**/
#else // defined(BOOST_ASIO_HAS_CXX11_ALLOCATORS)
struct allocator_arg_t {};
# define BOOST_ASIO_USES_ALLOCATOR(t)
# define BOOST_ASIO_REBIND_ALLOC(alloc, t) \
  typename alloc::template rebind<t>::other
  /**/
#endif // defined(BOOST_ASIO_HAS_CXX11_ALLOCATORS)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_MEMORY_HPP

/* memory.hpp
tvx6iX9eqxhaviGe251c/CSeaTl3a9dReFeIe2UbJDfKDP+9K2jXsTkbzn/yST7Rkd6kQHpdm9XMD6u2+Z+FK9k48qkoUIL/afg52AhYX5q0syGm9yPqjvSmEulbbrdNaAWKoKayPLF3+ebjW7t+CSRtWJQxFAnh86QAt3sPVimdmHqKvyi961SDCfpFAEO1OYF7reopuDW1fePwbCkQaLVU7cG3TDynNHE1yX78AalnSRpNBFjRl+KtbagOhh2tChxF/h2bIGOnc9p3LMVz2I74/Cnw2eA5D/4uxzx/B27z6dsxnv7e3EuHl6bIL1fqLrGlhO1Atn8Y/Lix+XTYU7vxG2KFH/ellc+FR6tjpW7vjo1Yxt4b6O8qKm8m/MWkcy28K/mT8Zr/Gpyq7XfQ99nwF7rGKb83lJ2Yfrnfg28udrIS5PZUzMMPp2I35JE7eoE9KXwr0RPB94Ziajt7MufxwreMPDPnFuBL+kHf9gy4791+Kda03Ul/52PdXd7tK+jOcvp7F/29h/6upr93w996zwb4a/Ztx5nlUHNqkfzgvWy3oxvCHizn1nC82NBs7a72YwnVHiyhmt4F6fo/3941WBfjxq6FeLWJ89Dxgh7sAZ8HuSHZxVqbj13wz8XmzMaZ4N2LuG3PAO/5Z8Tuizi3B51cdx6/XexewCeL3Qs5z6NwqZdIDG4CYa/OM8++QpjkX2SpypwpjJO+
*/