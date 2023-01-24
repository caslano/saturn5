//
// detail/mutex.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MUTEX_HPP
#define BOOST_ASIO_DETAIL_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_mutex.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_mutex.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_mutex.hpp>
#else
# error Only Windows, POSIX and std::mutex are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_mutex mutex;
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_mutex mutex;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_mutex mutex;
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_mutex mutex;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_MUTEX_HPP

/* mutex.hpp
DXuQbvE5ZLBJfA55bgougSdnpwscPXaZECd9G7waL93Mua/Ez59zbtT52as59wX4eyPnxqPFZy/l3KPhUzmXNbU34KXPoB3VrHsVXyp238anit0b+EtUNrDnar30K/gl/PHnmasyboM624M3wGuMdsauqHf2MfYH9+i3e/34aO8b7AZELOwlA9eDErUV+We6TK3UfVBIAbEo4hPqPfh8eHaOEMe+mrmaYWJTms//E3zt9B2cGzEo8fRNfJp4+h5+HBNBp8yPh84iIStjUq2MyDeKt/z4DIghWpjWiN1hzr0mAcUci5VIRKTtKAS4QRbuwnxdAtaymttmhaiFc+fbqVLOvd2KX6ATLocr3C+4GPx5y+YM8fTP+clIn6cH7FDVXmywSWrgPE54IbgwHuqiqpWHXTcv9+3CaoMfwcvpnbitV4LkQY3P86YoMbi317hrfURNvvzFdCSbUaiqfK0wBA/s9qwhfaxzys9uwclRfpX866XAAp/2o4AVHPagSnnHx/o9aEGcfs8m9rGUfaCBceaVyO8MU4+64tyFQHK+XDE9wjXlYcmDRiRy7IDXg7o5q47zELwVqZeNmuTLF+DrfqxEaqmmh722GWengdUl52uUCDcF64dgT5GKGppW9uOa1jlUb9r6IUibdGmkacTG8s1sr7NHxb1YJPT6TNLvlfwQsTuX85xvHoAMzs2RmcDa6m2xK7+HijURKtrt
*/