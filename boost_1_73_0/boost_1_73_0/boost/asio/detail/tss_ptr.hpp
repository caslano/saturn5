//
// detail/tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_tss_ptr.hpp>
#elif defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)
# include <boost/asio/detail/keyword_tss_ptr.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_tss_ptr.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_tss_ptr.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class tss_ptr
#if !defined(BOOST_ASIO_HAS_THREADS)
  : public null_tss_ptr<T>
#elif defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)
  : public keyword_tss_ptr<T>
#elif defined(BOOST_ASIO_WINDOWS)
  : public win_tss_ptr<T>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
  : public posix_tss_ptr<T>
#endif
{
public:
  void operator=(T* value)
  {
#if !defined(BOOST_ASIO_HAS_THREADS)
    null_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION)
    keyword_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_WINDOWS)
    win_tss_ptr<T>::operator=(value);
#elif defined(BOOST_ASIO_HAS_PTHREADS)
    posix_tss_ptr<T>::operator=(value);
#endif
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_TSS_PTR_HPP

/* tss_ptr.hpp
ci9kb2NzL2NtZGxpbmUtb3B0cy9jb25uZWN0LXRvLmRVVAUAAbZIJGCFUmFr2zAQ/a5fcfhLN2jcNgzKwhiEwmghNKPOfsDVOjuiss6T5Gz59zvJSvH2ZQTCWbp77+m927HrN9Cyc9TGVWS19fL95XHfHO423/cv8p/qda7XX9Uj2XEDD3M/RIYjh6i2WpPewH396XN9qxqiFdrAG/AU2J4IjoSavHrASD378zuhYadWq5VS39gDSvvPiUKGjUeC3pzIwUIKjGj89WU4tS20gXEhCk+tDkcTgMeEDlKFyUR8tZT6tfFpshAFwCi0YaTWdKaFQP5EQkB1X+cr9X7V2knQPTjWJEwydTnhrsyFGv5hZmfPMAXSQq2ET1SYcMxvcxR/sX9bGFHDUwTNFOB5fwDsuvxEaU0OOxzoZmSfTkSYCSrDdmLbYdfcNM0OPmTVzfOTGEQ+JtViN4iwuRSKjyD9aSbB4jjacq5Gz5FbtvKEKvtdAToNVXa9ggHP8Ep5ioYxniFEb1x/DQOhkwIqdGeVdGaNVUFZL1DWM0pai/9AycPStSoZXYmN3vTGoYUFg1JbqNJ3dYkvuyyTfyXQ8jCilysMKejCJRpMlAhIh5TMgLEtqYjNc2AS8WUbf7zscjYtuiSdjHTKIkyD
*/