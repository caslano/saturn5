//
// detail/fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP
#define BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/posix_fd_set_adapter.hpp>
#include <boost/asio/detail/win_fd_set_adapter.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
typedef win_fd_set_adapter fd_set_adapter;
#else
typedef posix_fd_set_adapter fd_set_adapter;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP

/* fd_set_adapter.hpp
MmEmZVRS7ZiA/R9ajeSBIjNFmfrxfSopviwpMsgtGcEU5lrYv43nntGN2Aa1YvWsTyM/Veo5xfRPoJh90wxAsZaj3kuK/U71FioWx91Q26djAZqq7g4KP2gKOUoDbMZbta78HsrHfKEpujyJUswdZG3S7myQHbp6RrTxWD7MGhy7RF3HtY9riVQe/aDreBJNMo+z7w47GqEsDdO/b7E98WNDAnfL33jceaOf+hKi0iI2PFmU
*/