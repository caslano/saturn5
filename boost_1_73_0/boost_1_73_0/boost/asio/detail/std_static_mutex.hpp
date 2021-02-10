//
// detail/std_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#include <mutex>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_event;

class std_static_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<std_static_mutex> scoped_lock;

  // Constructor.
  std_static_mutex(int)
  {
  }

  // Destructor.
  ~std_static_mutex()
  {
  }

  // Initialise the mutex.
  void init()
  {
    // Nothing to do.
  }

  // Lock the mutex.
  void lock()
  {
    mutex_.lock();
  }

  // Unlock the mutex.
  void unlock()
  {
    mutex_.unlock();
  }

private:
  friend class std_event;
  std::mutex mutex_;
};

#define BOOST_ASIO_STD_STATIC_MUTEX_INIT 0

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_STATIC_MUTEX_HPP

/* std_static_mutex.hpp
YlqIZhZCtZlnlweFQ88wCkXMdKfJ1DYdzQKKHlkMkuRRMif2CfaU/hCPkXP9bNHJTmjaxE7orCv1retqgVwvkJsFQheQqPUFguXhRUZ6r6U3YLB4H9Kjs2wKYPQ8f202oK0yYnH9D9cDelkaLxUIuGcuqrQYe0ewHdjMuChKYu+4k1W41jxtIKIXGOmFYW8lNsTxXUHADsJ7XPDi4u3DTz+8H94T4rxUAS8N9k/b/+6z8eL/UEsDBAoAAAAIAC1nSlJW0cnm4wAAAGQBAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvYWJzdHJhY3QtdW5peC1zb2NrZXQuZFVUBQABtkgkYH2Qz2rDMAyH734K3XppwqCUghljo5cexuihewDNVmPTVAq2knRvP7uhY6cdhX7fpz/vwp0F/Mqa0Gkzcrw1WdyF1Lyl0nkeUMOLOVA/WNgLMzmFKeIvAp8FAS9XjAwP0nvyFnbtdtM+mWMSFSd9tnA4nY5mj0qdpG8LbvFFYdM0jXnoNSQZuwDI/01ZQ+SshB7kDGOO3BWQgElnSZfWfIiSrWVWVMhB5nwP1IMq8te+GGFIdI438jDHklm9rtZQMJoomUouvwBM3XglvjvH3gOLQsCJij1m6MtGdRcX
*/