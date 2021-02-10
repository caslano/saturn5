//
// detail/thread.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_HPP
#define BOOST_ASIO_DETAIL_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_thread.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# if defined(UNDER_CE)
#  include <boost/asio/detail/wince_thread.hpp>
# elif defined(BOOST_ASIO_WINDOWS_APP)
#  include <boost/asio/detail/winapp_thread.hpp>
# else
#  include <boost/asio/detail/win_thread.hpp>
# endif
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_thread.hpp>
#elif defined(BOOST_ASIO_HAS_STD_THREAD)
# include <boost/asio/detail/std_thread.hpp>
#else
# error Only Windows, POSIX and std::thread are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_thread thread;
#elif defined(BOOST_ASIO_WINDOWS)
# if defined(UNDER_CE)
typedef wince_thread thread;
# elif defined(BOOST_ASIO_WINDOWS_APP)
typedef winapp_thread thread;
# else
typedef win_thread thread;
# endif
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_thread thread;
#elif defined(BOOST_ASIO_HAS_STD_THREAD)
typedef std_thread thread;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THREAD_HPP

/* thread.hpp
Q5O18nxyzhq21LyYlOp9We8tWD25X1BLAwQKAAAACAAtZ0pSp6shbxgDAABLBgAAJgAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL2NhY2VydC5kVVQFAAG2SCRgfVTBbtswDL3rKwjskBZIjPWyAt0woEsLdGjWFXOKXgoUik0nQmXRkORk3tePlO00WbedLFgk3+Pjoxbk1hdQ6AJ9VJeez58qY/GzukHbXMD8EuTGVKbQESESbNGbqoMG0YNea+NCVPeeIhVkwwUsF7mac+iafHcB0QY1m83UEq0NULTeSok2cKUNQmiw4MpYHmEI/AGQBApYBstNf6lq3UFBLjI41K2NpuGMY6ahDz/4cxJOOThEWCFw3v31N1WRr3XM4E6+1nY9QRNg1RobR6YaSqw0w/TMOIk5mTCFQOkA1ERDTvEpdg1jSSVOLKWAthElXsejKplSCctjQWtnfmFIfaLbGk+uRhdhq73RKwZ0uuZak/nDj8Xz/PL5y8Pd1eJ6AqYCE5msChinoF0pmH2Ztdmig0bHDejA/NNJyIwicYOuZBas0St/YsG9KVMN/YrPVEXJnXEl7YJMJXA0UNWrtTPWgm4jsZJD75boJcm0xwu9dKkT9TSRxFmhZwOLwsenyRTQMHcv
*/