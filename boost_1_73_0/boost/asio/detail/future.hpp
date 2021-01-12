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
3rJHffSgHffNTe8zYfBNS9FejFcxuj31OSgmw1DxVOzPYno6/3DWsyWQdG64DFc7f1t6kQbEMO97lQ5NuYMwcv42l4H1U41lANlxOtj3zBv1u7khK7qh0oGA22SvXKygTPs64YoyrA9brTj5PoGd9u/IECYt3/YpUVj0ijKOpfYHOccyWaYX7jC1ClweFud32SsyYGLlN5RnrNLHfNFiUWyo67SKTI5XMC1d+V1wu418aHCH
*/