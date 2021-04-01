//
// detail/assert.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ASSERT_HPP
#define BOOST_ASIO_DETAIL_ASSERT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <boost/assert.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <cassert>
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) BOOST_ASSERT(expr)
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) assert(expr)
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#endif // BOOST_ASIO_DETAIL_ASSERT_HPP

/* assert.hpp
kuzvToJsE4/1i7/Pa1JkqafY0L8wHi+AvFhvsxHZL+DKQMft5usi/GDtE9KuUQykQJdt0flns/kaF0B0NcSUyRN38a7wE6dg5+Bw2dJx1w61vzxd+2C8P2lmyXa+FtelpZMKtyZMUXLUQ0f2huUyDh/Zj37qlV1x/d3gpbNuSAEfvSxOSs7dUt1yrjQlbYobSuEc9bbxwvk26zppTc4XHdXpwHqQaBTxl+YZmP4epkQ+kZWlxq1aLUWHjd+ndn0YxwW4xJUH6o946/LkERAIL1sx2cHZ+UGBD0b9jCCEwbhutIGhsMaWgds3d3oa61UvP7OTK/27n01IFfSGsD9gbt2xLnsRL5DjGzQ5iCEZ+NeBk3XGjdZBTmts72zSiX1jHZiaskzcOGxdXNOkfuDPgGIFHqfB/PGol1m6k2elJCYFhHOL/bglpXPfI16bPCC3DDssY0wIlAZM2UkZ/RvEata/uwRJJ5lXg+fFJvNKLe0Sms8hI7SDqqCFgj8oNS69y8k5Kk0vYBlpBXWmnJLOIvpEWpqS+jFydV6MqVBaWqjjhKA1cj6Ah8X4VA==
*/