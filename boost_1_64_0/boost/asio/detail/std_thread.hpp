//
// detail/std_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_THREAD_HPP
#define BOOST_ASIO_DETAIL_STD_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_THREAD)

#include <thread>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  std_thread(Function f, unsigned int = 0)
    : thread_(f)
  {
  }

  // Destructor.
  ~std_thread()
  {
    join();
  }

  // Wait for the thread to exit.
  void join()
  {
    if (thread_.joinable())
      thread_.join();
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    return std::thread::hardware_concurrency();
  }

private:
  std::thread thread_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_THREAD)

#endif // BOOST_ASIO_DETAIL_STD_THREAD_HPP

/* std_thread.hpp
vUzn6EJntkH9GGj98qHfYOVwcTYV0CVgzKeaiifsNzmPJUm6CrAKLNwbzKdAMGOJFADRJiCGKW2fUrNkqSJop5tiq6X0MxfiEv+GPhQ+rxiwcjZwcaUNRREtaUiYCHAdiBZ3OIUl9QWv2jqQ0lPW29S9yVHz6oagxQSUbK68QEA4ptD2NbIMoK6AFj1DrJSegsVd8PNZBVZ76AostAC7nJSBHf7kU4QOU2/EE3fIuUHBEMpE+hAJ9YzoNPMWK3T1lx5YRGKnybqxSJKnsmUXBkcgamVHFaDyWiESI7KVt4CyYTBxJEpjCchtXg6y43nUQt0aqspgw7K68HU3JJfKXRd8zBxsnYCoci8ACCj2UQo4xX+zOpKnwEARKBMp0HN4W88Si6N0jot3vXE2uEa8Deh+1AAjOr08VSCTQIG54NiZVGYG5QzwSyh7PstqOz3b06UvjtTfvOS9FGicyaiEAHJ+zgH8273K5JvpS+k2R+QG4Wscpe2E0FnBEL/bLc/suPmHUXjTzpHWN/jo+HYa9lrqjU1I4cSyQ9gsKoEK4huvDR/OSVc6F16pjQ==
*/