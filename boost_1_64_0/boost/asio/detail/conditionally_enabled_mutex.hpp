//
// detail/conditionally_enabled_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP
#define BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Mutex adapter used to conditionally enable or disable locking.
class conditionally_enabled_mutex
  : private noncopyable
{
public:
  // Helper class to lock and unlock a mutex automatically.
  class scoped_lock
    : private noncopyable
  {
  public:
    // Tag type used to distinguish constructors.
    enum adopt_lock_t { adopt_lock };

    // Constructor adopts a lock that is already held.
    scoped_lock(conditionally_enabled_mutex& m, adopt_lock_t)
      : mutex_(m),
        locked_(m.enabled_)
    {
    }

    // Constructor acquires the lock.
    explicit scoped_lock(conditionally_enabled_mutex& m)
      : mutex_(m)
    {
      if (m.enabled_)
      {
        mutex_.mutex_.lock();
        locked_ = true;
      }
      else
        locked_ = false;
    }

    // Destructor releases the lock.
    ~scoped_lock()
    {
      if (locked_)
        mutex_.mutex_.unlock();
    }

    // Explicitly acquire the lock.
    void lock()
    {
      if (mutex_.enabled_ && !locked_)
      {
        mutex_.mutex_.lock();
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
    boost::asio::detail::mutex& mutex()
    {
      return mutex_.mutex_;
    }

  private:
    friend class conditionally_enabled_event;
    conditionally_enabled_mutex& mutex_;
    bool locked_;
  };

  // Constructor.
  explicit conditionally_enabled_mutex(bool enabled)
    : enabled_(enabled)
  {
  }

  // Destructor.
  ~conditionally_enabled_mutex()
  {
  }

  // Determine whether locking is enabled.
  bool enabled() const
  {
    return enabled_;
  }

  // Lock the mutex.
  void lock()
  {
    if (enabled_)
      mutex_.lock();
  }

  // Unlock the mutex.
  void unlock()
  {
    if (enabled_)
      mutex_.unlock();
  }

private:
  friend class scoped_lock;
  friend class conditionally_enabled_event;
  boost::asio::detail::mutex mutex_;
  const bool enabled_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP

/* conditionally_enabled_mutex.hpp
uq1up9vrDrqj7qQ7a3/dRXfV3XR33UP31L10b91H99X9dH8doAfoQD1QD9KD9RA9VA/Tw/UIPVKP0qN1kB6jx+pxOliP1xP0RD1JT9ZT9FQ9TU/XM/RMPUvP1nP0XD1Pz9cL9EK9SIfoxXqJXqqX6eV6hQ7VK/UqvVqv0Wt1mF6n1+sNeqPepDfrLXqrDtfbdITernfonXqX3q336L16n47U+/UBfVAf0of1EX1UH9PH9Ql9Up/SUfq0PqPP6nP6vL6go/VFfUnH6Mv6ir6qr+nr+oa+qW/p2/qOvqvv6fv6gX6oH+nHOlbH6Sf6qX6mn+sX+qV+pV/rN/qtfqff6w/6o/6kP+t4/UV/1d90gv6uf+if+pf+rf8w+KVRRhtjrHHGYxKZxCaJSWqSmeQmhUlpUpnUJo1Ja9KZv0x6k8H8bf4x/zH/NRlNJpPZZDFZjZfJZv412U0Ok9PkMrlNHpPX5DP5TQFT0BQyhU0RU9QUM8VNCVPSeJtSprQpY3xMWVPOlDcVTEVTyVQ2VUxVU81UNzVMTVPL1DZ1TF1Tz9Q3DYyvaWgamcamiWlqmpnmxs+0MC1NK9PatDFtTTvT3nQwHU0n09n4my6mq+lmupsepqfpZXqbPqav6Wf6mwAzwASagWaQGWyGmKFmmBluRpiRZpQZbYLMGDPWjDPBZryZYCaaSWaymWKmmmlmuplhZppZZraZY+aaeWa+WWAWmkUmxCw2S8xSs8wsNytMqFlpVpnVZo1Za8LMOrPebDAbzSaz2WwxW0242WYizHazw+w0u8xus8fsNftMpNlvDpiD5pA5bI6Yo+aYOW5OmJPmlIkyp80Zc9acM+fNBRNtLppLJsZcNlfMVXPNXDc3zE1zy9w2d8xdc8/cNw/MQ/PIPDaxJs48MU/NM/PcvDAvzSvz2rwxb8078958MB/NJ/PZxJsv5qv5ZhLMd/PD/DS/zG/zh2OftMpqa6y1znpsIpvYJrFJbTKb3KawKW0qm9qmsWltOvuXTW8z2L/tP/Y/9r82o81kM9ssNqv1stnsvza7zWFz2lw2t81j89p8Nr8tYAvaQrawLWKL2mK2uC1hS1pvW8qWtmWsjy1ry9nytoKtaCvZyraKrWqr2eq2hq1pa9nato6ta+vZ+raB9bUNbSPb2DaxTW0z29z62Ra2pW1lW9s2tq1tZ9vbDraj7WQ7W3/bxXa13Wx328P2tL1sb9vH9rX9bH8bYAfYQDvQDrKD7RA71A6zw+0IO9KOsqNtkB1jx9pxNtiOtxPsRDvJTrZT7FQ7zU63M+xMO8vOtnPsXDvPzrcL7EK7yIbYxXaJXWqX2eV2hQ21K+0qu9qusWttmF1n19sNdqPdZDfbLXarDbfbbITdbnfYnXaX3W332L12n420++0Be9AesoftEXvUHrPH7Ql70p6yUfa0PWPP2nP2vL1go+1Fe8nG2Mv2ir1qr9nr9oa9aW/Z2/aOvWvv2fv2gX1oH9nHNtbG2Sf2qX1mn9sX9qV9ZV/bN/atfWff2w/2o/1kP9t4+8V+td9sgv1uf9if9pf9bf9w6JdOOe2Ms845j0vkErskLqlL5pK7FC6lS+VSuzQurUvn/nLpXQb3t/vH/cf912V0mVxml8Xxd4Eum/vXZXc5XE6Xy+V2eVxel8/ldwVcQVfIFXZFXFFXzBV3JVxJ5+1KudKujPNxZV05V95VcBVdJVfZVXFVXTVX3dVwNV0tV9vVcXVdPVffNXC+rqFr5Bq7Jq6pa+aaOz/XwrV0rVxr18a1de1ce9fBdXSdXGfn77q4rq6b6+56uJ6ul+vt+ri+rp/r7wLcABfoBrpBbrAb4oa6YW64G+FGulFutAtyY9w=
*/