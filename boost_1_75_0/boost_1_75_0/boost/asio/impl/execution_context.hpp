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
ghryeI16k/XFcXdfAdsJ2xoRJYTt34CZ7fbu38CL1Qf5rueI/V97OYpVAY371zpRXwLHySiyFJ0CKXE6/zYtKi41U//b5MG5ZNyDVELjBwOi4DmnEpTAiNvEvuW8KI7Bixe3ZFHwwlPic9k4rPS6TnJzZpS5Mprl3++ac09N/iU7MvrABMQ7Ov/anlHw/NMsSoAi7v36seYS8XnmUxjJmgw1QHHFrsda5d/gGRWKgHMJ9G+33wuQeg+QDRRxG9wHFvDhHmzgvpWKks/7t+kwtp3/vwH7mhMlTutfNk8RPUUMZfg3K9JcKkv2xm+9ukdCHsXH//INgUZTXfVimXm0ojXrGDD7cTHKVypKO6ZVPGQdexVhKFEarne0Zh9fChZKl3Cv1Oit+U67VY7kRPPiEa7eUTQqZVp7blndYSKOFMQ7ypiuxvcdr1YVpTwOIS2mhRV1qXdSq+E6JCs17wFPpokqi+2pJwgK+rDyrvFUV/PDniNYZ8aTtTsA137fvSsXNHCv/5V1h3xZhPQ5zGyMPAh8Nvy84774BS1+gLGmxzBD3aJT/Y3BOrh5oQS36R/CuCKoL1CAT2Zcza7tlbS3fscboJnjWt/2bbfzEMw5MmuyJmG+dc/HWmD0CVVmGM3z19WRuUSC9/zNCMX7nWaz/hppma577rzCzNLVGKMcJnm/Xcdcbd0E1IjmSv/GbrS6+93rQNpf5ldkuA8H
*/