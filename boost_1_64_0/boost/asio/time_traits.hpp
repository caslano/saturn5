//
// time_traits.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TIME_TRAITS_HPP
#define BOOST_ASIO_TIME_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/socket_types.hpp> // Must come before posix_time.

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Time traits suitable for use with the deadline timer.
template <typename Time>
struct time_traits;

/// Time traits specialised for posix_time.
template <>
struct time_traits<boost::posix_time::ptime>
{
  /// The time type.
  typedef boost::posix_time::ptime time_type;

  /// The duration type.
  typedef boost::posix_time::time_duration duration_type;

  /// Get the current time.
  static time_type now()
  {
#if defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
    return boost::posix_time::microsec_clock::universal_time();
#else // defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
    return boost::posix_time::second_clock::universal_time();
#endif // defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
  }

  /// Add a duration to a time.
  static time_type add(const time_type& t, const duration_type& d)
  {
    return t + d;
  }

  /// Subtract one time from another.
  static duration_type subtract(const time_type& t1, const time_type& t2)
  {
    return t1 - t2;
  }

  /// Test whether one time is less than another.
  static bool less_than(const time_type& t1, const time_type& t2)
  {
    return t1 < t2;
  }

  /// Convert to POSIX duration type.
  static boost::posix_time::time_duration to_posix_duration(
      const duration_type& d)
  {
    return d;
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_TIME_TRAITS_HPP

/* time_traits.hpp
Wck1Y1UKB6RuFhZxvp7nOJxak0Ln2hT63yplCxZtHPbS5u1xpIuEh4VFH4eD62nnQKoIHwuLNg57N6SwlZS4XHhoLNa8AM39JOaUvE2o3C+FW0hnSl6FhdwlcXyxHcphIW0zZo5L4ZnHp3Dx5T4frS72StKVwjsQ0/m7ly9E4RVSmvh3l7Hde/8Unky6W/hoTK8B4oPM5sV5uLIxhQeekMLA24SXwozM6sWtydI+TfyVkN9h95dRxkHfJsbRId0gdbCwaOMAD0nh/qTcFcJDYR6PNHmkqjwqfh+uQw9N4YukMp+X9m5zsRtJu4R3EKbyG5u0rGszamyBhW8GU6ekUBjgum3x0FjMiYm33/P/PNhm2TgmXR8GCdrDjz0shYOkxNuFj8K8uYHzUTlT9ZO9W88NnLcfnsKnSYPCx8LmKbc7+pZtnr7F7KldHa/jl6wqEw6cwXuspBukXIWZO9s59LA9e3Ybm3j7rkcGg4/kd0TKvUP4aCx2Af0k92dkfuOZX01Gdb5pzrUDj+I7k84VPgoz/rlLWLE/wD/3soVYdkd+xtUussdqPtCn2becn+mP173DMHhWCm8nfV7KUZgpp+CuI7qc7pWcm+6SuUn8B3ltwvmpcnYKbfxuVr2T/KStXCxHGjA4KQiT/OHz08lqfhp/bAo/IV0hfBQWLBuI36Njq/ZWI3J+EbLv9O2ZZ85N4djHp1C6Usq1sahr5Dif/z7pXOFjYdHmo6knpJA/L4Vx4WFh0dbZge20PSdNCw8Li+g7Y76/UfQatl+4cqImh9TuiD6ZcvtQCte+S+qvseqakvOtKfyHI5FxZnZQdnpqCl3vlnIFi9b2fZwPn0EaEh4WFl3GGXpaCpeTrhE+FhbNt3gf48w9hXSn8LCxxuJnKKz6zbWg4xVOWwTIHWaeuVlSRUcm63yUful7LtuPtO898h6CReuXkd0pfIB0t/CwsOj9Mv68FL5H2jQufASL9o07cYWuIr1KePgwvR7WjesQeK7dxn0GfznnUfc55TsTmE1g8mUpdIylEL9K6qCwkO8o4fWRyBbybllMvYjj/MUk4RuANQHq2cB3bo2jlWcJTq/W5JfhhUiW4+yLBRi5MIW/km68ytI/Mx1Mh0qv79t5blzOmZczZtQruL+52qp3A3jkOHdmTjyXvlUc+wDKWou2iY2ArZ+YvDyFH72N63ytbCjMi5lN/t0cA91lz9eNfW54mbPfYj+/t8ZDYRH8YZo6P4XzSUicrEb8nU2+ieeib+Y6L3XSWHhdzknhnP7g2OSR4qQq3XrIvTHjP0WtZVV9XSm2BXoeHGgC/LEoud7FOrwYCf5n98COB9KOyjtSePc7uee7RtpDY5H8zKu6hvlhxjUpfJa05n1SnsJUu4XHwx55bwpvIe0SXhZW3zeaswftiC2G9oO9j2k1mdu5l+jcKfww9b+kCSkrAItX7yBGfH7e/m9qcYUj+Jip/R4FOyaVX/16MatKaBoJGGv0Bzqznzq8T1DW/YC0iWB6LmvMtndeNs1BMRDvknFwoV3/0Xb0fjaFYdIhqb8POyr1rZPe3bMAuTuqu0JbzjF3lPAl7o9IF14rdbSxSP6T3LIixNNQ85gbMypWQM27Yl/AXfryYlQOci7/Cvv8g1LHuVgTEPBsraz1reimD9lulic36qS8ML9Ykfooqp28jNVodwsi+p7rXsu9eIwn8TPe+Yg3HqfsdpzuweB3uOcnbf+QHV+m18ViN3GdNTgpAFP5vfmLfEEeOk0/H2bbLvNqJ+zVZ858MNuOmZu5X72F8uuHrfpPdLjYL0mbDE4KwFR+I1fnKA9neS6i7+5Sn/X9FG69LYXLhIfCTNt3ev4gQuo=
*/