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
AnqirQXywSaioHgr8Rzn1kerWwN0kxGzjg+JWUcmzO3Gh8isHyO684+g7+kFyKzHaW9DV2zsGY1dx04AqDO0xZJ/QLXwyC7Sd7j2IV6Bed/WL5XbTdWxlZ8QfXM5N9GglC9V6wGWvRMzBcVhSxFCgboOI91Ykm9EUH6hdweKMDH2RM83PTjfIoTKTtq4C9QZGkQMfemH+HysAvn80J7nsg6d6rbaTLDLsONisOMJ0PHnOI8sa8RAsDHDu1wNj3cK+Oah8QpGDirIhjqfacOgMWRzdahNJT6Xa1OXUMhYYSQqVFlRZIDVlU5hFB+9IVSeaUW5RXvL8yFc/qjbaG46ZzSbOo3mZXBUw/EWHJO6jOYfd2v+rr3EhgdHQDf6iA39+MWmaX6x+8kvNn0EOb8Cx9SPZ+ylI4KesX/+z3jGNg7q5RlrOZqNRgEnZlyXrWZ0BsxvIwdA+vss/S1pw1He0kZ6cvy7Y3cbfuVAj36xm9rUKCcR73n1KJVk4M+dt2hSyfY2kkrc29o43lEqGTyc/GXbyHY/kb2kDwzYiQ90OvWdd2HqtnFJxvsGSlD7pmM7G/Pkg9QOZ2UbKSnbcJYmtXGpRDpHvrXYLh3P9iS50UAKba3iJ2oyUOc23vDbCJSN/q6gvzuxlhphf6zLvatNFYASEBCM20GsUwd7Uxv6Yd5nJvMEsJJYPRdtejnVIvjeTrV4j3ycviFZF2HJ
*/