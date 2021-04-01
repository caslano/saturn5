//
// ssl/detail/password_callback.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_PASSWORD_CALLBACK_HPP
#define BOOST_ASIO_SSL_DETAIL_PASSWORD_CALLBACK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <cstddef>
#include <string>
#include <boost/asio/ssl/context_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

class password_callback_base
{
public:
  virtual ~password_callback_base()
  {
  }

  virtual std::string call(std::size_t size,
      context_base::password_purpose purpose) = 0;
};

template <typename PasswordCallback>
class password_callback : public password_callback_base
{
public:
  explicit password_callback(PasswordCallback callback)
    : callback_(callback)
  {
  }

  virtual std::string call(std::size_t size,
      context_base::password_purpose purpose)
  {
    return callback_(size, purpose);
  }

private:
  PasswordCallback callback_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_PASSWORD_CALLBACK_HPP

/* password_callback.hpp
9M6mH6aR6EC/K1I++yeiZQbi5D88/56oe4twWdJuq/1CsRtENCkL2ai2tbi/Wpx3pMm2JBFDBQrikjgxCuh3lEJyp7z6OZsvJHqzq3g3AQzVRi8/vz8Juy2xS5Y4ht3GvTU7C5718djlTPNf82HqwDDFOWQRGldVK4EZG2GTAnctxpRrBb+HCQGnqjHHu+uvMOZ65IiLk1yxpW5DNTT1ZEUK144ZS+skY8Me5IukD5NMjrvfLY3arHxQfvhD4rAYYLMU/4rlE04Slfctlyielbo++GcisTpiTlkJHLeB8XQk7of7BSMGK0tpZEYdX3PLaVNFM7JVNjQIlKCcSbl0796lfUM0beIj2iwLv96xQsxlcdqfIAyv+oZcMtISuMbkBTt5BlAyI4Bxm8giav+r7B0gbYk7SmwWQnSTkSSJz7sAIn12wvrp3kcyUP+Xho0UgOdzBMQJkYRoQCPMgdJse+xb9BDkjipL7u2/8JAjmHArd8iTk9ocopMhg9bjAnT78vuO1obzH6xTqmicrTS1B4nGTlc2K4FIABghLWZAo3oSdfMwP0w8vcXkLA==
*/