//
// streambuf.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_STREAMBUF_HPP
#define BOOST_ASIO_STREAMBUF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/basic_streambuf.hpp>

namespace boost {
namespace asio {

/// Typedef for the typical usage of basic_streambuf.
typedef basic_streambuf<> streambuf;

} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_STREAMBUF_HPP

/* streambuf.hpp
8jbimhEYPdNFsXdcXLW8MxkvMamujqYql79rwgwuJ/qFfLO54K9wvECAjuUeZYwUQpWtPbg08N49s0g+0N1tbT2kfpGBRvPcI13+swnrXpNvYWIX5+dOMpaOxrpUJ6onpvLJbxeTIBVwkP0nR7c0/0CA3xm9MPY1PWtnxgl1hDfZz1Mr7NXn+weT18/hoYO7K08dn9ePP6zqXaKXyDFvBjyaLBvSFTe2RhpJDBM9qHIYqSGZ
*/