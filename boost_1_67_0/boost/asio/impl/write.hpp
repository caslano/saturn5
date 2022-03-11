//
// impl/write.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_WRITE_HPP
#define BOOST_ASIO_IMPL_WRITE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

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

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  template <typename SyncWriteStream, typename ConstBufferSequence,
      typename ConstBufferIterator, typename CompletionCondition>
  std::size_t write_buffer_sequence(SyncWriteStream& s,
      const ConstBufferSequence& buffers, const ConstBufferIterator&,
      CompletionCondition completion_condition, boost::system::error_code& ec)
  {
    ec = boost::system::error_code();
    boost::asio::detail::consuming_buffers<const_buffer,
        ConstBufferSequence, ConstBufferIterator> tmp(buffers);
    while (!tmp.empty())
    {
      if (std::size_t max_size = detail::adapt_completion_condition_result(
            completion_condition(ec, tmp.total_consumed())))
        tmp.consume(s.write_some(tmp.prepare(max_size), ec));
      else
        break;
    }
    return tmp.total_consumed();;
  }
} // namespace detail

template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type*)
{
  return detail::write_buffer_sequence(s, buffers,
      boost::asio::buffer_sequence_begin(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
}

template <typename SyncWriteStream, typename ConstBufferSequence>
inline std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write(s, buffers, transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "write");
  return bytes_transferred;
}

template <typename SyncWriteStream, typename ConstBufferSequence>
inline std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    boost::system::error_code& ec,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type*)
{
  return write(s, buffers, transfer_all(), ec);
}

template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write(s, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "write");
  return bytes_transferred;
}

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

template <typename SyncWriteStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  typename decay<DynamicBuffer_v1>::type b(
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers));

  std::size_t bytes_transferred = write(s, b.data(),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  b.consume(bytes_transferred);
  return bytes_transferred;
}

template <typename SyncWriteStream, typename DynamicBuffer_v1>
inline std::size_t write(SyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "write");
  return bytes_transferred;
}

template <typename SyncWriteStream, typename DynamicBuffer_v1>
inline std::size_t write(SyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return write(s, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), ec);
}

template <typename SyncWriteStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "write");
  return bytes_transferred;
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename SyncWriteStream, typename Allocator,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  return write(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
}

template <typename SyncWriteStream, typename Allocator>
inline std::size_t write(SyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b)
{
  return write(s, basic_streambuf_ref<Allocator>(b));
}

template <typename SyncWriteStream, typename Allocator>
inline std::size_t write(SyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    boost::system::error_code& ec)
{
  return write(s, basic_streambuf_ref<Allocator>(b), ec);
}

template <typename SyncWriteStream, typename Allocator,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition)
{
  return write(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

template <typename SyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  std::size_t bytes_transferred = write(s, buffers.data(0, buffers.size()),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  buffers.consume(bytes_transferred);
  return bytes_transferred;
}

template <typename SyncWriteStream, typename DynamicBuffer_v2>
inline std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "write");
  return bytes_transferred;
}

template <typename SyncWriteStream, typename DynamicBuffer_v2>
inline std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return write(s, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), ec);
}

template <typename SyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "write");
  return bytes_transferred;
}

namespace detail
{
  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename ConstBufferIterator, typename CompletionCondition,
      typename WriteHandler>
  class write_op
    : detail::base_from_completion_cond<CompletionCondition>
  {
  public:
    write_op(AsyncWriteStream& stream, const ConstBufferSequence& buffers,
        CompletionCondition& completion_condition, WriteHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(buffers),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    write_op(const write_op& other)
      : detail::base_from_completion_cond<CompletionCondition>(other),
        stream_(other.stream_),
        buffers_(other.buffers_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    write_op(write_op&& other)
      : detail::base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(detail::base_from_completion_cond<
            CompletionCondition>)(other)),
        stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(buffers_type)(other.buffers_)),
        start_(other.start_),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(other.handler_))
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
          stream_.async_write_some(buffers_.prepare(max_size),
              BOOST_ASIO_MOVE_CAST(write_op)(*this));
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
    typedef boost::asio::detail::consuming_buffers<const_buffer,
        ConstBufferSequence, ConstBufferIterator> buffers_type;

    AsyncWriteStream& stream_;
    buffers_type buffers_;
    int start_;
    WriteHandler handler_;
  };

  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename ConstBufferIterator, typename CompletionCondition,
      typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename ConstBufferIterator, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename ConstBufferIterator, typename CompletionCondition,
      typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncWriteStream,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncWriteStream,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename ConstBufferIterator, typename CompletionCondition,
      typename WriteHandler>
  inline void start_write_buffer_sequence_op(AsyncWriteStream& stream,
      const ConstBufferSequence& buffers, const ConstBufferIterator&,
      CompletionCondition& completion_condition, WriteHandler& handler)
  {
    detail::write_op<AsyncWriteStream, ConstBufferSequence,
      ConstBufferIterator, CompletionCondition, WriteHandler>(
        stream, buffers, completion_condition, handler)(
          boost::system::error_code(), 0, 1);
  }

  template <typename AsyncWriteStream>
  class initiate_async_write_buffer_sequence
  {
  public:
    typedef typename AsyncWriteStream::executor_type executor_type;

    explicit initiate_async_write_buffer_sequence(AsyncWriteStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence,
        typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        const ConstBufferSequence& buffers,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      non_const_lvalue<WriteHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      start_write_buffer_sequence_op(stream_, buffers,
          boost::asio::buffer_sequence_begin(buffers),
          completion_cond2.value, handler2.value);
    }

  private:
    AsyncWriteStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream, typename ConstBufferSequence,
    typename ConstBufferIterator, typename CompletionCondition,
    typename WriteHandler, typename Allocator>
struct associated_allocator<
    detail::write_op<AsyncWriteStream, ConstBufferSequence,
      ConstBufferIterator, CompletionCondition, WriteHandler>,
    Allocator>
{
  typedef typename associated_allocator<WriteHandler, Allocator>::type type;

  static type get(
      const detail::write_op<AsyncWriteStream, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<WriteHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncWriteStream, typename ConstBufferSequence,
    typename ConstBufferIterator, typename CompletionCondition,
    typename WriteHandler, typename Executor>
struct associated_executor<
    detail::write_op<AsyncWriteStream, ConstBufferSequence,
      ConstBufferIterator, CompletionCondition, WriteHandler>,
    Executor>
{
  typedef typename associated_executor<WriteHandler, Executor>::type type;

  static type get(
      const detail::write_op<AsyncWriteStream, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<WriteHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream,
    typename ConstBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type*)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_buffer_sequence<AsyncWriteStream>(s),
      handler, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncWriteStream, typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type*)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_buffer_sequence<AsyncWriteStream>(s),
      handler, buffers, transfer_all());
}

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

namespace detail
{
  template <typename AsyncWriteStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename WriteHandler>
  class write_dynbuf_v1_op
  {
  public:
    template <typename BufferSequence>
    write_dynbuf_v1_op(AsyncWriteStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        CompletionCondition& completion_condition, WriteHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        completion_condition_(
          BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition)),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    write_dynbuf_v1_op(const write_dynbuf_v1_op& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        completion_condition_(other.completion_condition_),
        handler_(other.handler_)
    {
    }

    write_dynbuf_v1_op(write_dynbuf_v1_op&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(other.buffers_)),
        completion_condition_(
          BOOST_ASIO_MOVE_CAST(CompletionCondition)(
            other.completion_condition_)),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      switch (start)
      {
        case 1:
        async_write(stream_, buffers_.data(),
            BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition_),
            BOOST_ASIO_MOVE_CAST(write_dynbuf_v1_op)(*this));
        return; default:
        buffers_.consume(bytes_transferred);
        handler_(ec, static_cast<const std::size_t&>(bytes_transferred));
      }
    }

  //private:
    AsyncWriteStream& stream_;
    DynamicBuffer_v1 buffers_;
    CompletionCondition completion_condition_;
    WriteHandler handler_;
  };

  template <typename AsyncWriteStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncWriteStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncWriteStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }

  template <typename Function, typename AsyncWriteStream,
      typename DynamicBuffer_v1, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncWriteStream,
      typename DynamicBuffer_v1, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncWriteStream>
  class initiate_async_write_dynbuf_v1
  {
  public:
    typedef typename AsyncWriteStream::executor_type executor_type;

    explicit initiate_async_write_dynbuf_v1(AsyncWriteStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename WriteHandler, typename DynamicBuffer_v1,
        typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      non_const_lvalue<WriteHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      write_dynbuf_v1_op<AsyncWriteStream,
        typename decay<DynamicBuffer_v1>::type,
          CompletionCondition, typename decay<WriteHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
              completion_cond2.value, handler2.value)(
                boost::system::error_code(), 0, 1);
    }

  private:
    AsyncWriteStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream, typename DynamicBuffer_v1,
    typename CompletionCondition, typename WriteHandler, typename Allocator>
struct associated_allocator<
    detail::write_dynbuf_v1_op<AsyncWriteStream,
      DynamicBuffer_v1, CompletionCondition, WriteHandler>,
    Allocator>
{
  typedef typename associated_allocator<WriteHandler, Allocator>::type type;

  static type get(
      const detail::write_dynbuf_v1_op<AsyncWriteStream,
        DynamicBuffer_v1, CompletionCondition, WriteHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<WriteHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncWriteStream, typename DynamicBuffer_v1,
    typename CompletionCondition, typename WriteHandler, typename Executor>
struct associated_executor<
    detail::write_dynbuf_v1_op<AsyncWriteStream,
      DynamicBuffer_v1, CompletionCondition, WriteHandler>,
    Executor>
{
  typedef typename associated_executor<WriteHandler, Executor>::type type;

  static type get(
      const detail::write_dynbuf_v1_op<AsyncWriteStream,
        DynamicBuffer_v1, CompletionCondition, WriteHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<WriteHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return async_write(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
}

template <typename AsyncWriteStream,
    typename DynamicBuffer_v1, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type*)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_dynbuf_v1<AsyncWriteStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncWriteStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  return async_write(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
}

template <typename AsyncWriteStream,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  return async_write(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition),
      BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

namespace detail
{
  template <typename AsyncWriteStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename WriteHandler>
  class write_dynbuf_v2_op
  {
  public:
    template <typename BufferSequence>
    write_dynbuf_v2_op(AsyncWriteStream& stream,
        BOOST_ASIO_MOVE_ARG(BufferSequence) buffers,
        CompletionCondition& completion_condition, WriteHandler& handler)
      : stream_(stream),
        buffers_(BOOST_ASIO_MOVE_CAST(BufferSequence)(buffers)),
        completion_condition_(
          BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition)),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    write_dynbuf_v2_op(const write_dynbuf_v2_op& other)
      : stream_(other.stream_),
        buffers_(other.buffers_),
        completion_condition_(other.completion_condition_),
        handler_(other.handler_)
    {
    }

    write_dynbuf_v2_op(write_dynbuf_v2_op&& other)
      : stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(other.buffers_)),
        completion_condition_(
          BOOST_ASIO_MOVE_CAST(CompletionCondition)(
            other.completion_condition_)),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        std::size_t bytes_transferred, int start = 0)
    {
      switch (start)
      {
        case 1:
        async_write(stream_, buffers_.data(0, buffers_.size()),
            BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition_),
            BOOST_ASIO_MOVE_CAST(write_dynbuf_v2_op)(*this));
        return; default:
        buffers_.consume(bytes_transferred);
        handler_(ec, static_cast<const std::size_t&>(bytes_transferred));
      }
    }

  //private:
    AsyncWriteStream& stream_;
    DynamicBuffer_v2 buffers_;
    CompletionCondition completion_condition_;
    WriteHandler handler_;
  };

  template <typename AsyncWriteStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncWriteStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename AsyncWriteStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }

  template <typename Function, typename AsyncWriteStream,
      typename DynamicBuffer_v2, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncWriteStream,
      typename DynamicBuffer_v2, typename CompletionCondition,
      typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename AsyncWriteStream>
  class initiate_async_write_dynbuf_v2
  {
  public:
    typedef typename AsyncWriteStream::executor_type executor_type;

    explicit initiate_async_write_dynbuf_v2(AsyncWriteStream& stream)
      : stream_(stream)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return stream_.get_executor();
    }

    template <typename WriteHandler, typename DynamicBuffer_v2,
        typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        BOOST_ASIO_MOVE_ARG(DynamicBuffer_v2) buffers,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      non_const_lvalue<WriteHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      write_dynbuf_v2_op<AsyncWriteStream,
        typename decay<DynamicBuffer_v2>::type,
          CompletionCondition, typename decay<WriteHandler>::type>(
            stream_, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
              completion_cond2.value, handler2.value)(
                boost::system::error_code(), 0, 1);
    }

  private:
    AsyncWriteStream& stream_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition, typename WriteHandler, typename Allocator>
struct associated_allocator<
    detail::write_dynbuf_v2_op<AsyncWriteStream,
      DynamicBuffer_v2, CompletionCondition, WriteHandler>,
    Allocator>
{
  typedef typename associated_allocator<WriteHandler, Allocator>::type type;

  static type get(
      const detail::write_dynbuf_v2_op<AsyncWriteStream,
        DynamicBuffer_v2, CompletionCondition, WriteHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<WriteHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition, typename WriteHandler, typename Executor>
struct associated_executor<
    detail::write_dynbuf_v2_op<AsyncWriteStream,
      DynamicBuffer_v2, CompletionCondition, WriteHandler>,
    Executor>
{
  typedef typename associated_executor<WriteHandler, Executor>::type type;

  static type get(
      const detail::write_dynbuf_v2_op<AsyncWriteStream,
        DynamicBuffer_v2, CompletionCondition, WriteHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<WriteHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return async_write(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
}

template <typename AsyncWriteStream,
    typename DynamicBuffer_v2, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type*)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_dynbuf_v2<AsyncWriteStream>(s),
      handler, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_WRITE_HPP

/* write.hpp
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
*/