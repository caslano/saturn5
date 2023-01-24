//
// detail/signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) || defined(__SYMBIAN32__)
# include <boost/asio/detail/null_signal_blocker.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_signal_blocker.hpp>
#else
# error Only Windows and POSIX are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS) || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) || defined(__SYMBIAN32__)
typedef null_signal_blocker signal_blocker;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_signal_blocker signal_blocker;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_SIGNAL_BLOCKER_HPP

/* signal_blocker.hpp
hpsdbRtGizkWJddrRlPNXC178gvUyjVGLLcYBbN8NjCQ/OV+PDKquWn4fC9waGD3dYvRWwzZcT9Ck8zRgVrn9nYtpfbNamnjaGmCydu5FBhlXeBsKCoVoti1ObPqyN16KWk1dd5xJVNeAInwwt0dirdrsVTQnFZDkWN7sgYdvpCE+3UMOaAx3ssLWz+jWYsl59Fq54dylOR8H1Im+Jzvu7T6JlFQbFX/hWZKVwNHxK0WgzDMdQ2sZm9n4FWveSGWhZvXuIPccm1BgjkLj00UdML47HVD12tcCgko/J0AvdhlEOIYDtMOTkePOLYn/b7MK4ExYpeRl7fnHG33m4Rfyc73pSjZeUDKNtv2+v3EKDYbpGyL7GwmYwAddfq+72th+76Hd0XbP9vFPHuevzfca50HGkJuk6D/3vcm+HIa57tgrCtxsxgutlXRbacTeGDP+YpLiZuGhFKwB+bUtHaXJASVuCmMHCzpQnC9SRaCc30zFNP3HY0j23ij6XufeaijrcyIHmgu+n6hdHwysrwNxmeXI1g6HsREXOm6PUpcBitkCJ5oLjEbWOBMFsgM79NqfEXP64eDbynCw8HewpK2PwAZ/GsWkEEfMm02niI+jZZlN+Ld5/ywcPuxt1ep9mMZRIH0tVbOm+FNXOYhYg51InJAyjmDPrbD81RreQKHd2OJ0vRCmMsicFvOcaBsYnFDppmLEaMVKd9SsSKp
*/