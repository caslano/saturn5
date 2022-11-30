//
// impl/buffered_read_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_BUFFERED_READ_STREAM_HPP
#define BOOST_ASIO_IMPL_BUFFERED_READ_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/associator.hpp>
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
      BOOST_ASIO_MOVE_OR_LVALUE(ReadHandler)(handler_)(ec, bytes_transferred);
    }

  //private:
    detail::buffered_stream_storage& storage_;
    std::size_t previous_size_;
    ReadHandler handler_;
  };

  template <typename ReadHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      buffered_fill_handler<ReadHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename ReadHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename ReadHandler>
  inline bool asio_handler_is_continuation(
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    return boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      buffered_fill_handler<ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename ReadHandler, typename DefaultCandidate>
struct associator<Associator,
    detail::buffered_fill_handler<ReadHandler>,
    DefaultCandidate>
  : Associator<ReadHandler, DefaultCandidate>
{
  static typename Associator<ReadHandler, DefaultCandidate>::type get(
      const detail::buffered_fill_handler<ReadHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<ReadHandler, DefaultCandidate>::get(h.handler_, c);
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
        BOOST_ASIO_MOVE_OR_LVALUE(ReadHandler)(handler_)(ec, length);
      }
      else
      {
        const std::size_t bytes_copied = boost::asio::buffer_copy(
            buffers_, storage_.data(), storage_.size());
        storage_.consume(bytes_copied);
        BOOST_ASIO_MOVE_OR_LVALUE(ReadHandler)(handler_)(ec, bytes_copied);
      }
    }

  //private:
    detail::buffered_stream_storage& storage_;
    MutableBufferSequence buffers_;
    ReadHandler handler_;
  };

  template <typename MutableBufferSequence, typename ReadHandler>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename MutableBufferSequence, typename ReadHandler>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename MutableBufferSequence,
      typename ReadHandler>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename MutableBufferSequence, typename ReadHandler,
    typename DefaultCandidate>
struct associator<Associator,
    detail::buffered_read_some_handler<MutableBufferSequence, ReadHandler>,
    DefaultCandidate>
  : Associator<ReadHandler, DefaultCandidate>
{
  static typename Associator<ReadHandler, DefaultCandidate>::type get(
      const detail::buffered_read_some_handler<
        MutableBufferSequence, ReadHandler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<ReadHandler, DefaultCandidate>::get(h.handler_, c);
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