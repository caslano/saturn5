//
// detail/thread_group.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_GROUP_HPP
#define BOOST_ASIO_DETAIL_THREAD_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/thread.hpp>

namespace boost {
namespace asio {
namespace detail {

class thread_group
{
public:
  // Constructor initialises an empty thread group.
  thread_group()
    : first_(0)
  {
  }

  // Destructor joins any remaining threads in the group.
  ~thread_group()
  {
    join();
  }

  // Create a new thread in the group.
  template <typename Function>
  void create_thread(Function f)
  {
    first_ = new item(f, first_);
  }

  // Create new threads in the group.
  template <typename Function>
  void create_threads(Function f, std::size_t num_threads)
  {
    for (std::size_t i = 0; i < num_threads; ++i)
      create_thread(f);
  }

  // Wait for all threads in the group to exit.
  void join()
  {
    while (first_)
    {
      first_->thread_.join();
      item* tmp = first_;
      first_ = first_->next_;
      delete tmp;
    }
  }

  // Test whether the group is empty.
  bool empty() const
  {
    return first_ == 0;
  }

private:
  // Structure used to track a single thread in the group.
  struct item
  {
    template <typename Function>
    explicit item(Function f, item* next)
      : thread_(f),
        next_(next)
    {
    }

    boost::asio::detail::thread thread_;
    item* next_;
  };

  // The first thread in the group.
  item* first_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THREAD_GROUP_HPP

/* thread_group.hpp
ocnNlEIIgRQ2NLCbW6Fo5bE9RJaENNpl/31mvG6SQy9CQjNv3vukbQxjB84my5O5z7L/0VP+aZ7Qpw4e7kFO6DjmM3CEI2YazpAQM9jRUihsXnLk6KIvHey3O/NgGUcp74B9MU3TmD16X8DV7FWiFgSeEEpCRwNhDw4zy85J43+nSbXRiS08V8+UPIK6FUkb4CCHHI/Ui9DhDAWTzZYpjNo2w4l4gk23gStsx9b8+bbR1u+drrfLere5bmEvhr7YKDDXwqpNAV4en2GIebZ8Azb0QMMlCxVzqOT5Hwj4nTDsdtubJd5nkEVqskcUPQzq1mEpYreW1aZxfzNOtkxQmTyxxKgpeWWz+F+FW3hdOprm8lxLfut9PJm1oknxhFmRrrBn+4agFy6GIH4oBs3mJphjRsBB8hIG9kpZ1BZLRgcoDY2qWT7OAwl7kWINLOLhrD/kK7jWmF/aRAVi0nGCSR6FVyg4WHnC9bvB0fqKEtH7BfUYxFP/AZlYEVclVVC+gpVENGO5SHkrVGP4bNfC1rwDUEsDBAoAAAAIAC1nSlL4kuRANwEAABwCAAArAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvY2VydC1zdGF0dXMuZFVUBQABtkgkYI1QwWrDMAy9
*/