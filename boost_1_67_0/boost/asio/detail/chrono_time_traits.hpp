//
// detail/chrono_time_traits.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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