//
// detail/null_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_fenced_block
  : private noncopyable
{
public:
  enum half_or_full_t { half, full };

  // Constructor.
  explicit null_fenced_block(half_or_full_t)
  {
  }

  // Destructor.
  ~null_fenced_block()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP

/* null_fenced_block.hpp
RyInfqb1DGZBkEe1CE3IVFwzh0kgY68iP6zsXiLEpYTe1BtOyjsRqxrOYrCzc7jd72/PkuZ+mnzp1iKGTJbdvC6a3n0zBU0/UQIlA3HH8mFd3w8oS6q45SYkpLfp8BQJSNSw184LUMXBy1QZKrIs9V1Jc7dvgZMHPCajQUxJurCBuJ4mdE7ALBsRALmQKkdBIblv4lSPfddyInuHW84UQ6z4tg8gii8hCI7QH5947O1w+bI1QMJcVMzNrXg8L5QlyjSyyRiiuMwuF3yRKUv/kRtAuOIS4lnjcOr47Pbk+OLy4uL4/Wk8niR3HfOIWYcLOGpEZphXlBgiM4+nKmyYTT3Jb0eJ6B0qgOipHOfZxPtrtAMyQq8S9+huq1u/3BybKGyYnNQBQjeAa/G2QGGrGcSIRmEnMK4S2CNpoeV6A3kIAlWtnqMEEo47CUJaG8iGdnKfQFv3dw/72Lgn+WYi34gesxLwtuaCZrQtYrqtAgSPiveMTeUo4og849Tu7h/uYHZP8wgZ7E2tJZURsjibTUymow+UYrzsnXCzUUYfW2tXNaGNXpJIwf17HQH26F6rtIh6FNiz+NmMZho8Xe3duo48z293UScZLuFZJK0/ONgDcL7jBYvi45Un6hDBYVKnCDZokn8CrYMfRp4p
*/