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
8c0pX+3Gl+OxwO346gyTHE/m9f3X1jIQ8JxcxW8TOYGXslmc6yLA8P349MusBBmrctmWs6s4SVMBfe0o1FgOMQiJtD0UQlOlBAeG25iUstH3Zd1stB+x4VH89s3tyfnl6Z9OT/jgZfxxdlclKQntIhvW5ehT1rDx7g7mPc7v5IQKGsySqgYaRPHAH9O4G0/lEOayZ01WjZNRhrd92VY540VZdIcyk09EnoGc2ddZI81WdqcGdq+h+EDO7UXwsaIPB7qtsqlQ5dt72Z1JBjQayIm+nk3yxgGZGycH5F5ojeC7Ar0qRwIEtBawpndZV4B6dwdCHNuKhRyQDCsWDOTk68rms09ZNsOTw/iPedXMk0ksKJRVhfzw0BrIAQ9PWJqNcoXpXHZQm82SvBLo7fbiN0YKOTk8GcRXwmzwxWiafMoM7l3AXb7Y68Vvb67wbz9+d3l9g18DobqA5SwR+v45205GJBayVqCFMEmCoRJCuETz3fg0qSY52ESSxhPdByUgnMKewOX4+uTszG0OHh3EP15fA5c/54kjvvH19dUZXgrhE7znHp6fXd+QyJTzJhYikgT4jqZHguDcBgFHflcAN2ZV/lmozSpWy8G/Or7+IzBhJoQAS9/vkZjiR9+hzywTRKwbOf5LT20FXXfQ
*/