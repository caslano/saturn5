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
a2jAcOU1xa0oX0EJM0NfoTvX35JWQH04yI/qnCMVAkB/c+h+A80pd4uUXdyVkO2pwOH81hRCW69PSsE+Nwvl5M5VqMcjMmPa4rGHkmc4bUlU6+4LIekyPjFVe3XAvTEHvmZX9pHnqm1p484k+dD764T8F7qQQCAdL3x9pvVUUc/xEBSuTVbmKTne3cqP+pGNgrU3GNtPXhv54JhifNw/ZLbL2ZF1z0r7YWpmDsggEuCq+tblvY5GIZJpm6orN+pmnPFdK/x5uHIeX6eiXPZ4XJvVcAGpHbNPkIWs0tU0FT+T/UKB22yUTJuzIl9fOMvO9pt1ZHKdaPLar1SZfmsCXXtShEv0v82hBiTCHWrZA6o9v0dIRd+Z8qseysZy9dhaES+FkAnpv+ZufQsLTjuNTEWx1+hukXnQfF7eLvo3kv8MaHVcr7gAaoChNcWpQqSzK/t1DoK6hDeWoKdOpVoz1fTvVLiFlK9E4z05d5fwvBBdFSHC7MKVro9g5an2WTOaiSugsnGlN/4Yuopvs47cyiHtg1a0GiH6VRqcmLjHOqYk+zC+MkU0hq5ByA==
*/