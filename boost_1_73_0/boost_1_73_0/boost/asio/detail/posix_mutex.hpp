//
// detail/posix_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP
#define BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class posix_event;

class posix_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<posix_mutex> scoped_lock;

  // Constructor.
  BOOST_ASIO_DECL posix_mutex();

  // Destructor.
  ~posix_mutex()
  {
    ::pthread_mutex_destroy(&mutex_); // Ignore EBUSY.
  }

  // Lock the mutex.
  void lock()
  {
    (void)::pthread_mutex_lock(&mutex_); // Ignore EINVAL.
  }

  // Unlock the mutex.
  void unlock()
  {
    (void)::pthread_mutex_unlock(&mutex_); // Ignore EINVAL.
  }

private:
  friend class posix_event;
  ::pthread_mutex_t mutex_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_mutex.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_MUTEX_HPP

/* posix_mutex.hpp
fndvj/v2xKsPW05rRmGa+32E17tbZODeqlHs9qfTP9+iB+fmQN1EFru1g+mY7QtUCFz2OJos5C4rUDuT3kmm6GXCT9WMUpdBsTvvnFpNJ6ybqizu6G+uWU0jmdzBUns/1QPNu2rMjumKmnmztVbuD0ItnO8umRjdZZidd125QpfX7467/YcOEVS/4huQQWzrgxWpEz4FbVhZnDciQk93vtEovManjalfL3mJIQf7B2GFJO7xN+6stBiwRWkMm0+9Bsc4Gn8HGIdgASDveFtQUBKBHVIWadm8UFFLiFQtXfyGE3jOrZgkFf7eo9XSQ+qNPLkSKTR1GQsPu00aGgKtpsnVhydkrBzsDPqwts3hfiaGru6/d1C7fbAJ93CFXz2fwmBt8Z/+cmMRnLfXJDSnCyqsvXjeZmw8fiVo1F4JGonwyRpcXfzpEliCZJXtsRDFf+x3+zs7/9Sr6nqDNbG/9VGRNdv/ipCgL50RclvSpOrIQiAX/Du9WBu0+9l9lsiBpjqigUugrsw6abmu0VcEvSqmUODKrcxdQH1jLcPoaA7By/KJjCWMj+NzOWHd97yNMdPrhNSNrabUqC3KyAPmVZS6vcfRX99IMc/WYHGNCu6V+1VFEJU/huvqe1djy7tvOxpRFL9QcAqnxCr/
*/