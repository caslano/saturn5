//
// detail/functional.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUNCTIONAL_HPP
#define BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <functional>

#if !defined(BOOST_ASIO_HAS_STD_FUNCTION)
# include <boost/function.hpp>
#endif // !defined(BOOST_ASIO_HAS_STD_FUNCTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_FUNCTION)
using std::function;
#else // defined(BOOST_ASIO_HAS_STD_FUNCTION)
using boost::function;
#endif // defined(BOOST_ASIO_HAS_STD_FUNCTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_FUNCTIONAL_HPP

/* functional.hpp
+WYNe9zmjKNuh5WOlsP6xq4l/nNJwyd7FfBSYCVW2nr/A7as2aQzhqUzhiSxiFkts53MdjHricQ+SZLYf2jZ9QR/lEl8nBJrvKWRflKOxFaTSWzYXtTSQf75uWTf15Jsk7+nkq1Rku0ve2tqCfAdvoE+lrDES0iSS5gtY5Zgtp3ZaWZnmPWkFD5NKoXX4W9CllIIZNTbxuamhuwlgE7LPDqY+lVBlvBX+M9b+Go0bR6BRtUtdj5SH8dSH0eSq2E=
*/