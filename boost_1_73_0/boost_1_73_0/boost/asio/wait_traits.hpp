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
qCY1dWQ35asWBg9pu5MBL1XT4L6wnp3ZYxLydQt67EO5HWpG/CQUliwr7uhaNIV6BKYhpGTnqoKhNm0nQKa+vr15r/KzEueO9YF3iQ066SUR+grswuswCrv+uyOac0IXnVsjqd9tDaCpa4tOz8+O6fT16ayw34co9W74EcM65+buC70WrAo75iSqpvO6yt8z9d9esRP6RWSgdRgxG2u0KGC/1cWMHhcyWoBZTBblCkawyTCoYlrFaj4ukrKHEnFDQNjRDGApj/6uZIkbYe9ktSXR9ri87qVexx2EGkuO9P8BUEsDBAoAAAAIAC1nSlISWxMAEAEAAO8BAAAaAAkAY3VybC1tYXN0ZXIvZG9jcy9SRUFETUUubWRVVAUAAbZIJGB1kDFPAzEMhff8CiOGUqnc7cwszEyoYshdnLuIXFzZTkv/Pc61lagQU5KXl+/55WE/Vs6QaaLPp1n1IC9936ROsG/qenhuu06O09a5R3ilsS5Y1Gui4twH1U3OEFMJ4GFJ30ARjp4TVYHw2wupgM7J1MQ4KvEZfAlO6nATEsoOqqQygeAR2WfzxohsCIjEi1fp4J0WbCE64wKeEQoppIA+O/MAow+NcIHmc4s9U2UYmE6C3Dn3FpuyCcDeIGxh2Gj2tAQLC2DZ0ia+
*/