//
// detail/gcc_hppa_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class gcc_hppa_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit gcc_hppa_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit gcc_hppa_fenced_block(full_t)
  {
    barrier();
  }

  // Destructor.
  ~gcc_hppa_fenced_block()
  {
    barrier();
  }

private:
  static void barrier()
  {
    // This is just a placeholder and almost certainly not sufficient.
    __asm__ __volatile__ ("" : : : "memory");
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))

#endif // BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP

/* gcc_hppa_fenced_block.hpp
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
*/