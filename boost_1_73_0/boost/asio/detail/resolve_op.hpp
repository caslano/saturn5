//
// detail/resolve_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVE_OP_HPP
#define BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class resolve_op : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  resolve_op(func_type complete_func)
    : operation(complete_func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RESOLVE_OP_HPP

/* resolve_op.hpp
RPsdk1z2NK/Y1eD5h1dEhxO7A0s5G83q7GJf4Je0AMvv7FF+fNVqT+R58KQSw3vE3KTUQ+lNZhWcRhWcRhWs9NBvL5XMxvFrQQVGpgy8aC/UhW+K1ufV2Q1LB0XSAh5fxg7g14HEmH33QF82v+34TpW0hpSomTKoLR4dvOVc5eUC+atvzZoxAV47P1dnzfgVT7NVGgpY+IYcEyLtiB7UIg7xzXl2Kb5TG+i+c1enTIu9Woia
*/