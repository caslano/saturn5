//
// impl/write_at.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_WRITE_AT_HPP
#define BOOST_ASIO_IMPL_WRITE_AT_HPP

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
  template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence,
      typename ConstBufferIterator, typename CompletionCondition>
  std::size_t write_at_buffer_sequence(SyncRandomAccessWriteDevice& d,
      uint64_t offset, const ConstBufferSequence& buffers,
      const ConstBufferIterator&, CompletionCondition completion_condition,
      boost::system::error_code& ec)
  {
    ec = boost::system::error_code();
    boost::asio::detail::consuming_buffers<const_buffer,
        ConstBufferSequence, ConstBufferIterator> tmp(buffers);
    while (!tmp.empty())
    {
      if (std::size_t max_size = detail::adapt_completion_condition_result(
            completion_condition(ec, tmp.total_consumed())))
      {
        tmp.consume(d.write_some_at(offset + tmp.total_consumed(),
              tmp.prepare(max_size), ec));
      }
      else
        break;
    }
    return tmp.total_consumed();
  }
} // namespace detail

template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  return detail::write_at_buffer_sequence(d, offset, buffers,
      boost::asio::buffer_sequence_begin(buffers),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
}

template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence>
inline std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write_at(
      d, offset, buffers, transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "write_at");
  return bytes_transferred;
}

template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence>
inline std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    boost::system::error_code& ec)
{
  return write_at(d, offset, buffers, transfer_all(), ec);
}

template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence,
    typename CompletionCondition>
inline std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write_at(d, offset, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "write_at");
  return bytes_transferred;
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

template <typename SyncRandomAccessWriteDevice, typename Allocator,
    typename CompletionCondition>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec)
{
  std::size_t bytes_transferred = write_at(d, offset, b.data(),
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  b.consume(bytes_transferred);
  return bytes_transferred;
}

template <typename SyncRandomAccessWriteDevice, typename Allocator>
inline std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write_at(d, offset, b, transfer_all(), ec);
  boost::asio::detail::throw_error(ec, "write_at");
  return bytes_transferred;
}

template <typename SyncRandomAccessWriteDevice, typename Allocator>
inline std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    boost::system::error_code& ec)
{
  return write_at(d, offset, b, transfer_all(), ec);
}

template <typename SyncRandomAccessWriteDevice, typename Allocator,
    typename CompletionCondition>
inline std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition)
{
  boost::system::error_code ec;
  std::size_t bytes_transferred = write_at(d, offset, b,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition), ec);
  boost::asio::detail::throw_error(ec, "write_at");
  return bytes_transferred;
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

namespace detail
{
  template <typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  class write_at_op
    : public base_from_cancellation_state<WriteHandler>,
      base_from_completion_cond<CompletionCondition>
  {
  public:
    write_at_op(AsyncRandomAccessWriteDevice& device,
        uint64_t offset, const ConstBufferSequence& buffers,
        CompletionCondition& completion_condition, WriteHandler& handler)
      : base_from_cancellation_state<WriteHandler>(
          handler, enable_partial_cancellation()),
        base_from_completion_cond<CompletionCondition>(completion_condition),
        device_(device),
        offset_(offset),
        buffers_(buffers),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    write_at_op(const write_at_op& other)
      : base_from_cancellation_state<WriteHandler>(other),
        base_from_completion_cond<CompletionCondition>(other),
        device_(other.device_),
        offset_(other.offset_),
        buffers_(other.buffers_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    write_at_op(write_at_op&& other)
      : base_from_cancellation_state<WriteHandler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            WriteHandler>)(other)),
        base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(base_from_completion_cond<
            CompletionCondition>)(other)),
        device_(other.device_),
        offset_(other.offset_),
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
            BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, "async_write_at"));
            device_.async_write_some_at(
                offset_ + buffers_.total_consumed(), buffers_.prepare(max_size),
                BOOST_ASIO_MOVE_CAST(write_at_op)(*this));
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

        BOOST_ASIO_MOVE_OR_LVALUE(WriteHandler)(handler_)(
            static_cast<const boost::system::error_code&>(ec),
            static_cast<const std::size_t&>(buffers_.total_consumed()));
      }
    }

  //private:
    typedef boost::asio::detail::consuming_buffers<const_buffer,
        ConstBufferSequence, ConstBufferIterator> buffers_type;

    AsyncRandomAccessWriteDevice& device_;
    uint64_t offset_;
    buffers_type buffers_;
    int start_;
    WriteHandler handler_;
  };

  template <typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
    return this_handler->start_ == 0 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline void start_write_at_buffer_sequence_op(AsyncRandomAccessWriteDevice& d,
      uint64_t offset, const ConstBufferSequence& buffers,
      const ConstBufferIterator&, CompletionCondition& completion_condition,
      WriteHandler& handler)
  {
    detail::write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
      ConstBufferIterator, CompletionCondition, WriteHandler>(
        d, offset, buffers, completion_condition, handler)(
          boost::system::error_code(), 0, 1);
  }

  template <typename AsyncRandomAccessWriteDevice>
  class initiate_async_write_at_buffer_sequence
  {
  public:
    typedef typename AsyncRandomAccessWriteDevice::executor_type executor_type;

    explicit initiate_async_write_at_buffer_sequence(
        AsyncRandomAccessWriteDevice& device)
      : device_(device)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return device_.get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence,
        typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        uint64_t offset, const ConstBufferSequence& buffers,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_cond) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      non_const_lvalue<WriteHandler> handler2(handler);
      non_const_lvalue<CompletionCondition> completion_cond2(completion_cond);
      start_write_at_buffer_sequence_op(device_, offset, buffers,
          boost::asio::buffer_sequence_begin(buffers),
          completion_cond2.value, handler2.value);
    }

  private:
    AsyncRandomAccessWriteDevice& device_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
    typename ConstBufferIterator, typename CompletionCondition,
    typename WriteHandler, typename DefaultCandidate>
struct associator<Associator,
    detail::write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
      ConstBufferIterator, CompletionCondition, WriteHandler>,
    DefaultCandidate>
  : Associator<WriteHandler, DefaultCandidate>
{
  static typename Associator<WriteHandler, DefaultCandidate>::type get(
      const detail::write_at_op<AsyncRandomAccessWriteDevice,
        ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<WriteHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncRandomAccessWriteDevice,
    typename ConstBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token)
{
  return async_initiate<WriteToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_at_buffer_sequence<
        AsyncRandomAccessWriteDevice>(d),
      token, offset, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteToken) token)
{
  return async_initiate<WriteToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_at_buffer_sequence<
        AsyncRandomAccessWriteDevice>(d),
      token, offset, buffers, transfer_all());
}

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

namespace detail
{
  template <typename Allocator, typename WriteHandler>
  class write_at_streambuf_op
  {
  public:
    write_at_streambuf_op(
        boost::asio::basic_streambuf<Allocator>& streambuf,
        WriteHandler& handler)
      : streambuf_(streambuf),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    write_at_streambuf_op(const write_at_streambuf_op& other)
      : streambuf_(other.streambuf_),
        handler_(other.handler_)
    {
    }

    write_at_streambuf_op(write_at_streambuf_op&& other)
      : streambuf_(other.streambuf_),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        const std::size_t bytes_transferred)
    {
      streambuf_.consume(bytes_transferred);
      BOOST_ASIO_MOVE_OR_LVALUE(WriteHandler)(handler_)(ec, bytes_transferred);
    }

  //private:
    boost::asio::basic_streambuf<Allocator>& streambuf_;
    WriteHandler handler_;
  };

  template <typename Allocator, typename WriteHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Allocator, typename WriteHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Allocator, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }

  template <typename Function, typename Allocator, typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename Allocator, typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename AsyncRandomAccessWriteDevice>
  class initiate_async_write_at_streambuf
  {
  public:
    typedef typename AsyncRandomAccessWriteDevice::executor_type executor_type;

    explicit initiate_async_write_at_streambuf(
        AsyncRandomAccessWriteDevice& device)
      : device_(device)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return device_.get_executor();
    }

    template <typename WriteHandler,
        typename Allocator, typename CompletionCondition>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        uint64_t offset, basic_streambuf<Allocator>* b,
        BOOST_ASIO_MOVE_ARG(CompletionCondition) completion_condition) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      non_const_lvalue<WriteHandler> handler2(handler);
      async_write_at(device_, offset, b->data(),
          BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition),
          write_at_streambuf_op<Allocator, typename decay<WriteHandler>::type>(
            *b, handler2.value));
    }

  private:
    AsyncRandomAccessWriteDevice& device_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename Executor, typename WriteHandler, typename DefaultCandidate>
struct associator<Associator,
    detail::write_at_streambuf_op<Executor, WriteHandler>,
    DefaultCandidate>
  : Associator<WriteHandler, DefaultCandidate>
{
  static typename Associator<WriteHandler, DefaultCandidate>::type get(
      const detail::write_at_streambuf_op<Executor, WriteHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<WriteHandler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncRandomAccessWriteDevice,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token)
{
  return async_initiate<WriteToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_at_streambuf<
        AsyncRandomAccessWriteDevice>(d),
      token, offset, &b,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncRandomAccessWriteDevice, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteToken) token)
{
  return async_initiate<WriteToken,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_at_streambuf<
        AsyncRandomAccessWriteDevice>(d),
      token, offset, &b, transfer_all());
}

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_WRITE_AT_HPP

/* write_at.hpp
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
*/