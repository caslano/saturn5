//
// impl/write.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_WRITE_HPP
#define BOOST_ASIO_IMPL_WRITE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

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
    return tmp.total_consumed();
  }
} // namespace detail

template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type)
{
  return detail::write_buffer_sequence(s, buffers,
      boost::asio::buffer_sequence_begin(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
}

template <typename SyncWriteStream, typename ConstBufferSequence>
inline std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write(s, buffers, transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "write");
  return bytes_transferred;
}

template <typename SyncWriteStream, typename ConstBufferSequence>
inline std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    boost::system::error_code& ec,
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type)
{
  return write(s, buffers, transfer_all(), ec);
}

template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type)
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
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
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
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
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
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  return write(s, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), ec);
}

template <typename SyncWriteStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s,
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
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  std::size_t bytes_transferred = write(s, buffers.data(0, buffers.size()),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  buffers.consume(bytes_transferred);
  return bytes_transferred;
}

template <typename SyncWriteStream, typename DynamicBuffer_v2>
inline std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
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
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  return write(s, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), ec);
}

template <typename SyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
inline std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
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
    : public base_from_cancellation_state<WriteHandler>,
      base_from_completion_cond<CompletionCondition>
  {
  public:
    write_op(AsyncWriteStream& stream, const ConstBufferSequence& buffers,
        CompletionCondition& completion_condition, WriteHandler& handler)
      : base_from_cancellation_state<WriteHandler>(
          handler, enable_partial_cancellation()),
        base_from_completion_cond<CompletionCondition>(completion_condition),
        stream_(stream),
        buffers_(buffers),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    write_op(const write_op& other)
      : base_from_cancellation_state<WriteHandler>(other),
        base_from_completion_cond<CompletionCondition>(other),
        stream_(other.stream_),
        buffers_(other.buffers_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    write_op(write_op&& other)
      : base_from_cancellation_state<WriteHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            WriteHandler>)(other)),
        base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(base_from_completion_cond<
            CompletionCondition>)(other)),
        stream_(other.stream_),
        buffers_(BOOST_ASIO_MOVE_CAST(buffers_type)(other.buffers_)),
        start_(other.start_),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(other.handler_))
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
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_write"));
            stream_.async_write_some(buffers_.prepare(max_size),
                BOOST_ASIO_MOVE_CAST(write_op)(*this));
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

        BOOST_ASIO_MOVE_OR_LVALUE(WriteHandler)(handler_)(
            static_cast<const boost::system::error_code&>(ec),
            static_cast<const std::size_t&>(buffers_.total_consumed()));
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
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncWriteStream, typename ConstBufferSequence,
      typename ConstBufferIterator, typename CompletionCondition,
      typename WriteHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncWriteStream,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      write_op<AsyncWriteStream, ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename AsyncWriteStream, typename ConstBufferSequence,
    typename ConstBufferIterator, typename CompletionCondition,
    typename WriteHandler, typename DefaultCandidate>
struct associator<Associator,
    detail::write_op<AsyncWriteStream, ConstBufferSequence,
      ConstBufferIterator, CompletionCondition, WriteHandler>,
    DefaultCandidate>
  : Associator<WriteHandler, DefaultCandidate>
{
  static typename Associator<WriteHandler, DefaultCandidate>::type get(
      const detail::write_op<AsyncWriteStream, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<WriteHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream,
    typename ConstBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type)
{
  return async_initiate<WriteToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_buffer_sequence<AsyncWriteStream>(s),
      token, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncWriteStream, typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type)
{
  return async_initiate<WriteToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_buffer_sequence<AsyncWriteStream>(s),
      token, buffers, transfer_all());
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
        BOOST_ASIO_MOVE_OR_LVALUE(WriteHandler)(handler_)(ec,
            static_cast<const std::size_t&>(bytes_transferred));
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
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncWriteStream, typename DynamicBuffer_v1,
      typename CompletionCondition, typename WriteHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncWriteStream,
      typename DynamicBuffer_v1, typename CompletionCondition,
      typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      write_dynbuf_v1_op<AsyncWriteStream, DynamicBuffer_v1,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename AsyncWriteStream, typename DynamicBuffer_v1,
    typename CompletionCondition, typename WriteHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::write_dynbuf_v1_op<AsyncWriteStream,
      DynamicBuffer_v1, CompletionCondition, WriteHandler>,
    DefaultCandidate>
  : Associator<WriteHandler, DefaultCandidate>
{
  static typename Associator<WriteHandler, DefaultCandidate>::type get(
      const detail::write_dynbuf_v1_op<AsyncWriteStream,
        DynamicBuffer_v1, CompletionCondition, WriteHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<WriteHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  return async_write(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      transfer_all(), BOOST_ASIO_MOVE_CAST(WriteToken)(token));
}

template <typename AsyncWriteStream,
    typename DynamicBuffer_v1, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type)
{
  return async_initiate<WriteToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_dynbuf_v1<AsyncWriteStream>(s),
      token, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v1)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename AsyncWriteStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteToken) token)
{
  return async_write(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(WriteToken)(token));
}

template <typename AsyncWriteStream,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token)
{
  return async_write(s, basic_streambuf_ref<Allocator>(b),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition),
      BOOST_ASIO_MOVE_CAST(WriteToken)(token));
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
        BOOST_ASIO_MOVE_OR_LVALUE(WriteHandler)(handler_)(ec,
            static_cast<const std::size_t&>(bytes_transferred));
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
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncWriteStream, typename DynamicBuffer_v2,
      typename CompletionCondition, typename WriteHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncWriteStream,
      typename DynamicBuffer_v2, typename CompletionCondition,
      typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      write_dynbuf_v2_op<AsyncWriteStream, DynamicBuffer_v2,
        CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename AsyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition, typename WriteHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::write_dynbuf_v2_op<AsyncWriteStream,
      DynamicBuffer_v2, CompletionCondition, WriteHandler>,
    DefaultCandidate>
  : Associator<WriteHandler, DefaultCandidate>
{
  static typename Associator<WriteHandler, DefaultCandidate>::type get(
      const detail::write_dynbuf_v2_op<AsyncWriteStream,
        DynamicBuffer_v2, CompletionCondition, WriteHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<WriteHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

template <typename AsyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition, typename WriteHandler,
    typename CancellationSlot>
struct associated_cancellation_slot<
    detail::write_dynbuf_v2_op<AsyncWriteStream,
      DynamicBuffer_v2, CompletionCondition, WriteHandler>,
    CancellationSlot>
  : detail::associated_cancellation_slot_forwarding_base<
      WriteHandler, CancellationSlot>
{
  typedef typename associated_cancellation_slot<
      WriteHandler, CancellationSlot>::type type;

  static type get(
      const detail::write_dynbuf_v2_op<AsyncWriteStream,
        DynamicBuffer_v2, CompletionCondition, WriteHandler>& h,
      const CancellationSlot& s = CancellationSlot()) BOOST_ASIO_NOEXCEPT
  {
    return associated_cancellation_slot<WriteHandler,
        CancellationSlot>::get(h.handler_, s);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncWriteStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  return async_write(s,
      BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      transfer_all(), BOOST_ASIO_MOVE_CAST(WriteToken)(token));
}

template <typename AsyncWriteStream,
    typename DynamicBuffer_v2, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type)
{
  return async_initiate<WriteToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_dynbuf_v2<AsyncWriteStream>(s),
      token, BOOST_ASIO_MOVE_CAST(DynamicBuffer_v2)(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_WRITE_HPP

/* write.hpp
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
*/