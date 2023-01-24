//
// detail/scoped_lock.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP
#define BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper class to lock and unlock a mutex automatically.
template <typename Mutex>
class scoped_lock
  : private noncopyable
{
public:
  // Tag type used to distinguish constructors.
  enum adopt_lock_t { adopt_lock };

  // Constructor adopts a lock that is already held.
  scoped_lock(Mutex& m, adopt_lock_t)
    : mutex_(m),
      locked_(true)
  {
  }

  // Constructor acquires the lock.
  explicit scoped_lock(Mutex& m)
    : mutex_(m)
  {
    mutex_.lock();
    locked_ = true;
  }

  // Destructor releases the lock.
  ~scoped_lock()
  {
    if (locked_)
      mutex_.unlock();
  }

  // Explicitly acquire the lock.
  void lock()
  {
    if (!locked_)
    {
      mutex_.lock();
      locked_ = true;
    }
  }

  // Explicitly release the lock.
  void unlock()
  {
    if (locked_)
    {
      mutex_.unlock();
      locked_ = false;
    }
  }

  // Test whether the lock is held.
  bool locked() const
  {
    return locked_;
  }

  // Get the underlying mutex.
  Mutex& mutex()
  {
    return mutex_;
  }

private:
  // The underlying mutex.
  Mutex& mutex_;

  // Whether the mutex is currently locked or unlocked.
  bool locked_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCOPED_LOCK_HPP

/* scoped_lock.hpp
frMwyK8IGBQ8BDsu19BwiqNANBuOSxYftxRrj2s8I3zHsTZMaDqM3bpI6/NbUMQrsHmBGx8VqqisYUZt1MPe+FXvN56FN6CbaIslNyrXHBL6MptwKzqFRHAIEsFI9uRZWolEkqQHDHpha3XPkYkJdcBLO4+Kg+VY/H6YrFeWGq6qrgsyCo5IS3XdjKS1w2ckrx+Keyy7UmUb6iwnvAnASXw8I23tFTNs6yfVfGqg76q8HtmoFtmon5HqOLVRr17CRaRcWycdUXgK1y1kYsaI7Wvw8au43oVD0RfntE54I8+izEFNQSbpcui55E8TNrvIrfTuKMooV3k7hQZcKTxio4R708rnS/5kYXM6JuE7NEdRrnZu+QVnRn6+HEZjnR8t34uiNNrRZCvZvg2fN7Ld99Cot9iwWBOgznMdFIOmyB/D3jW90MQ/SOJ2ogLHxub5OBFpstlnIOnZZKPXX7Dh9GiipdVShLtSC6B1BKDVZphxo2MQLtgW9gcoRbsiewpfo7jfSNh/OBqmX+QwY1QxUHAYwlbPXnQ0KmyZw5GQ53aWQgvybOzSElpQNgPuC7Cmcrp4CagwsaJcmea4NLCQylFS9SygJg7FKjObUb9KL4HcE5iyNxRpthSqHfhdTzLUPp8D5pvprV/TPPIkEMbThcpT+M3PR/5MQSu3Co80UlTNEsF5EKN1DkXP0QZvgbAZk+9J/tmCu4oKJa8v
*/