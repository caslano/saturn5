//
// impl/buffered_write_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_BUFFERED_WRITE_STREAM_HPP
#define BOOST_ASIO_IMPL_BUFFERED_WRITE_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

template <typename Stream>
std::size_t buffered_write_stream<Stream>::flush()
{
  std::size_t bytes_written = write(next_layer_,
      buffer(storage_.data(), storage_.size()));
  storage_.consume(bytes_written);
  return bytes_written;
}

template <typename Stream>
std::size_t buffered_write_stream<Stream>::flush(boost::system::error_code& ec)
{
  std::size_t bytes_written = write(next_layer_,
      buffer(storage_.data(), storage_.size()),
      transfer_all(), ec);
  storage_.consume(bytes_written);
  return bytes_written;
}

namespace detail
{
  template <typename WriteHandler>
  class buffered_flush_handler
  {
  public:
    buffered_flush_handler(detail::buffered_stream_storage& storage,
        WriteHandler& handler)
      : storage_(storage),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    buffered_flush_handler(const buffered_flush_handler& other)
      : storage_(other.storage_),
        handler_(other.handler_)
    {
    }

    buffered_flush_handler(buffered_flush_handler&& other)
      : storage_(other.storage_),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        const std::size_t bytes_written)
    {
      storage_.consume(bytes_written);
      handler_(ec, bytes_written);
    }

  //private:
    detail::buffered_stream_storage& storage_;
    WriteHandler handler_;
  };

  template <typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename WriteHandler>
  inline bool asio_handler_is_continuation(
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Stream>
  class initiate_async_buffered_flush
  {
  public:
    typedef typename remove_reference<
      Stream>::type::lowest_layer_type::executor_type executor_type;

    explicit initiate_async_buffered_flush(
        typename remove_reference<Stream>::type& next_layer)
      : next_layer_(next_layer)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return next_layer_.lowest_layer().get_executor();
    }

    template <typename WriteHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        buffered_stream_storage* storage) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      non_const_lvalue<WriteHandler> handler2(handler);
      async_write(next_layer_, buffer(storage->data(), storage->size()),
          buffered_flush_handler<typename decay<WriteHandler>::type>(
            *storage, handler2.value));
    }

  private:
    typename remove_reference<Stream>::type& next_layer_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename WriteHandler, typename Allocator>
struct associated_allocator<
    detail::buffered_flush_handler<WriteHandler>, Allocator>
{
  typedef typename associated_allocator<WriteHandler, Allocator>::type type;

  static type get(const detail::buffered_flush_handler<WriteHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<WriteHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename WriteHandler, typename Executor>
struct associated_executor<
    detail::buffered_flush_handler<WriteHandler>, Executor>
{
  typedef typename associated_executor<WriteHandler, Executor>::type type;

  static type get(const detail::buffered_flush_handler<WriteHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<WriteHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename Stream>
template <
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
buffered_write_stream<Stream>::async_flush(
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_buffered_flush<Stream>(next_layer_),
      handler, &storage_);
}

template <typename Stream>
template <typename ConstBufferSequence>
std::size_t buffered_write_stream<Stream>::write_some(
    const ConstBufferSequence& buffers)
{
  using boost::asio::buffer_size;
  if (buffer_size(buffers) == 0)
    return 0;

  if (storage_.size() == storage_.capacity())
    this->flush();

  return this->copy(buffers);
}

template <typename Stream>
template <typename ConstBufferSequence>
std::size_t buffered_write_stream<Stream>::write_some(
    const ConstBufferSequence& buffers, boost::system::error_code& ec)
{
  ec = boost::system::error_code();

  using boost::asio::buffer_size;
  if (buffer_size(buffers) == 0)
    return 0;

  if (storage_.size() == storage_.capacity() && !flush(ec))
    return 0;

  return this->copy(buffers);
}

namespace detail
{
  template <typename ConstBufferSequence, typename WriteHandler>
  class buffered_write_some_handler
  {
  public:
    buffered_write_some_handler(detail::buffered_stream_storage& storage,
        const ConstBufferSequence& buffers, WriteHandler& handler)
      : storage_(storage),
        buffers_(buffers),
        handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
      buffered_write_some_handler(const buffered_write_some_handler& other)
        : storage_(other.storage_),
          buffers_(other.buffers_),
          handler_(other.handler_)
      {
      }

      buffered_write_some_handler(buffered_write_some_handler&& other)
        : storage_(other.storage_),
          buffers_(other.buffers_),
          handler_(BOOST_ASIO_MOVE_CAST(WriteHandler)(other.handler_))
      {
      }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec, std::size_t)
    {
      if (ec)
      {
        const std::size_t length = 0;
        handler_(ec, length);
      }
      else
      {
        using boost::asio::buffer_size;
        std::size_t orig_size = storage_.size();
        std::size_t space_avail = storage_.capacity() - orig_size;
        std::size_t bytes_avail = buffer_size(buffers_);
        std::size_t length = bytes_avail < space_avail
          ? bytes_avail : space_avail;
        storage_.resize(orig_size + length);
        const std::size_t bytes_copied = boost::asio::buffer_copy(
            storage_.data() + orig_size, buffers_, length);
        handler_(ec, bytes_copied);
      }
    }

  //private:
    detail::buffered_stream_storage& storage_;
    ConstBufferSequence buffers_;
    WriteHandler handler_;
  };

  template <typename ConstBufferSequence, typename WriteHandler>
  inline void* asio_handler_allocate(std::size_t size,
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename ConstBufferSequence, typename WriteHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename ConstBufferSequence, typename WriteHandler>
  inline bool asio_handler_is_continuation(
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename ConstBufferSequence,
      typename WriteHandler>
  inline void asio_handler_invoke(Function& function,
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename ConstBufferSequence,
      typename WriteHandler>
  inline void asio_handler_invoke(const Function& function,
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Stream>
  class initiate_async_buffered_write_some
  {
  public:
    typedef typename remove_reference<
      Stream>::type::lowest_layer_type::executor_type executor_type;

    explicit initiate_async_buffered_write_some(
        typename remove_reference<Stream>::type& next_layer)
      : next_layer_(next_layer)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return next_layer_.lowest_layer().get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        buffered_stream_storage* storage,
        const ConstBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      using boost::asio::buffer_size;
      non_const_lvalue<WriteHandler> handler2(handler);
      if (buffer_size(buffers) == 0 || storage->size() < storage->capacity())
      {
        next_layer_.async_write_some(BOOST_ASIO_CONST_BUFFER(0, 0),
            buffered_write_some_handler<ConstBufferSequence,
              typename decay<WriteHandler>::type>(
                *storage, buffers, handler2.value));
      }
      else
      {
        initiate_async_buffered_flush<Stream>(this->next_layer_)(
            buffered_write_some_handler<ConstBufferSequence,
              typename decay<WriteHandler>::type>(
                *storage, buffers, handler2.value),
            storage);
      }
    }

  private:
    typename remove_reference<Stream>::type& next_layer_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename ConstBufferSequence,
    typename WriteHandler, typename Allocator>
struct associated_allocator<
    detail::buffered_write_some_handler<ConstBufferSequence, WriteHandler>,
    Allocator>
{
  typedef typename associated_allocator<WriteHandler, Allocator>::type type;

  static type get(
      const detail::buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<WriteHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename ConstBufferSequence,
    typename WriteHandler, typename Executor>
struct associated_executor<
    detail::buffered_write_some_handler<ConstBufferSequence, WriteHandler>,
    Executor>
{
  typedef typename associated_executor<WriteHandler, Executor>::type type;

  static type get(
      const detail::buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<WriteHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename Stream>
template <typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
buffered_write_stream<Stream>::async_write_some(
    const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
{
  return async_initiate<WriteHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_buffered_write_some<Stream>(next_layer_),
      handler, &storage_, buffers);
}

template <typename Stream>
template <typename ConstBufferSequence>
std::size_t buffered_write_stream<Stream>::copy(
    const ConstBufferSequence& buffers)
{
  using boost::asio::buffer_size;
  std::size_t orig_size = storage_.size();
  std::size_t space_avail = storage_.capacity() - orig_size;
  std::size_t bytes_avail = buffer_size(buffers);
  std::size_t length = bytes_avail < space_avail ? bytes_avail : space_avail;
  storage_.resize(orig_size + length);
  return boost::asio::buffer_copy(
      storage_.data() + orig_size, buffers, length);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_BUFFERED_WRITE_STREAM_HPP

/* buffered_write_stream.hpp
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
*/