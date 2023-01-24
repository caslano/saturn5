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
dBIHLKtmgxba6m1zTMu0rLvhiN5xF0fFeymYxCbLL9eoEzNwLGUlckkYsQrZJO/+WOfRMWCQRs8hbRnOEqCHuDZ1vg14CN3O2Ae8KyplrKOCSuSx0ezTp9xMjdA2PYq2NBXbGU/zDUYc0Xhz2UvEG5Y1fIXzz8J8K7DyqEZcs8asXXiQTXEKhhZzbUCaH9fqbR7qqd08JOuNyhjaGaGotBCYSXnD9ZQzpeiUPfShShmUBe2hxuCqgGTasAPKU9uSq0U1s/ttBAVKckhWDodw2n0c9TgEfPkfYlOU4VJlClCf1b02WZ6Jl85d4cuQf/IPsylIm/2rrdmvteYrPO/GSe24NiyeDm8a688Pg5IkTe0qLfJDNuWUXyPNcygQlcE9p3q1mukjLdTLIyOegvhvFa0NMFWbZjXycXRd+K46Ng98VZxy/uyVeA0d13fSW4uq5kzHkyrysr1whR+idMjiYQxNqypbScWPqoYC3RpyrvSwzjmSkj++pJvB8uDj8GMwbz4pN5F58wHsX4q/QMbQT/4tTiMqt/tzzFfhUswNnJQrS1UYl0ARS5U7pLpAyI4zQApk5pIDXcwJ8CPAWbks3tyQt/x0fW6XqUyJT2/ylofqc0+bsqEUMORrbDjBhIZC/XjBKfduo81a0DVm5HZgsNOOwQ5oCmKmPUByVWUHsaEd2bCsSQ8wVHwI06mqq038ZlpGz29Q3fKhD5jt
*/