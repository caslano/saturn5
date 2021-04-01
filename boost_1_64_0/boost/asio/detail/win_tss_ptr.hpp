//
// detail/win_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_WIN_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper function to create thread-specific storage.
BOOST_ASIO_DECL DWORD win_tss_ptr_create();

template <typename T>
class win_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  win_tss_ptr()
    : tss_key_(win_tss_ptr_create())
  {
  }

  // Destructor.
  ~win_tss_ptr()
  {
    ::TlsFree(tss_key_);
  }

  // Get the value.
  operator T*() const
  {
    return static_cast<T*>(::TlsGetValue(tss_key_));
  }

  // Set the value.
  void operator=(T* value)
  {
    ::TlsSetValue(tss_key_, value);
  }

private:
  // Thread-specific storage to allow unlocked access to determine whether a
  // thread is a member of the pool.
  DWORD tss_key_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_tss_ptr.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_TSS_PTR_HPP

/* win_tss_ptr.hpp
a/7H8vNJaAecnykF6Q1UckU/L6kk/7yzs+1RVgegDlSsMU4ZpM9LCIYW83RjOJ3pXv/Qt9D26iA4TtdnxJBB+8uNRG2Tn0Ss7wYFc93YHFJXh8ONt7ZExrbc05QJFEeAUABaP89GdSVt9OnvVnOqrhU2VyfQy1Qct+h1edLIocvHC7evFdFTowQ1+AHfb/5lgsBUJMwxoJNzfb6Lg9g5iwMub9FWGvRpjkUhLT09S+WJKQPakv/7FqicWEUt9iLvv+xcXZTjZK8VAU41/dSiQWPoGiU7V2EqbTq0EBypzkjP5fUTHppZVN7ny7f5AnR+CJERxYXP0Fz2YYnb5jGRe7Bwon2nTQrUU6D9rDFUjhmAMSdAeBMtP5GQVdSLPtG8hMBnSs9+hwy9+cmJfAyUpY44aVBEx5WCVHMmIaGF5xEMrPzZnO9sKbGtEAzuM4H7GCfvwCO+4udZF3qMblml/LYRK3X8VE2gp2IxmR1PYxcy11raKKQTOZ9iVRkAj8OhKrJRlEiqs0ZeqPSeo7mxgAz5fxHNwRkJW8ta15K76nB9g9zuY+EbgJOElg==
*/