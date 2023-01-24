// Copyright (C) 2000, 2001 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOLFWD_HPP
#define BOOST_POOLFWD_HPP

/*!
  \file
  \brief Forward declarations of all public (non-implemention) classes.
*/


#include <boost/config.hpp> // for workarounds

// std::size_t
#include <cstddef>

// boost::details::pool::default_mutex
#include <boost/pool/detail/mutex.hpp>

namespace boost {

//
// Location: <boost/pool/simple_segregated_storage.hpp>
//
template <typename SizeType = std::size_t>
class simple_segregated_storage;

//
// Location: <boost/pool/pool.hpp>
//
struct default_user_allocator_new_delete;
struct default_user_allocator_malloc_free;

template <typename UserAllocator = default_user_allocator_new_delete>
class pool;

//
// Location: <boost/pool/object_pool.hpp>
//
template <typename T, typename UserAllocator = default_user_allocator_new_delete>
class object_pool;

//
// Location: <boost/pool/singleton_pool.hpp>
//
template <typename Tag, unsigned RequestedSize,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32,
    unsigned MaxSize = 0>
class singleton_pool;

//
// Location: <boost/pool/pool_alloc.hpp>
//
struct pool_allocator_tag;

template <typename T,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32,
    unsigned MaxSize = 0>
class pool_allocator;

struct fast_pool_allocator_tag;

template <typename T,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32,
    unsigned MaxSize = 0>
class fast_pool_allocator;

} // namespace boost

#endif

/* poolfwd.hpp
KpE0/N19d4rj39usFECFHm0QJeG/F9Ui3T/JPuYi3ctx7IGHa30Yu3P7cdOPnYbFdL6c3hQzL5epqZaWTx2ulVtM2qUL3qdWVnm/05TlWTKqOto77slmNW3x7XYHxq/5Ac7tra2TnJXTlFnVmUV6JNIj6wJdC00EjjKcQ+UEc9nF4/YbIfBO3DHGZ3AtjefbXKX1zYs2hgZ4LFKLxEKd+XiJxW3EWZ5oGUG9ba6Xa02VtKvhupwlwW2u3u1hmkuOnrLam8R2cPPNSsTCpuHn0LbKkxPr9RMsnEUcJkb2lg3SKHUb82f8IoUC7daFeUTktdCmz3otzeh6VpyjDxGA0QenmCZL0/D3rq5dqUKGzk92QcIWzxLPv243+dDzz9p8/abSkqicLYvGMwmAnnJT3Xa71I9rXD7juSDG1QutduEb7cYoxkh9GgbdFmCQsFPs5bbraN691GzNk5MgefmksWcL3hg7cjhix09GaMws2hvrc1/7M5nBfXkKeDzABA1HqVJ3ebu/bjg3MuFgn5gpJzZ7EcfYTupDijauceU0wkQPPmE4227vpOm3jdpa48e07Q400HekACPiyJ3fEEev+4zPJbi2Y0IkbWgljddT2CyiNzFF4RWT3aORnwotNXffOuVZcxhFzQE4zPZRoHUBwJm+lCoDxMMf9d7kgEcZwtRe/Rr22UGI3Ulr05J+wXeGWB/eXeyg0MRdjod4
*/