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
IgWKqa1wfVNPZj1lguLB1Ql10fgqziSqk8DWoy9lzWBlTez7KxJUzSoYIU7ro98ba++NBQByCuyPKu/S7Fs/Rk4wk6muFh83VvKbOnTEBj+CLDcTXeRvtVInht8B+ftcnU6lqSJOz/a8X/6Us+zJnMHOFNIP5PCq9q+ViuPk2zvgHCmJJbE7FgqJ2qVHNP1SPscF31CpujiXQxBEUzc+z8vR01p5ES8z2ei7Kvdcnr6s+uCH7q2j9wy35RGIXByZSbCHCqoGSj3dxXkTdUCgY5DzGiRUZdSJJsv2lLXVS7vuLQK1x4jtFUzQyhc8ebRL8BEiT1NaK1UX6VyruGK1GTot7ghNdgTf+0r3muvjbSg+a73zVD08QQyNE+ij5ox4vn2q4eMdaCgwz/cIVLaKAb/Jt77qq27UOkAzZYmGffCFC9fRDrQd39cMAV661IVJ5Fn4hge53OUigbqV+Mz9wnrTcrJAuVL7XNNNjujoa8ZQziUUWU5H2rEy84AfPJ53lCoqtef3cfz402V703egQmmq2jxwmAcD3PrOMqw5yOF/soZQdh0ZVEeONQ==
*/