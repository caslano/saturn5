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
C1+nCkO43al4gDHGLyGigPN+h4YnZObcbfTlPG7b5zgJrlaYXiTP20cQCsZZSyFpUwq43bGujbQPRaJrKX1iwPW5y4G3xZBDmFokD2UvCRMiD9vZw0I8t3s51i7W26B2QwR21FfQKn8LUuErlzG6AmMAylXcViS/HsCtYBoh6BNPh4VSV/bSiqy6Ddic69df5hrjz3kCS15/Eei9VI6hiHjcAnEQ53kEk1sWC0HsBtFQ8DvEV8eUwSvwBre7DnyNnOaf3+Qr6MBXc3swSNtLQVoIg7RLpeL2DRAnrT0/a5+QhFHasPSDWcUyi9OOReK0EMVp92Gc1opnjvbidm+gRCa0O11Lk0KM7cFLwFliRJaOEdlKFpGNUCOyiWvtUPi+9TZlZPpBKC9bjcsyWVx2mRy3f6C47FwMuRKwgSwyS9YjM3B8PWDBc3vgphag4cNjT7UkdZ36RIEAAd1dDIgmzpcCO3a6ik6ckAoOqSHb8h8Ssw0dPGY70fNDY7bGnkFjtj8bbpUHd0pd4eiK5B2S8dg63NIJgUN/QZtP6JFX7kO4tQ3zaim3LbyGZ9m1U34xFFJnaICE9PQB6pgfLywh5abT93rkB/E0bs3T3BH1tvbCAAPOCIWWYIR4NIDQlH3raezu9dfR/p9SICDbvbnQU+3egiHiRruJL0JcV4WjXRZanwjsufMuFYzm0yvEyl6TcPGp3B4cJeUnKVOg
*/