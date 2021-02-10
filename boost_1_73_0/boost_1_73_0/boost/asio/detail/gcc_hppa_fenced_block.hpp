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
Juf2YDZAigtqVPLVTqVZC6E6UzxH4tWTkHNiQqIanhxOV1D5SW1kyWCm5MSvkQTPLorU8jyHgLhrnt0q4Foz+wjSBi5wYDBVo2kDuGOcJZKw9GouHAiSRTV9dgl3If4+h4Rg2EgAA1rBViE8606ceNIYs5X1aEhwNw4qJl2d7JEMuzbpETCNRh86xlyptKetLuy6HnU7PG/wNnvmC6iedc83LAWaqh/xEY5dWx9yJk12HNgBEmwhtGgSOQcgAIZSVbGn2xI5tKbjpbDujDqEl/R1t5RQdTisPEbAcLFIjIhf9bKODSQKvmjDWOEmjaOnH7xwsT8D6ZuiYzMOoutA93suBH2oVgzjCx1ToeJ1ENzN6lB1RTzYpuG8UmXAx1TSAMVTDqMo50FcRfwBc+KGvk583is3PQbaM5y7bjr6pli7rgC2iNXdqCCEFV4UR/iI9sl8OWAEdRrRq+xoRX2kLaykYe58E4Ykswa5Pw3eSV1I9zRmW0mqdSiPRt5FBfOi6NCl+uGbxnTo6jwJVMdg7FC5I9LZsaBbZ9O+nDHHR3VErqmOV95JKmUH0KfVGqZjx7gPhl9E8GdKJjKsj3dM9G4XA5SRM9VlrjuwyGlm978tGqV0cUTW1dv37zv80hN6W71/E+5i5nnmpL98
*/