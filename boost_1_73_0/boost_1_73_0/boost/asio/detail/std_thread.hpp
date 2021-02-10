//
// detail/std_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_THREAD_HPP
#define BOOST_ASIO_DETAIL_STD_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_THREAD)

#include <thread>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  std_thread(Function f, unsigned int = 0)
    : thread_(f)
  {
  }

  // Destructor.
  ~std_thread()
  {
    join();
  }

  // Wait for the thread to exit.
  void join()
  {
    if (thread_.joinable())
      thread_.join();
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    return std::thread::hardware_concurrency();
  }

private:
  std::thread thread_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_THREAD)

#endif // BOOST_ASIO_DETAIL_STD_THREAD_HPP

/* std_thread.hpp
sKopteYHUEsDBAoAAAAIAC1nSlINbVHwegEAAIcCAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvYWx0LXN2Yy5kVVQFAAG2SCRgXZHfa9wwDMff/VeIPm1wl1EoG4QxOLbSFkYp68Ge1VhOvDmSsZVbu79+cm7rtXuLiT7fH9JX4bEHTLqth8Htij0+hpgIGGf65O6KqAySag/X+/3dvbumlHu4ZHywmb8Y/Io6gU6xwoDDRNAE3M578j186N5fdOfuMyqNUp56mFSz22637vvu2+3N7VV/JCVrFAb7osdMJc7EiqmDLwIsCksliAy5iF+GNtk5t3/B0ZqomtYpVsZSqTRsWIpJ3YT193M9yBJZjRFAdvQYq0Yen/FTl41xqFYzJXiglsV3sAtq4giDzDmRkgctyDVQ2bhmc8T/MRUPbUL+S4AjWrwYICpMWG2SGGbxMUTzcO4+0xDDk9mcnb3A3vymIpCIR53ervkPEj0kQW8N3pnZWoQ9zPiT1vrux1KbB3sTOeUz95lmO4yZrft5dYrWFCodqGACtZvUzSp2rNXsrD4rtS2GIrPtLjVx16Jam0VXq4RmLUyvNghBChyTdu4PUEsDBAoAAAAIAC1nSlKa/mEFuQEAAAkDAAAnAAkA
*/