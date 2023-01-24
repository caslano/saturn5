//
// detail/null_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_MUTEX_HPP
#define BOOST_ASIO_DETAIL_NULL_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<null_mutex> scoped_lock;

  // Constructor.
  null_mutex()
  {
  }

  // Destructor.
  ~null_mutex()
  {
  }

  // Lock the mutex.
  void lock()
  {
  }

  // Unlock the mutex.
  void unlock()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_MUTEX_HPP

/* null_mutex.hpp
IyPE2mZrndZ+uq23PDO65aWjDS0v7t9y3NuujNUQyfVbWJnpR8Rv8k59Mi48iTwj555mNsh08mlNptnrhgx/oc5HzPCpZyHDv+k7DP9RprUQFTN9QqAw01/4Hcv0r/lOzfTzIdPPj26NbxTL9OPyWYvQUtPpPci/9XVatv+zUZjtc/mQ7d9ifD/9CG1q8vNg4bdGy40nRFoUa73FJKetwIQ5EWdh5xTJtThV4khZjpIpx8ENVWXZfZ5ei1XGg76mKilOGU98KZJxIjmhByjpZcDBvRixRPCDhBnQyWK3WXDILy3Xk/N3r4R2UZKtggrLo0CFfexM9WXyuuX9QIWGbwYEFXYaLouV9jAfWx5cN85sogs0Qy0cK88aieyEZIcfxtUcKJT/cpxFR8dwUp2KR8y39hn193vmnsGUvxUMYXoTnjLl86QhjBzw7Zh+Bj12e48KSvjlHnzyGP092kOWFJ6gs1tryvXWv3cFgyauGw4/lu80QhN74CV5IjyaXiu1S81ez1XwPrfb6tuVgUTsSsG/2zvgqQrUt5MORJJb4OdU1DU/fiv1+e1Inv8Q/HBNXtHgweNeplE81oaX7E65MkM902iB34NFImyBn/KLk3Bj71qn3IFgUJlYZ3HZ8Sgy+boM7YAoiRFBbWdkBSc58C1rRVaI83zO4e4Y91g4dz2HE2+k9urmGjPYR0+IGNJMfxPpZRvSGfJ6wnDN
*/