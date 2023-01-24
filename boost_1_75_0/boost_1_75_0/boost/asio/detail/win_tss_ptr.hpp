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
S/9jSP+Ff+m/DOn/8C/9nyHjB/5l/DBk/MG/jD+GjF/4l/HLSLe3VH+QDs+Q8L/zL5U+Q9L/zZfKP0Py/2/lZ0j5/63+GFJ/v/MvVf8Mqf/ffKn2Y0j7/eZLtT9D2v/f+g9D+s9vvlT/Y0j/+91/pPov5uP++zu8VP9n40f9/3d4qfHDxo/GD+ELpccfGx6Nv998qfGL+Xj8kvQFUu3/z/4gNX9Ih5eef6TTl56/pPMvPf9Jl196/pSuP+n5V7r+pedv6faTnv+l2196/ZDuP9Lrj3T/k16/pPuv9Pon3f+l10/p8SO9/kqPP+n1W3r8cve9Mlx/02B/vsT9KvQMk0F/g5luHnFdPeLmMWbJ865W6iZbid1brSjKpeeSRyGWf5CH5MUo8PKUHXqgx9Kx/impa0yc9Xni+C1+v38h3YuPJRcZsZzIp9wsd01U2/ueEsuJU7LYlxNYwtGl2GfjHGzOXq82X1Cv5qhiy7otZBH5qcRvW5Ao5vVd103N4ZVYYkTSIhYzu7NeHPLQP131LCw5UmlYcpTDkqPXN12xuTe+jBrfdY2NKrA0qG5gkcVe22xsmPXbHB0LeCN5YndLE7G7AJum64mfRdh6gTw3o+dqbLmA/GLaUZGYQ7wWS5bz4xN29cDFwcXV+x3XQiQaz8dC3U6BAX4lYsm+F9FFMh32K5brSqc3t5dguU5dLNehimBNxKXG8+95n1u/
*/