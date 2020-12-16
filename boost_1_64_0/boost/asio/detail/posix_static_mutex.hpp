//
// detail/posix_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_POSIX_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct posix_static_mutex
{
  typedef boost::asio::detail::scoped_lock<posix_static_mutex> scoped_lock;

  // Initialise the mutex.
  void init()
  {
    // Nothing to do.
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

  ::pthread_mutex_t mutex_;
};

#define BOOST_ASIO_POSIX_STATIC_MUTEX_INIT { PTHREAD_MUTEX_INITIALIZER }

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_STATIC_MUTEX_HPP

/* posix_static_mutex.hpp
mO/DfkzEQfyRAF52t6JnQGFcxXkswMH7LOkZUBhXcZ7wc6Jt0/OfMK7iPBXgqu0Kxnk6jIs42D6fCXBevbKVY2/ZLpapfz/bkcckMN/ngpotm/QsKIxDJOJeCHPqnPJiBCciyrp/yeBFPfYY3MvE9Q9k8Ua8730nr/g533Xvq5qTHQPx1/y4erff62Ecxw2nzM+GiM+lk4OhvN7UnC+vtzTuy+ttwtdfbkl4hAqPXrbCtxdWHWgwyL+jef3IdP3GlvLa5d0wr1Ngm94jTXHYE8Pk1vVmmeZ/7zNe5jHmA3WMIsQ+ZMwr9QzL+y8fEQZvQdXYx4wB5MpnU5+YWKOo+vCnCofb24x9prDNlN2fK6ziUAqk/ULh1YbL2i8lhifaZlGOm18hznd9Wfu1gdnGs7FvDJwqlfz0LePVBtX/d3hMT9ZxeYW3dbHB2u8l16B7iT/QcdkR/mPNj4y5W5GNP6ljmAuUaC7+s8KwLjCeNTZh7QalMxYdO9vw8dh4rNdndcnjuuhrtdZoveo0tyXtOMSNlvhcNi4e6yZU9opi6lSS4/t4mtdNjPv0+FGcscZuAuTplUE1uE/Bgu7levj5SjTf0zOGn6904JdamviJo/kll+X4k0TzS/XwvcNJmdenb8InUzjNeTzuc5NrvDlS6hmzxHKyREv0jGHNFJ00yyy9rOy7U/o0Sy7Vs7RMZ6kll2bNVJ00PUuMWZY1U3fSLLnEMj2smaaTBiyTeU3bSbN09xhZruk6aZaF6uS+PL3S6HFkBsKgc/cMy/FhRsJcT3RCY13YTAqvOaPFFoyJlO7MCq+X5fX0LBqryTnzrBIj0zDN2SSmWic/lwngI0Xo03hLn/g5OvCQAOY1p+SpqIjNpbDtnGadyjQ3YVs0wczSFvqe8jyEVxwaTRGblzFvM3ekxbr5TIzb7fyEiaf+4EF9zb0A4jS1KfM5a0EfBid5t7SF1C+kODGWkH5hH9aD44fsF4v4OEHxu2LDuB4k2Z+LhTXoOZn24j4ex0O0Zwk/7rnwwjj5fK9bcXiZoNZd9Chc+pLwJYN4N9k2JoQrP6ENSwV5otGHSyMnp2CU3jI+zByCiV/Wx4uyuo2m+AQa18tyyMtpEmHL+zB61rCCgbXlcxUf5q/vlRSn++fKjDVcfZ5aBTFhG8VbVR3rc1ICMf0O4tXwGIdZkYEY5BFP+nExuCOeCuJLLY14OoAvuSzpe/24GMSxvKsH8JF2rSTLuwZzNSAklmGsXcWug2ms6cdEIZV+LeT8z8z7CMNrcKnrNzD5XCzLmOe0y3Wcm1D9D4Rw8b9Rx2L/DyKPBKaztjzWQsRziIfbT55xcxwpKEyPI+sQpq8Nub2va+Bua1vfGLOe5FoCpnTWZyx4Ht1A4WpAR3xDxtX5ldPeSOG6nQ0hhv0Ajzfm4/YwxdlEHes4NmI4O0N/b4rHYrUtrnTSb43m8hZNXr0Fl7hhyfm7MeZTIg6umyjfMh/DhBGPHT4G47DcI3S8VbHSdvi0hfgo4Vu7rc3YgVS2zRDHkwkMfqR1BbZOr92f7vddf2xu4KPNun6naACn5UiUfkVz6nql6scgX9LWGG86ONDSswjAkol8wbfCRT6LYC6wygXz2FJyZccXp8m4f6ULxfGYC+bTkng9nE+bOb26hcqylcD1Ahc8h20tsHSukOnNJKFpDA70ZZKZdN53X2ubaA2kQfy20bzar7Kd4PsTSXEhKJeFyfJtz5y6wGV8BwM3n9/taOA4w+U7x7hKjOPuZGiEEbL8O0u8160VeYzfRWIZcT+Vn2NIbB28SYXYboyJNQrtKq1x3h2xvJ2EHgL3yjJwp9a3PmuPMK/WZ+0Z5tS7nPcKczQ=
*/