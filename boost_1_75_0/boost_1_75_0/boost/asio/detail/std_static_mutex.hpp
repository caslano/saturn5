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
K0Zp46cSTXDqWynSEjkPMI+qvyAfmVwCGUpwlZX71vkvou25ykl5OlW04TVKQoryiRj0CP2Q+UEUCxxIovVyx7JyUXAqsbRE64ct0f/FCHIuiWruPnGRITz1Y0EuAUnidwx+B+bIk/EmKyjZy8lB5aSnBFuBuj4UckFoj0YD2rjO56kHHq/ZRc2fYomUpKtCtyRRhqFdnwDjOZObybm5TM4FPCCNu5W7Bb7ncOj7ZseO3E1lfNGDWcKalXhxWGrabRx5SGlXxJpCoJzqEFGTxTR0OcpZTdAs8nEUtJgjoyyqkEOvXYh7q2YVZJlMnzSj1xgY8NY2LGfyNr00bxzdEFwmlTfDxG4Tuwx8jHaJl2TShJ5+VDgTBgBbHCqjTqcZfX9HoeSDOcwe5SRe605+BUG1Zu6H5d1XAWZvUsn+r/D+uyimH2lOAxmriQqLfba6+Di53mvMT/HzI+B/C/y/NMUvzCK3drUzm1JgAgNRVVLI7mnHNu7CR2CpsmEJyHPILPLFGgtefMQF3HK9SGz8bSKJ5EfO4vuTr0boMxxeBxF4DcpABO/CR2AIfCGCduEjYIWv97F8fFC1RbOLoQ5WyGIQZFBcTkLPR+HWyJqrStVp3gLY+W2k1htdFj4GmsVHiF1mIUHOXi45G8X7l2OEkClnF0rOIw3ZhejGAEMmyH1fAczIx6S8E7v2wJvJ72gsHy0feuCgVc5eIhYa
*/