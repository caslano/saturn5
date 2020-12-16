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
tPCfBVMOsxFmDNy2wm8nzD2w58O+H/gWTB1+74X7iQbEezHSh9+ZwGkwiZPASzD5MHUwN8M8DrMdYXbBHJyE78MkTgYN6PfDLRO/c2GqYbbC7IbpMAxpg/8Y4HZFB7cjMIXKHeYemN1w3wuzZxjopyBtFyPfMKmXIBzMALjlAacBXwTNIZjjMA1wK4fbZphdMPtgUrMRP3AW0JiKb4JmSzbiBqbDvh94GGYkfiesRpnBFKqBFmbaatADy4FbYB5HuAMwh2F2w30X3E7g917gQdiPABPXwA2/s4CJZwJhpuF3NUyHaSgH9RtujwDHTEM44GJgHcxxpViGX8Ja0MG+C2YL7BmwT4IpgWlQfjC7YQ7AKOVzKkw2TB5MA8wWmHtg9sIcgelwGdIBkwtTDrMZZhfMizBHYOIakW+YSTCFMGtgtsPsgTkAcwImfR34DKYQZhPMTpinYd6CCa5HGmHGwCyGaYS5GWYPzAGYEzDpG1DGMPkwdTBbYO6B+ebvm79v/r75++bvm7//l7+g7JX1yTmLSaMWqyvGaqvqa4pL9c/a8oFL6svKSwYOGTRkUNbSgStrh2YNGWH5NQzPHli7rKimtGRgDQ59FtWWmhTFNRdX11UtbsBBk5XDFq8choMDg6qWXISzXWOSjEK1P7o99PaPFRkWzi4rrqmqrVpal5E5v2/G3Oq6soqyS3DhR8bEqorqsvLSGpwrSEgaASVAzk+UDiMfUS8aVoDTAwVL6yuL62qN7vDvo84X3xHhX4OUVVXW6vsaZiV9iX35Z/PMZDn1cRN5TuZsmFEdkb6hcrZk8vz5+sCkHRuSVGtYZzV/hVieool99oVnG3mGYZsv9l5/773mp372wPssROyzE957+k/9jIFvqHLPnNd5+It3fPjS2Se/U/SzzBfOjX2mwvvMQOyzAd5nFWKdGTj1swF6zw3rn3xxwHDvuXmAe78f5J71h7i3/GFD63R/zud1HgM2BBDXdsz1YGZVcX7fgrm9Oa+vg9Hz+ebn8t7z+Fjzd87ZZb7e/Fxdz9Gbn5/ncU7O+bhrLm7Pw1s2B9+Z455372pmvp0+3muObc+vs2DymplDc/7MebP3nJnzZcyVvebJnB9zbmzPh93z4NhzYJn/cu7LeW/MOW/kXNd7nss5rj2/5dzWNa/1nNO2fB6r57Atm7+e6tzVPWf1mq+656mT1oL21m/mc9/8ffP3zd83f9/8ffP3zd83f7Hm/5X/hfl/QX1duSgADONr6QDU/P2QY/4e5EVUai9wKjEwGuu4fpm/c9ouV8Soy0cLanEzVVlVpXX3l493f/GeCIbrZt0ztk7sx4wkfPkw7wxLS5H7Q3EX+3L7zWmh62q9G3yp2D81Oqs7fmCSrTeBi5fJZYL4S+GdEKuF9gRo4o33YHiPEOPs4nnf2B3it8/4mdxVZPpX4E4P++3ntgFFM1BuY2pjv6tl3YW0X+KYKn4PdVR+K607754Xv5mOuzEk1eI/H/4viX+Z3B/1CPcBHEtS95iNlXvMGm+Q5xC830NgmK3w+FSFaVsYdY+ZaX90gNHi+yT2yH0olRXO+2RRV3DTdcX7ZHmvol0PzjdI00M64hyfvmuxF/DIKMQdcPITrqLl9Smnme8b8d0t8hHpJxnJvPMwIajsw1BbbR1hdBzkIYYZbN3N+rHYE+Ue7fdHKfrShjo81OZ8T+iI0LT1sU4ZxwAj2a43xz0vfPNaaOIRxqp3XABu32f1tviHxJ9xSObM+1DfFf84n7qTLi4ge+uNbfIWRuPtCXHxRtS7GqTbCLpdii7UeF3kuxrmm2m7k8TIPSSLYYps0+ydhuoOz43BqLf++GaRZEHcplluUjTWHYc=
*/