//
// impl/buffered_read_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_BUFFERED_READ_STREAM_HPP
#define BOOST_ASIO_IMPL_BUFFERED_READ_STREAM_HPP

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
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

template <typename Stream>
std::size_t buffered_read_stream<Stream>::fill()
{
  detail::buffer_resize_guard<detail::buffered_stream_storage>
    resize_guard(storage_);
  std::size_t previous_size = storage_.size();
  storage_.resize(storage_.capacity());
  storage_.resize(previous_size + next_layer_.read_some(buffer(
          storage_.data() + previous_size,
          storage_.size() - previous_size)));
  resize_guard.commit();
  return storage_.size() - previous_size;
}

template <typename Stream>
std::size_t buffered_read_stream<Stream>::fill(boost::system::error_code& ec)
{
  detail::buffer_resize_guard<detail::buffered_stream_storage>
    resize_guard(storage_);
  std::size_t previous_size = storage_.size();
  storage_.resize(storage_.capacity());
  storage_.resize(previous_size + next_layer_.read_some(buffer(
          storage_.data() + previous_size,
          storage_.size() - previous_size),
        ec));
  resize_guard.commit();
  return storage_.size() - previous_size;
}

namespace detail
{
  template <typename ReadHandler>
  class buffered_fill_handler
  {
  public:
    buffered_fill_handler(detail::buffered_stream_storage& storage,
        std::size_t previous_size, ReadHandler& handler)
      : storage_(storage),
        previous_size_(previous_size),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    buffered_fill_handler(const buffered_fill_handler& other)
      : storage_(other.storage_),
        previous_size_(other.previous_size_),
        handler_(other.handler_)
    {
    }

    buffered_fill_handler(buffered_fill_handler&& other)
      : storage_(other.storage_),
        previous_size_(other.previous_size_),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec,
        const std::size_t bytes_transferred)
    {
      storage_.resize(previous_size_ + bytes_transferred);
      handler_(ec, bytes_transferred);
    }

  //private:
    detail::buffered_stream_storage& storage_;
    std::size_t previous_size_;
    ReadHandler handler_;
  };

  template <typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename ReadHandler>
  inline bool asio_handler_is_continuation(
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Stream>
  class initiate_async_buffered_fill
  {
  public:
    typedef typename remove_reference<
      Stream>::type::lowest_layer_type::executor_type executor_type;

    explicit initiate_async_buffered_fill(
        typename remove_reference<Stream>::type& next_layer)
      : next_layer_(next_layer)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return next_layer_.lowest_layer().get_executor();
    }

    template <typename ReadHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        buffered_stream_storage* storage) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      non_const_lvalue<ReadHandler> handler2(handler);
      std::size_t previous_size = storage->size();
      storage->resize(storage->capacity());
      next_layer_.async_read_some(
          buffer(
            storage->data() + previous_size,
            storage->size() - previous_size),
          buffered_fill_handler<typename decay<ReadHandler>::type>(
            *storage, previous_size, handler2.value));
    }

  private:
    typename remove_reference<Stream>::type& next_layer_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::buffered_fill_handler<ReadHandler>, Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(const detail::buffered_fill_handler<ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename ReadHandler, typename Executor>
struct associated_executor<
    detail::buffered_fill_handler<ReadHandler>, Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(const detail::buffered_fill_handler<ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename Stream>
template <
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
buffered_read_stream<Stream>::async_fill(
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_buffered_fill<Stream>(next_layer_),
      handler, &storage_);
}

template <typename Stream>
template <typename MutableBufferSequence>
std::size_t buffered_read_stream<Stream>::read_some(
    const MutableBufferSequence& buffers)
{
  using boost::asio::buffer_size;
  if (buffer_size(buffers) == 0)
    return 0;

  if (storage_.empty())
    this->fill();

  return this->copy(buffers);
}

template <typename Stream>
template <typename MutableBufferSequence>
std::size_t buffered_read_stream<Stream>::read_some(
    const MutableBufferSequence& buffers, boost::system::error_code& ec)
{
  ec = boost::system::error_code();

  using boost::asio::buffer_size;
  if (buffer_size(buffers) == 0)
    return 0;

  if (storage_.empty() && !this->fill(ec))
    return 0;

  return this->copy(buffers);
}

namespace detail
{
  template <typename MutableBufferSequence, typename ReadHandler>
  class buffered_read_some_handler
  {
  public:
    buffered_read_some_handler(detail::buffered_stream_storage& storage,
        const MutableBufferSequence& buffers, ReadHandler& handler)
      : storage_(storage),
        buffers_(buffers),
        handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(handler))
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
      buffered_read_some_handler(const buffered_read_some_handler& other)
        : storage_(other.storage_),
          buffers_(other.buffers_),
          handler_(other.handler_)
      {
      }

      buffered_read_some_handler(buffered_read_some_handler&& other)
        : storage_(other.storage_),
          buffers_(other.buffers_),
          handler_(BOOST_ASIO_MOVE_CAST(ReadHandler)(other.handler_))
      {
      }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    void operator()(const boost::system::error_code& ec, std::size_t)
    {
      if (ec || storage_.empty())
      {
        const std::size_t length = 0;
        handler_(ec, length);
      }
      else
      {
        const std::size_t bytes_copied = boost::asio::buffer_copy(
            buffers_, storage_.data(), storage_.size());
        storage_.consume(bytes_copied);
        handler_(ec, bytes_copied);
      }
    }

  //private:
    detail::buffered_stream_storage& storage_;
    MutableBufferSequence buffers_;
    ReadHandler handler_;
  };

  template <typename MutableBufferSequence, typename ReadHandler>
  inline void* asio_handler_allocate(std::size_t size,
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename MutableBufferSequence, typename ReadHandler>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename MutableBufferSequence, typename ReadHandler>
  inline bool asio_handler_is_continuation(
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename MutableBufferSequence,
      typename ReadHandler>
  inline void asio_handler_invoke(Function& function,
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename MutableBufferSequence,
      typename ReadHandler>
  inline void asio_handler_invoke(const Function& function,
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Stream>
  class initiate_async_buffered_read_some
  {
  public:
    typedef typename remove_reference<
      Stream>::type::lowest_layer_type::executor_type executor_type;

    explicit initiate_async_buffered_read_some(
        typename remove_reference<Stream>::type& next_layer)
      : next_layer_(next_layer)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return next_layer_.lowest_layer().get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        buffered_stream_storage* storage,
        const MutableBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      using boost::asio::buffer_size;
      non_const_lvalue<ReadHandler> handler2(handler);
      if (buffer_size(buffers) == 0 || !storage->empty())
      {
        next_layer_.async_read_some(BOOST_ASIO_MUTABLE_BUFFER(0, 0),
            buffered_read_some_handler<MutableBufferSequence,
              typename decay<ReadHandler>::type>(
                *storage, buffers, handler2.value));
      }
      else
      {
        initiate_async_buffered_fill<Stream>(this->next_layer_)(
            buffered_read_some_handler<MutableBufferSequence,
              typename decay<ReadHandler>::type>(
                *storage, buffers, handler2.value),
            storage);
      }
    }

  private:
    typename remove_reference<Stream>::type& next_layer_;
  };
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename MutableBufferSequence,
    typename ReadHandler, typename Allocator>
struct associated_allocator<
    detail::buffered_read_some_handler<MutableBufferSequence, ReadHandler>,
    Allocator>
{
  typedef typename associated_allocator<ReadHandler, Allocator>::type type;

  static type get(
      const detail::buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<ReadHandler, Allocator>::get(h.handler_, a);
  }
};

template <typename MutableBufferSequence,
    typename ReadHandler, typename Executor>
struct associated_executor<
    detail::buffered_read_some_handler<MutableBufferSequence, ReadHandler>,
    Executor>
{
  typedef typename associated_executor<ReadHandler, Executor>::type type;

  static type get(
      const detail::buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<ReadHandler, Executor>::get(h.handler_, ex);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

template <typename Stream>
template <typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
buffered_read_stream<Stream>::async_read_some(
    const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
{
  return async_initiate<ReadHandler,
    void (boost::system::error_code, std::size_t)>(
      detail::initiate_async_buffered_read_some<Stream>(next_layer_),
      handler, &storage_, buffers);
}

template <typename Stream>
template <typename MutableBufferSequence>
std::size_t buffered_read_stream<Stream>::peek(
    const MutableBufferSequence& buffers)
{
  if (storage_.empty())
    this->fill();
  return this->peek_copy(buffers);
}

template <typename Stream>
template <typename MutableBufferSequence>
std::size_t buffered_read_stream<Stream>::peek(
    const MutableBufferSequence& buffers, boost::system::error_code& ec)
{
  ec = boost::system::error_code();
  if (storage_.empty() && !this->fill(ec))
    return 0;
  return this->peek_copy(buffers);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_BUFFERED_READ_STREAM_HPP

/* buffered_read_stream.hpp
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
*/