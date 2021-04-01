//
// detail/handler_invoke_helpers.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP
#define BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/handler_invoke_hook.hpp>

#include <boost/asio/detail/push_options.hpp>

// Calls to asio_handler_invoke must be made from a namespace that does not
// contain overloads of this function. The boost_asio_handler_invoke_helpers
// namespace is defined here for that purpose.
namespace boost_asio_handler_invoke_helpers {

template <typename Function, typename Context>
inline void invoke(Function& function, Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  Function tmp(function);
  tmp();
#else
  using boost::asio::asio_handler_invoke;
  asio_handler_invoke(function, boost::asio::detail::addressof(context));
#endif
}

template <typename Function, typename Context>
inline void invoke(const Function& function, Context& context)
{
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
  Function tmp(function);
  tmp();
#else
  using boost::asio::asio_handler_invoke;
  asio_handler_invoke(function, boost::asio::detail::addressof(context));
#endif
}

} // namespace boost_asio_handler_invoke_helpers

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_INVOKE_HELPERS_HPP

/* handler_invoke_helpers.hpp
flpqz+Slcg3X9n4+lu9yYChQLz7qtrmzpr7+VARGSClrlFjGnjgX+DxzX5qMcK8olhmM+xN+Sy490p68+W2MoTBiGKSirvkZJ/EmBttxOQrKoYIOsCB+/UMmPl97by+45sBVEPM3W+g3QxS+hEQwQX4NkMIMbwnHbRm9Hxt+NueUK2Bxxwfb0b1nxLkDDbC8UhCl9KZXZbjaquV0jXQ3zaCCLIUSX/trTFeYVAbKOT/SWjrP6bVU74vtOIVeVpXYc7JbzysdKuWgMUvT0pcmA0N3DdkYLlYl6a8+5GQzV/U4ARtTAAnbENq2pqWRXBZVNkkHw92OqgIDS1zGbfp6TnU+TlDrTRXbyrjpPVppBneJFLhYnJHUbSdqhzpg2U54Zfdx8r5P9yrLsMf0JMHbZQAb5fU6b9shc8uxZSoS3syQsU2AwLMo8JzC8bTic9nf+Bt+e2kUxvU+OT9p3iVfiQ1My1kK4FIEXNo5W93tcpn+61lZeboQQAAvXRunyUvOLT78H2v+edH4x/CW88UxUODbO9gtLNolC75j5gTRk9X1xLaOrR6Uoil0iA==
*/