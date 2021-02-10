//
// detail/future.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUTURE_HPP
#define BOOST_ASIO_DETAIL_FUTURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#if defined(BOOST_ASIO_HAS_STD_FUTURE)
# include <future>
// Even though the future header is available, libstdc++ may not implement the
// std::future class itself. However, we need to have already included the
// future header to reliably test for _GLIBCXX_HAS_GTHREADS.
# if defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#  if defined(_GLIBCXX_HAS_GTHREADS)
#   define BOOST_ASIO_HAS_STD_FUTURE_CLASS 1
#  endif // defined(_GLIBCXX_HAS_GTHREADS)
# else // defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#  define BOOST_ASIO_HAS_STD_FUTURE_CLASS 1
# endif // defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#endif // defined(BOOST_ASIO_HAS_STD_FUTURE)

#endif // BOOST_ASIO_DETAIL_FUTURE_HPP

/* future.hpp
YgNjs7tnrnXakdLBQi5K09Nf1Ux+mNB6MtXWUkcQzDGw9BuXr4hemIcqV5WWJnblGe+bGEncpX3POM1kS5uFoWiqCSDYx8fVWR48wBwRXxtfRyR5HKD1vqmhk15UasrRxC4Nt/nmfHFarNciLzDG+nzp5EMtM23AmXA7MzR7bmGcmH/4zV/+w29++w+/+R+B/SHzKcO+g4Fr95S2+yTkCplRTn+JC/ODaxj3ZE+pN9UKgt6pUo/X3XpYh054jEEH/5Ov2OdI+ypkgPacyfv3WdXY3e7Impm0u4C5Xs94JR52IBzaTXADC52GJRk4yqoI66rc7q0i4yZXbyyEKda3TM4N2WOTNyaF2LBfBNJp0mLSSWjNhh4lDmkadQDcMLWa8D2JpufQI+t1AAtOWTyjtZnsZU9tg8e3tS42aMCb84dR8dOf7n4upvFdn4I9hX5lbsvjT661AmI+x1SHXPQpI1WYiI6XuRBt0GJtE8Or4HK5hNsDvFVZZXUEFAyBYryBC2UdCo/lyQeeHhMMKEGD7GPBeNULVUc62rk6/tZZ0QKeuf1X1FRg+bDVDW4oervHc7jXuhHI1qkls0WQDnmGZ8wjV4Vmdd7ChogZxEDGWFXPeWXCRjCcp3rDhbsXvAEH/VRnTAjisnRKZGA0
*/