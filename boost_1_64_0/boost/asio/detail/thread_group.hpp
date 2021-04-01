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
PFpWD3wMCLH554NiYb5a5daP3wc63PyvZLHXAD65dbj8WdnuhP0VTxdDZURGoflxc/9v+KXpGtiMyP5sdoa5tEI/syS4PUWsPyxAMByfI4OOHnrYkvRBMih0TM1lV6habXZFPLEzEnJB+mkFhKIVkGgrew7CeHtVa7ZGMDDzevmY3GDUQ7fyDXYwU9oeuoFhI294Yp/bhsL/iO3gw6Ap2m9q9f6+ujsUlEwEkJ3ebhDriUpiWoFwIg4BEKuaMMsxVepwVleLM5TSE9+vs6zLn/0Z3CGVHjxh9KOAswB+RSkQ6bzqW2XZho0dqw3v7bq1ImtoABgWcj7CgOHGudJTzz7PskHQApCui/nrd42gmil5EwGoK1Ilny5BLKi7zeDOEf7dKg0DXgqC15sK5Bhvzaf7A5diksL1P9NoxSHnC7CPJy9aNucfBnXlxpH9NaPkeLFzU15ViR8B3Om45D7p92BA8S61uCuX2dHgp0wgSzjrsb6Jtxh8lkgiJQIkLfdEBLxJA1b/35YzHqzUBu9bVHLCqWJ1yzyu31S2j4YPptYjaTkXl3Bn6mUaLg==
*/