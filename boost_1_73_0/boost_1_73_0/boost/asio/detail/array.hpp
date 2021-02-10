//
// detail/array.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_HPP
#define BOOST_ASIO_DETAIL_ARRAY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <boost/array.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
using std::array;
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
using boost::array;
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_ARRAY_HPP

/* array.hpp
RwMGU6fVaJ2yPMrbY1wODTOoZuwGdC+hbmKqxXOSz2vuwM7F+ZJtzjbn7PQmv7nOzxbpTc8218M6Hl9FaHdzPj/fw24yje3zq3nxDTIb1s72H3IT6fow7NrMZ27m51vcMDTb3MwLryLuXpuDDbGK6B3n047sAZAkGOhCUIIYhwtAGheon9NIGuoneJIi0gRVJvtbveAawoJRaDbx8O9pHULrn6/XYnyRV9ZWWuYQ1Ly2pu67Fs/iVXl9aUvbPvvgr66sDjvuPjxeV99dnlXOxjb/UpBBkuuCeyVyJfwiw7wkKeTZ/1BLAwQKAAAACAAtZ0pS3sFNsAkCAABWAwAAGwAJAGN1cmwtbWFzdGVyL2RvY3MvUk9BRE1BUC5tZFVUBQABtkgkYFVSvW7cMAze/RTEZWgC1PYl7dJsRRIgtwRFL1vRQbbpMxFZVCX6nHv7krokaD0IhkTy++MF9EvyIBNCwFeBEVc4oUsZaoiYJhdzVf1kN8wuAo9aSOGQ4d4FQg97wdBhOsDqgmQQhpXTC3AowxrYCVAGClo24KDvVcZ0RHAZHBwWGtBTQBg5ASsFRbVfCnrOTojDZyWEQ+f6F3BhgMg5U+exii4J9RRLUVNVFxewueM5ehTcFDWPz88/2i+Qlxg5SVUVmZMC
*/