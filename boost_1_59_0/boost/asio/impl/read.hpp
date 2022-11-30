//
// impl/read.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_READ_HPP
#define BOOST_ASIO_IMPL_READ_HPP

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
  template <typename SyncReadStream, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition>
  std::size_t read_buffer_sequence(SyncReadStream& s,
      const MutableBufferSequence& buffers, const MutableBufferIterator&,
      CompletionCondition completion_condition, boost::system::error_code& ec)
  {
    ec = boost::system::error_code();
    boost::asio::detail::consuming_buffers<mutable_buffer,
        MutableBufferSequence, MutableBufferIterator> tmp(buffers);
    while (!tmp.empty())
    {
      if (std::size_t max_size = detail::adapt_completion_condition_result(
            completion_condition(ec, tmp.total_consumed())))
        tmp.consume(s.read_some(tmp.prepare(max_size), ec));
      else
        break;
    }
    return tmp.total_consumed();
  }
} // namespace detail

template <typename SyncReadStream, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type)
{
  return detail::read_buffer_sequence(s, buffers,
      boost::asio::buffer_sequence_begin(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
}

template <typename SyncReadStream, typename MutableBufferSequence>
inline std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read(s, buffers, transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "read");
  return bytes_transferred;
}

template <typename SyncReadStream, typename MutableBufferSequence>
inline std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    boost::system::error_code& ec,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type)
{
  return read(s, buffers, transfer_all(), ec);
}

template <typename SyncReadStream, typename MutableBufferSequence,
    typename CompletionCondition>
inline std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read(s, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "read");
  return bytes_transferred;
}

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

template <typename SyncReadStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  typename decay<DynamicBuffer_v1>::type b(
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers));

  ec = boost::system::error_code();
  std::size_t total_transferred = 0;
  std::size_t max_size = detail::adapt_completion_condition_result(
        completion_condition(ec, total_transferred));
  std::size_t bytes_available = std::min<std::size_t>(
        std::max<std::size_t>(512, b.capacity() - b.size()),
        std::min<std::size_t>(max_size, b.max_size() - b.size()));
  while (bytes_available > 0)
  {
    std::size_t bytes_transferred = s.read_some(b.prepare(bytes_available), ec);
    b.commit(bytes_transferred);
    total_transferred += bytes_transferred;
    max_size = detail::adapt_completion_condition_result(
          completion_condition(ec, total_transferred));
    bytes_available = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(max_size, b.max_size() - b.size()));
  }
  return total_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v1>
inline std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers), transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "read");
  return bytes_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v1>
inline std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  return read(s, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), ec);
}

template <typename SyncReadStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
inline std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "read");
  return bytes_transferred;
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename SyncReadStream, typename Allocator,
    typename CompletionCondition>
inline std::size_t read(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  return read(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
}

template <typename SyncReadStream, typename Allocator>
inline std::size_t read(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b)
{
  return read(s, basic_streambuf_ref<Allocator>(b));
}

template <typename SyncReadStream, typename Allocator>
inline std::size_t read(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    boost::system::error_code& ec)
{
  return read(s, basic_streambuf_ref<Allocator>(b), ec);
}

template <typename SyncReadStream, typename Allocator,
    typename CompletionCondition>
inline std::size_t read(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition)
{
  return read(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

template <typename SyncReadStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  DynamicBuffer_v2& b = buffers;

  ec = boost::system::error_code();
  std::size_t total_transferred = 0;
  std::size_t max_size = detail::adapt_completion_condition_result(
        completion_condition(ec, total_transferred));
  std::size_t bytes_available = std::min<std::size_t>(
        std::max<std::size_t>(512, b.capacity() - b.size()),
        std::min<std::size_t>(max_size, b.max_size() - b.size()));
  while (bytes_available > 0)
  {
    std::size_t pos = b.size();
    b.grow(bytes_available);
    std::size_t bytes_transferred = s.read_some(
        b.data(pos, bytes_available), ec);
    b.shrink(bytes_available - bytes_transferred);
    total_transferred += bytes_transferred;
    max_size = detail::adapt_completion_condition_result(
          completion_condition(ec, total_transferred));
    bytes_available = std::min<std::size_t>(
          std::max<std::size_t>(512, b.capacity() - b.size()),
          std::min<std::size_t>(max_size, b.max_size() - b.size()));
  }
  return total_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v2>
inline std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers), transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "read");
  return bytes_transferred;
}

template <typename SyncReadStream, typename DynamicBuffer_v2>
inline std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  return read(s, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), ec);
}

template <typename SyncReadStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
inline std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "read");
  return bytes_transferred;
}

namespace detail
{
  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition,
      typename ReadHandler>
  class read_op
    : public base_from_cancellation_state<ReadHandler>,
      base_from_completion_cond<CompletionCondition>
  {
  public:
    read_op(AsyncReadStream& stream, const MutableBufferSequence& buffers,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : base_from_cancellation_state<ReadHandler>(
          handler, enable_partial_cancellation()),
        base_from_completion_cond<CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(buffers),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_op(const read_op& other)
      : base_from_cancellation_state<ReadHandler>(other),
        base_from_completion_cond<CompletionCondition>(other),
        stream_(other.stream_),
        buffers_(other.buffers_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    read_op(read_op&& other)
      : base_from_cancellation_state<ReadHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            ReadHandler>)(other)),
        base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(base_from_completion_cond<
            CompletionCondition>)(other)),
        stream_(other.stream_),
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
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_read"));
            stream_.async_read_some(buffers_.prepare(max_size),
                BOOST_ASIO_MOVE_CAST(read_op)(*this));
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
            ec = error::operation_aborted;
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

    AsyncReadStream& stream_;
    buffers_type buffers_;
    int start_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition,
      typename ReadHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
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

  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition,
      typename ReadHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition,
      typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncReadStream,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition,
      typename ReadHandler>
  inline void start_read_buffer_sequence_op(AsyncReadStream& stream,
      const MutableBufferSequence& buffers, const MutableBufferIterator&,
      CompletionCondition& completion_condition, ReadHandler& handler)
  {
    detail::read_op<AsyncReadStream, MutableBufferSequence,
      MutableBufferIterator, CompletionCondition, ReadHandler>(
        stream, buffers, completion_condition, handler)(
          boost::system::error_code(), 0, 1);
  }

  template <typename AsyncReadStream>
  class initiate_async_read_buffer_sequence
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_buffer_sequence(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence,
        typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        const MutableBufferSequence& buffers,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      start_read_buffer_sequence_op(stream_, buffers,
          boost::asio::buffer_sequence_begin(buffers),
          completion_cond2.value, handler2.value);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename AsyncReadStream, typename MutableBufferSequence,
    typename MutableBufferIterator, typename CompletionCondition,
    typename ReadHandler, typename DefaultCandidate>
struct associator<Associator,
    detail::read_op<AsyncReadStream, MutableBufferSequence,
      MutableBufferIterator, CompletionCondition, ReadHandler>,
    DefaultCandidate>
  : Associator<ReadHandler, DefaultCandidate>
{
  static typename Associator<ReadHandler, DefaultCandidate>::type get(
      const detail::read_op<AsyncReadStream, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<ReadHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream,
    typename MutableBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type)
{
  return async_initiate<ReadToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_buffer_sequence<AsyncReadStream>(s), token,
      buffers, BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncReadStream, typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadToken) token,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type)
{
  return async_initiate<ReadToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_buffer_sequence<AsyncReadStream>(s),
      token, buffers, transfer_all());
}

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

namespace detail
{
  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename ReadHandler>
  class read_dynbuf_v1_op
    : public base_from_cancellation_state<ReadHandler>,
      base_from_completion_cond<CompletionCondition>
  {
  public:
    template <typename BufferSequence>
    read_dynbuf_v1_op(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : base_from_cancellation_state<ReadHandler>(
          handler, enable_partial_cancellation()),
        base_from_completion_cond<CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_dynbuf_v1_op(const read_dynbuf_v1_op& other)
      : base_from_cancellation_state<ReadHandler>(other),
        base_from_completion_cond<CompletionCondition>(other),
        stream_(other.stream_),
        buffers_(other.buffers_),
        start_(other.start_),
        total_transferred_(other.total_transferred_),
        handler_(other.handler_)
    {
    }

    read_dynbuf_v1_op(read_dynbuf_v1_op&& other)
      : base_from_cancellation_state<ReadHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            ReadHandler>)(other)),
        base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(base_from_completion_cond<
            CompletionCondition>)(other)),
        stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(other.buffers_)),
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
        bytes_available = std::min<std::size_t>(
              std::max<std::size_t>(512,
                buffers_.capacity() - buffers_.size()),
              std::min<std::size_t>(max_size,
                buffers_.max_size() - buffers_.size()));
        for (;;)
        {
          {
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_read"));
            stream_.async_read_some(buffers_.prepare(bytes_available),
                BOOST_ASIO_MOVE_CAST(read_dynbuf_v1_op)(*this));
          }
          return; default:
          total_transferred_ += bytes_transferred;
          buffers_.commit(bytes_transferred);
          max_size = this->check_for_completion(ec, total_transferred_);
          bytes_available = std::min<std::size_t>(
                std::max<std::size_t>(512,
                  buffers_.capacity() - buffers_.size()),
                std::min<std::size_t>(max_size,
                  buffers_.max_size() - buffers_.size()));
          if ((!ec && bytes_transferred == 0) || bytes_available == 0)
            break;
          if (this->cancelled() != cancellation_type::none)
          {
            ec = error::operation_aborted;
            break;
          }
        }

        BOOST_ASIO_MOVE_OR_LVALUE(ReadHandler)(handler_)(
            static_cast<const boost::system::error_code&>(ec),
            static_cast<const std::size_t&>(total_transferred_));
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v1 buffers_;
    int start_;
    std::size_t total_transferred_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
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

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename CompletionCondition,
      typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename CompletionCondition,
      typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncReadStream>
  class initiate_async_read_dynbuf_v1
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_dynbuf_v1(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename DynamicBuffer_v1,
        typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      read_dynbuf_v1_op<AsyncReadStream, typename decay<DynamicBuffer_v1>::type,
        CompletionCondition, typename decay<ReadHandler>::type>(
          stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
            completion_cond2.value, handler2.value)(
              boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename AsyncReadStream, typename DynamicBuffer_v1,
    typename CompletionCondition, typename ReadHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::read_dynbuf_v1_op<AsyncReadStream,
      DynamicBuffer_v1, CompletionCondition, ReadHandler>,
    DefaultCandidate>
  : Associator<ReadHandler, DefaultCandidate>
{
  static typename Associator<ReadHandler, DefaultCandidate>::type get(
      const detail::read_dynbuf_v1_op<AsyncReadStream,
        DynamicBuffer_v1, CompletionCondition, ReadHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<ReadHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_MOVE_ARG(ReadToken) token,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  return async_read(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), BOOST_ASIO_MOVE_CAST(ReadToken)(token));
}

template <typename AsyncReadStream,
    typename DynamicBuffer_v1, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  return async_initiate<ReadToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_dynbuf_v1<AsyncReadStream>(s),
      token, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadToken) token)
{
  return async_read(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(ReadToken)(token));
}

template <typename AsyncReadStream,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token)
{
  return async_read(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition),
      BOOST_ASIO_MOVE_CAST(ReadToken)(token));
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

namespace detail
{
  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename ReadHandler>
  class read_dynbuf_v2_op
    : public base_from_cancellation_state<ReadHandler>,
      base_from_completion_cond<CompletionCondition>
  {
  public:
    template <typename BufferSequence>
    read_dynbuf_v2_op(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : base_from_cancellation_state<ReadHandler>(
          handler, enable_partial_cancellation()),
        base_from_completion_cond<CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        start_(0),
        total_transferred_(0),
        bytes_available_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_dynbuf_v2_op(const read_dynbuf_v2_op& other)
      : base_from_cancellation_state<ReadHandler>(other),
        base_from_completion_cond<CompletionCondition>(other),
        stream_(other.stream_),
        buffers_(other.buffers_),
        start_(other.start_),
        total_transferred_(other.total_transferred_),
        bytes_available_(other.bytes_available_),
        handler_(other.handler_)
    {
    }

    read_dynbuf_v2_op(read_dynbuf_v2_op&& other)
      : base_from_cancellation_state<ReadHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            ReadHandler>)(other)),
        base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(base_from_completion_cond<
            CompletionCondition>)(other)),
        stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(other.buffers_)),
        start_(other.start_),
        total_transferred_(other.total_transferred_),
        bytes_available_(other.bytes_available_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(boost::system::error_code ec,
        std::size_t bytes_transferred, int start = 0)
    {
      std::size_t max_size, pos;
      switch (start_ = start)
      {
        case 1:
        max_size = this->check_for_completion(ec, total_transferred_);
        bytes_available_ = std::min<std::size_t>(
              std::max<std::size_t>(512,
                buffers_.capacity() - buffers_.size()),
              std::min<std::size_t>(max_size,
                buffers_.max_size() - buffers_.size()));
        for (;;)
        {
          pos = buffers_.size();
          buffers_.grow(bytes_available_);
          {
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_read"));
            stream_.async_read_some(buffers_.data(pos, bytes_available_),
                BOOST_ASIO_MOVE_CAST(read_dynbuf_v2_op)(*this));
          }
          return; default:
          total_transferred_ += bytes_transferred;
          buffers_.shrink(bytes_available_ - bytes_transferred);
          max_size = this->check_for_completion(ec, total_transferred_);
          bytes_available_ = std::min<std::size_t>(
                std::max<std::size_t>(512,
                  buffers_.capacity() - buffers_.size()),
                std::min<std::size_t>(max_size,
                  buffers_.max_size() - buffers_.size()));
          if ((!ec && bytes_transferred == 0) || bytes_available_ == 0)
            break;
          if (this->cancelled() != cancellation_type::none)
          {
            ec = error::operation_aborted;
            break;
          }
        }

        BOOST_ASIO_MOVE_OR_LVALUE(ReadHandler)(handler_)(
            static_cast<const boost::system::error_code&>(ec),
            static_cast<const std::size_t&>(total_transferred_));
      }
    }

  //private:
    AsyncReadStream& stream_;
    DynamicBuffer_v2 buffers_;
    int start_;
    std::size_t total_transferred_;
    std::size_t bytes_available_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
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

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename ReadHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename CompletionCondition,
      typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename CompletionCondition,
      typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncReadStream>
  class initiate_async_read_dynbuf_v2
  {
  public:
    typedef typename AsyncReadStream::executor_type executor_type;

    explicit initiate_async_read_dynbuf_v2(AsyncReadStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename ReadHandler, typename DynamicBuffer_v2,
        typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v2) buffers,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      read_dynbuf_v2_op<AsyncReadStream, typename decay<DynamicBuffer_v2>::type,
        CompletionCondition, typename decay<ReadHandler>::type>(
          stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
            completion_cond2.value, handler2.value)(
              boost::system::error_code(), 0, 1);
    }

  private:
    AsyncReadStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename AsyncReadStream, typename DynamicBuffer_v2,
    typename CompletionCondition, typename ReadHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::read_dynbuf_v2_op<AsyncReadStream,
      DynamicBuffer_v2, CompletionCondition, ReadHandler>,
    DefaultCandidate>
  : Associator<ReadHandler, DefaultCandidate>
{
  static typename Associator<ReadHandler, DefaultCandidate>::type get(
      const detail::read_dynbuf_v2_op<AsyncReadStream,
        DynamicBuffer_v2, CompletionCondition, ReadHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<ReadHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_MOVE_ARG(ReadToken) token,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  return async_read(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), BOOST_ASIO_MOVE_CAST(ReadToken)(token));
}

template <typename AsyncReadStream,
    typename DynamicBuffer_v2, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  return async_initiate<ReadToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_dynbuf_v2<AsyncReadStream>(s),
      token, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_READ_HPP

/* read.hpp
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
*/