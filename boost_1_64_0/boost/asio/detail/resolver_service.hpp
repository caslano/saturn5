//
// detail/resolver_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RESOLVER_SERVICE_HPP
#define BOOST_ASIO_DETAIL_RESOLVER_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/detail/concurrency_hint.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/resolve_endpoint_op.hpp>
#include <boost/asio/detail/resolve_query_op.hpp>
#include <boost/asio/detail/resolver_service_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class resolver_service :
  public execution_context_service_base<resolver_service<Protocol> >,
  public resolver_service_base
{
public:
  // The implementation type of the resolver. A cancellation token is used to
  // indicate to the background thread that the operation has been cancelled.
  typedef socket_ops::shared_cancel_token_type implementation_type;

  // The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  // The query type.
  typedef boost::asio::ip::basic_resolver_query<Protocol> query_type;

  // The results type.
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

  // Constructor.
  resolver_service(execution_context& context)
    : execution_context_service_base<resolver_service<Protocol> >(context),
      resolver_service_base(context)
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
    this->base_shutdown();
  }

  // Perform any fork-related housekeeping.
  void notify_fork(execution_context::fork_event fork_ev)
  {
    this->base_notify_fork(fork_ev);
  }

  // Resolve a query to a list of entries.
  results_type resolve(implementation_type&, const query_type& query,
      boost::system::error_code& ec)
  {
    boost::asio::detail::addrinfo_type* address_info = 0;

    socket_ops::getaddrinfo(query.host_name().c_str(),
        query.service_name().c_str(), query.hints(), &address_info, ec);
    auto_addrinfo auto_address_info(address_info);

    return ec ? results_type() : results_type::create(
        address_info, query.host_name(), query.service_name());
  }

  // Asynchronously resolve a query to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type& impl, const query_type& query,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef resolve_query_op<Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl, query, scheduler_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "resolver", &impl, 0, "async_resolve"));

    start_resolve_op(p.p);
    p.v = p.p = 0;
  }

  // Resolve an endpoint to a list of entries.
  results_type resolve(implementation_type&,
      const endpoint_type& endpoint, boost::system::error_code& ec)
  {
    char host_name[NI_MAXHOST];
    char service_name[NI_MAXSERV];
    socket_ops::sync_getnameinfo(endpoint.data(), endpoint.size(),
        host_name, NI_MAXHOST, service_name, NI_MAXSERV,
        endpoint.protocol().type(), ec);

    return ec ? results_type() : results_type::create(
        endpoint, host_name, service_name);
  }

  // Asynchronously resolve an endpoint to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type& impl, const endpoint_type& endpoint,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef resolve_endpoint_op<Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(impl, endpoint, scheduler_, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "resolver", &impl, 0, "async_resolve"));

    start_resolve_op(p.p);
    p.v = p.p = 0;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_RESOLVER_SERVICE_HPP

/* resolver_service.hpp
Q8gKDPtue+EX7UidZrs/MEA85DV+L8Wa0AvIb8d5eh1jxbSMsyuok4p6Bj9TyO7ZQfax9joGbnffNj+M7x8mSQu/fEIoH0/nHcKcB53DYYsr8MKhlk7aPeWXqlcPljNnvcKpqK2JgwM9YxVzask6uoS/M66Ejb47lzHcT7AzuG35bfNkW55Yv1XLT5bzuczj9Otj8EPEQ74NifL6hK4XuvML5svyquSBykbbBPD7Uc6JNqGA7/eGetDTpoWaifaXyy0aVuYdwF9v9ne0u8aX718N9SS7+/RQc85jYTdfFYvX1kd4PAvlMI+5b4T60/9Z9D6hDBGmuo8DTT6oWOV/d5Tkij0s0f7QjxPn152z2X8s9B3Vi7HUxn9HdXrmYPF+JtW1OSI52TUGJ3Vvk0Nm4T7U1ndrSaKTSDQuuXnbLi0OMjZjH1NCnXyXn32AWqXJ/vf7tSxbFsomXWSfc0zCsSbwgu0X6uRQTnc+h5urhHsWyV5zOrNuOIjamamDPd2qrFHdStqXDv1b3bMvXZR70DEnv50qsNTzUrdf5Hou6hP2WYCdEXUF/eVGTieNr6B//M18fRzqB+P+7Vyd32OBuL/M70+xDys+uB6Bvesqul5BnJ3M3yTfHdYeLO8Oyvwj5teF8C7B/zT7O+Pjk/3+9298P4n9L6JynZfP/SfhQodp6XAE/PodYjxMaRlPskz6zhK/v3I4PUJdWUZENz+Zu4KYyeb74j9/YD70AeP5eHfpp5QH6mI75kzDvefncLwbarsr/byUh29Lmx+zHUZ7spL9XIl7z09/wwYmxxsGMv9u2oMgHd+onp/BjmejGuXuxUtuBLkj0p1DsjU5iq0p3WJrmoj6nMf1WdS7nnm6fajGuL/AuH/NuJ+U7+mB0L1x33a8bs94fJiIbQbsSVNgz9iXr/UB0dgqbbzVr78HmJeGvgD+yNqY6Bv7e8ZbCrsOxpH6U6Y83edQ+kHTjiHfx53DYcdg3UNcz3L3qilQ0lEfieB99N4Pwljgp2cR86cjPZ7/rv5Y8la+D0G/P2j/rdmjTuR2jJ6HMl5SoOvylQW6Lh8vkGWo6lmvjxCB12J/imVu+++2PUpaV0bi3G3L9Fr7bvjp6b9nz/B9njlnQrY/jA/w8o9+SA/al98zvtDUi+UYMeNTUf5Cfx3FfeOh75PU+BwEvX4XH4H5vs3EPMOPKQ5XufVioZpXIpvseeRxh/g6YCXfPxuS+xDpbc98389Avi+m+wq+3yf9GG1cge+nn99+Lef7N5QxjDo2SGIMAvxJ/hjGOr7fzc8QfEpVrC5Swfkk9J+bCsU4xmLSjuXcAoRF/7BPUrB8UT82Me++kNR/5XCO/44zp5tf5l34mat8neZkvr/NGUaxuIKsqEpYXkb69ekAh3UG7j2/d7G+so/eg/2jPH0ljfWVPgn0FY/fa7THP7FR/WY4yVq5MVJ0d4wTQp/718Ypajj+S0n7yTlofXf1/h8Ldb2/wDLXttTfL0rWQ+hEkMu6hnFb2GtEfcKeU5ChzqCNOrZQH5fYifsb0EZ9g/u1hr2heLxIyFEteD9rpwddtxHn+SL9vatT2if0LTUr5bsHPukqeI+Si9k21vzZUP+QeLdodm8p2+oCbXoPjEX8wGEc1uKUUJrTLinf2ZC0EO+pF/4wDr+E7r/h+3XN3w515/BL/PDP43raT+gnDSv4EbLfuJzjNbG5G4chnV2knhhST2rP+KeM701RbNOo5x0Z/4LxNPYfFv7RFvRi/E3Gpe4i7c/SDlzjv6ufHc15jXsvHXQWkx8GT9+vFV8Scmy0H/M6KmFKO8jfOMzNuPfCLOUwRd4gzIaqhpiitw5iXltlHmF1+Uo=
*/