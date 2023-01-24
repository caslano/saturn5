//
// ssl/stream_base.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_STREAM_BASE_HPP
#define BOOST_ASIO_SSL_STREAM_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// The stream_base class is used as a base for the boost::asio::ssl::stream
/// class template so that we have a common place to define various enums.
class stream_base
{
public:
  /// Different handshake types.
  enum handshake_type
  {
    /// Perform handshaking as a client.
    client,

    /// Perform handshaking as a server.
    server
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~stream_base()
  {
  }
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_STREAM_BASE_HPP

/* stream_base.hpp
Wxr+rkv4/QO83LZNzGPweOc8tvdzxmHuR3GMFfZftX5UZ073o2WqF8xrglnWi5obBXONsM+0vjd1awVzqmCGCXtw0+6j7lvCvoF3X+reJqyX7xLc64XwtwTzo/upv1JYB9YIZg8wy4Rx1jZhzXVvAKX9YADl/wnBfU4IRxN19Y9gYn/wWwDFnT+Ihi8eRN02YR2m4UGhXgdS88JAiu+HgRS/bSDVLTcFf69BFL9mEMXfU8A3UcATJuIT1sC+G0DdPwnmVcHc0Z+Gl/eneI/0p/md7k/zuwgmylB9f5rf9f40PzmkxzM1GjBxTeO+AbTuBwt4bcL6asMDFK+HgLejgLe7gLefgHeYgHd8f4o3sj/Fm9Cf4k3v33aft2UijSu2I6/j7mUWoXaic3/S4wfaTw4fTnGMH952vv0mOePw7tN2v5nkkqaHv/s0yLvVk5zbV8O9zmOV6C5t4zjuguPHfs44tgVQHGZhnmAbQcu/WhjrvjBSkCthbPmdYA58p1M0I+QxEGDWwypm1kgVI4aNlhf3as9QfZQEYUkQVtzL4/OY2LDY904u63/eujtq+/LE4qMJ6d8hjgWFC9MKRowYPjQrcOyYofnpc5m733/qKwqhdYymTCYJaGGUjXUna+7tFC7/dxJ397v73f3ufne/u9/d7+5397v73f3ufne/u9/d7+539/tv/xXl0zUl2690TXNdjEpTDRAdG/eX
*/