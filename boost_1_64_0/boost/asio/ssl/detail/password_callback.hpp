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
jjolz4z2KRJe4u5T5F53z3qq6VMkfK3Wnwh9N586NzxzfMgiNUojqR/G+EuYWVslPdL9OPofob1V6s0n1IPFxzWu/5kE7TzcvVnx1ZE/Fh6NOkI+TB1xrts2/M4xuLv/d0zhEHe90b03MjkTWGeGNPwdozRB7+iEf1nfMWFdZvtUHjm4lupObMv7Slge1XPD8pg6ZMyU4TPDqiwlL32hIb9zo+/nykNMZq6i3nNGuS79e8RH+ogv0s41fTt6eNP3L2jX+qWvckHlzIuqysrMOrcnjcqXI2WWIeE2g30Yy5SZoTHv3I3IB8/UfETXtjLknnmOS/5re3rzV0D+tvrlj8+dhWWB8leeHDO2sD5UGqlrrUENj+5laUS+TPk49CPyDO7xjIh+RM1T317ePGUQyW6TJ9EXec64EePtKiXpbZXvzc/uI6hPxOdbn9J7e9N2LW3joDdtzuokaUz1SSN8pj61zvKvTwePoD7xTE994jmB9Wm/T/6yiSPjbG/+tDoFyR+eeusT4Ydfn1rlx1+fRvXx5unWXN6l3HmaX3YZ1amiIrr/K470OJ+Te7z3Oet5TpH7OaZatJK1dq/coDd14v/sXQt4VMUVvgkBAgmwCSGEEEMSAgQI74gISsNLIy8XEhALmgQSSEpI1jwAEWuKaGlFm1oftAVNFW1q0caKFhVrFGqtYouWKvpRGx9tbYs1RVTa0sd/z/47e+/eezebh33u/b6z/86dc2bmzJyZ+5i5Zw7Z2wR4Om8TyNNiE4esNqH8VZ600WsX9PIE6FVXU+akE3hpC3yWwX1KbbXx2TpAnxWd1MdnC8gD55BHQBu9O846x/91fe2sV5faGu94WVxSUri2otjxHST5RzpfuxVPunpueFjCd2j5+DWujyutKFHP/g8Jz83aQj77u1U6qYZ+JEVTa6u+K/F3agV8TihXMkOD3ueBR93nuf3zYjikZ0v6S8H7uPBdC197g8CDc7ofV/0cwqZ1QRg7loWwzqPz6zhYVziXp/q71IXTfYpqd/hklWMF5wsvAW0Db/0cU7uXV0L18hLrHCHbnfzp6v73WxKebOCvLTb6v75D4qfRJnzyieb74uDv0ebbzvlZ1h1Kvqax/OgEe53bzDpXVFWtr8OQVFxe4ax3W4DecXOD691rrlnvtn+B3qeBGozx3gz9u+Z7Hv7GM6+8cNWZa+IPJIyN/mSRk4/Y7vN1av+9ttP37x3/Dt3+e21n37S/lu/T50W8cP0V815cEfNA9Z3/WPbGHqfv5Z2+r++4D2D7798dvqPvhB+AjvoYtvfp6+RT1snHcMe/r7f3Mdx9+7k5+QH4mHsC4JB5hRbgMNBHhv8V8eq/rHs/DiwGuQz/49V/Wfcu/8+CnjL8Xzpa/Zfn/mi0QTn+L+P/KvrNLdL4vQjXkOtxfYAFLGct/QnUAeOBG+k3dxP95m4GVgG3ADcBrwFuZfg6hk/JWOf7XgOykg8IuBCk0W/tQOBE4Gj6kb0AmAOcBTwXWAycCiynf9kK4DSm3wRqZfofMv144G6QRn+zKcALgcOAs+gPYQ7wIuBFwOX0K3s5w6sY9gDzgNcCLwHeAJwPvJl+cxvIdy/95d4HdAN/BFwCPEa/vyekXlV9YE09692mPi6jH9rL6cdhJXAS/QLPBRYCLwEWsT6KgVcB1zD946AWpv9mhKQv91VHmP4mXGjSgZuBw4FbgTOBnwfmA68D7gTWA+8AbgM2A68HHgZuB74DvAF4Engj8CPgF4F9I2DnwIHALwFTgF8GTgLeBJwO3AmcA9TTXQa8FXgd8E7gLcBdwAbg14F3A28BngB+BajrV6Zx7SzwWtZfX+Aq6vcLFD0J+CowDfg=
*/