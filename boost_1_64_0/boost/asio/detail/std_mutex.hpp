//
// detail/std_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_MUTEX_HPP
#define BOOST_ASIO_DETAIL_STD_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#include <mutex>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_event;

class std_mutex
  : private noncopyable
{
public:
  typedef boost::asio::detail::scoped_lock<std_mutex> scoped_lock;

  // Constructor.
  std_mutex()
  {
  }

  // Destructor.
  ~std_mutex()
  {
  }

  // Lock the mutex.
  void lock()
  {
    mutex_.lock();
  }

  // Unlock the mutex.
  void unlock()
  {
    mutex_.unlock();
  }

private:
  friend class std_event;
  std::mutex mutex_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_MUTEX_HPP

/* std_mutex.hpp
QhgHu8HasInURw/JR4n5BuK9XfJRV70z4CyZi58Ki2BD8TcWfwt4BzwXboA94FI4Fd4t7WM5vAfeB9fAlXA/fACWwFXwPbha8vEgrKK+I2FDuBZ2gOvgQPgIHA+XwxlwPbwNqvTvhQ+ZuQryjg713LcgG//TbHJbwpQrCVPuqE1uf5DcRX453pPKlyvCtRG5JQ5zxzaLrfYWqYfn4PlwL+wk/m5wNxwsxzPEPxI+BS+F22EufBrOhs/AQpFfCJ+AN4kfG3Ox2S7bVntwbvj22V7b7F/GLvu3bJNdUXvscGywA+yv3W2vxe66TJtrsbc+flvrE2FnXY6Ntd2+WmyrT4xddbg21f9P9tSBttQVs6Nu8yLliivALccV40px8S9RNrgM3KyXfnu2yCdP/z9tbF6+sgA4Pv3/GWg2O9WzWAwizqLW0gcP6HVJ5pAeGRkDhvZjn6mrMgsKrDORKa7FM9dB5qLMKQUTpykpS9sSzG1t+ffX9XjLJN4LPc93B/EU7dFjB6ERhbEnSh2uZT9xJHdT15KdO35sNgEDdU/J0uwa4qrJ8/6PvAC0ecEhXRngU2POu2vb10QUeWKRMRb0uOXvV+LTsRKXXgPRfl2LopzLo9CpPLzFUe5+P77yKL7QvTyOOZTHGqVrdSwPvcSzyXNOzfL3H7GPF40Q+5GXcU1x63GZquyf12lNaXt1ZlC9W5bYUXDeb0chdSDhmulxlKOiO4iO89fTICPTxuj3xmj/ncQrY7baPiF7Sn6Bfy920ZNI2A74qT78k7V/qQ773CmiL1B6Wl78RH/hrHvT4Zbj1+2In7pB/TrMW/X5/uJn1Ej7U0PTaWsZGw5l7/AddTcrhnfXlkrX0DQptlpS9O9QNTjpGeqI/GrkX1TyCb2S1PqfIevEyljUD8le176Vt45Lneu4F8GIo1PNEpjOtTNWpOuCOsNvqzOOfwepH9X2tRyZlDFsUwdGj0C+OW7KV9YBDzreNrB9HYt10S+8UAn9wguVHwcmPsf9BvbHOY+/b3mh4uPvhClrDJjzlR8DDmf8vafkqUuV0Dytpf8oMXkK7UIo++xsWz/ydRjXZh9PL3VIc0gnnkEuadrrelAnhzH/46hr4pOyCiyXvfGh1zgM2eR9ztcYrE9qEnKdElb0SXud9UnIVF6fRJoh+qS9ofokUw8rq4bm8WE1/u+aR1Z+d8+fhKsj/WTI2u+cr/za76QX0qZJw3Ht94KE0HylEz7DLV9yrzq3Lwnnfq9yvvL36qBO5d+rvv6nmeg3E9X6rMIZZHK19x3j6rZTKvb89YarL3oPb/476HY5vsCXv0FBcll2fanN7jHDyNXS9gUX49+m/f/ydOD/b3DSbuT5mW/sF3Zpub97WmKH8CXOyYYg9o/IsJLBCqtq8HPY2CWO1zITGX9rZWwC4tWzty0y8v4wRMtc4elspckx9gbTxwqtrlZnrqmXtp3Ue5Tq42lYVHwbGJ96noltQh8tM8nTi/gu9ESJfYIvzoVYJvWyUoizjtT+/L3qeBThORaUToJ11G8jJHZOKfKO0VDL3OaZKtc9wKRxC+17qrYLmpVAWSahx2utbH5q2fpnWR9eZI4k+Wx+hiXF1kqKnuHyzuGLM7ma2PtUywt93xCZdsgsVOkmFW4375dBMqOReaklMjXmfhuydr3ILEBmEfFgdbE/KVrtfGz5+wuRbYVfr/uajL6JYzj+9rr3bPybOHUv9rfKts9cuNfYZ4oeLeQdyNhXcI9wnHtEjuUZXb6+H4xe7XBUxfU0ET3cydHD5Wg93Irqz/z5zVWT5yxKfmtj6d8Tv2ZtFl1f1UuSFk1q/NGF3+xs92TtaQOy3PVnznq7X48=
*/