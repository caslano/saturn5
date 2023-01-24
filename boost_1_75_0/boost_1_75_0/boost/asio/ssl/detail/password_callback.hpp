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
6dTcNF1OTioOeeLy5utyY3TzsgrZAuKREpdaOB93+Vo4m9ssIQ4wW8+z7fTSjO9sn2VBViEMTealLErNara57pQX2Zot0JO5pGQWeyf8KRS3ZVJy89iUVJbFfaf0NvZ/shbo0mOBshxdIpAWkpOXNv+O9tbuLIlTmih9DpvVdhKnNG1Fd40bnLvkjssAY8msNOdlgOb4cnLuGF9QvxRh2T64oCB1SWReTrquQBvdyqGKOyt/Vu7C1Jys9JTUgnl63Pts6Wx6GkWfos+di6SimZqDIttG3TfJy6K8gvlgpBXoaFuiPHFXlyy0tpQ00i6aZeNE/4L8grx8wN2UGRVMd2mEMmM62sRaj0vO5QNzdM2PrLRFR4EuQ4exW9jlbrkOmpLm5+VkpS1JYcnmaUphvi4tKyMrrS1aHeVJYbHVpeTp3Z+zEfNdgO0mP0cnEgBNz226BbrCwtR5OqIFMkDHuq0fIQ9AOr81Rkrj63ML9fn5eQUs0n+HstuMb/N1zTay7ygdeOvbOFsirV56hiFF2Em7M7l2yN5CXUGhfm5hWkHWXF2rkthyOyzU5WSIjdFtOZvLJOoEt20jV1eIrG9KIXYsLaZsJb8WCJPGS9dlpILISTLRLYbuzq3uiyjQ6f7MGR1xHTNS6aVJAsgEWAywDmArwH6AUwBmAKadl8a3nfDuZNvnKoRTInemX2N0UN1LdemhmXd2biUiNavg
*/