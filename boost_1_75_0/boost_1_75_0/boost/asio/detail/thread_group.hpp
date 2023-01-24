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
9AuVBt+UXNWgLjZ2J1QoeWOo5FlYbXx4tYtDkSnYpHdw7HjIcHRA36ZVeAN8VdbvAeI01b+L+Mp31OezSNujtZTqvpnWobyB3h6Qw7EoELGmruvSKOZDQ3d0QuzZLXrdrxq6gw2x/lDsr1GZmqyDDZEvhiL5a7M+Gop1Y9ad4VlXhSLRu3xJ/0SDiu2SJkjnIsfGUA4mBk22bTdBilbciQb6KVsEJHPsWySabhSbt1anGTzRHt5INUV7uV5lPU4LHabXkW4Z7bW+ix09sgchcqFCf8NdQ4h/0AoUNjEi9FrCybBujZpZWNQj42o9Y4ZMx45Yc6l1Ksa1PoDuWIJmwX5EV7FeiUahRwxG8OcDa8hvgE10ZMxBlxz80EAqm5UcX0DlA8mGr2AZDxw2yg1M93Su15xLCimryXCRsmeoJQGqaZTXkbxKzmyw2slMLf6Bs7C6uE37evMcPVREfH047khmWVlRKSpwE4tXrFpdVIj3VLtK195fuuLBqXjf6LR17CNxzYoHixKFNQ+sWbthzR3cDvRIignmrFpDf50b15UWlZVBQTTbjqy1pYmrQurhRPivZO2GxE1rhdJErciVK9bA/0JZUSK8rNAAiUFAhNKicYllRUWJfElRontVmbBideKMlJTEwrUrhQeL1vB6oSxbGZfswuoTFxTxpZsS+bWJhUX3CffT3CvWrVu9aiXLMD7x7tn3Jj4olPGJ
*/