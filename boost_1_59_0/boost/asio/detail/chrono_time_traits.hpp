//
// detail/chrono_time_traits.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CHRONO_TIME_TRAITS_HPP
#define BOOST_ASIO_DETAIL_CHRONO_TIME_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/cstdint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper template to compute the greatest common divisor.
template <int64_t v1, int64_t v2>
struct gcd { enum { value = gcd<v2, v1 % v2>::value }; };

template <int64_t v1>
struct gcd<v1, 0> { enum { value = v1 }; };

// Adapts std::chrono clocks for use with a deadline timer.
template <typename Clock, typename WaitTraits>
struct chrono_time_traits
{
  // The clock type.
  typedef Clock clock_type;

  // The duration type of the clock.
  typedef typename clock_type::duration duration_type;

  // The time point type of the clock.
  typedef typename clock_type::time_point time_type;

  // The period of the clock.
  typedef typename duration_type::period period_type;

  // Get the current time.
  static time_type now()
  {
    return clock_type::now();
  }

  // Add a duration to a time.
  static time_type add(const time_type& t, const duration_type& d)
  {
    const time_type epoch;
    if (t >= epoch)
    {
      if ((time_type::max)() - t < d)
        return (time_type::max)();
    }
    else // t < epoch
    {
      if (-(t - (time_type::min)()) > d)
        return (time_type::min)();
    }

    return t + d;
  }

  // Subtract one time from another.
  static duration_type subtract(const time_type& t1, const time_type& t2)
  {
    const time_type epoch;
    if (t1 >= epoch)
    {
      if (t2 >= epoch)
      {
        return t1 - t2;
      }
      else if (t2 == (time_type::min)())
      {
        return (duration_type::max)();
      }
      else if ((time_type::max)() - t1 < epoch - t2)
      {
        return (duration_type::max)();
      }
      else
      {
        return t1 - t2;
      }
    }
    else // t1 < epoch
    {
      if (t2 < epoch)
      {
        return t1 - t2;
      }
      else if (t1 == (time_type::min)())
      {
        return (duration_type::min)();
      }
      else if ((time_type::max)() - t2 < epoch - t1)
      {
        return (duration_type::min)();
      }
      else
      {
        return -(t2 - t1);
      }
    }
  }

  // Test whether one time is less than another.
  static bool less_than(const time_type& t1, const time_type& t2)
  {
    return t1 < t2;
  }

  // Implement just enough of the posix_time::time_duration interface to supply
  // what the timer_queue requires.
  class posix_time_duration
  {
  public:
    explicit posix_time_duration(const duration_type& d)
      : d_(d)
    {
    }

    int64_t ticks() const
    {
      return d_.count();
    }

    int64_t total_seconds() const
    {
      return duration_cast<1, 1>();
    }

    int64_t total_milliseconds() const
    {
      return duration_cast<1, 1000>();
    }

    int64_t total_microseconds() const
    {
      return duration_cast<1, 1000000>();
    }

  private:
    template <int64_t Num, int64_t Den>
    int64_t duration_cast() const
    {
      const int64_t num1 = period_type::num / gcd<period_type::num, Num>::value;
      const int64_t num2 = Num / gcd<period_type::num, Num>::value;

      const int64_t den1 = period_type::den / gcd<period_type::den, Den>::value;
      const int64_t den2 = Den / gcd<period_type::den, Den>::value;

      const int64_t num = num1 * den2;
      const int64_t den = num2 * den1;

      if (num == 1 && den == 1)
        return ticks();
      else if (num != 1 && den == 1)
        return ticks() * num;
      else if (num == 1 && period_type::den != 1)
        return ticks() / den;
      else
        return ticks() * num / den;
    }

    duration_type d_;
  };

  // Convert to POSIX duration type.
  static posix_time_duration to_posix_duration(const duration_type& d)
  {
    return posix_time_duration(WaitTraits::to_wait_duration(d));
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_CHRONO_TIME_TRAITS_HPP

/* chrono_time_traits.hpp
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
*/