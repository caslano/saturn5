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
CzlQsxVXcYs0wsU5XUHYr8B7WRKQbGrbwyLIvw6Pz5OF3fQ/P6g9r+/gwnyWarVJyBcmSRfkQpYigQ6QnWCM7rUsIYvTHgAEUV2HVtZhRRmPxXhzlonF5J1Jlobm1PD7cNdZ70t2WZ1/xMZw7ZlTlMTRVirKO2Exk6tLkxDGg6XTMreeYSi1Cszg3cCWvgwulD6bqicjzgTNzpAKUBRtQHc23UB/CN2tFwuQvEehpuqt58642TOQ/WpaQDaDLGmlZoDBxyDJ3QWvSpZBmSuX3JoK8iBKFTLmdG+LQGO4Fvypkh+5hKDx+06aFKhFfxhd97+2sBKZ2FqH0oUDy6B6/65Hx1tnyjRckcj0jvZH5D7xhY53P6sjmZmlONLAVnKeNXQabKWIH21ZCw2BN/PrtWrOZnRBbNFxQ2JWh14s7fHwKK5zQIjbVR4RzMV7yjeVwtAgucP4jLmF98zXZEZnDRehjPDBBnEmgLXe6gau72Y5nH6GW4fwp8TA5EokKYxoGmeBjjIRJPzsGB4nkmVcGQCmRFOMua7JmhhM9+u9dSoP9J1j8DvQ92rpaUremx/+l/ff0jV//yYfbUsuXzbDfMBtdZKwdG9X8H05h8KujHsrC+nS6VbLVsEVNYPQ0lWWWRI0DIW61jtrKW+3
*/