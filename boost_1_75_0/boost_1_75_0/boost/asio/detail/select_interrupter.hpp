//
// detail/select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
# include <boost/asio/detail/socket_select_interrupter.hpp>
#elif defined(BOOST_ASIO_HAS_EVENTFD)
# include <boost/asio/detail/eventfd_select_interrupter.hpp>
#else
# include <boost/asio/detail/pipe_select_interrupter.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
typedef socket_select_interrupter select_interrupter;
#elif defined(BOOST_ASIO_HAS_EVENTFD)
typedef eventfd_select_interrupter select_interrupter;
#else
typedef pipe_select_interrupter select_interrupter;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP

/* select_interrupter.hpp
a9e1wGpYlLlBBIq/QF8GgIeE9FkUZZCmYjh1FzDeEeQBhhogo2s67D2c/935cZR5LxyNcJyGwwBLBvViE09Gma+Ao2VrjPlqOE+HYwYcqXDMhgOVDkieb4Zzwud6sw3Ot8CRD8dteG9bhHkpnIvwHeDES+C8Ao5SOEQ4yuBYC0cFwoPnlXhdEWWugvMmOLbA8Sgc27AeOHbCsQuO3XA8C8ceOPbCUQ3HMTjegaMZn0Ob/HA2nYL2w3EzHCvg2ATHs3A0wnEGDvOHUeYkOPLhEOGohKMKji1w7ITjMBzH4GiCg8Fh+CjKPBGOm+EQ4dgOxxE4TsNhBLxdAUc+HJVwoKx8+eW6LStLl69aJq5charGpavFVXfde+flJGrADu8YbTeUNEFjVXNRF8X0mzEk2Ygas4SZMzVpnBRvJvZUcVBHENyzHwheLHGsgNmfZtfZ+A32//L2LXBVVVnj5z6AC169NwVFJSVFxdDE0BKvFqQXtESvEveKio8EwpupwTk+GlHoSHE8cyfnm/rGpsdkNt/UTDM585XamwsFvjI0xzCdxKLazHUKy4GrIue/1t7nnHtB7PH7/39/qXPP2c+111577bXXXnvtl+fRNQoqfp6bp5Ii1EHXBuNA7uWtjCbp2uNbFMIHwuzCwlQSVNfLOZZZXgMNJx3/UpfIvaxDGLz0rDAsEsJ0CCCQ91AikHP3d1Mf6FI53l6Q2csq
*/