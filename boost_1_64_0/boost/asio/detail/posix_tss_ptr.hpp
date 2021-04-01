//
// detail/posix_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <pthread.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper function to create thread-specific storage.
BOOST_ASIO_DECL void posix_tss_ptr_create(pthread_key_t& key);

template <typename T>
class posix_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  posix_tss_ptr()
  {
    posix_tss_ptr_create(tss_key_);
  }

  // Destructor.
  ~posix_tss_ptr()
  {
    ::pthread_key_delete(tss_key_);
  }

  // Get the value.
  operator T*() const
  {
    return static_cast<T*>(::pthread_getspecific(tss_key_));
  }

  // Set the value.
  void operator=(T* value)
  {
    ::pthread_setspecific(tss_key_, value);
  }

private:
  // Thread-specific storage to allow unlocked access to determine whether a
  // thread is a member of the pool.
  pthread_key_t tss_key_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_tss_ptr.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_TSS_PTR_HPP

/* posix_tss_ptr.hpp
XbfWjQLd1GwI+BtwrGKx7EtrYc0a3fjbuOJpm1TK4ybh6gv3TzRIapRTVmk+fA4k8bNI9ZJbqz2biI5dav2RKSSplhGa/1u7rOM/IskC9HQLvu/UGi2QAKnuv1lbHGvOw7CgJ/TtItYW3cVjF3hP8ED/nlWKFwDH23qCPitYrqA34v1E65jZ7QMCcVLUP7fFWRMst0vAMwGhhXe9qiuDHQd0dXo8L9FPBXL0OSQYQZRaGScwS5AW/hn3/qM7IIRsVDm9N/0HCOfMmpLYp8PYoL8LkdFDB5hHHq84ZoZI9IJlQodsMr67HfvJ+n3uZ590ks9X0LSo34JPNmbMjS3wUHIksGh3Gw00pM2Wbs3QErMm6HhQIpgPyUTTJ5uIj1/uKkKXRbiaS0F5KmDYDJrfNHHEEjfHKZ+F3/qzDyNMw8/PjUsxbJ6XYVaVpWRxR5Az/t9c5cv8zssAy0WPoNJ61dXJQDpfBjQRV6gB1cXfGY5zbS/KXgJStwsmXZf7kELuSBWFrPVbcO1255XagJ/KlpaH1lrIDxoxDiMhwPWPl7ri0TrPLx3hzSZsCw==
*/