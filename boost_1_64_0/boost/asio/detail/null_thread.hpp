//
// detail/null_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_THREAD_HPP
#define BOOST_ASIO_DETAIL_NULL_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  null_thread(Function, unsigned int = 0)
  {
    boost::asio::detail::throw_error(
        boost::asio::error::operation_not_supported, "thread");
  }

  // Destructor.
  ~null_thread()
  {
  }

  // Wait for the thread to exit.
  void join()
  {
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    return 1;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_THREAD_HPP

/* null_thread.hpp
K6aIjW+IdR2aaZJyNu1C81goER5Ivyi9cKNKXVaQV8kVEj9yOlCxnvT3vLA3m+KM5iiubaE2k5UYvHeTtgnFOwS5/d33N89cbiDlt2PPV3NLd+lWRNALX17v1Ls5Yt3cPp3jXEv2sfcf0J9g4Cb2g3qXN2DJuNS2TwzbuvVn3BLfr0B0alBkYrF8uIa1Mrlbzx5Mg2d0+uVUR6AuQAU3jNVtcCQKxLbX5FcAoDPz7j9rgAuZii+HR8WLSXSIhUoeSiG2mYrWvEQtLeZA23FdTzp2zqMjMAqMOfQbzFXpAVQnYWhr2R5cXIUaLThW/AjJpoc9tpwXUBxKgD9PsmHmlFlwlZlDK79NKg/4+jY9DbNr3qDH5cFFYTT3iDcs/+HlYth11JgqUlt3zT/VeAs/UWq1ElhUUC2oTebb+8Ff3oR4EibKULT8py6cTp6j5kt5mrQgAukA/b/RLtHVI7SfOcDLGOofk+nOrZIibFlGI7n3/cFjeGQCEaEIGCOyl2J1HMBz866wzZaNck3iiu++Yiam5QUEXi2oi5TBXYYG/GxmE0KwQYOQZoFWew==
*/