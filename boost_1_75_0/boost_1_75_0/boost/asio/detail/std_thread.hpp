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
LNxdEMeSBc7oN67ltEgGrb/i1cISlQ2FbiXvTH5gCMqrBWh9qsKXgPDV0cjuEN4gOxul7OWYPVJ2HpGyC9NqyOsRTIZFr1PRlFpD/ft2j/4t/oqtH3OsctyZ5gg7CgfpD5l5m1z7QI3V5LSKfqvjQOn5B45bTXlWx6GyaIgVzLKfSovqTkZS2AUTeOnMjdhGt4feZGVNU+ClWfkYSZeQmCswPznPp0+37ISlQRVeYU+ZhqekGmpX4kq0A9ZJTLAFpmGrKgESUePf38XibdtyMfAiiba7NQZp23YnhMHQLnkeW7Ibq2BxGLaHhlm7hXGtkH23PTxsd/xOymxjS97HDKHwWAiXBcLmOkgwlN7+xUcBgTUDUOnl5/kbveaFrbj7gh8wchkAdOSaAl/uoiXciJ/AkOalT8aa+GwoW6GvgBbAUs55yUmqDvIToOwU5Rj1v5JzZr7X6stpm+81uJQ8AmGR7c6gQegjC/bKo2gMFkjdhS2DcpMoa+NvVBpldMYYt8vOwq0sPMKDEZBPhQ7DrG51v1VpxF6FGXrZUjQAXToc5+gdO3KKyspgNrlr7UYPB3NMXllR6bz7vEUr+dlriteWPrgCOaCHU+eyRFixeZBBdAbu8Xi8isvjUeJSqWMPAMflNXrIH6Oo4hynAP5Oj8urKLcBkajJ8OA9MzZY9L9BKv9t7CvWm2W82eRVdA+VXt5JuTkZfKGdWi0H
*/