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
Wfiz8OM3QVkYGfldGXnELviAztxSEkzS3IU8Ug51/gSGkLKoKSAPeBC2nYS0A/s54JmGuvf5ab0y5sGfQeAEyYsCqsQmd/reB+lVYGX5E1lhk6JClmxCqsu6wqwGYU/8d6a7wNiJtgFBD0OMkEjgTcMqc89BNM4RkgCZieuQoU4XreDSoSPM6UoWp9OFTx2bDXyW3NusKIPeK1/DbntkvJrPwCp0GGUu2mFHDuFLk/FfwdRp+q8TyjdY4lzcbiVdQyZzDhrsdBqDicqxJraqZigJD2pWzhdkNfPqv7/cPD0+PP589ZsWfhyQu6B3/qe40AUqub4A8ueJrgFrcBvjBMp9CcnRPq/gxjDtykdLHZXo9EM7ne3MKY6vy2thd+s1aMdU3VVL9UKPGn1RObzFyej1RLJzbFuEBiuhq9S36USdl2SqvQdWpWWZ9MDL3jKuzH9QSwMECgAAAAgALWdKUkzoeg7eAAAAXgEAAC8ACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9yZW1vdGUtbmFtZS1hbGwuZFVUBQABtkgkYFWQMU7EMBBFe5/ia2scQYVIh2gotlrYA8zG49hS1hPZY6K9PXYAaSmteX7/zxwlzSMyX0XZJrqypWUx77ysI86FoYF/
*/