//
// ip/impl/network_v4.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2014 Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP
#define BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const network_v4& addr)
{
  boost::system::error_code ec;
  std::string s = addr.to_string(ec);
  if (ec)
  {
    if (os.exceptions() & std::basic_ostream<Elem, Traits>::failbit)
      boost::asio::detail::throw_error(ec);
    else
      os.setstate(std::basic_ostream<Elem, Traits>::failbit);
  }
  else
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
      os << os.widen(*i);
  return os;
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP

/* network_v4.hpp
Slm4Vxl3Z96Fr2sy+SVh6ox7WB7ht85855C8EPn1Zh2VM83usnMkxZLfTdpOXY05njTk3RdRdhqd73CWhCmzjqFuaXlSPZ3NfIdrxJ7oXb5MmJyI+6vfvdW/n+c91bKlcr0d38eXli+T5WPucoWcue/cQ6f8wpVh8rluebm/o6n/71MH81O0rUxsl5rMyYLtaZxoKjvQVPppKqs5QLBfan/TXAbPoqRta7zNfFGumWrWeT0m9jZqD+Vrimn3qs03/ErxW8pcB598yx5J25adou3dyNR+2txJe7efP7qkBNu7Y62o7Z3qmJYSbO+K01I7WEetvfO72jstHypbEKWcz41aznUNmpHXe2/qpXHXe+w+f/WAnp1JMs08zJdoU9O3O+tFbXXpikLOzlzo1Z6qfEspU/FSVk0YLe+RMtyxipKAiJmX0V5kEhv95ilnOkfJz3SIbtzM9V3tQL5+D71Z24EfYiajI9uV3sB6PW0IPNuBYyVMubMdQI+7HajZ3ng7QJiG2gH8Y2sHsrfH1g5kb29aO+CULxO/0HNXtcbC9C9h8lXabhyknK1tHUO7MeCrtRv3bXe3GxuwO9oN7oN3uzFT/JaZdqOiFXW7dfR2IxP3Oa0bbzfQwYFwjnbD/7/fbvhd/bm59+5ntAxLfhX2xBw4Cz5Ee3LQ1C9mq1KvaotrCjXmEfXLL3UpGGY99SvZuoQvAxk6B/f8+2333bg87nie4kW7FKWOZ7OTjY7B5lzfrhL2OF9EuGULl5Y61n1niVyeT5/xVA/nxWodtLQeO9uDHAnj9yVaO9QtGNc37LhK2Avah8KOCM1TEb956SG/4eqXo34vjwr5DVO/3q517axJdtSH38h148y8yGfEzhmvlM0C2sCVCP2Q69llu+7+1NTU/vyVkOJ4p+ImOfLxdgnfV+1BfQH52rDrZ8A68T9R7UF5f+BdRONwUOMQX3cVLziD7Ai09Lr+egmfZPn1+t8T+0yZid2deEWLR1t4ochlWlLXqH/cOnlvqsXzPLfRdfwNzxUaq3OFoj0HZ7megx3lMeJZ2F3m/DrHiLKBn5YNdc+BlAvjPlzde0PKhHEfpvNh+kp6LesV/Jz9/FPtLPnVa793LWYvMrseMPWSOVg1pTKmVFniKAcSSdO/Ie86Z/1lsV9qfdvySTl9p19gDwXVY+rGxyJXwQzhJHM+9Cfo307sFsL56Y2fF6xtoeahHS+da6VprOgQEL5F3w9vxLxGGtf/3KSxZkWFV3ujcoTux1z5eZhQf1y81DGvUuWOpX1rL/1Jhs7b0rP7jZ5BxGIBJsU8E1WJzKkOmU6U3tPRQ32222mR3dlZngGcfTbyUftsfqwFKi20G3uzB0PKDlvWNVZg8ndsDPkb8U5u+gLywZzbjJ+4lYt9rnnuYo6t1g3SgX2xq3/o77fkN03nox2H2cc9Ktqh94gKQ82vXKUFCG9TrnyhcmXmnK2QcMO0fAb1ZJi0U7Ywjc858+ucM65DnM11XHF/ODMQYJAPfbADlLGuUNxrq2IcVw2E6Wf6pffE/peoY1rT8H9H/LOD7SHh9VlP5yoPf1DOAKAljAv1UaKDDrdqlenXPpRwn8m4V46f/MoMPJMlxcevoAEeFB+fy9DXMAad2gdHvVJ745EcZ55fGnwOGyzxSDRjXqPEXm/6oZfE7ld/tVMShhAfqyN9AkbGwGpT+xCJbklJaUlxZhCsn8QlIclqdBwsWD5Wiv6zAv2OXmNkZnAM7GXXGNgh/HIzzRjYvqjPdqpjfqYZA/vYawxM40gb17T2rSljYgWdo5fJvJ2OMhnj+CthXGVyCfaGymQJ/qZManhnmdy2M7Yyec7OUJncRb4eyjo=
*/