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
siYrg96RPrOHic7i5IOe+XJIJmWJpLOqkh30AeuT8d3zrTZaiJAKY0lqihRFzfiyr4KvCBQ4RuXgv2oKtgWZ8tcrC0KGaVxxf2TUaQ14TPyTR7PMXqLfo1CemrV2Bv7m3R4d7Zsjuo+uYVnheMiV4oUU135y3SR4Sfq9Uauas2IVkyhydDIJZzB8RgWrEDxnFP+dthjcsW6t5YNQAFTclBm9ukUaeR0lFvi2wUF76FAHTPtgZmiidRKxSsx9OUOl6ZKp/GdbvL/jVFuYsE0YGbf/dzocQ7M2bUfLAcGYFuQMdlg7BqhpDV0MaMd0jd/O7N4hTZIeWgqHZdP//C54KvvZyQF0va+T4M1plAqD/z5Jyrka25rytaQLcvLe3JsOyq65kWM8kk+NX/YT0GKkn7mENsKAECbAoFRLvxeFcQxrmq1pD2bwmMFknj5oDwKZp8jW9el7AM1kIT4liOmyQBg19/JWCK0cCfZpinwPPlTtF5Ve052MybXm+MEM4IpGskrV6ijOFWBqPgeIJEbRwz4kKMKdJxdiW5Cul4ulp8wokW6gy8jDnLOsFQ==
*/