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
glDOsAREDVgBc5H43GKg1C1XQGEA7pKrLUaKfXEFzmXs1YtxEr9fAXQQL4bFQMlyWQH0Buu0hSDLJna73UrOxwc/NRcleZV7r64PMaeAhl/nl1tYUUOLV02Lo9o4DYP5j7jHynWjeH9eJZxI/CziqSJXMrC5jAHHlOECbYkSOyNs9/wiVpE77MDOtrDVwxbYm7j2F4z4HMyYvw7YE9ejOner7261moPWtlaiOy+UgNuLo54fyakahElikE8/I8eTQj9uZ6EVI2ia9LBhQX4sXcXENvz8M1SsThOoiO2qQVwL05hyluMcyoU1olSdpwRTN5ubA54cs1Mzu0Q7zd4YzirjeziBA111eH2yV9bTetdvVF7fwJT/r3U4825hc33jP30Nr/nBL71/b/bWs2ssdyPTocIg53MJGlYO5xfXJ+dndU95OnG7vGxIsE4ukCQP10oTSKo0CFaFSh+V6qBsyjN1hFJhOXlweVIULZ6ftjFxi6Ie0qbHOHHm1LfHnpd5ZBJ+8yRp0GxX+o4d6gYYnTRG5xoLLhqwbSzeoW2aXVgv3nSjGd6UI9MxA31vlgMh+vT0NWyWQ88abSNx44x9d+RT682bWL6HgpYyKxNloC7Uhmziwi4ylmuykKW6aJz04dSSrg6MKvQ0x9QR
*/