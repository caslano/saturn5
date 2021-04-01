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
TBnQ+xB++Dh7B8grghvlyY72IFyUKvX3z8P2Smi2ekJ2Qx98QXYVsU9LdgrLYZwo5Kgaj8Fo0Rw166B9kQBYXV5NcFOt32NLwuUMJ0gTx3sjXnezf8kTr3TmsVzKFvDJDrf1d1xEcHd0IbFogj4SvmhzmTUYaoRguly/XTTi/3QLVAFopx7+d/pJF+c2+A7nc0tXUg/73V9D/iReWhdKLh9SG/oX4unDhh2MgtkXnacMQFgD+RJ+1e8wr6GDhb8nCxCBKQIxQrV21KD1TaYXS3QdIvEMn8huIhdaqrUjaPs+MZAku+G01hgiwDg1jrpY8Q4tCLLJVol+GdtNtq182UHg7qN2Qo+OLWQOtuyleXl7jHTUQuVtEqHLNObSYAzC0RLE+wT4VxV7rurbmeQdq2wIbgCj6nc8a0KHAWzlulNyJq+9P0+J0q7ibkfiDrgO5Z7Q8+BsoSteC9K2K6Wbm6lnCnQ0nH7wxYENLCBq099xy+sARsiJ26F8qfapRGh4FJgTUbY6R2E7K00aKdA/H1t41dYCXx+P/bkFUU8PeLIvn0p+0ArVn9nkOw==
*/