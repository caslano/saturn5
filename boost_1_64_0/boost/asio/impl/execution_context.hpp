//
// impl/execution_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXECUTION_CONTEXT_HPP
#define BOOST_ASIO_IMPL_EXECUTION_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>
#include <boost/asio/detail/service_registry.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(GENERATING_DOCUMENTATION)

template <typename Service>
inline Service& use_service(execution_context& e)
{
  // Check that Service meets the necessary type requirements.
  (void)static_cast<execution_context::service*>(static_cast<Service*>(0));

  return e.service_registry_->template use_service<Service>();
}

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Service, typename... Args>
Service& make_service(execution_context& e, BOOST_ASIO_MOVE_ARG(Args)... args)
{
  detail::scoped_ptr<Service> svc(
      new Service(e, BOOST_ASIO_MOVE_CAST(Args)(args)...));
  e.service_registry_->template add_service<Service>(svc.get());
  Service& result = *svc;
  svc.release();
  return result;
}

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Service>
Service& make_service(execution_context& e)
{
  detail::scoped_ptr<Service> svc(new Service(e));
  e.service_registry_->template add_service<Service>(svc.get());
  Service& result = *svc;
  svc.release();
  return result;
}

#define BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF(n) \
  template <typename Service, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  Service& make_service(execution_context& e, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    detail::scoped_ptr<Service> svc( \
        new Service(e, BOOST_ASIO_VARIADIC_MOVE_ARGS(n))); \
    e.service_registry_->template add_service<Service>(svc.get()); \
    Service& result = *svc; \
    svc.release(); \
    return result; \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF)
#undef BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Service>
inline void add_service(execution_context& e, Service* svc)
{
  // Check that Service meets the necessary type requirements.
  (void)static_cast<execution_context::service*>(static_cast<Service*>(0));

  e.service_registry_->template add_service<Service>(svc);
}

template <typename Service>
inline bool has_service(execution_context& e)
{
  // Check that Service meets the necessary type requirements.
  (void)static_cast<execution_context::service*>(static_cast<Service*>(0));

  return e.service_registry_->template has_service<Service>();
}

#endif // !defined(GENERATING_DOCUMENTATION)

inline execution_context& execution_context::service::context()
{
  return owner_;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_EXECUTION_CONTEXT_HPP

/* execution_context.hpp
h9mmUdVIz1At2erW66Z9/jQPgElzGhh77W9UHvrCynApsaAVZtPAoD1dYVeuMWtMvtLpRA0QtZxrBUICOWFAsGXEArucAMfwEGLOfA7CM/XXp9q9I+KL5eQV/HpgPXloStOGeuM03qUbRp2oViCrVezg4coaQ0kLIfbxRtgH0V0QcxLNpRmQ5qJLJsk0zyc5+VUlauCwWmZkwmYBN2NWNGcjUa/TEjxsFT54suofT/UM4f8Jx2g2OfEhkJvNdtArwxCdb6q6OW6unloQrB2sDZfd6SFjY1D0+n47wfjss42wzq2n03VQeNFu093TZcIEj4WRgM6pTYrUPTiJcqclUJQIls0Pckvx3JRw4VjfrraKZf6hNrd63Nli1hpP8Myi4eFdNRjLlHR5nopZASgNoCyo5blGm7oTCkgGAaMyzutU3Yt8oIAwjQON9BxanWhrctZC78v9nFOpLmlV7aYssgFt+EMztySOrU56q1+BYtup2yWg3xS6XonZnUDy3bK9PpPkhV2cUDp6GQtpOkqYn1JvII/yr6Uc/go8X6Jky3HWEDw9u1rDOAkkZg==
*/