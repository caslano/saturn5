//
// detail/std_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STD_MUTEX_HPP

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

class std_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<std_mutex> scoped_lock;

  // Constructor.
  std_mutex()
  {
  }

  // Destructor.
  ~std_mutex()
  {
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

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_MUTEX_HPP

/* std_mutex.hpp
hlVcD+OX8u0G6Ta1tR2S7P6qrZKFgtMOR1sNNT9zzO+nctxsgfzCFIDzCVNP0xKQ3+IgIK3LaCUpSxZkHrOAZqDRKk5XAcY7eZUcReRwy7e/HvzvfLcw4SwNHWGjV9NQ/kG0/GKMUciz60HDFhdDJO6qgqS9NzIM+BNWPjFvVrxbatPrj4pVt1BmReeXN4317djY7lfyJIHDY+x0DYM9/an5b4iE4HH9K9tpRQ8EpR3DJlvPolyETg9+uwjUlwkoPLyUPD4h/WOU78p/3HRIb/ksXIIWMjPTe0x9YtsSa4pepF8jWgjC0hO+5i0C8MYMMNfuhc7cfYdf0kCVSngfnMwOAT4YXbvpoZVkRblCvbPp5ajfrQVoo0ydSFWOb7nyS7HfjA9eqSx2ZHVv0nnmztij8dpJn2VP9KeA6BT8Yy5dP8N4mfqcJiM9hoO72z6QDdMCEpIazGi9aPP3lDeNv67G3GZCkA71MgIoMQ8PhM2SyaJiGpjgfrL55RjCk7nUrgkMYlmBv1nCRDN4kPc3qQJSr190toeJt0PZH/i1q02CowHF73/MxCqnLQ==
*/