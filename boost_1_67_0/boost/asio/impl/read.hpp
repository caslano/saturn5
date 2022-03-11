//
// impl/read.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    return tmp.total_consumed();;
  }
} // namespace detail

template <typename SyncReadStream, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type*)
{
  return detail::read_buffer_sequence(s, buffers,
      boost::asio::buffer_sequence_begin(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
}

template <typename SyncReadStream, typename MutableBufferSequence>
inline std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = read(s, buffers, transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "read");
  return bytes_transferred;
}

template <typename SyncReadStream, typename MutableBufferSequence>
inline std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    boost::system::error_code& ec,
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type*)
{
  return read(s, buffers, transfer_all(), ec);
}

template <typename SyncReadStream, typename MutableBufferSequence,
    typename CompletionCondition>
inline std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type*)
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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return read(s, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), ec);
}

template <typename SyncReadStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
inline std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return read(s, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), ec);
}

template <typename SyncReadStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
inline std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
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
    : detail::base_from_completion_cond<CompletionCondition>
  {
  public:
    read_op(AsyncReadStream& stream, const MutableBufferSequence& buffers,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(buffers),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_op(const read_op& other)
      : detail::base_from_completion_cond<CompletionCondition>(other),
        stream_(other.stream_),
        buffers_(other.buffers_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    read_op(read_op&& other)
      : detail::base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(detail::base_from_completion_cond<
            CompletionCondition>)(other)),
        stream_(other.stream_),
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
          stream_.async_read_some(buffers_.prepare(max_size),
              BOOST_ASIO_MOVE_CAST(read_op)(*this));
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

    AsyncReadStream& stream_;
    buffers_type buffers_;
    int start_;
    ReadHandler handler_;
  };

  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition,
      typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename MutableBufferSequence,
      typename MutableBufferIterator, typename CompletionCondition,
      typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename MutableBufferSequence, typename MutableBufferIterator,
      typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_op<AsyncReadStream, MutableBufferSequence, MutableBufferIterator,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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

template <typename AsyncReadStream, typename MutableBufferSequence,
    typename MutableBufferIterator, typename CompletionCondition,
    typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_op<AsyncReadStream, MutableBufferSequence,
      MutableBufferIterator, CompletionCondition, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_op<AsyncReadStream, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename MutableBufferSequence,
    typename MutableBufferIterator, typename CompletionCondition,
    typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_op<AsyncReadStream, MutableBufferSequence,
      MutableBufferIterator, CompletionCondition, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_op<AsyncReadStream, MutableBufferSequence,
        MutableBufferIterator, CompletionCondition, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream,
    typename MutableBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_buffer_sequence<AsyncReadStream>(s), handler,
      buffers, BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncReadStream, typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_buffer_sequence<AsyncReadStream>(s),
      handler, buffers, transfer_all());
}

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

namespace detail
{
  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename ReadHandler>
  class read_dynbuf_v1_op
    : detail::base_from_completion_cond<CompletionCondition>
  {
  public:
    template <typename BufferSequence>
    read_dynbuf_v1_op(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        start_(0),
        total_transferred_(0),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    read_dynbuf_v1_op(const read_dynbuf_v1_op& other)
      : detail::base_from_completion_cond<CompletionCondition>(other),
        stream_(other.stream_),
        buffers_(other.buffers_),
        start_(other.start_),
        total_transferred_(other.total_transferred_),
        handler_(other.handler_)
    {
    }

    read_dynbuf_v1_op(read_dynbuf_v1_op&& other)
      : detail::base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(detail::base_from_completion_cond<
            CompletionCondition>)(other)),
        stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(other.buffers_)),
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
        bytes_available = std::min<std::size_t>(
              std::max<std::size_t>(512,
                buffers_.capacity() - buffers_.size()),
              std::min<std::size_t>(max_size,
                buffers_.max_size() - buffers_.size()));
        for (;;)
        {
          stream_.async_read_some(buffers_.prepare(bytes_available),
              BOOST_ASIO_MOVE_CAST(read_dynbuf_v1_op)(*this));
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
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
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
  inline void* asio_handler_allocate(std::size_t size,
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v1, typename CompletionCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_dynbuf_v1_op<AsyncReadStream, DynamicBuffer_v1,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename CompletionCondition, typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_dynbuf_v1_op<AsyncReadStream,
      DynamicBuffer_v1, CompletionCondition, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_dynbuf_v1_op<AsyncReadStream,
        DynamicBuffer_v1, CompletionCondition, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    typename CompletionCondition, typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_dynbuf_v1_op<AsyncReadStream,
      DynamicBuffer_v1, CompletionCondition, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_dynbuf_v1_op<AsyncReadStream,
        DynamicBuffer_v1, CompletionCondition, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return async_read(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
}

template <typename AsyncReadStream,
    typename DynamicBuffer_v1, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_dynbuf_v1<AsyncReadStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_read(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
}

template <typename AsyncReadStream,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_read(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition),
      BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

namespace detail
{
  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename ReadHandler>
  class read_dynbuf_v2_op
    : detail::base_from_completion_cond<CompletionCondition>
  {
  public:
    template <typename BufferSequence>
    read_dynbuf_v2_op(AsyncReadStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        CompletionCondition& completion_condition, ReadHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
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
      : detail::base_from_completion_cond<CompletionCondition>(other),
        stream_(other.stream_),
        buffers_(other.buffers_),
        start_(other.start_),
        total_transferred_(other.total_transferred_),
        bytes_available_(other.bytes_available_),
        handler_(other.handler_)
    {
    }

    read_dynbuf_v2_op(read_dynbuf_v2_op&& other)
      : detail::base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(detail::base_from_completion_cond<
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

    void operator()(const boost::system::error_code& ec,
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
          stream_.async_read_some(buffers_.data(pos, bytes_available_),
              BOOST_ASIO_MOVE_CAST(read_dynbuf_v2_op)(*this));
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
        }

        handler_(ec, static_cast<const std::size_t&>(total_transferred_));
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
  inline void* asio_handler_allocate(std::size_t size,
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
        CompletionCondition, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncReadStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncReadStream,
      typename DynamicBuffer_v2, typename CompletionCondition,
      typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      read_dynbuf_v2_op<AsyncReadStream, DynamicBuffer_v2,
        CompletionCondition, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename CompletionCondition, typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::read_dynbuf_v2_op<AsyncReadStream,
      DynamicBuffer_v2, CompletionCondition, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::read_dynbuf_v2_op<AsyncReadStream,
        DynamicBuffer_v2, CompletionCondition, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    typename CompletionCondition, typename ReadHandler, typename Executor>
struct associated_executor<
    detail::read_dynbuf_v2_op<AsyncReadStream,
      DynamicBuffer_v2, CompletionCondition, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::read_dynbuf_v2_op<AsyncReadStream,
        DynamicBuffer_v2, CompletionCondition, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return async_read(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
}

template <typename AsyncReadStream,
    typename DynamicBuffer_v2, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_read_dynbuf_v2<AsyncReadStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_READ_HPP

/* read.hpp
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
*/