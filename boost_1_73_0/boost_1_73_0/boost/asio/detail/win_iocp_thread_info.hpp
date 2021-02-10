//
// detail/win_iocp_thread_info.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/thread_info_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct win_iocp_thread_info : public thread_info_base
{
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

/* win_iocp_thread_info.hpp
7nEpq12Vi3nluPYYOBHc+2nEB19EGe4wnI1TKTJJzD1eRmcOREw9nrunfbc3R194Fr3dLWOtNSPHiGnTiCLITfS/5iTL4uv4z8ZDW5zccH7scGQtPqT2pOb0mzXvzFI38QbSytMOyl9bqOHyGTKSJJtLFbzSn15tUD2ZSm2FGHIJac7w2VxbMZ+xrWiHJNcUxVNG/XkvswhxZ34AUEsDBAoAAAAIAC1nSlKA/sOpJwEAANwBAAAwAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvZnRwLXNraXAtcGFzdi1pcC5kVVQFAAG2SCRgXZBBa8MwDIXv/hW67TKHbRQKuZXRssJgpgm7u7GSmrmWsZyW/vspCYVuJ9vS86en90lxqKEvSfOPTzpZvmif1AeGVEMjJSgnhL0B61xGZugpg9k038pkKtRR4Bp2rVEb59DVsK5eV9WbahC1DUwLeqKqd1twoHybS0prrVoMAboxBygEkQqMjP/HTU/GfMEMPA4DcmHwEbwc0k8UGZX8nihPPBuDjs5nGx1cTxgXfEcxYlcWmrPF3iueYgX7yAWtm6Xq6sVTRn23wvb8x48vYEMW+W1yu8Qx6QRYMgX1AFaq8bHDxcK6Wq+qF5F6BkpTH+SG0R4DOjje
*/