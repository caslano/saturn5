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
qy+QVnCgdzulvR26ID+aXBY1d9GvUfoRjqNYmjgsx37KZgNQ+7l0zIySyH5YSYB8aGExig4Lz4ummCkv7O7W4nYfMbDcZJ8AqZKUzu8Bya1rI21qYtWtDBUrnVkfoZqDNVtHYnvNLGfXI6gS9ZWCKieljI4nxu4PCddOi+KuDIa1TijQcfrj5bBxRGT+l6cRiVO53kKBhXX838XZ8Fp8HQ1ASe41ARbqSngEc8gXMESFEo5XLDOk69kJUQ0DAsVA9a3qHQxk/k774vJfBcnAlswDyBavCaj79Ry+2hgi4jKnYCzQlm5A9+gtN0SJBYbzIboVJQIOUscuAkSDb4D1FSRJYrExzumBSip3WoC+UTQSZMnGFhPS9CUHRsekcaxAg+jJtDAjDQWCQ4k+qSbdopuUCX1kopVC1aMWx471Dbdfp14qoe4ZMM+f7j1xqyvCmXs0ftaryEdv8YGn6AZI3Sw9WjttVAv/374Fbi5Cr0Xuf4GOpXalgFtg7bt7pgHVYa6ycGixMIU1l0fqz3UNimtn/lxAYEhFgM/TPW8nS3uDDxyaijtpUHg5/w==
*/