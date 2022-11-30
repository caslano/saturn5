//
// detail/thread_group.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#include <boost/asio/detail/push_options.hpp>

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

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_THREAD_GROUP_HPP

/* thread_group.hpp
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
*/