//
// detail/winrt_resolver_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_RESOLVER_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WINRT_RESOLVER_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/winrt_async_manager.hpp>
#include <boost/asio/detail/winrt_resolve_op.hpp>
#include <boost/asio/detail/winrt_utils.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Protocol>
class winrt_resolver_service :
  public execution_context_service_base<winrt_resolver_service<Protocol> >
{
public:
  // The implementation type of the resolver. A cancellation token is used to
  // indicate to the asynchronous operation that the operation has been
  // cancelled.
  typedef socket_ops::shared_cancel_token_type implementation_type;

  // The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  // The query type.
  typedef boost::asio::ip::basic_resolver_query<Protocol> query_type;

  // The results type.
  typedef boost::asio::ip::basic_resolver_results<Protocol> results_type;

  // Constructor.
  winrt_resolver_service(execution_context& context)
    : execution_context_service_base<
        winrt_resolver_service<Protocol> >(context),
      scheduler_(use_service<scheduler_impl>(context)),
      async_manager_(use_service<winrt_async_manager>(context))
  {
  }

  // Destructor.
  ~winrt_resolver_service()
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
  }

  // Perform any fork-related housekeeping.
  void notify_fork(execution_context::fork_event)
  {
  }

  // Construct a new resolver implementation.
  void construct(implementation_type&)
  {
  }

  // Move-construct a new resolver implementation.
  void move_construct(implementation_type&,
      implementation_type&)
  {
  }

  // Move-assign from another resolver implementation.
  void move_assign(implementation_type&,
      winrt_resolver_service&, implementation_type&)
  {
  }

  // Destroy a resolver implementation.
  void destroy(implementation_type&)
  {
  }

  // Cancel pending asynchronous operations.
  void cancel(implementation_type&)
  {
  }

  // Resolve a query to a list of entries.
  results_type resolve(implementation_type&,
      const query_type& query, boost::system::error_code& ec)
  {
    try
    {
      using namespace Windows::Networking::Sockets;
      auto endpoint_pairs = async_manager_.sync(
          DatagramSocket::GetEndpointPairsAsync(
            winrt_utils::host_name(query.host_name()),
            winrt_utils::string(query.service_name())), ec);

      if (ec)
        return results_type();

      return results_type::create(
          endpoint_pairs, query.hints(),
          query.host_name(), query.service_name());
    }
    catch (Platform::Exception^ e)
    {
      ec = boost::system::error_code(e->HResult,
          boost::system::system_category());
      return results_type();
    }
  }

  // Asynchronously resolve a query to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type& impl, const query_type& query,
      Handler& handler, const IoExecutor& io_ex)
  {
    bool is_continuation =
      boost_asio_handler_cont_helpers::is_continuation(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef winrt_resolve_op<Protocol, Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(query, handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(),
          *p.p, "resolver", &impl, 0, "async_resolve"));
    (void)impl;

    try
    {
      using namespace Windows::Networking::Sockets;
      async_manager_.async(DatagramSocket::GetEndpointPairsAsync(
            winrt_utils::host_name(query.host_name()),
            winrt_utils::string(query.service_name())), p.p);
      p.v = p.p = 0;
    }
    catch (Platform::Exception^ e)
    {
      p.p->ec_ = boost::system::error_code(
          e->HResult, boost::system::system_category());
      scheduler_.post_immediate_completion(p.p, is_continuation);
      p.v = p.p = 0;
    }
  }

  // Resolve an endpoint to a list of entries.
  results_type resolve(implementation_type&,
      const endpoint_type&, boost::system::error_code& ec)
  {
    ec = boost::asio::error::operation_not_supported;
    return results_type();
  }

  // Asynchronously resolve an endpoint to a list of entries.
  template <typename Handler, typename IoExecutor>
  void async_resolve(implementation_type&, const endpoint_type&,
      Handler& handler, const IoExecutor& io_ex)
  {
    boost::system::error_code ec = boost::asio::error::operation_not_supported;
    const results_type results;
    boost::asio::post(io_ex, detail::bind_handler(handler, ec, results));
  }

private:
  // The scheduler implementation used for delivering completions.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

  winrt_async_manager& async_manager_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_RESOLVER_SERVICE_HPP

/* winrt_resolver_service.hpp
X2vt39EH50//W3P73vzpc/O3v82fvjab9dXOeG21lvStNadf7edaR+1/YQ21eKfzX7KO2gbUUbvgXoQ71qdl/Vc/3/s/ZgKVn/n7fyLe7QdHIWz7QDGWfMTMCaPE2xdeUUZMmDprJqZQXZhbUeF9v6/Saf2v5e/DneHacDs3Q7zvZND7julAPIeC3ityYKdpj01UtTCd5fP2svZNa75q83XFsaap+T7vYsc4bkEcoBXcg4hgTR+buBVXsK6E/fkikE/P4RihYSKflpdi2gSC+Wro5DnMeTJTaOjY5UlJ4RqYyHSX+JFu/fkKnObzzRH9NN7zFeCd03ROha/BLMM1QBip81rh1bopkTo3hv1hCvbzuHs5F9hwDUtDm54rpl3DWXwN5Ts29XWI83Nfhxzbi3Ma8qC/y5wH83C8mgzuZyqwywNzOazRpbGS8qB0VYV+vQlDGq9pRhpzDGmspDTi+EZ9kgAez8dzd0bBLRAaMn1kv5lFehrtS+Cw3fXj3TntVInIOSLPkF0Gp1cLF6HTrZLa4WSTI21iuW+s4f16A+qKq36Cfi9vvlE8YSv7vcw65px/HQKt+77qMprf91WX8dP3fR0JtO77OpbR/L4vhGms7wv7/7V9X1qZLWstx4go4cxc0Raka31fzS+z3rAxVK5ybHSSJkm7bmSHdxBdWaXM8+kr6k22F6kZsHapgVyGtWN0NvV5dRBppn0Z6v1KqLnvivuVbyOb1uqlSmfepirVtG0zru+l8n5T+H7T+uAyyeZCtQ/+qwgj+qGOonzkoeFaL7RzW4W7g4J92wea08R2W4K0Pq4F3j6uTfZ9XGEc5sEg7uNq4/HIcmGwOQSbdWmkESBtluk1sVkj4CS2XaZpdPrR7yXmh1T3lfNDWKfPdO/bawLIe19eW9kXdsTR/L6Vs31nP0/f2XzqO7t05oDbJt4f0f+Cw6c3zTu8KM+ub8uuT+2/p8/Lrm9rE5XPtnXuDecnvDf860f6P9BxxYQiuz4y+z7EEw3jdun+r3NwH5n8TfUH9UGlKHQvy99yzF4Ga4Va9FWlyD4tfmYGgyzsknR22X4er8xPuxo/7GhMM8dvAtvpxzSn85i+vmAyj5Ufzn1/o8iu4Xx1fD7YIw/t+/iO+WH3oMJtCreFiBfZ7NKNwQ/nMfcx7O/M/hTwHHA8j8WfyH10C7hP0MN9gtdyn+BecAz4OPf9Hea+vm/ZPhjnzgE7geI4PcFJ4Dju2/OAM8BN4EwR3uXfWLp9H2F/urNZfXYP7jnbb/ff3G93cE8TfXeP/ef2332756ftw3Pfh3DiGPed7cs7k768f0U/Xoe+TmUoXB7ceridcC/CHYMLzXAq/TNa1rd39u/s39m/s39n/87+nf07+3f27+zf2b+zf/+W7//55cUFP8H6/3H8/V8JEd+1R8yckV+ytFB+9Vfk/jLeP6Fg2kqygbYdTOT4gXq5v7Ckovj84sKVo4pKi5doZko3tstxG+3KfcYYzEpTpL5enYP71fi7UgdwaQS2t6XvSj6RWVHm/UZUGEHfdHN135LYfrYSQ36oobUT/i3QLAhQpiE2i5U0XdjFMuwkGXYqwsIvwz6AcYRuzOPOwDz7MPpu5F0zbrHU+/oE4QD1Wez9EK7BJl9qP39ENkHqy4jHZ3AN359WSv28m+h8CXI96sPkD5Ga/iNDvW6Pj2v6u6v2nQ9pFt+lc+V3PrkN+SC1ae3HG7yCNGWHGq8Hjfag9DzT0ecbO2xbPtYDxxJx9YnTQaf1WI+6IGOcaLiG3+M8doeYxnnIc2ZbjDloJ8ZdmPMBIzyaP75D0yot4zW5z3F5y38m2B7nqeHzWNxs+SWlJcUXk04a1uc=
*/