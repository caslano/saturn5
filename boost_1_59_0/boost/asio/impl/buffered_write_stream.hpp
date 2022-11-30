//
// impl/buffered_write_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_BUFFERED_WRITE_STREAM_HPP
#define BOOST_ASIO_IMPL_BUFFERED_WRITE_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/associator.hpp>
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
      BOOST_ASIO_MOVE_OR_LVALUE(WriteHandler)(handler_)(ec, bytes_written);
    }

  //private:
    detail::buffered_stream_storage& storage_;
    WriteHandler handler_;
  };

  template <typename WriteHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      buffered_flush_handler<WriteHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename WriteHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename WriteHandler>
  inline bool asio_handler_is_continuation(
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      buffered_flush_handler<WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename WriteHandler, typename DefaultCandidate>
struct associator<Associator,
    detail::buffered_flush_handler<WriteHandler>,
    DefaultCandidate>
  : Associator<WriteHandler, DefaultCandidate>
{
  static typename Associator<WriteHandler, DefaultCandidate>::type get(
      const detail::buffered_flush_handler<WriteHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<WriteHandler, DefaultCandidate>::get(h.handler_, c);
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
        BOOST_ASIO_MOVE_OR_LVALUE(WriteHandler)(handler_)(ec, length);
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
        BOOST_ASIO_MOVE_OR_LVALUE(WriteHandler)(handler_)(ec, bytes_copied);
      }
    }

  //private:
    detail::buffered_stream_storage& storage_;
    ConstBufferSequence buffers_;
    WriteHandler handler_;
  };

  template <typename ConstBufferSequence, typename WriteHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename ConstBufferSequence, typename WriteHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename ConstBufferSequence,
      typename WriteHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename ConstBufferSequence, typename WriteHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::buffered_write_some_handler<ConstBufferSequence, WriteHandler>,
    DefaultCandidate>
  : Associator<WriteHandler, DefaultCandidate>
{
  static typename Associator<WriteHandler, DefaultCandidate>::type get(
      const detail::buffered_write_some_handler<
        ConstBufferSequence, WriteHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<WriteHandler, DefaultCandidate>::get(h.handler_, c);
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