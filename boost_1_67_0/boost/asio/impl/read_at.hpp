//
// impl/read_at.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/asio/detail/array_fwd.hpp>
#include <boost/asio/detail/base_from_completion_cond.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/consuming_buffers.hpp>
#include <boost/asio/detail/dependent_type.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
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
    return tmp.total_consumed();;
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
    : detail::base_from_completion_cond<CompletionCondition>
  {
  public:
    read_at_op(AsyncRandomAccessReadDevice& device,
        uint64_t offset, const MutableBufferSequence& buffers,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        device_(device),
        offset_(offset),
        buffers_(buffers),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_at_op(const read_at_op& other)
      : detail::base_from_completion_cond<CompletionCondition>(other),
        device_(other.device_),
        offset_(other.offset_),
        buffers_(other.buffers_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    read_at_op(read_at_op&& other)
      : detail::base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(detail::base_from_completion_cond<
            CompletionCondition>)(other)),
        device_(other.device_),
        offset_(other.offset_),
        buffers_(BOOST_ASIO_MOVE_CAST(buffers_type)(other.buffers_)),
        start_(other.start_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      std::size_t max_size;
      switch (start_ = start)
      {
        case 1:
        max_size = this->check_for_completion(ec, buffers_.total_consumed());
        do
        {
          device_.async_read_some_at(
              offset_ + buffers_.total_consumed(), buffers_.prepare(max_size),
              BOOST_ASIO_MOVE_CAST(read_at_op)(*this));
          return; default:
          buffers_.consume(bytes_transferred);
          if ((!ec && bytes_transferred == 0) || buffers_.empty())
            break;
          max_size = this->check_for_completion(ec, buffers_.total_consumed());
        } while (max_size > 0);

        handler_(ec, buffers_.total_consumed());
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
  inline void* asio_handler_allocate(std::size_t size,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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

template <typename AsyncRandomAccessReadDevice,
    typename MutableBufferSequence, typename MutableBufferIterator,
    typename CompletionCondition, typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
    MutableBufferIterator, CompletionCondition, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_at_op<AsyncRandomAccessReadDevice,
      MutableBufferSequence, MutableBufferIterator,
      CompletionCondition, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncRandomAccessReadDevice,
    typename MutableBufferSequence, typename MutableBufferIterator,
    typename CompletionCondition, typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_at_op<AsyncRandomAccessReadDevice, MutableBufferSequence,
    MutableBufferIterator, CompletionCondition, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_at_op<AsyncRandomAccessReadDevice,
      MutableBufferSequence, MutableBufferIterator,
      CompletionCondition, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncRandomAccessReadDevice,
    typename MutableBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_at_buffer_sequence<
        AsyncRandomAccessReadDevice>(d),
      handler, offset, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncRandomAccessReadDevice, typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_at_buffer_sequence<
        AsyncRandomAccessReadDevice>(d),
      handler, offset, buffers, transfer_all());
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

namespace detail
{
  template <typename AsyncRandomAccessReadDevice, typename Allocator,
      typename CompletionCondition, typename ReadHandler>
  class read_at_streambuf_op
    : detail::base_from_completion_cond<CompletionCondition>
  {
  public:
    read_at_streambuf_op(AsyncRandomAccessReadDevice& device,
        uint64_t offset, basic_streambuf<Allocator>& streambuf,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
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
      : detail::base_from_completion_cond<CompletionCondition>(other),
        device_(other.device_),
        offset_(other.offset_),
        streambuf_(other.streambuf_),
        start_(other.start_),
        total_transferred_(other.total_transferred_),
        handler_(other.handler_)
    {
    }

    read_at_streambuf_op(read_at_streambuf_op&& other)
      : detail::base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(detail::base_from_completion_cond<
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

    void operator()(const boost::system::error_code& ec,
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
          device_.async_read_some_at(offset_ + total_transferred_,
              streambuf_.prepare(bytes_available),
              BOOST_ASIO_MOVE_CAST(read_at_streambuf_op)(*this));
          return; default:
          total_transferred_ += bytes_transferred;
          streambuf_.commit(bytes_transferred);
          max_size = this->check_for_completion(ec, total_transferred_);
          bytes_available = read_size_helper(streambuf_, max_size);
          if ((!ec && bytes_transferred == 0) || bytes_available == 0)
            break;
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
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
  inline void* asio_handler_allocate(std::size_t size,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncRandomAccessReadDevice, typename Allocator,
      typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncRandomAccessReadDevice,
      typename Allocator, typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_at_streambuf_op<AsyncRandomAccessReadDevice, Allocator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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

template <typename AsyncRandomAccessReadDevice, typename Allocator,
    typename CompletionCondition, typename ReadHandler, typename Allocator1>
struct associated_allocator<
    detail::read_at_streambuf_op<AsyncRandomAccessReadDevice,
      Allocator, CompletionCondition, ReadHandler>,
    Allocator1>
{
  typedef typename associated_allocator<ReadHandler, Allocator1>::type type;

  static type get(
      const detail::read_at_streambuf_op<AsyncRandomAccessReadDevice,
        Allocator, CompletionCondition, ReadHandler>& h,
      const Allocator1& a = Allocator1()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator1>::get(h.handler_, a);
  }
};

template <typename AsyncRandomAccessReadDevice, typename Executor,
    typename CompletionCondition, typename ReadHandler, typename Executor1>
struct associated_executor<
    detail::read_at_streambuf_op<AsyncRandomAccessReadDevice,
      Executor, CompletionCondition, ReadHandler>,
    Executor1>
{
  typedef typename associated_executor<ReadHandler, Executor1>::type type;

  static type get(
      const detail::read_at_streambuf_op<AsyncRandomAccessReadDevice,
        Executor, CompletionCondition, ReadHandler>& h,
      const Executor1& ex = Executor1()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor1>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncRandomAccessReadDevice,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_at_streambuf<AsyncRandomAccessReadDevice>(d),
      handler, offset, &b,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncRandomAccessReadDevice, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_at_streambuf<AsyncRandomAccessReadDevice>(d),
      handler, offset, &b, transfer_all());
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