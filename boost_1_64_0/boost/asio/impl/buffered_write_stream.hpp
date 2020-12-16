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
4sP608iHtajiywqRLy9EPn+IfA0h8jWFyNes49trKpepOr7WEPm80aHxZYXIlxcinz9EvoYQ+GQ8J99gm3ExhePYQGAi/fqkMKzG5SDygyk/hPJDKY8w+yX3t4EjbfrlMPbL4eyPI4BDGc5gWMsv9pg73K84CGqIMY67ccB95FvBcTwf2J/hZODH6A+miOubVXwFvxo4CbgWOJXxc4DrgEuBxcAVDBfQ/5Sffqd2AcuB++kH6yD9YD1MP1jZkW1+WzwPu10ZD7s79N+Sdzd8XVS2+Q9pAWUj3LjTbfDpchjho8DWSr1vFxA6TgbIzsfLXlxrAmm+Xk767f29nMP100jf3u8L6Brc55PwaQEsAWl+YPbg7/2gtfj7MDCYT5hTiNf8wnirjL5hJiCcC6oANYCaQWdBZp8xKdVGvzFzqq2+Ywqg5/24vgvXTgLPgfS+ZLw18EUCMvuUyakBL7AIaPYtU19j71+mqcbqY+ZcDcLAhrtxr1qkATqPcE4AwVcE1HzPNOFvP/TVfNA0I6z5oWmtbfdFk7gFPkxAmk+aRsgcAeVvMfqn2bOlYx81Z8DbvAUIOhuI29ruryZra7vPmoQDRr81ZYjzjANfAGfDjwywBTpk4NrRrfa+bM5sNfqzmX+gY582mduQJ9B5pL0TqPdxcz/CBQifBup93aTc5Hadw7Wz+DtjO9oSwna+b4pucofs/6Zgu7MPnJ1IR/ODU7c9NF84x8Gn+cM5jb8PgTfxWsiBMnEtH2jnHydjqtu17drQ/eQ0grcBfx8FpiB8BpgN9FwHPUGa75z514EXWAE0+9BpwrVz+Ps48BTCZ4HeOlzD31nAQ8i/3rfO/Drw4loO/vbXtfvY2VOn/OyIj6rDCE/D9VNAvc8dzw6j3505O0AYN0tADaAjoDOghEfQV0AloAbQUVArKOVRt2s+qAa0H9QMOgdKO+R25YFqQPtAx0Hvg1IeAz+oBrQfdBLketztygStBe0GHQadBnm/iXyBCkB1oP2gI6DToKjDblcWKB+0DbQf9BLoHCjlCdwD5AftAx0DnQUlPIn0QGWgPaD7QcdAp0DhT3X7A+r+df+6f92/7l/3z/H3Lz//f8P2i3X+f//AecJnAt92birfvK68ppon8KUirrcX62eJW7JyceHMlfnzC3Pnrpqbu4I+AM6Oxn6cdhYbD9c878aeILAVOD6Q9q3t5xrOXp5bWFK+YYNmexkRZzzff2EY+bHyHsXvgRdI+BX3TSjdl0BxYeGutaBHQNPd4a67QO1pwSIY+VJnWorscElrMcLzJPxD9278+yooMQx3Bx0GPdnjqOuAG7ZWwgvm2+UcS1cidiY+xXOsX287NxMOAviNibrHULnHaoRnS/iE+9MooWaQLwxn24AeB83EB77fAAXSOiX6bqJtNr7nVGmlSVr5COdI+A33baiBH4EGhvVwbQR9CzTfjXk8yHyOQ5xrbuxSyGa4tPTC5CyneoR1Z+vw+16837gNPHhrOoR2aP1x7T65Ns/lEx5VFtgz7QV7AA9kwYcrlXJ9GdIdIHq8kdh2Bt6W6vbvj38jaUWqM/fflfDXkc4AXrOmg7rEb30V9i7UeT2xIvdQ2Pown/CsFJ7SbciPutfTwtNX4islvmrLZl18tNynj/q2OlHCdajhKZZ6j0b+Ue+GtPBlNsKzYtHdND75ZvZ9BNPDxfc7zve58UVPRKTHvQwH/OC63Rk/PsrkQuaFgEz0jS0edz/LGZqfRzgd4ZdHtdGgJOwPoU/+brQRHwYF8PejQbzWCnwXFJB7D/gK8A/AZuD7wFGgcaAxoNH8+1XEfQD8I+hPoHOgPzO91ARBUFB/GrQVjIjdI+XjSt8=
*/