//
// wait_traits.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WAIT_TRAITS_HPP
#define BOOST_ASIO_WAIT_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Wait traits suitable for use with the basic_waitable_timer class template.
template <typename Clock>
struct wait_traits
{
  /// Convert a clock duration into a duration used for waiting.
  /**
   * @returns @c d.
   */
  static typename Clock::duration to_wait_duration(
      const typename Clock::duration& d)
  {
    return d;
  }

  /// Convert a clock duration into a duration used for waiting.
  /**
   * @returns @c d.
   */
  static typename Clock::duration to_wait_duration(
      const typename Clock::time_point& t)
  {
    typename Clock::time_point now = Clock::now();
    if (now + (Clock::duration::max)() < t)
      return (Clock::duration::max)();
    if (now + (Clock::duration::min)() > t)
      return (Clock::duration::min)();
    return t - now;
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_WAIT_TRAITS_HPP

/* wait_traits.hpp
jUVS1i4m8ahxSmdIyx006DhaDTrWZdrtNGzYLg3EoGFH4EvJzy4LX6oEI5ts8BajCIr5hV5Tir5yNqlZrwSvZ8OnbU7ahdc03cU5xKw2itRRAcEPwNAO4DV9Fw8vnGSbHiMuGklZtswdfH2c5ONsPIIm47/iqBqF1xXzefZwJwgQ9QoCXNkhCLiw/ZwL21PmxatdjMi+FAOM6aKPJyOVPr6fd6k+9h7qvI9/fdsiM+JXLtnHn7rowxOtwDE/tA8WF9BJT5Mu7MlG3hiqyITYeVqsuk+ODI1XBvY0gHz4VktgcBJ5yaMu/88WMr1lqtdabUNSiNvPiE9db9VHME9QTZPVVCBZq2Ex1LXjpo3O5hCt1YG4I2yNHJKXx0JyjadFPfetPQSECRBkNlTDJ9pJehsLjRpBBr2lLla9R12sQwCyhuP4KxxPY1QDPQ8E5tWdHC9Uxf4x+OoBUWjMFSOBbVWKWY0evNUnI2Rdj9Gsa1939niWPjZJA6uRkVlP2pyz6ZLHhXAHfKl/mrWRsp27yEOFCjOj+4W+WTI7C3OQbos07GxGocrOZr6psrPBtHOH2rkhrWz1VgW1+V9SVoaK0EK8MrXZrYic5CYWXlXLJsOoxMPi1WwOYv2SLUHcrZPjTsIUN0xdSAusgcdDbKSH3EbdQaO167uo/f3hDrXXnSwwaNUDeT5NzuSApwYoa/4boHGlkAy3Sll3LoD5
*/