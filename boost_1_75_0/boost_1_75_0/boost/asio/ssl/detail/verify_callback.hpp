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
U0BA83aQVyAULEvSt5GajUTmXRG4G6tbkJqPy2dU80ON5OhSC5u8cbsS5Dx3XrO6NaA8BuOyFsOsd6nn8MUMY8RwbO6MD+GSMxf2Sds+5Ozl1Gfm5+XlUHmZ1lRih+dLtLdt8qUEMXtE3eQSEpqakzM3NW1+IbPeNSXBN9U5DwHbvYpH9Wy+niXXRWJB6ebOAzp3SjUYiJW0Z/9MGpaYqcsVM47RQZeZC1L5pOvoCfSTZ7OSUwI6NnENPSC1r4zQEgJeIAuX6MgJ6aJdDVMK/XQCrq4TLZw6T8fswfFScGg0XsMH26PhUWj/koyiolHmmM8UMez/Ye/N43O4/v7hyR5JkBIEQRDEfmbfZ2IPglQigiAIQoOIWEul9iUltlpL7EEQal9TS2utWEqUEqoVe2y11PK8Z65Y+m2/9/39vZ7nfp77jyd9VXLNNdfMnHM+n/dyzmfmSmjXfygIn/rUBaGRaA8Z1cr+2zG8uz6KR2srRUXa77bt6Xg/yn4VgfiiqAj7bxtn/hLTHezt9tWhrRTV2n4NKQd5kEx1tF+175aAdjX+MBoRyei8ZoO7JXVDWvak7n9Abvva17kVzogXRuEmtw8z5MkWhFDfvttiXxBFtX/Hu1aPUd3szGjTv0dPx42ZPa0/qQuOfu2GzyVap2lPhb/71Ectajj8nWKt6Bres+dnFvnGhffBUc8XZpaDLz3tzBzQf9CAhJ4O
*/