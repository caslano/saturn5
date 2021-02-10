//
// ssl/detail/verify_callback.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_VERIFY_CALLBACK_HPP
#define BOOST_ASIO_SSL_DETAIL_VERIFY_CALLBACK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/ssl/verify_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

class verify_callback_base
{
public:
  virtual ~verify_callback_base()
  {
  }

  virtual bool call(bool preverified, verify_context& ctx) = 0;
};

template <typename VerifyCallback>
class verify_callback : public verify_callback_base
{
public:
  explicit verify_callback(VerifyCallback callback)
    : callback_(callback)
  {
  }

  virtual bool call(bool preverified, verify_context& ctx)
  {
    return callback_(preverified, ctx);
  }

private:
  VerifyCallback callback_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_VERIFY_CALLBACK_HPP

/* verify_callback.hpp
ABYbzHWx21dDdw3RQR1QXMuIa+d3A7qwFvOonRVJkojeeLnMzrrnGgNIyOsQXXVAqjCWbg8E2xJtA15bncuo7Rq2OpYQSxQMBQH9C/oUYFkihA5WnaJttTGwQoZUoG2IKBW4gmG6EuHo22916Ip621LnJSgsZG1iYD4/RsuzFOb8lN817S/Si31XpucsFM4LhVFqQ+LIEXzdGGmbu5DCNUmhIqmU5hNpWpiObiBuuakVQvZzya/FzWg6Wo76sKojFRmylZpjXlpn3Jr9M/oZ4ReuboYPJKhAHyCbz7Lbyf1NH65n2VMf7mYPowasch5TIe6dr6QxO9i5GpSznyJYZNxSB3Ab5pXCkAwLlIDANpHyPoxHQ4LMZouGGTMUB9rSI3jJDpKCF/dMaKsdGcnzUqjYGzrah8Roi12jQHyWb33BWeKVl9KuSRu7LPNYk0tb59V+em/ud/37oCMJoRfWRSFNJBpcs5WEVXuefClfkOxfOJ4PzURWG4Ogi8aDrbSRB1xJ8lLCxrsNIbBecejQakkem+M2T9QMQl3Q5DGFJ8JpXWyDy/2TpGxy1lrKQvdpgxA943H3gLHNdJLsU/tXXJkwjeuQkT400RQd+WM93DhJjOuiWLF+yYe0PTaipVFA0AoTpKTkNLd2vcgi
*/