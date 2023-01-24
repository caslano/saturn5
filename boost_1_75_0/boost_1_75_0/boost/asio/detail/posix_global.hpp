//
// detail/posix_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <exception>
#include <pthread.h>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct posix_global_impl
{
  // Helper function to perform initialisation.
  static void do_init()
  {
    instance_.static_ptr_ = instance_.ptr_ = new T;
  }

  // Destructor automatically cleans up the global.
  ~posix_global_impl()
  {
    delete static_ptr_;
  }

  static ::pthread_once_t init_once_;
  static T* static_ptr_;
  static posix_global_impl instance_;
  T* ptr_;
};

template <typename T>
::pthread_once_t posix_global_impl<T>::init_once_ = PTHREAD_ONCE_INIT;

template <typename T>
T* posix_global_impl<T>::static_ptr_ = 0;

template <typename T>
posix_global_impl<T> posix_global_impl<T>::instance_;

template <typename T>
T& posix_global()
{
  int result = ::pthread_once(
      &posix_global_impl<T>::init_once_,
      &posix_global_impl<T>::do_init);

  if (result != 0)
    std::terminate();

  return *posix_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP

/* posix_global.hpp
11aRtrEHgJXDR6j38hY7RlYcxAV+p2MRv00c3oIb8D2uqMCbXFGRrCkqaiaSn9A22gPzCaoYLbfI73nNMtXCQXFVxXZinhyjVHVFqo+rK/iEmhBCMxb6CXObOOb0atE0g8s5O0hblX0ZvgCno+x7lLZINxXNtbHBB/uoNLAEqTTo9VzWMZ+rNHinVZWG+mzJ/IBKA3UkmlYAR2SOZ1W31q8wlca9nVylMU9TaeyIJJWG3QykmuSWwNS7UtVoVPhIo7GBEIWcHGk0hlG0fWDWYZ+Ds25Kb1ozuAGzVug8mzuDk8/g2UHExNKuTb8yg2ennvRVsE2KWQGJ5lB3WF1N7aF1HeqnLhTgPBNC6oryTCNpN4GTTdQllKjgHcOE10OYwuM0CwJ1rWg//2oqD6lE7zl2LpQ6vq7zUACnWk848VsRUklMaCXir0IJn3c2tjVDgzEgeTvcFkbeblFCl7XuMblJPmdp984N9BkXJKmjaEn2eKeGwCoLh2VUwkepR46XnTjJdqeKY1N61o9ea0j5aPUw30lUTQ2hOUiPfxdUTHF+S1NMNft4AVJPqYqpOq6Ywunl3vcSVoO6KXoPdVPwWLxGrkG9VDb7TYKql0JpGHum6qRw+vK6UCeF03i+9wDnLtxOhElqqSqfppbi/BIQg9iKG5OESrQ3z1foeX10Ev8SUxApd7QGkOKIkRs8uzBnjy+yXd7bRli5VlVu
*/