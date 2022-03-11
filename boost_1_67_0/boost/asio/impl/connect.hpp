//
// impl/connect.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
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
        (*static_cast<legacy_connect_condition_helper<T, Iterator>*>(0))(
          *static_cast<const boost::system::error_code*>(0),
          *static_cast<const Iterator*>(0)))) != 1;
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
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type*)
{
  boost::system::error_code ec;
  typename Protocol::endpoint result = connect(s, endpoints, ec);
  boost::asio::detail::throw_error(ec, "connect");
  return result;
}

template <typename Protocol, typename Executor, typename EndpointSequence>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, boost::system::error_code& ec,
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type*)
{
  return detail::deref_connect_result<Protocol>(
      connect(s, endpoints.begin(), endpoints.end(),
        detail::default_connect_condition(), ec), ec);
}

#if !defined(BOOST_ASIO_NO_DEPRECATED)
template <typename Protocol, typename Executor, typename Iterator>
Iterator connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type*)
{
  boost::system::error_code ec;
  Iterator result = connect(s, begin, ec);
  boost::asio::detail::throw_error(ec, "connect");
  return result;
}

template <typename Protocol, typename Executor, typename Iterator>
inline Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, boost::system::error_code& ec,
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type*)
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
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type*)
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
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type*)
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
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type*)
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
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type*)
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
  class range_connect_op : base_from_connect_condition<ConnectCondition>
  {
  public:
    range_connect_op(basic_socket<Protocol, Executor>& sock,
        const EndpointSequence& endpoints,
        const ConnectCondition& connect_condition,
        RangeConnectHandler& handler)
      : base_from_connect_condition<ConnectCondition>(connect_condition),
        socket_(sock),
        endpoints_(endpoints),
        index_(0),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(RangeConnectHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    range_connect_op(const range_connect_op& other)
      : base_from_connect_condition<ConnectCondition>(other),
        socket_(other.socket_),
        endpoints_(other.endpoints_),
        index_(other.index_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    range_connect_op(range_connect_op&& other)
      : base_from_connect_condition<ConnectCondition>(other),
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
            socket_.async_connect(*iter,
                BOOST_ASIO_MOVE_CAST(range_connect_op)(*this));
            return;
          }

          if (start)
          {
            ec = boost::asio::error::not_found;
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

          ++iter;
          ++index_;
        }

        handler_(static_cast<const boost::system::error_code&>(ec),
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
  inline void* asio_handler_allocate(std::size_t size,
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename Protocol, typename Executor, typename EndpointSequence,
      typename ConnectCondition, typename RangeConnectHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename Executor, typename Protocol,
      typename EndpointSequence, typename ConnectCondition,
      typename RangeConnectHandler>
  inline void asio_handler_invoke(const Function& function,
      range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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
  class iterator_connect_op : base_from_connect_condition<ConnectCondition>
  {
  public:
    iterator_connect_op(basic_socket<Protocol, Executor>& sock,
        const Iterator& begin, const Iterator& end,
        const ConnectCondition& connect_condition,
        IteratorConnectHandler& handler)
      : base_from_connect_condition<ConnectCondition>(connect_condition),
        socket_(sock),
        iter_(begin),
        end_(end),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(IteratorConnectHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    iterator_connect_op(const iterator_connect_op& other)
      : base_from_connect_condition<ConnectCondition>(other),
        socket_(other.socket_),
        iter_(other.iter_),
        end_(other.end_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    iterator_connect_op(iterator_connect_op&& other)
      : base_from_connect_condition<ConnectCondition>(other),
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
            socket_.async_connect(*iter_,
                BOOST_ASIO_MOVE_CAST(iterator_connect_op)(*this));
            return;
          }

          if (start)
          {
            ec = boost::asio::error::not_found;
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

          ++iter_;
        }

        handler_(static_cast<const boost::system::error_code&>(ec),
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
  inline void* asio_handler_allocate(std::size_t size,
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename Protocol, typename Executor, typename Iterator,
      typename ConnectCondition, typename IteratorConnectHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename Executor, typename Protocol,
      typename Iterator, typename ConnectCondition,
      typename IteratorConnectHandler>
  inline void asio_handler_invoke(const Function& function,
      iterator_connect_op<Protocol, Executor, Iterator,
        ConnectCondition, IteratorConnectHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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

template <typename Protocol, typename Executor, typename EndpointSequence,
    typename ConnectCondition, typename RangeConnectHandler, typename Allocator>
struct associated_allocator<
    detail::range_connect_op<Protocol, Executor, EndpointSequence,
      ConnectCondition, RangeConnectHandler>, Allocator>
{
  typedef typename associated_allocator<
      RangeConnectHandler, Allocator>::type type;

  static type get(
      const detail::range_connect_op<Protocol, Executor, EndpointSequence,
        ConnectCondition, RangeConnectHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<RangeConnectHandler,
        Allocator>::get(h.handler_, a);
  }
};

template <typename Protocol, typename Executor, typename EndpointSequence,
    typename ConnectCondition, typename RangeConnectHandler, typename Executor1>
struct associated_executor<
    detail::range_connect_op<Protocol, Executor, EndpointSequence,
      ConnectCondition, RangeConnectHandler>, Executor1>
{
  typedef typename associated_executor<
      RangeConnectHandler, Executor1>::type type;

  static type get(
      const detail::range_connect_op<Protocol, Executor, EndpointSequence,
      ConnectCondition, RangeConnectHandler>& h,
      const Executor1& ex = Executor1()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<RangeConnectHandler,
        Executor1>::get(h.handler_, ex);
  }
};

template <typename Protocol, typename Executor, typename Iterator,
    typename ConnectCondition, typename IteratorConnectHandler,
    typename Allocator>
struct associated_allocator<
    detail::iterator_connect_op<Protocol, Executor,
      Iterator, ConnectCondition, IteratorConnectHandler>,
    Allocator>
{
  typedef typename associated_allocator<
      IteratorConnectHandler, Allocator>::type type;

  static type get(
      const detail::iterator_connect_op<Protocol, Executor,
        Iterator, ConnectCondition, IteratorConnectHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<IteratorConnectHandler,
        Allocator>::get(h.handler_, a);
  }
};

template <typename Protocol, typename Executor, typename Iterator,
    typename ConnectCondition, typename IteratorConnectHandler,
    typename Executor1>
struct associated_executor<
    detail::iterator_connect_op<Protocol, Executor,
      Iterator, ConnectCondition, IteratorConnectHandler>,
    Executor1>
{
  typedef typename associated_executor<
      IteratorConnectHandler, Executor1>::type type;

  static type get(
      const detail::iterator_connect_op<Protocol, Executor,
        Iterator, ConnectCondition, IteratorConnectHandler>& h,
      const Executor1& ex = Executor1()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<IteratorConnectHandler,
        Executor1>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename Protocol, typename Executor, typename EndpointSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      typename Protocol::endpoint)) RangeConnectHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(RangeConnectHandler,
    void (boost::system::error_code, typename Protocol::endpoint))
async_connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints,
    BOOST_ASIO_MOVE_ARG(RangeConnectHandler) handler,
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type*)
{
  return async_initiate<RangeConnectHandler,
    void (boost::system::error_code, typename Protocol::endpoint)>(
      detail::initiate_async_range_connect<Protocol, Executor>(s),
      handler, endpoints, detail::default_connect_condition());
}

#if !defined(BOOST_ASIO_NO_DEPRECATED)
template <typename Protocol, typename Executor, typename Iterator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectHandler,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler,
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type*)
{
  return async_initiate<IteratorConnectHandler,
    void (boost::system::error_code, Iterator)>(
      detail::initiate_async_iterator_connect<Protocol, Executor>(s),
      handler, begin, Iterator(), detail::default_connect_condition());
}
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Protocol, typename Executor, typename Iterator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectHandler,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin, Iterator end,
    BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler)
{
  return async_initiate<IteratorConnectHandler,
    void (boost::system::error_code, Iterator)>(
      detail::initiate_async_iterator_connect<Protocol, Executor>(s),
      handler, begin, end, detail::default_connect_condition());
}

template <typename Protocol, typename Executor,
    typename EndpointSequence, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      typename Protocol::endpoint)) RangeConnectHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(RangeConnectHandler,
    void (boost::system::error_code, typename Protocol::endpoint))
async_connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(RangeConnectHandler) handler,
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type*)
{
  return async_initiate<RangeConnectHandler,
    void (boost::system::error_code, typename Protocol::endpoint)>(
      detail::initiate_async_range_connect<Protocol, Executor>(s),
      handler, endpoints, connect_condition);
}

#if !defined(BOOST_ASIO_NO_DEPRECATED)
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectHandler,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler,
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type*)
{
  return async_initiate<IteratorConnectHandler,
    void (boost::system::error_code, Iterator)>(
      detail::initiate_async_iterator_connect<Protocol, Executor>(s),
      handler, begin, Iterator(), connect_condition);
}
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectHandler,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler)
{
  return async_initiate<IteratorConnectHandler,
    void (boost::system::error_code, Iterator)>(
      detail::initiate_async_iterator_connect<Protocol, Executor>(s),
      handler, begin, end, connect_condition);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_CONNECT_HPP

/* connect.hpp
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
*/