//
// detail/std_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_STD_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_CALL_ONCE)

#include <exception>
#include <mutex>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct std_global_impl
{
  // Helper function to perform initialisation.
  static void do_init()
  {
    instance_.ptr_ = new T;
  }

  // Destructor automatically cleans up the global.
  ~std_global_impl()
  {
    delete ptr_;
  }

  static std::once_flag init_once_;
  static std_global_impl instance_;
  T* ptr_;
};

template <typename T>
std::once_flag std_global_impl<T>::init_once_;

template <typename T>
std_global_impl<T> std_global_impl<T>::instance_;

template <typename T>
T& std_global()
{
  std::call_once(std_global_impl<T>::init_once_, &std_global_impl<T>::do_init);
  return *std_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_CALL_ONCE)

#endif // BOOST_ASIO_DETAIL_STD_GLOBAL_HPP

/* std_global.hpp
I4FN9u7yQs/+33ta1ffG4h04nrQaX3nbn//sNXi5P+MawvJnUvsaXaYdwiUELECi+vhb8UY2GFiw/pJr/cEACSz20+G5Ul5QVAx8tKiYqJ9Zkzd6sTutHZW0IL/Z3VWK0J8egVjE1jcv4aqov9eEYQ+rYS/2sKCpOr2lP6xYp5WgBwDmDeCewJ8h5Gasqh9WFe0mhl+gANGf/DoFW45bfOS3c1AKxgkQltTaLRmqfiOWlKTo/OMxM1VsDHaTlTCC8E7Gfpy+pkVt0lL1KiTM7MGF6BecfuMUKg1y3eSVpfRMeb5U3um4YhPx/CP5oPyqgifcnZ3z8ALlR9DZnaPJ9ijKmGmnTV2BCTDO7aVdzDZqdMWdC5mjbvFKRFk8ML60496Y/I4LMypqU6sHQUHzHF1lH0IqoRBSlC7z3re4PmoF+f3NuNKFaPLkzWy9BtPnmueuqp7LyVYMndJXiBGv/IIfUD18RuAkeeBm5pbeAs1OqY/kyKKbERs3INTzaHmBWAyecbOmmFmJ7hfqNf/bSBb0KPlLdKlcoIWx0CdOBfUD5teX22/f0NFTbg/vnwNj9f752qj1T9WEH+ifUPd8Feqe06x7PjNq3WPB7qnBYkdvvgpyF+B5nm/aFtpBL6sdhMZhaQcDY4rTo2xV9EbfSxFliXItdsjiju8zAdm+u1LlPEuxFCV+a/QuXAg9cxxSC15IWVrkXbEQOgci
*/