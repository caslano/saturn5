//
// detail/null_signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) \
  || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) \
  || defined(__SYMBIAN32__)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_signal_blocker
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  null_signal_blocker()
  {
  }

  // Destructor restores the previous signal mask.
  ~null_signal_blocker()
  {
  }

  // Block all signals for the calling thread.
  void block()
  {
  }

  // Restore the previous signal mask.
  void unblock()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)
       // || defined(BOOST_ASIO_WINDOWS)
       // || defined(BOOST_ASIO_WINDOWS_RUNTIME)
       // || defined(__CYGWIN__)
       // || defined(__SYMBIAN32__)

#endif // BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP

/* null_signal_blocker.hpp
WR1bnHJT+sNu0pLR1LtS/VmK96rJfGm8yCZ0XIR4tULWIJSRnLB7ESIayO+vK4ENwBXuuA+a8s5fnntSQzdpH9erUs7V8Un9VEQ+ekmT7TdiTCMLIg2RXDUDOvsf/4qtHJaCiuGUU3qKHJHX3XUgRHsRnvJyXgc63aZohZN56mxgv9niXn8t5DWKP6i9MTAWCibB8kdHkNHFF63BdUb5rW7kzHTo4RbsjSzySbnsk+TV/SP1nTw53lZkYSGJjMhalUldpL1+CkaOz7MvFmQVMphPInA6DhsfFxx0FKjfDI1HEJv2JfD9RfCsfTwpy1lIqFuCo1xrTYpwJq3PLnXgMcZttFR36VsBxa0lytCqXlGZ5MPbt8fXN9C7nK1RLQSHvb2XvR0NmKOFiQzifTKKL6973oXqO12dAR1lgCN1NNe4v9PxonP/YOdQhfeFU6YhJ6wgf65m+CcHREfxzzixbsF4Wq9hf0KLJawAbtCABpbEKUqZK0TLURGhVQ/HXsCg4+zXVM9E+pjOmier1P2BEoYnhXLToFdlL2olWYWIsqBNkNQI7ySVTXQSYp0s65V+HJwnC7zhhq6bJQAO5Z7ejoxNgvRDX5NaKoiOSWCx6cXHEZyhwrSSgCnhgOVfzL7orVzCBOg74oK7fsXO
*/