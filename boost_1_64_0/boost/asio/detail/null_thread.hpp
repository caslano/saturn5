//
// detail/null_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_THREAD_HPP
#define BOOST_ASIO_DETAIL_NULL_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  null_thread(Function, unsigned int = 0)
  {
    boost::asio::detail::throw_error(
        boost::asio::error::operation_not_supported, "thread");
  }

  // Destructor.
  ~null_thread()
  {
  }

  // Wait for the thread to exit.
  void join()
  {
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    return 1;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_THREAD_HPP

/* null_thread.hpp
3gAhOoT3wQE6io9BhHaZzBWEaQOvgyht4m9AJx3BR2APLS3MFQzSTpwNQdqNSyBAG3gtmHQQt0MzHcK7oZ6O4ENg0DE8vpXrRdvwFKijnTgbfLQbl4KfczTw/dBwF/vEF2zk/ch6D57bxpzTAXzmJt6ltAsbcJQO4HPbeS/xWTcOwAjrg/ijHbzTdD3e08lzQbs2J8tdMIlW53XxHqbVpeCmpZufHbCGduF82KvjwbWwnQ7gJthFm7gXdtBh3A89dBQPQSMtPVxfaKAdOANW0S6cD+tpD66FNjqAm2ANbeKKrdy3QeYWe7dxL9EhvA9sdBQfg0TaFuKd8AhzyPiD+ObHeIfTsp1rDQ62ceL5kEoH8SvgodWX9HJdaHUeBOkI/vzXmH86gH8Fh2np4/6Co7Tjce4vWHU32+Nff537Vo/1RLK8Zwfjod24EWxso34NHLT60zt5b9Bqt0KrPeCjQ/iRJ5kfPe43mE9o5LwcOAPW0y6cD220B9dCDx3ATbCLNnEvbKfDuB/20lE8BDto/rCX38B6juv4ZrI8/hTPHR3clSyfeZrt6fAzfBbW0FE8BI207GVs0EA78XxI/Qr3OV4HNtrEO2FY5wofgRgt+7hG4GAbJ54PQnvwaking3gLJNIRfOb3mCvaib/5fd5p2hE+Czm0B68GFx3E7eCkQ3g3ZNIRfOOzjJ8O4+dhFR3DE57jfqAdeBasod24HBpoEx9WaHXnD3gGaXX3fs7lHsbzw2S5HrJo9Q/BQ6v/BHW0s58xw4COGa+Gg3QQt0MbHcK7oYeO4EOwi47h8T/imtI2PAX2006cDXtpNy6BHbSBwz9m/jmu5yfJ8h1IbeQ64nf9lP2wXn3OQT5Lqz8MA3QA7wAn26s/+DPOi1afBT46iNuhge1DeDespyP4EDTSMTz+55wXbcNToId24h3QoOPBM6O875oYJ94BdXQUX/EL3ne0gQchSNt+yfsYmukQHgGTtv2K33Whk47gYQjRtgH+toIw7cb7DvE838s+f8PnYIQO4ddgB+0c5L6AA3QQe37L/NMm/h5sp+WFZLkD0ukQTnyR39NodTUsodWd4KdjuOUw72o6gh8/wj1Jy0uM7Xe82+kgHoQeWmLsA9roAO6HRjqGc3/PPNMG3gs9jazHV73MfOp+8BFw0M6jzBPUc+5hfAwS7puMuf//wO9ttHoQnLRrKFk6YA/bq0/7I/NAqydAjHbhfGjkuB5cC210ADfBetrEvbCLDuN+2EtH8RBsp2WYdwjsoB04A0ZoF86HAdqDa2E/HcBNcJQ2cS8cpsO4Hw7SUXzaq5wj41Tf+xpzS4/6GNeLVn8LXLT6KCyhPa9z3tBHx/BFkiJLmBN1Lfhp9V3QQKtrx6SISatvgT46hpNOS5Es2oG3QC4dw58ZmyK2+yeLeg+k0eqD4KIdCSnyM8ijbeNSZBpMamZO8FKw0wZOGJ8ixbS6BlbR6tugkVa73pUinbR6OYTpGC5PTJEZdBBPf3eK5NAevBpGGGcQv+f0FBlmvRO3w346gq9/T4oM0CbeCUfZXpJS5CxI0O3xfEijPXg1JNFBvAWm0mHcD3v5bBQPwX5aJqRIChykHTgDDtMunA8DtAffBiHmRz0MYVqd+F4+S6vTIEZ7cA8kPTBZ1D9+H/NJq2+1ce6044wUmQWdbO/G5WDSAdwEdbSJe8FHh3E/1NNRPAQBWt7P+MGgHTgDgrQL50Mz7VFD5obJoq78APcGra4GHx3GkpwiMx9kPLgOPHQQPwGT6Aj+M/hotSOF7Wj1IgjSAdwEi2kT2yZy/9BO3PhB5kj7zBR5FKbSUXxoEvO4nnvsrBT5HThp29kp8gyYtExOkR0=
*/