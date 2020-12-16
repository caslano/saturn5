//
// detail/posix_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <exception>
#include <pthread.h>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct posix_global_impl
{
  // Helper function to perform initialisation.
  static void do_init()
  {
    instance_.static_ptr_ = instance_.ptr_ = new T;
  }

  // Destructor automatically cleans up the global.
  ~posix_global_impl()
  {
    delete static_ptr_;
  }

  static ::pthread_once_t init_once_;
  static T* static_ptr_;
  static posix_global_impl instance_;
  T* ptr_;
};

template <typename T>
::pthread_once_t posix_global_impl<T>::init_once_ = PTHREAD_ONCE_INIT;

template <typename T>
T* posix_global_impl<T>::static_ptr_ = 0;

template <typename T>
posix_global_impl<T> posix_global_impl<T>::instance_;

template <typename T>
T& posix_global()
{
  int result = ::pthread_once(
      &posix_global_impl<T>::init_once_,
      &posix_global_impl<T>::do_init);

  if (result != 0)
    std::terminate();

  return *posix_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_GLOBAL_HPP

/* posix_global.hpp
pJb8mfPH1s1iI1z2tSL7/8dsU7smYuFQo+z9VNsDxrAkIq6K+Tlz4bgYU7S7z8W1N1xcHiqeMco+PyVh14+lsTJj1wrd7y2/V+seKkJTa3mtJjjAX/6CWX7l8xHIJ5HPdttwB1Tc685kV7dLmzmlLQzNZhGaUacFGelxffOwRozhqj1XmDc5mX4tKi6mrzWNKfX5E2beTbvpFCvwuML0eRM0cKfcbrTh3NFs1ptG29sKuFKPawfysY5YrHus5VdaeANxHX/uOi98eefyR6xx8W37Vg7Yc+OcxWEs/PnDC2svOZYVhzjEIQ5xiEMc4hCHOMQhDnGIQxz+FWEc+G1ojTWl+Bseyog1R96QeD69mesNJRqNFCzEHOoTyyKHCk61MVSpbbF9ojuVWCaZ6l10yd70mEXH9CydWHS1pVM9iyZTqeXSSy679DLLLrHcjou1qg1xv8ZaccoJ4D7jIyrHyWDtxfVFy9JfHlggt+AcyXVhoSJ8cOAka6UprdLW5b/zobvlbOP8+QUEW7VgMddiIgkRvoDfDPBLLQz3gMdaz76kz7p01kvmH3u7nxfe/ag5rDjEIQ5xiEMc4hCHOMQhDnGIQxz+kWEc+E3H1/+waJhWUvSn4Hq3gdfu41sT/Oa1u1gpLdjj/mnX7hW3tgVfuc9mLTvlWPBvIplM5/OwajifzGUGC2JD4EjTcZAfO5p3Wxy/K5qvOVvDekTgx7Ei1zpZ0wE3rhVaW4pxxrMi128iN77BaYa4CTS3rMlNBdyEVmBNImATWaF1fqidWOI1rZ2EMC6EtnVSK2r9EuU5meVbQ4X6ya3ItY7ITWFFrnPE/Ke0QmuSEJ+KcYlKX0wt8HymPNDMFWujDlWoRXGmCXAu18e0flxUItbxdIzD7j13xHWayc3qbsnRbWT6SF63kRkied1GZgzwHiZN3EwhzlX1PXOQE0lyfc9i8fqhRHYDiIJ2zGp1WNfEds4W5skS5me3Oq55QnvmCPNo7VzAzRnB1YpV2FfddGvctucKa1QdzB3Ftat20Sth3HmsyPVSGHfeaE7ERX6+SF6Xa37F9w8abkFuAZPTRUZuQYPTxaG2tpDiBgbEJgdZRwtLPJ2F/XJi51qKMuM0Fwnzog7Qx4tGczY4eOkxHH+xCI3L/l88zAmDkVsigvM43+4oTueL5eqJ0LTq9mpZtmtJyfcaDoEg0h8judXTWYjaB/t/U4UM7LsuljeXmqU6aKiBk2bpDhp0MNu5TCeNS2VdtgNPNUv5LNdBQ22dNMt30KBTIcwHmhV+RQP7xSCxUbR5xYDOaKPIrxTJ6/Fp5Uhej0+rSD6TWCrY/lcNcbr9J0KcTnM1xWUL6dVhZ3Kp2pBtPBnkym3FpQIcWsJcOsBhx+Ay9gY43TGIXz2Kb6MA++saQZ7HhkwA53aA3JpBztP2rBXi/Pb0hXhlD6bdH+C5M6GtWcll1+nrQwcRPmDiWE2ED5o4FQDzWJtxuZW2BOtLW3xeyvk53/k17+fU+bXgx0VO2BfWUXiykFYjMGys69VtdN0ojWg0zK8XyZfbkl8/ikerid8gkndVfW0YxYsSML9RFI8VTmUfkvxgsrA+5Ytl39jEsdGVHHjpyEilOOrJdrRJQMM05muHuFqVaeQ3DfF1t2zEL/p5GliIR7uHTR7LS3aXfLgXaXc5pNH5On4uZPeInw/ZPRrktd1o32aKh4rAt0yYVU55uB00cqzfvANv9vEtQho9NlZCnB4bqyFOj421MNfatuFgfdQllxfl1u23oXBZj8VGA1+ZQ2lu6edlXSDXDHJgplOldL0QBxS8GKPFY0rLx+v+0PbhnmEP8VspHl5FI15EwRNV6detQ7wer7Y=
*/