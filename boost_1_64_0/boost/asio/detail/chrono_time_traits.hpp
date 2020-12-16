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
GPFIdY7ZgnJogSGYjXCcwiP8QLrzvCfKoim6YCQWYBOO4hpewl3g7IRy6IBhWI7tiMYz2GiuQRX4YxSW4ggu4jn+IOVFZg3yohzqoi36YjRmYjnCcQRXEYevSHyJdSM7vFEdfuiF0ZiFMOzHRcTiCxLHMJuQB6VQCy3RB6MwG6sRibO4hzf4haSXyVEUQCU0QlcEYQE24SDO4SHe4BdSXOEMjirwQ2+MQwi2IhovIa+SoyiI6miFfpiApYhADN7AXKNXwgsF4IOaaIWeCMIsLMMG7EUUruM5fiPldX4PHzRCLwRhAXYgGnGIR+Ib9D5UQlP0xBjMw1acxmPEI/lNZiOKoTbaoB8mIRTbcQYP8RUpb7EfqIyOCMA4zMZy7MZFPMQXJL3N/VEY1dAWfTEei7EeuxGFW3iL//9BTVrkhDdqoS36YSZWIhJX8ApJ71KXyIWyaICOGIhJCEUkYvAc6h7fcSiBuvBHEBYiAmfxCp775B+KoTY6YDjmYStO4j4SkOoBtYEq6IwgLMUGHMIlPMMvpHvItaiCluiJkZiDNTiOa3iFBCR7RO0hN0qhJtpgIOYgFFuwH+dwH2/wE8keE0dURiN0wiBMxEKswx5E4Qae4xeSx/IdggIoj4boiACMxRyswnYcx008h4qj7lAQFdAInTAA4zAXq7EDJ3ALL/AZ8gnrRQbkRAnURnsMwQysxl5cwGN8Q6qnXA8f+MIfwzAL63EIV/Acv5D0GfuPPPBGVbREFwzAGMzAYoRhB07gOl7gB5I9Jz4ohApoiA7oj5GYgoXYjKO4god4h59I/IL+gX+QE0Xhg9poAX8MwGhMxVwsRziO4Rae4TPMS+6FzCiM0qiKBmgJfwzAVKzEXhzDJcTiM9wr4o7cKINm6INRmIlVOITreIXfSPOa3yAHiqEKfNEOARiJiZiHUGzEfkTjAV7jD5K9obehJCqgJtqgH4IRgs04gut4iT9I+5ZnoxR80QUjMR6TMRdLsRG7sA/HcR638QQvEY8/SPqOeY2yaIQuGI6JmI812I6DuICH+Aj9nrmBTMiHEmiInpiAxdiMw7iJDzAfuB4FURFN0BtBmI81iMBhnMc9vIH5yF4jC4qiMhqiHXphBIIxE6uwEYdwDbF4iwTYT9QNMiIXiqEC6qMF/NEf07EGh3AZb2E/8+2MSuiMMZiLMOxGFK7jKX4gRTxxRVFURAN0wwjMxRocRAxew/OFNaESfNEeARiLudiCY7iN13BfqWd4ozECMRMrsA3HcRdvkegbvRT5UA6N0RnDMAOh2IFTuIEX+I7ECTwD+VAZLdEbozALaxCJaMTiG5J+Z59QDNXgh4GYjvU4iGv4iCQ/6EeoiV6YgmWIwDnE4htS/CTnUQI14IfeGIkZWIXtOIpreIRPcL94b+RBeTRFbwRjOfYgGg/xGeY39YU8KIV6aIdhmIv1OIrreAfxh36Af1ERfuiFEZiOFdiGS3iMT0gkvMQ/yIPKaIJOGIq5CMdFxOEbUksvkQ3eqI2W6I4RmIal2IQ9OIVbeAOpvEQ6eKEEaqAFBmE8FmMzjiEGj/AZhv+QIT3yoQzqow16IQizsAJ7cBo38Qo/kcx4iYzIj7LwRXv0x1jMwgpsRiTO4j7e4DsSWZ6NbCiEimiAduiN0ZiBlQjHAZzDfcQjufMSWVEE5VEXnRGA4ZiExYjASdzEezgPe4LSqInmCEQwFiEcJ3ELz5CApIm8RCbkhQ8aoheCsQR7EIPnSJbYS2RBUTRGV4zGQmzHecThC5Il4f1RCpXhi04YjJlYg72IwXP8RKakXqIAyqE5BmIu1mAfYvAcv5AsGWtBUVRDa/RAMBYgHKdwH9+RNjm5gJo=
*/