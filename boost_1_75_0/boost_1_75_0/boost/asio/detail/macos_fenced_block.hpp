//
// detail/macos_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__MACH__) && defined(__APPLE__)

#include <libkern/OSAtomic.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class macos_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit macos_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit macos_fenced_block(full_t)
  {
    OSMemoryBarrier();
  }

  // Destructor.
  ~macos_fenced_block()
  {
    OSMemoryBarrier();
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__MACH__) && defined(__APPLE__)

#endif // BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP

/* macos_fenced_block.hpp
WbFCzKwSMz8+X4nFX3wSzh0ZphzIl3Pd2ngEXLmQFRLrlH+vFYITaSBarkzMUx6WU/SH4QIEE3BrM5qiAxAJZNj5q3QabonQsNgMRipNpWGRmXdoNAxFGuzKATwL2povHciYKFyg13++VkAsoiAJeUhFElSqPOhNVeK9qXmIJcMHcAH32gll1fMWqaXPtkTLl634/2G06rN7tdEqy0+No1XlNQOOVuXf+yNHqyxRo1Udl599tCrtx4xWXXCvcbRqzL1Ro1V9nLC+79R9W9V9p2hp2E8gkJPqaGEYYrDe8jMs+lukDkuH2LB0bo+Tjbupw9KyU75Ib8m50MNcTQtXsz/wud3agttEtKEJZCPgKWPM/XakGnRekk5la9V/SqUlikr3zO+jMu3HU6lNNMqqMq4CBiEVyqVmiLy3fhamMaZG/7xPxFD5hln+bPq8rHOfmefE0ys2xIiBiYpdDKQpVjGwGR57R47ZCu9c9QQ21yrWzg202hMCylA5pyqys+yPG97esQXRro6tdxN1PK6fCqpnMhRJjaUQn7yOZE56m7gSYK78ps5rksbY+Z9uPf2kCc+5EFtrYwLwbWqja/Pyrd1I3tqh/sLhgc+G+HPuTWhWUrJO4mkYYu3EwKdDpHenNm8NmM4xmRLe8d/7ycfh8FXl5SbThqHSvkkNWfW4L8k564bKq4Gy9IOsVSuWacPp/bCjQbj+r83EdWiO
*/