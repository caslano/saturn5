//
// detail/solaris_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__sun)

#include <atomic.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class solaris_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit solaris_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit solaris_fenced_block(full_t)
  {
    membar_consumer();
  }

  // Destructor.
  ~solaris_fenced_block()
  {
    membar_producer();
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__sun)

#endif // BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP

/* solaris_fenced_block.hpp
/HY22Nr2H6HiVM2dhnHjAk0zmYXN1h2WDpqGG/DAcx/PeBp27GQwEkEsm8V5AeZmJrgcq97dHX3lfvKm4HYanW/I2DP7/vDfCbfkwz7A1LIKEyCJyuWCN0yPzKXqvf0Pk+M+PmdtbyhuuR+lXMYkjlG0MY5r2eEdLbc/rq5mpuKyLOmKMYmno3md5vAHRjNGwHFI8f/JJFT0YPpXCGzhfLCrezJxgtWOjsOYXhb5vDZo78DHy5SSIitd4w1MfQ/+sY/WTDjXhbuorZOcQsi5wzRiCREDD2YPtYAkO2KIiIS8bUqcW1YNI2C3Eo7wSJ62S9Km6EyZJbbHKxzZo5jdqnLHAMWkKJYEXg/p3HOGSI9LuwZyknGTqyCk+gSKapSI10YQ2xz/SxImvpOE76b9qhUKNzg9JbfYQheKmLbyyag+b6OzRTtB+9lHpDrdVmZNZgXb3px8TWJVJMqztD1tTOHlwdjZvJfXvir+AVBLAwQKAAAACAAtZ0pSf0cZE3wCAAA8BQAAKQAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL01ha2VmaWxlLmFtVVQFAAG2SCRgrVJdT9swFH1efsVVmVA7hQR4GoihRqWDCmirNohVQorc+Lbx5tiR7UCR+PG7DkEF
*/