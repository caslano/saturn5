//
// detail/null_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class null_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  null_tss_ptr()
    : value_(0)
  {
  }

  // Destructor.
  ~null_tss_ptr()
  {
  }

  // Get the value.
  operator T*() const
  {
    return value_;
  }

  // Set the value.
  void operator=(T* value)
  {
    value_ = value;
  }

private:
  T* value_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP

/* null_tss_ptr.hpp
qiRaPGKANBezdLgp+L6Z3UwtiQ0p6pLhGI8f3aOaxoIUkan+gChjJFlRsmV9X0pfc5eEbUtR2XzD/IqtQ/r7uhv0V1A0oK4hFnH3mNn2LWVLFV9LmqaCOPRrWmp/avn7kNJYNBQG8GgRdkjzW5f+nUYpVFN0jEFMomgF7F6Szd2bOoAMxRnCO6/nyLrwU2gdfliphjpjbjSnIUH+ODB0s6Rlk0Rca2zbQ7ZFfAlSy1vupSZ+y5wFic6D+vPne2tgcFS/3yluEmCPpIO2srJl6n9JTqKHPijd29Hn9wln3zesBNkAukL2Fl7u8w1Qyj+56A7EVYXaL+IETDg+sv0Q4p1bttd/z8iNAQDSJLsLo6AuOCvfGRf5KkWFV9oHVgijNKKNjWyoCQlrZE49cM81jUr/qIQlP3L52iOR+ujDSurb6QaBeZStmdwhu7K3/GdGxTTmIeRWLDrCe6CKgE8W5sW8xUoYtQbeoKyGFT62oWCz4sYa+wU1VXK9Za4V9o4O7KhUJDADTdXexZ32D9OA1p5krJi+PwsVddce771zv3vH8ceMW3TxKdoV0g==
*/