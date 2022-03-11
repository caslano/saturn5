//
// impl/write_at.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_WRITE_AT_HPP
#define BOOST_ASIO_IMPL_WRITE_AT_HPP

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
    return tmp.total_consumed();;
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
    : detail::base_from_completion_cond<CompletionCondition>
  {
  public:
    write_at_op(AsyncRandomAccessWriteDevice& device,
        uint64_t offset, const ConstBufferSequence& buffers,
        CompletionCondition& completion_condition, WriteHandler& handler)
      : detail::base_from_completion_cond<
          CompletionCondition>(completion_condition),
        device_(device),
        offset_(offset),
        buffers_(buffers),
        start_(0),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    write_at_op(const write_at_op& other)
      : detail::base_from_completion_cond<CompletionCondition>(other),
        device_(other.device_),
        offset_(other.offset_),
        buffers_(other.buffers_),
        start_(other.start_),
        handler_(other.handler_)
    {
    }

    write_at_op(write_at_op&& other)
      : detail::base_from_completion_cond<CompletionCondition>(
          BOOST_ASIO_MOVE_CAST(detail::base_from_completion_cond<
            CompletionCondition>)(other)),
        device_(other.device_),
        offset_(other.offset_),
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
          device_.async_write_some_at(
              offset_ + buffers_.total_consumed(), buffers_.prepare(max_size),
              BOOST_ASIO_MOVE_CAST(write_at_op)(*this));
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

    AsyncRandomAccessWriteDevice& device_;
    uint64_t offset_;
    buffers_type buffers_;
    int start_;
    WriteHandler handler_;
  };

  template <typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename AsyncRandomAccessWriteDevice,
      typename ConstBufferSequence, typename ConstBufferIterator,
      typename CompletionCondition, typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
        ConstBufferIterator, CompletionCondition, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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

template <typename AsyncRandomAccessWriteDevice,
    typename ConstBufferSequence, typename ConstBufferIterator,
    typename CompletionCondition, typename WriteHandler, typename Allocator>
struct associated_allocator<
    detail::write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
      ConstBufferIterator, CompletionCondition, WriteHandler>,
    Allocator>
{
  typedef typename associated_allocator<WriteHandler, Allocator>::type type;

  static type get(
      const detail::write_at_op<AsyncRandomAccessWriteDevice,
        ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<WriteHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename AsyncRandomAccessWriteDevice,
    typename ConstBufferSequence, typename ConstBufferIterator,
    typename CompletionCondition, typename WriteHandler, typename Executor>
struct associated_executor<
    detail::write_at_op<AsyncRandomAccessWriteDevice, ConstBufferSequence,
      ConstBufferIterator, CompletionCondition, WriteHandler>,
    Executor>
{
  typedef typename associated_executor<WriteHandler, Executor>::type type;

  static type get(
      const detail::write_at_op<AsyncRandomAccessWriteDevice,
        ConstBufferSequence, ConstBufferIterator,
        CompletionCondition, WriteHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<WriteHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncRandomAccessWriteDevice,
    typename ConstBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_at_buffer_sequence<
        AsyncRandomAccessWriteDevice>(d),
      handler, offset, buffers,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_at_buffer_sequence<
        AsyncRandomAccessWriteDevice>(d),
      handler, offset, buffers, transfer_all());
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
      handler_(ec, bytes_transferred);
    }

  //private:
    boost::asio::basic_streambuf<Allocator>& streambuf_;
    WriteHandler handler_;
  };

  template <typename Allocator, typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename Allocator, typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename Allocator, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
  }

  template <typename Function, typename Allocator, typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename Allocator, typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      write_at_streambuf_op<Allocator, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
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

template <typename Allocator, typename WriteHandler, typename Allocator1>
struct associated_allocator<
    detail::write_at_streambuf_op<Allocator, WriteHandler>,
    Allocator1>
{
  typedef typename associated_allocator<WriteHandler, Allocator1>::type type;

  static type get(
      const detail::write_at_streambuf_op<Allocator, WriteHandler>& h,
      const Allocator1& a = Allocator1()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<WriteHandler, Allocator1>::get(h.handler_, a);
  }
};

template <typename Executor, typename WriteHandler, typename Executor1>
struct associated_executor<
    detail::write_at_streambuf_op<Executor, WriteHandler>,
    Executor1>
{
  typedef typename associated_executor<WriteHandler, Executor1>::type type;

  static type get(
      const detail::write_at_streambuf_op<Executor, WriteHandler>& h,
      const Executor1& ex = Executor1()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<WriteHandler, Executor1>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename AsyncRandomAccessWriteDevice,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_at_streambuf<
        AsyncRandomAccessWriteDevice>(d),
      handler, offset, &b,
      BOOST_ASIO_MOVE_CAST(CompletionCondition)(completion_condition));
}

template <typename AsyncRandomAccessWriteDevice, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_write_at_streambuf<
        AsyncRandomAccessWriteDevice>(d),
      handler, offset, &b, transfer_all());
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