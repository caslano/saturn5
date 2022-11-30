//
// impl/connect.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_CONNECT_HPP
#define BOOST_ASIO_IMPL_CONNECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <algorithm>
#include <boost/asio/associator.hpp>
#include <boost/asio/detail/base_from_cancellation_state.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_tracking.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/post.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  struct default_connect_condition
  {
    template <typename Endpoint>
    bool operator()(const boost::system::error_code&, const Endpoint&)
    {
      return true;
    }
  };

  template <typename Protocol, typename Iterator>
  inline typename Protocol::endpoint deref_connect_result(
      Iterator iter, boost::system::error_code& ec)
  {
    return ec ? typename Protocol::endpoint() : *iter;
  }

  template <typename T, typename Iterator>
  struct legacy_connect_condition_helper : T
  {
    typedef char (*fallback_func_type)(...);
    operator fallback_func_type() const;
  };

  template <typename R, typename Arg1, typename Arg2, typename Iterator>
  struct legacy_connect_condition_helper<R (*)(Arg1, Arg2), Iterator>
  {
    R operator()(Arg1, Arg2) const;
    char operator()(...) const;
  };

  template <typename T, typename Iterator>
  struct is_legacy_connect_condition
  {
    static char asio_connect_condition_check(char);
    static char (&asio_connect_condition_check(Iterator))[2];

    static const bool value =
      sizeof(asio_connect_condition_check(
        (declval<legacy_connect_condition_helper<T, Iterator> >())(
          declval<const boost::system::error_code>(),
          declval<const Iterator>()))) != 1;
  };

  template <typename ConnectCondition, typename Iterator>
  inline Iterator call_connect_condition(ConnectCondition& connect_condition,
      const boost::system::error_code& ec, Iterator next, Iterator end,
      typename enable_if<is_legacy_connect_condition<
        ConnectCondition, Iterator>::value>::type* = 0)
  {
    if (next != end)
      return connect_condition(ec, next);
    return end;
  }

  template <typename ConnectCondition, typename Iterator>
  inline Iterator call_connect_condition(ConnectCondition& connect_condition,
      const boost::system::error_code& ec, Iterator next, Iterator end,
      typename enable_if<!is_legacy_connect_condition<
        ConnectCondition, Iterator>::value>::type* = 0)
  {
    for (;next != end; ++next)
      if (connect_condition(ec, *next))
        return next;
    return end;
  }
}

template <typename Protocol, typename Executor, typename EndpointSequence>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints,
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type)
{
  boost::system::error_code ec;
  typename Protocol::endpoint result = connect(s, endpoints, ec);
  boost::asio::detail::throw_error(ec, "connect");
  return result;
}

template <typename Protocol, typename Executor, typename EndpointSequence>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, boost::system::error_code& ec,
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type)
{
  return detail::deref_connect_result<Protocol>(
      connect(s, endpoints.begin(), endpoints.end(),
        detail::default_connect_condition(), ec), ec);
}

#if !defined(BOOST_ASIO_NO_DEPRECATED)
template <typename Protocol, typename Executor, typename Iterator>
Iterator connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type)
{
  boost::system::error_code ec;
  Iterator result = connect(s, begin, ec);
  boost::asio::detail::throw_error(ec, "connect");
  return result;
}

template <typename Protocol, typename Executor, typename Iterator>
inline Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, boost::system::error_code& ec,
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type)
{
  return connect(s, begin, Iterator(), detail::default_connect_condition(), ec);
}
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Protocol, typename Executor, typename Iterator>
Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, Iterator end)
{
  boost::system::error_code ec;
  Iterator result = connect(s, begin, end, ec);
  boost::asio::detail::throw_error(ec, "connect");
  return result;
}

template <typename Protocol, typename Executor, typename Iterator>
inline Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, Iterator end, boost::system::error_code& ec)
{
  return connect(s, begin, end, detail::default_connect_condition(), ec);
}

template <typename Protocol, typename Executor,
    typename EndpointSequence, typename ConnectCondition>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, ConnectCondition connect_condition,
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type)
{
  boost::system::error_code ec;
  typename Protocol::endpoint result = connect(
      s, endpoints, connect_condition, ec);
  boost::asio::detail::throw_error(ec, "connect");
  return result;
}

template <typename Protocol, typename Executor,
    typename EndpointSequence, typename ConnectCondition>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, ConnectCondition connect_condition,
    boost::system::error_code& ec,
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type)
{
  return detail::deref_connect_result<Protocol>(
      connect(s, endpoints.begin(), endpoints.end(),
        connect_condition, ec), ec);
}

#if !defined(BOOST_ASIO_NO_DEPRECATED)
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, ConnectCondition connect_condition,
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type)
{
  boost::system::error_code ec;
  Iterator result = connect(s, begin, connect_condition, ec);
  boost::asio::detail::throw_error(ec, "connect");
  return result;
}

template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition>
inline Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, ConnectCondition connect_condition,
    boost::system::error_code& ec,
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type)
{
  return connect(s, begin, Iterator(), connect_condition, ec);
}
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition)
{
  boost::system::error_code ec;
  Iterator result = connect(s, begin, end, connect_condition, ec);
  boost::asio::detail::throw_error(ec, "connect");
  return result;
}

template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition,
    boost::system::error_code& ec)
{
  ec = boost::system::error_code();

  for (Iterator iter = begin; iter != end; ++iter)
  {
    iter = (detail::call_connect_condition(connect_condition, ec, iter, end));
    if (iter != end)
    {
      s.close(ec);
      s.connect(*iter, ec);
      if (!ec)
        return iter;
    }
    else
      break;
  }

  if (!ec)
    ec = boost::asio::error::not_found;

  return end;
}

namespace detail
{
  // Enable the empty base class optimisation for the connect condition.
  template <typename ConnectCondition>
  class base_from_connect_condition
  {
  protected:
    explicit base_from_connect_condition(
        const ConnectCondition& connect_condition)
      : connect_condition_(connect_condition)
    {
    }

    template <typename Iterator>
    void check_condition(const boost::system::error_code& ec,
        Iterator& iter, Iterator& end)
    {
      iter = detail::call_connect_condition(connect_condition_, ec, iter, end);
    }

  private:
    ConnectCondition connect_condition_;
  };

  // The default_connect_condition implementation is essentially a no-op. This
  // template specialisation lets us eliminate all costs associated with it.
  template <>
  class base_from_connect_condition<default_connect_condition>
  {
  protected:
    explicit base_from_connect_condition(const default_connect_condition&)
    {
    }

    template <typename Iterator>
    void check_condition(const boost::system::error_code&, Iterator&, Iterator&)
    {
    }
  };

  template <typename Protocol, typename Executor, typename EndpointSequence,
      typename ConnectCondition, typename RangeConnectHandler>
  class range_connect_op
    : public base_from_cancellation_state<RangeConnectHandler>,
      base_from_connect_condition<ConnectCondition>
  {
  public:
    range_connect_op(basic_socket<Protocol, Executor>& sock,
        const EndpointSequence& endpoints,
        const ConnectCondition& connect_condition,
        RangeConnectHandler& handler)
      : base_from_cancellation_state<RangeConnectHandler>(
          handler, enable_partial_cancellation()),
        base_from_connect_condition<ConnectCondition>(connect_condition),
        socket_(sock),
        endpoints_(endpoints),
        index_(0),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(RangeConnectHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    range_connect_op(const range_connect_op& other)
      : base_from_cancellation_state<RangeConnectHandler>(other),
        base_from_connect_condition<ConnectCondition>(other),
        socket_(other.socket_),
        endpoints_(other.endpoints_),
        index_(other.index_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    range_connect_op(range_connect_op&& other)
      : base_from_cancellation_state<RangeConnectHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            RangeConnectHandler>)(other)),
        base_from_connect_condition<ConnectCondition>(other),
        socket_(other.socket_),
        endpoints_(other.endpoints_),
        index_(other.index_),
        start_(other.start_),
        handler_(BOOST_ASIO_MOVE_CAST(RangeConnectHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(boost::system::error_code ec, int start = 0)
    {
      this->process(ec, start,
          const_cast<const EndpointSequence&>(endpoints_).begin(),
          const_cast<const EndpointSequence&>(endpoints_).end());
    }

  //private:
    template <typename Iterator>
    void process(boost::system::error_code ec,
        int start, Iterator begin, Iterator end)
    {
      Iterator iter = begin;
      std::advance(iter, index_);

      switch (start_ = start)
      {
        case 1:
        for (;;)
        {
          this->check_condition(ec, iter, end);
          index_ = std::distance(begin, iter);

          if (iter != end)
          {
            socket_.close(ec);
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_connect"));
            socket_.async_connect(*iter,
                BOOST_ASIO_MOVE_CAST(range_connect_op)(*this));
            return;
          }

          if (start)
          {
            ec = boost::asio::error::not_found;
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_connect"));
            boost::asio::post(socket_.get_executor(),
                detail::bind_handler(
                  BOOST_ASIO_MOVE_CAST(range_connect_op)(*this), ec));
            return;
          }

          /* fall-through */ default:

          if (iter == end)
            break;

          if (!socket_.is_open())
          {
            ec = boost::asio::error::operation_aborted;
            break;
          }

          if (!ec)
            break;

          if (this->cancelled() != cancellation_type::none)
          {
            ec = boost::asio::error::operation_aborted;
            break;
          }

          ++iter;
          ++index_;
        }

        BOOST_ASIO_MOVE_OR_LVALUE(RangeConnectHandler)(handler_)(
            static_cast<const boost::system::error_code&>(ec),
            static_cast<const typename Protocol::endpoint&>(
              ec || iter == end ? typename Protocol::endpoint() : *iter));
      }
    }

    basic_socket<Protocol, Executor>& socket_;
    EndpointSequence endpoints_;
    std::size_t index_;
    int start_;
    RangeConnectHandler handler_;
  };

  template <typename Protocol, typename Executor, typename EndpointSequence,
      typename ConnectCondition, typename RangeConnectHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Protocol, typename Executor, typename EndpointSequence,
      typename ConnectCondition, typename RangeConnectHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Protocol, typename Executor, typename EndpointSequence,
      typename ConnectCondition, typename RangeConnectHandler>
  inline bool asio_handler_is_continuation(
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }

  template <typename Function, typename Executor, typename Protocol,
      typename EndpointSequence, typename ConnectCondition,
      typename RangeConnectHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename Executor, typename Protocol,
      typename EndpointSequence, typename ConnectCondition,
      typename RangeConnectHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Protocol, typename Executor>
  class initiate_async_range_connect
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_range_connect(basic_socket<Protocol, Executor>& s)
      : socket_(s)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return socket_.get_executor();
    }

    template <typename RangeConnectHandler,
        typename EndpointSequence, typename ConnectCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(RangeConnectHandler) handler,
        const EndpointSequence& endpoints,
        const ConnectCondition& connect_condition) const
    {
      // If you get an error on the following line it means that your
      // handler does not meet the documented type requirements for an
      // RangeConnectHandler.
      BOOST_ASIO_RANGE_CONNECT_HANDLER_CHECK(RangeConnectHandler,
          handler, typename Protocol::endpoint) type_check;

      non_const_lvalue<RangeConnectHandler> handler2(handler);
      range_connect_op<Protocol, Executor, EndpointSequence, ConnectCondition,
        typename decay<RangeConnectHandler>::type>(socket_, endpoints,
          connect_condition, handler2.value)(boost::system::error_code(), 1);
    }

  private:
    basic_socket<Protocol, Executor>& socket_;
  };

  template <typename Protocol, typename Executor, typename Iterator,
      typename ConnectCondition, typename IteratorConnectHandler>
  class iterator_connect_op
    : public base_from_cancellation_state<IteratorConnectHandler>,
      base_from_connect_condition<ConnectCondition>
  {
  public:
    iterator_connect_op(basic_socket<Protocol, Executor>& sock,
        const Iterator& begin, const Iterator& end,
        const ConnectCondition& connect_condition,
        IteratorConnectHandler& handler)
      : base_from_cancellation_state<IteratorConnectHandler>(
          handler, enable_partial_cancellation()),
        base_from_connect_condition<ConnectCondition>(connect_condition),
        socket_(sock),
        iter_(begin),
        end_(end),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(IteratorConnectHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    iterator_connect_op(const iterator_connect_op& other)
      : base_from_cancellation_state<IteratorConnectHandler>(other),
        base_from_connect_condition<ConnectCondition>(other),
        socket_(other.socket_),
        iter_(other.iter_),
        end_(other.end_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    iterator_connect_op(iterator_connect_op&& other)
      : base_from_cancellation_state<IteratorConnectHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            IteratorConnectHandler>)(other)),
        base_from_connect_condition<ConnectCondition>(other),
        socket_(other.socket_),
        iter_(other.iter_),
        end_(other.end_),
        start_(other.start_),
        handler_(BOOST_ASIO_MOVE_CAST(IteratorConnectHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(boost::system::error_code ec, int start = 0)
    {
      switch (start_ = start)
      {
        case 1:
        for (;;)
        {
          this->check_condition(ec, iter_, end_);

          if (iter_ != end_)
          {
            socket_.close(ec);
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_connect"));
            socket_.async_connect(*iter_,
                BOOST_ASIO_MOVE_CAST(iterator_connect_op)(*this));
            return;
          }

          if (start)
          {
            ec = boost::asio::error::not_found;
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_connect"));
            boost::asio::post(socket_.get_executor(),
                detail::bind_handler(
                  BOOST_ASIO_MOVE_CAST(iterator_connect_op)(*this), ec));
            return;
          }

          /* fall-through */ default:

          if (iter_ == end_)
            break;

          if (!socket_.is_open())
          {
            ec = boost::asio::error::operation_aborted;
            break;
          }

          if (!ec)
            break;

          if (this->cancelled() != cancellation_type::none)
          {
            ec = boost::asio::error::operation_aborted;
            break;
          }

          ++iter_;
        }

        BOOST_ASIO_MOVE_OR_LVALUE(IteratorConnectHandler)(handler_)(
            static_cast<const boost::system::error_code&>(ec),
            static_cast<const Iterator&>(iter_));
      }
    }

  //private:
    basic_socket<Protocol, Executor>& socket_;
    Iterator iter_;
    Iterator end_;
    int start_;
    IteratorConnectHandler handler_;
  };

  template <typename Protocol, typename Executor, typename Iterator,
      typename ConnectCondition, typename IteratorConnectHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Protocol, typename Executor, typename Iterator,
      typename ConnectCondition, typename IteratorConnectHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Protocol, typename Executor, typename Iterator,
      typename ConnectCondition, typename IteratorConnectHandler>
  inline bool asio_handler_is_continuation(
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }

  template <typename Function, typename Executor, typename Protocol,
      typename Iterator, typename ConnectCondition,
      typename IteratorConnectHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename Executor, typename Protocol,
      typename Iterator, typename ConnectCondition,
      typename IteratorConnectHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Protocol, typename Executor>
  class initiate_async_iterator_connect
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_iterator_connect(
        basic_socket<Protocol, Executor>& s)
      : socket_(s)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return socket_.get_executor();
    }

    template <typename IteratorConnectHandler,
        typename Iterator, typename ConnectCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler,
        Iterator begin, Iterator end,
        const ConnectCondition& connect_condition) const
    {
      // If you get an error on the following line it means that your
      // handler does not meet the documented type requirements for an
      // IteratorConnectHandler.
      BOOST_ASIO_ITERATOR_CONNECT_HANDLER_CHECK(
          IteratorConnectHandler, handler, Iterator) type_check;

      non_const_lvalue<IteratorConnectHandler> handler2(handler);
      iterator_connect_op<Protocol, Executor, Iterator, ConnectCondition,
        typename decay<IteratorConnectHandler>::type>(socket_, begin, end,
          connect_condition, handler2.value)(boost::system::error_code(), 1);
    }

  private:
    basic_socket<Protocol, Executor>& socket_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename Protocol, typename Executor, typename EndpointSequence,
    typename ConnectCondition, typename RangeConnectHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::range_connect_op<Protocol, Executor,
      EndpointSequence, ConnectCondition, RangeConnectHandler>,
    DefaultCandidate>
  : Associator<RangeConnectHandler, DefaultCandidate>
{
  static typename Associator<RangeConnectHandler, DefaultCandidate>::type get(
      const detail::range_connect_op<Protocol, Executor,
        EndpointSequence, ConnectCondition, RangeConnectHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<RangeConnectHandler, DefaultCandidate>::get(
        h.handler_, c);
  }
};

template <template <typename, typename> class Associator,
    typename Protocol, typename Executor, typename Iterator,
    typename ConnectCondition, typename IteratorConnectHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::iterator_connect_op<Protocol, Executor,
      Iterator, ConnectCondition, IteratorConnectHandler>,
    DefaultCandidate>
  : Associator<IteratorConnectHandler, DefaultCandidate>
{
  static typename Associator<IteratorConnectHandler, DefaultCandidate>::type
  get(
      const detail::iterator_connect_op<Protocol, Executor,
        Iterator, ConnectCondition, IteratorConnectHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<IteratorConnectHandler, DefaultCandidate>::get(
        h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename Protocol, typename Executor, typename EndpointSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      typename Protocol::endpoint)) RangeConnectToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(RangeConnectToken,
    void (boost::system::error_code, typename Protocol::endpoint))
async_connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints,
    BOOST_ASIO_MOVE_ARG(RangeConnectToken) token,
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type)
{
  return async_initiate<RangeConnectToken,
    void (boost::system::error_code, typename Protocol::endpoint)>(
      detail::initiate_async_range_connect<Protocol, Executor>(s),
      token, endpoints, detail::default_connect_condition());
}

#if !defined(BOOST_ASIO_NO_DEPRECATED)
template <typename Protocol, typename Executor, typename Iterator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectToken,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    BOOST_ASIO_MOVE_ARG(IteratorConnectToken) token,
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type)
{
  return async_initiate<IteratorConnectToken,
    void (boost::system::error_code, Iterator)>(
      detail::initiate_async_iterator_connect<Protocol, Executor>(s),
      token, begin, Iterator(), detail::default_connect_condition());
}
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Protocol, typename Executor, typename Iterator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectToken,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin, Iterator end,
    BOOST_ASIO_MOVE_ARG(IteratorConnectToken) token)
{
  return async_initiate<IteratorConnectToken,
    void (boost::system::error_code, Iterator)>(
      detail::initiate_async_iterator_connect<Protocol, Executor>(s),
      token, begin, end, detail::default_connect_condition());
}

template <typename Protocol, typename Executor,
    typename EndpointSequence, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      typename Protocol::endpoint)) RangeConnectToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(RangeConnectToken,
    void (boost::system::error_code, typename Protocol::endpoint))
async_connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(RangeConnectToken) token,
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type)
{
  return async_initiate<RangeConnectToken,
    void (boost::system::error_code, typename Protocol::endpoint)>(
      detail::initiate_async_range_connect<Protocol, Executor>(s),
      token, endpoints, connect_condition);
}

#if !defined(BOOST_ASIO_NO_DEPRECATED)
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectToken,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(IteratorConnectToken) token,
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type)
{
  return async_initiate<IteratorConnectToken,
    void (boost::system::error_code, Iterator)>(
      detail::initiate_async_iterator_connect<Protocol, Executor>(s),
      token, begin, Iterator(), connect_condition);
}
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectToken,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(IteratorConnectToken) token)
{
  return async_initiate<IteratorConnectToken,
    void (boost::system::error_code, Iterator)>(
      detail::initiate_async_iterator_connect<Protocol, Executor>(s),
      token, begin, end, connect_condition);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_CONNECT_HPP

/* connect.hpp
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
*/