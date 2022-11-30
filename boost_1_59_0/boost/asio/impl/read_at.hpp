//
// impl/read_at.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_READ_AT_HPP
#define BOOST_ASIO_IMPL_READ_AT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <algorithm>
#include <boost/asio/associator.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/asio/detail/array_fwd.hpp>
#include <boost/asio/detail/base_from_cancellation_state.hpp>
#include <boost/asio/detail/base_from_completion_cond.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/consuming_buffers.hpp>
#include <boost/asio/detail/dependent_type.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_tracking.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition>
  std::size_t read_at_buffer_sequence(SyncRandomAccessReadDevice& d,
      uint64_t offset, const MutableBufferSequence& buffers,
      const MutableBufferIterator&, CompletionCondition completion_condition,
      boost::system::error_code& ec)
  {
    ec = boost::system::error_code();
    boost::asio::detail::consuming_buffers<mutable_buffer,
        MutableBufferSequence, MutableBufferIterator> tmp(buffers);
    while (!tmp.empty())
    {
      if (std::size_t max_size = detail::adapt_completion_condition_result(
            completion_condition(ec, tmp.total_consumed())))
      {
        tmp.consume(d.read_some_at(offset + tmp.total_consumed(),
              tmp.prepare(max_size), ec));
      }
      else
        break;
    }
    return tmp.total_consumed();
  }
} // namespace detail

template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  return detail::read_at_buffer_sequence(d, offset, buffers,
      boost::asio::buffer_sequence_begin(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
}

template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence>
inline std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_at(
      d, offset, buffers, transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "read_at");
  return bytes_transferred;
}

template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence>
inline std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    boost::system::error_code& ec)
{
  return read_at(d, offset, buffers, transfer_all(), ec);
}

template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename CompletionCondition>
inline std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_at(d, offset, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "read_at");
  return bytes_transferred;
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename SyncRandomAccessReadDevice, typename Allocator,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  ec = boost::system::error_code();
  std::size_t total_transferred = 0;
  std::size_t max_size = detail::adapt_completion_condition_result(
        completion_condition(ec, total_transferred));
  std::size_t bytes_available = read_size_helper(b, max_size);
  while (bytes_available > 0)
  {
    std::size_t bytes_transferred = d.read_some_at(
        offset + total_transferred, b.prepare(bytes_available), ec);
    b.commit(bytes_transferred);
    total_transferred += bytes_transferred;
    max_size = detail::adapt_completion_condition_result(
          completion_condition(ec, total_transferred));
    bytes_available = read_size_helper(b, max_size);
  }
  return total_transferred;
}

template <typename SyncRandomAccessReadDevice, typename Allocator>
inline std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_at(
      d, offset, b, transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "read_at");
  return bytes_transferred;
}

template <typename SyncRandomAccessReadDevice, typename Allocator>
inline std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    boost::system::error_code& ec)
{
  return read_at(d, offset, b, transfer_all(), ec);
}

template <typename SyncRandomAccessReadDevice, typename Allocator,
    typename CompletionCondition>
inline std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read_at(d, offset, b,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "read_at");
  return bytes_transferred;
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

namespace detail
{
  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  class read_at_op
    : public base_from_cancellation_state<ReadHandler>,
      base_from_completion_cond<CompletionCondition>
  {
  public:
    read_at_op(AsyncRandomAccessReadDevice& device,
        uint64_t offset, const MutableBufferSequence& buffers,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : base_from_cancellation_state<ReadHandler>(
          handler, enable_partial_cancellation()),
        base_from_completion_cond<CompletionCondition>(completion_condition),
        device_(device),
        offset_(offset),
        buffers_(buffers),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_at_op(const read_at_op& other)
      : base_from_cancellation_state<ReadHandler>(other),
        base_from_completion_cond<CompletionCondition>(other),
        device_(other.device_),
        offset_(other.offset_),
        buffers_(other.buffers_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    read_at_op(read_at_op&& other)
      : base_from_cancellation_state<ReadHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            ReadHandler>)(other)),
        base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(base_from_completion_cond<
            CompletionCondition>)(other)),
        device_(other.device_),
        offset_(other.offset_),
        buffers_(BOOST_ASIO_MOVE_CAST(buffers_type)(other.buffers_)),
        start_(other.start_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(boost::system::error_code ec,
        std::size_t bytes_transferred, int start = 0)
    {
      std::size_t max_size;
      switch (start_ = start)
      {
        case 1:
        max_size = this->check_for_completion(ec, buffers_.total_consumed());
        for (;;)
        {
          {
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_read_at"));
            device_.async_read_some_at(
                offset_ + buffers_.total_consumed(), buffers_.prepare(max_size),
                BOOST_ASIO_MOVE_CAST(read_at_op)(*this));
          }
          return; default:
          buffers_.consume(bytes_transferred);
          if ((!ec && bytes_transferred == 0) || buffers_.empty())
            break;
          max_size = this->check_for_completion(ec, buffers_.total_consumed());
          if (max_size == 0)
            break;
          if (this->cancelled() != cancellation_type::none)
          {
            ec = boost::asio::error::operation_aborted;
            break;
          }
        }

        BOOST_ASIO_MOVE_OR_LVALUE(ReadHandler)(handler_)(
            static_cast<const boost::system::error_code&>(ec),
            static_cast<const std::size_t&>(buffers_.total_consumed()));
      }
    }

  //private:
    typedef boost::asio::detail::consuming_buffers<mutable_buffer,
        MutableBufferSequence, MutableBufferIterator> buffers_type;

    AsyncRandomAccessReadDevice& device_;
    uint64_t offset_;
    buffers_type buffers_;
    int start_;
    ReadHandler handler_;
  };

  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline void start_read_at_buffer_sequence_op(AsyncRandomAccessReadDevice& d,
      uint64_t offset, const MutableBufferSequence& buffers,
      const MutableBufferIterator&, CompletionCondition& completion_condition,
      ReadHandler& handler)
  {
    detail::read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
      MutableBufferIterator, CompletionCondition, ReadHandler>(
        d, offset, buffers, completion_condition, handler)(
          boost::system::error_code(), 0, 1);
  }

  template <typename AsyncRandomAccessReadDevice>
  class initiate_async_read_at_buffer_sequence
  {
  public:
    typedef typename AsyncRandomAccessReadDevice::executor_type executor_type;

    explicit initiate_async_read_at_buffer_sequence(
        AsyncRandomAccessReadDevice& device)
      : device_(device)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return device_.get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence,
        typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        uint64_t offset, const MutableBufferSequence& buffers,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      start_read_at_buffer_sequence_op(device_, offset, buffers,
          boost::asio::buffer_sequence_begin(buffers),
          completion_cond2.value, handler2.value);
    }

  private:
    AsyncRandomAccessReadDevice& device_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename AsyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename MutableBufferIterator, typename CompletionCondition,
    typename ReadHandler, typename DefaultCandidate>
struct associator<Associator,
    detail::read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
      MutableBufferIterator, CompletionCondition, ReadHandler>,
    DefaultCandidate>
  : Associator<ReadHandler, DefaultCandidate>
{
  static typename Associator<ReadHandler, DefaultCandidate>::type get(
      const detail::read_at_op<AsyncRandomAccessReadDevice,
        MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<ReadHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncRandomAccessReadDevice,
    typename MutableBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token)
{
  return async_initiate<ReadToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_at_buffer_sequence<
        AsyncRandomAccessReadDevice>(d),
      token, offset, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncRandomAccessReadDevice, typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadToken) token)
{
  return async_initiate<ReadToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_at_buffer_sequence<
        AsyncRandomAccessReadDevice>(d),
      token, offset, buffers, transfer_all());
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

namespace detail
{
  template <typename AsyncRandomAccessReadDevice, typename Allocator,
      typename CompletionCondition, typename ReadHandler>
  class read_at_streambuf_op
    : public base_from_cancellation_state<ReadHandler>,
      base_from_completion_cond<CompletionCondition>
  {
  public:
    read_at_streambuf_op(AsyncRandomAccessReadDevice& device,
        uint64_t offset, basic_streambuf<Allocator>& streambuf,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : base_from_cancellation_state<ReadHandler>(
          handler, enable_partial_cancellation()),
        base_from_completion_cond<CompletionCondition>(completion_condition),
        device_(device),
        offset_(offset),
        streambuf_(streambuf),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_at_streambuf_op(const read_at_streambuf_op& other)
      : base_from_cancellation_state<ReadHandler>(other),
        base_from_completion_cond<CompletionCondition>(other),
        device_(other.device_),
        offset_(other.offset_),
        streambuf_(other.streambuf_),
        start_(other.start_),
        total_transferred_(other.total_transferred_),
        handler_(other.handler_)
    {
    }

    read_at_streambuf_op(read_at_streambuf_op&& other)
      : base_from_cancellation_state<ReadHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            ReadHandler>)(other)),
        base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(base_from_completion_cond<
            CompletionCondition>)(other)),
        device_(other.device_),
        offset_(other.offset_),
        streambuf_(other.streambuf_),
        start_(other.start_),
        total_transferred_(other.total_transferred_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(boost::system::error_code ec,
        std::size_t bytes_transferred, int start = 0)
    {
      std::size_t max_size, bytes_available;
      switch (start_ = start)
      {
        case 1:
        max_size = this->check_for_completion(ec, total_transferred_);
        bytes_available = read_size_helper(streambuf_, max_size);
        for (;;)
        {
          {
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_read_at"));
            device_.async_read_some_at(offset_ + total_transferred_,
                streambuf_.prepare(bytes_available),
                BOOST_ASIO_MOVE_CAST(read_at_streambuf_op)(*this));
          }
          return; default:
          total_transferred_ += bytes_transferred;
          streambuf_.commit(bytes_transferred);
          max_size = this->check_for_completion(ec, total_transferred_);
          bytes_available = read_size_helper(streambuf_, max_size);
          if ((!ec && bytes_transferred == 0) || bytes_available == 0)
            break;
          if (this->cancelled() != cancellation_type::none)
          {
            ec = boost::asio::error::operation_aborted;
            break;
          }
        }

        BOOST_ASIO_MOVE_OR_LVALUE(ReadHandler)(handler_)(
            static_cast<const boost::system::error_code&>(ec),
            static_cast<const std::size_t&>(total_transferred_));
      }
    }

  //private:
    AsyncRandomAccessReadDevice& device_;
    uint64_t offset_;
    boost::asio::basic_streambuf<Allocator>& streambuf_;
    int start_;
    std::size_t total_transferred_;
    ReadHandler handler_;
  };

  template <typename AsyncRandomAccessReadDevice, typename Allocator,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessReadDevice, typename Allocator,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessReadDevice, typename Allocator,
      typename CompletionCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename Allocator, typename CompletionCondition, typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename Allocator, typename CompletionCondition, typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessReadDevice>
  class initiate_async_read_at_streambuf
  {
  public:
    typedef typename AsyncRandomAccessReadDevice::executor_type executor_type;

    explicit initiate_async_read_at_streambuf(
        AsyncRandomAccessReadDevice& device)
      : device_(device)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return device_.get_executor();
    }

    template <typename ReadHandler,
        typename Allocator, typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        uint64_t offset, basic_streambuf<Allocator>* b,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, typename decay<ReadHandler>::type>(
          device_, offset, *b, completion_cond2.value, handler2.value)(
            boost::system::error_code(), 0, 1);
    }

  private:
    AsyncRandomAccessReadDevice& device_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename AsyncRandomAccessReadDevice, typename Executor,
    typename CompletionCondition, typename ReadHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::read_at_streambuf_op<AsyncRandomAccessReadDevice,
      Executor, CompletionCondition, ReadHandler>,
    DefaultCandidate>
  : Associator<ReadHandler, DefaultCandidate>
{
  static typename Associator<ReadHandler, DefaultCandidate>::type get(
      const detail::read_at_streambuf_op<AsyncRandomAccessReadDevice,
        Executor, CompletionCondition, ReadHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<ReadHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncRandomAccessReadDevice,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token)
{
  return async_initiate<ReadToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_at_streambuf<AsyncRandomAccessReadDevice>(d),
      token, offset, &b,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncRandomAccessReadDevice, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadToken) token)
{
  return async_initiate<ReadToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_at_streambuf<AsyncRandomAccessReadDevice>(d),
      token, offset, &b, transfer_all());
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_READ_AT_HPP

/* read_at.hpp
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
*/