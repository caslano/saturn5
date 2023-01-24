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
l+wDNSxVb9ic14wNCx2LdiKdx3RpHfnaoDnhZafDfZ3IF98Ynchfj0U5kduTdSey/ViUE1Gr3RKp9nd7B6v2TzP6V3vlKWO1GdHVdibp1ab2qbYtLWpLKbu2ZVSiujZqxYDb25ToS/7CgsMpj/42FFk4xbHVi9rKKYe60O/Epz2RpVMxxuWNLeyOvrwxahnj0nD0IUfGe7MN9/7DhhSVYKHpR/S9eha2G5oy4BqwC40NMawBG641gy0B21pphy4z4VbjzLeDJnA1dU551OIutkl6VfcKAU+mXaYumrLLJaMZumoHaVjBW3AmwFxtsoTYukVtKDbfX9Auf/UpdHJBu3gXb948EncAd6XR7lZD2JHpjYpD8j1IOQrE6InZ4qdpVXjIc5wEcfwNa85Igabo8n5lKC+FdhQfTWmXXW62a0UmRRW59VN84uylZvejkuYcVNoHo9IxYHlXyaW4o8tw8KdPVS1FM2Gbz06bJQo/742kNuqjScZHJyOh2sOx4X4P9ynXoT06o/+jseXB4HAEKMLRJ+1Ck0kbsdELW6HRue3iRt4sDMXndg+n6btKgUT7I+KJmaUlYEPX2CDUfZLSk6Hyva2o/Beh25ucHlbGQUlcTW2hU/6JRU0HYmkOkj2fzlIUPlE5VRASbwRONaw4y3HuSB1Lr1Lksa26kcl8mQ2x4EoPnJWwtRuVY32K3PlJxP6pz/zKREc2ObCB
*/