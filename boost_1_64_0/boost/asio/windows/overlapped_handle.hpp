//
// windows/overlapped_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_overlapped_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of an overlapped handle.
typedef basic_overlapped_handle<> overlapped_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP

/* overlapped_handle.hpp
0Snz5JTu9t7+06mDRA+31Iek8LpeGJyLD6EKBnqPjJiFI9sJFWVEzjCvrZfCjEK5IxsVb1+FEurpvKk7E3dw2yqcsErrKTbEFDmmVh7ToMLwrvDr5CSnVZKGux7dW+qe76Mm0qI0x+TlnqppIPS/4aDGPS9AOUJ6iTQNqScbg+REmcRhEHqGeKgg6py9fi8nOCSlu5UJtxI6y2OuF4SwjUSfRDSvmCPApj3KRIfvW7/iamSu3MU0mnl5zhIrKFsV9kYANqWIYgL5V0lAlB/YYLuTj2XU/ZTQ2xG6ZrDs0gbLCjNMmsfQARN9x317yot5icWD2vocsf2av7WwWuCK3M8MArUlfzAdOSpMjhTGqZs6MRCDw48OoApGwDGPlgiciXcXP22dg+kaUljtnkrmiFUy4bmP4XzsrVfEazemkWyqJQuZ9HoQynQHl+0mcbc1H1klgElWOUkf/MjxdoqP67/Bi5+2wGd52Ye7V2MkhGVX/tD4QW2fNKdlHfwo6NXqqo3NivnvZSMAKN55u99fY2d4AOY12gwrwd60NzCqI4H2JKXJMVeH2QsKYg==
*/