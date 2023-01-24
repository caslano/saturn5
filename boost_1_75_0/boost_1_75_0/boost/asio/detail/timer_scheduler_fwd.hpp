//
// detail/timer_scheduler_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP
#define BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
typedef class winrt_timer_scheduler timer_scheduler;
#elif defined(BOOST_ASIO_HAS_IOCP)
typedef class win_iocp_io_context timer_scheduler;
#elif defined(BOOST_ASIO_HAS_EPOLL)
typedef class epoll_reactor timer_scheduler;
#elif defined(BOOST_ASIO_HAS_KQUEUE)
typedef class kqueue_reactor timer_scheduler;
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
typedef class dev_poll_reactor timer_scheduler;
#else
typedef class select_reactor timer_scheduler;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP

/* timer_scheduler_fwd.hpp
aBAVy4aB1Ma0EznFf6jjwtjWQyj+Oi3HvrW92mUKelzzpfI25WPazVv6ohmohaT+g2o/WEbsMjXappVl0xN4wqL7YrSHfHeCnb8p6MTjj3l2qeC8rDi61g83fScJFx0dZQM9lA7yYiGS5fzS0bXhJshg+s7x/Yb+10QTueA8ZIXvlE8dZ9f39+SyBDR2K2F1OD4rzZTyWqQC4vieHwXdJgnNKd/LH/uGbjdutw6sNt9aHeNbYJgntMlQVHkb5HJcsVWtRKV1F+CgFW/+NX3quFKWQGsZqNWigcETx5XSYdAmiP4sBEQoGsvN66SHyYDbHE1pcPg3j4fy4mRnMEN6uwpvfZGeoSpwyRmEHnZ8V3a73AWEIJVbWqejKvo7NfFrLPETemIBgC2zyR9DrlY06IaAgImqboOzIN5W/Tke7X+7Cqd5+Qmqu8dCv4RQZi6ATMJxav1S3ATyxRo88nfyJUD2cFnR0M1wbQSAnHZTm+P79V/h/lGb/LHjCp8A7YtPuYKYHFRtHkQxORcw6UQFeEoTFOg4teEVyl3IxFpgrLNiVx28OsPEVfrrnhvNSbNi/a32ynO4lSn7kW2RPrWUcUOMKkYe8utiZPCmHmJkEoiRhlxy20dMjEyiYiSmomIkUKS8Pol8cBKXP25SEK8ZoaL8+E8mP77znio/hqxCZiy4d2ri3LV8YtGatcL9JYkPFj24lhmdrFz74LrV
*/