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
alUm2wgW45FhHWxeREaDuBAyEn0yJCyE1o7NQaXiJ3FE3lcC7ZuKn4dfDu3oNpJzcmIkrkCPLVgNiUEXmNOFkQ7kgFcChIjjpB9JE7ozb8iUCio6BoNRxLpITqKZuo3QyeBxmQ3G5LG0vBitDJuahHr0L0bCkbUMkliRIcKBmAJNMLuQqADjlDmNPDeRYZoC/GBqZv4GoBU5A4V6BxqdAvSFkcaFr43u5/ZZF77WT0/rre45tH+FeuuclX1ptI4p9ZKMxYCX4xgNGY9BjsaRxCCzubqr4qxJ5UdJgFDg5Pkh+t/KYcGZoxM5EFYwdUYUkTUXfspprLDSh6Oz06avA3QSJa1n0Cbj4oWWQcn57gDVmiWYU6aPXvtLzbm5FWSmTMjqeRl2yBtGui8iz49QKNJYSiXX5ICqfiAVBkVW6R03OvUPpPlzt3tC5/168dN6s9v57ajknLUa3e7HTtfrdOun3Xn/NmtQWQel6RioYVYPkxAVsGJOBMW9QYFneeb6D4BQvJnX2T5x1jAyuMiOH4oYdGKVGOHv1d29P2pEZCdhncPNdwwk+WSSyDKJCirxuR8w6FINNKxTKcEhHDFEU7InCULGB0AOiq/oecnhHpVFtlVLo2SNd+QiLYIisdO5iYe5/JSzBN9THfPs
*/