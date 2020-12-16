//
// detail/eventfd_select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Roelof Naude (roelof.naude at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EVENTFD_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_EVENTFD_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_EVENTFD)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class eventfd_select_interrupter
{
public:
  // Constructor.
  BOOST_ASIO_DECL eventfd_select_interrupter();

  // Destructor.
  BOOST_ASIO_DECL ~eventfd_select_interrupter();

  // Recreate the interrupter's descriptors. Used after a fork.
  BOOST_ASIO_DECL void recreate();

  // Interrupt the select call.
  BOOST_ASIO_DECL void interrupt();

  // Reset the select interrupter. Returns true if the reset was successful.
  BOOST_ASIO_DECL bool reset();

  // Get the read descriptor to be passed to select.
  int read_descriptor() const
  {
    return read_descriptor_;
  }

private:
  // Open the descriptors. Throws on error.
  BOOST_ASIO_DECL void open_descriptors();

  // Close the descriptors.
  BOOST_ASIO_DECL void close_descriptors();

  // The read end of a connection used to interrupt the select call. This file
  // descriptor is passed to select such that when it is time to stop, a single
  // 64bit value will be written on the other end of the connection and this
  // descriptor will become readable.
  int read_descriptor_;

  // The write end of a connection used to interrupt the select call. A single
  // 64bit non-zero value may be written to this to wake up the select which is
  // waiting for the other end to become readable. This descriptor will only
  // differ from the read descriptor when a pipe is used.
  int write_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/eventfd_select_interrupter.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_EVENTFD)

#endif // BOOST_ASIO_DETAIL_EVENTFD_SELECT_INTERRUPTER_HPP

/* eventfd_select_interrupter.hpp
2Guuv+Xm2lvLzkrKpeTotdqfTq7fKBpCBAO9Fut5sd1td7p0teH6clW/tsLl7nPbbm97RuZY515A83Rgz6Vu0lN2Cs94PCsgR2Yep9A9ZboS1ofTF55yANNDJrrlJDjNJp3KBJHWrOC3PhGbEvSGQWlwudKggtIkvcegYyoi/Or7pWSuUSrseDpBRBmrpxF5GDxhmjXnfL7Fl2XKopI5TykxUpmFyvybAviyPU3yZuzoaLKmUZoKBKURQZKGY1DPk7grvmcN7Bi1MCOtoFny48xDqpt5qFTbHVmVVKmKqlQlVap/U6UqqVI5VdDL6E8jpxHpIcMqFUFVLLrKFR1gJqzrDdYcygZwWgWJR06a1JjbKq2HOUSu5qe42nObbXfdfueddtqeV/3NR3rSHDmZKiSW2UJC9a8nJPfQ++BLiNSckXGHlvijc4HZny18DACyAXlqUU6GcOAwMTPxHG8QSSwhb/D20HEUfOUYk+FOQYxdmhAFkcE8wGhdB4N+RxfuIk+UnECNd+pigh380UbJ59Wo6DrVVAuQA+s01QBGq8eSk4MWBs1XCBTLl+SBSJ1qme0jUUEAlSM5ne1RoHTK4VTnjaA6Pg+Qsc2sB8xTyb6syUS9wQb1ZJW7q08au1MOTVY0XjRbtuHYyfEN6ApZlZKIOIpIq0gI01fyDTiYOpgFTg+PBs7iQjfRhJX3LP3QQJk5vMXbfPe5ngzXM1Kf0GVWzYZ2IQyHduHk+HAzpDmjmG5y3AKyJND9JYsiPOJCZKPgFZmXU8iwdXjHTODumJaw4asyKk5qlPnhnbbAeLoZAhC+CegT/S4NP08hhCd8qB16c9voYsacdB5l6fXC8FhY3wOyjY2+PAuS99W3INUUz82DyaJuE9DcbXDYxoRIp1qIpwzuE5DKFbUpWRuBVesm49nDZIJFB9lxtZngaATJBP41s+dtpzZHuvRmhnfg2XjI5yZ3ELIBexq9Jkmuo3ZcKe31sNJqPulijsTX6RTRUqzJtBth2pqJVKMGy2Z9hK6K8slAiGcjmdQumSYvKGofB3BOppkmLwooKOdQVUousiZD6aFBZtyowboGg1hMlYS5OLZ+hJCKXXNZiNqVCdnK/MLdnENZsg5GGbPC8+wlnSQmAAWdU1X7LWns57y/ZdZpZv3j9jvttN3uOyNfZOiZk4fi8T1cYKWjSKsFOxonrKamAGlYuM5fWtfrCCjpCFkiOhgtOBIzIS7ikJjq8Olktv1VImVsiE+wdt071pAoZRWJUj6+gxQ1KHBMDUnWk1zAihJEo0ghyYFDuUeu7XZV6XZ4psnqmBLHbAsi5lkQxQzDE5FIH4n5XfU5SMJnsHiXXp+sz3AbLA0XPBVuBU5mo1wCowgJzEQT9xzLJSFMqs0ZTOeCknIl7csYy/sW4b0zGen7c4znXoHCE4IsKwrU6+kiM0eknJsRRTZ1y7nERpgkR4PjfU9AEVLmsO1h5/1HuT0ZKdKnRbMq4MsUaXuEvKF+J7HjTlu6/MPOCRbKEUhYjtcOhCx4cfTIB8PtHUYBeBxi2XXnnXZLrcgTNNxJUinH8Hnt6arIpw59UKTLAZjjji5GgmmnyntlDmByhA+ojBplfpiPYPgNVIFiq4wStsooQU/lJGHEHHkO9yATI6BeV4tXoxRJT+c1dv0cMLs5AN7E3cPnlNbA6cHuXqUhOvdaPwovBx3Xb1RGJ8i0BROzl4KYu9mBvY73yataZBkfExpH3hRZZ9JoC9nqB5KNyubrGbsJQuiXM4c2Cq76h9RVhVRUrapWJVWRYKJsPK1LKWbXJBpDaLPQnFUbJDOBI7X2Rh4V1hFWO8nkpmcQisl9SFouu+VBk0JoHWQ=
*/