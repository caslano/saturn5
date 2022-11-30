//
// experimental/basic_concurrent_channel.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_BASIC_CONCURRENT_CHANNEL_HPP
#define BOOST_ASIO_EXPERIMENTAL_BASIC_CONCURRENT_CHANNEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/experimental/detail/channel_send_functions.hpp>
#include <boost/asio/experimental/detail/channel_service.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

} // namespace detail

/// A channel for messages.
/**
 * The basic_concurrent_channel class template is used for sending messages
 * between different parts of the same application. A <em>message</em> is
 * defined as a collection of arguments to be passed to a completion handler,
 * and the set of messages supported by a channel is specified by its @c Traits
 * and <tt>Signatures...</tt> template parameters. Messages may be sent and
 * received using asynchronous or non-blocking synchronous operations.
 *
 * Unless customising the traits, applications will typically use the @c
 * experimental::concurrent_channel alias template. For example:
 * @code void send_loop(int i, steady_timer& timer,
 *     concurrent_channel<void(error_code, int)>& ch)
 * {
 *   if (i < 10)
 *   {
 *     timer.expires_after(chrono::seconds(1));
 *     timer.async_wait(
 *         [i, &timer, &ch](error_code error)
 *         {
 *           if (!error)
 *           {
 *             ch.async_send(error_code(), i,
 *                 [i, &timer, &ch](error_code error)
 *                 {
 *                   if (!error)
 *                   {
 *                     send_loop(i + 1, timer, ch);
 *                   }
 *                 });
 *           }
 *         });
 *   }
 *   else
 *   {
 *     ch.close();
 *   }
 * }
 *
 * void receive_loop(concurent_channel<void(error_code, int)>& ch)
 * {
 *   ch.async_receive(
 *       [&ch](error_code error, int i)
 *       {
 *         if (!error)
 *         {
 *           std::cout << "Received " << i << "\n";
 *           receive_loop(ch);
 *         }
 *       });
 * } @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * The basic_concurrent_channel class template is thread-safe, and would
 * typically be used for passing messages between application code that run on
 * different threads. Consider using @ref basic_channel, and its alias template
 * @c experimental::channel, to pass messages between code running in a single
 * thread or on the same strand.
 */
template <typename Executor, typename Traits, typename... Signatures>
class basic_concurrent_channel
#if !defined(GENERATING_DOCUMENTATION)
  : public detail::channel_send_functions<
      basic_concurrent_channel<Executor, Traits, Signatures...>,
      Executor, Signatures...>
#endif // !defined(GENERATING_DOCUMENTATION)
{
private:
  class initiate_async_send;
  class initiate_async_receive;
  typedef detail::channel_service<boost::asio::detail::mutex> service_type;
  typedef typename service_type::template implementation_type<
      Traits, Signatures...>::payload_type payload_type;

  template <typename... PayloadSignatures,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(PayloadSignatures...) CompletionToken>
  auto do_async_receive(detail::channel_payload<PayloadSignatures...>*,
      BOOST_ASIO_MOVE_ARG(CompletionToken) token)
    -> decltype(
        async_initiate<CompletionToken, PayloadSignatures...>(
          declval<initiate_async_receive>(), token))
  {
    return async_initiate<CompletionToken, PayloadSignatures...>(
        initiate_async_receive(this), token);
  }

public:
  /// The type of the executor associated with the channel.
  typedef Executor executor_type;

  /// Rebinds the channel type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The channel type when rebound to the specified executor.
    typedef basic_concurrent_channel<Executor1, Traits, Signatures...> other;
  };

  /// The traits type associated with the channel.
  typedef typename Traits::template rebind<Signatures...>::other traits_type;

  /// Construct a basic_concurrent_channel.
  /**
   * This constructor creates and channel.
   *
   * @param ex The I/O executor that the channel will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the channel.
   *
   * @param max_buffer_size The maximum number of messages that may be buffered
   * in the channel.
   */
  basic_concurrent_channel(const executor_type& ex,
      std::size_t max_buffer_size = 0)
    : service_(&boost::asio::use_service<service_type>(
            basic_concurrent_channel::get_context(ex))),
      impl_(),
      executor_(ex)
  {
    service_->construct(impl_, max_buffer_size);
  }

  /// Construct and open a basic_concurrent_channel.
  /**
   * This constructor creates and opens a channel.
   *
   * @param context An execution context which provides the I/O executor that
   * the channel will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the channel.
   *
   * @param max_buffer_size The maximum number of messages that may be buffered
   * in the channel.
   */
  template <typename ExecutionContext>
  basic_concurrent_channel(ExecutionContext& context,
      std::size_t max_buffer_size = 0,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : service_(&boost::asio::use_service<service_type>(context)),
      impl_(),
      executor_(context.get_executor())
  {
    service_->construct(impl_, max_buffer_size);
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_concurrent_channel from another.
  /**
   * This constructor moves a channel from one object to another.
   *
   * @param other The other basic_concurrent_channel object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_concurrent_channel(const executor_type&)
   * constructor.
   */
  basic_concurrent_channel(basic_concurrent_channel&& other)
    : service_(other.service_),
      executor_(other.executor_)
  {
    service_->move_construct(impl_, other.impl_);
  }

  /// Move-assign a basic_concurrent_channel from another.
  /**
   * This assignment operator moves a channel from one object to another.
   * Cancels any outstanding asynchronous operations associated with the target
   * object.
   *
   * @param other The other basic_concurrent_channel object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_concurrent_channel(const executor_type&)
   * constructor.
   */
  basic_concurrent_channel& operator=(basic_concurrent_channel&& other)
  {
    if (this != &other)
    {
      service_->move_assign(impl_, *other.service_, other.impl_);
      executor_.~executor_type();
      new (&executor_) executor_type(other.executor_);
      service_ = other.service_;
    }
    return *this;
  }

  // All channels have access to each other's implementations.
  template <typename, typename, typename...>
  friend class basic_concurrent_channel;

  /// Move-construct a basic_concurrent_channel from another.
  /**
   * This constructor moves a channel from one object to another.
   *
   * @param other The other basic_concurrent_channel object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_concurrent_channel(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  basic_concurrent_channel(
      basic_concurrent_channel<Executor1, Traits, Signatures...>&& other,
      typename constraint<
          is_convertible<Executor1, Executor>::value
      >::type = 0)
    : service_(other.service_),
      executor_(other.executor_)
  {
    service_->move_construct(impl_, *other.service_, other.impl_);
  }

  /// Move-assign a basic_concurrent_channel from another.
  /**
   * This assignment operator moves a channel from one object to another.
   * Cancels any outstanding asynchronous operations associated with the target
   * object.
   *
   * @param other The other basic_concurrent_channel object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_concurrent_channel(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  typename constraint<
    is_convertible<Executor1, Executor>::value,
    basic_concurrent_channel&
  >::type operator=(
      basic_concurrent_channel<Executor1, Traits, Signatures...>&& other)
  {
    if (this != &other)
    {
      service_->move_assign(impl_, *other.service_, other.impl_);
      executor_.~executor_type();
      new (&executor_) executor_type(other.executor_);
      service_ = other.service_;
    }
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  ~basic_concurrent_channel()
  {
    service_->destroy(impl_);
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  /// Get the capacity of the channel's buffer.
  std::size_t capacity() BOOST_ASIO_NOEXCEPT
  {
    return service_->capacity(impl_);
  }

  /// Determine whether the channel is open.
  bool is_open() const BOOST_ASIO_NOEXCEPT
  {
    return service_->is_open(impl_);
  }

  /// Reset the channel to its initial state.
  void reset()
  {
    service_->reset(impl_);
  }

  /// Close the channel.
  void close()
  {
    service_->close(impl_);
  }

  /// Cancel all asynchronous operations waiting on the channel.
  /**
   * All outstanding send operations will complete with the error
   * @c boost::asio::experimental::error::channel_cancelled. Outstanding receive
   * operations complete with the result as determined by the channel traits.
   */
  void cancel()
  {
    service_->cancel(impl_);
  }

  /// Determine whether a message can be received without blocking.
  bool ready() const BOOST_ASIO_NOEXCEPT
  {
    return service_->ready(impl_);
  }

#if defined(GENERATING_DOCUMENTATION)

  /// Try to send a message without blocking.
  /**
   * Fails if the buffer is full and there are no waiting receive operations.
   *
   * @returns @c true on success, @c false on failure.
   */
  template <typename... Args>
  bool try_send(BOOST_ASIO_MOVE_ARG(Args)... args);

  /// Try to send a number of messages without blocking.
  /**
   * @returns The number of messages that were sent.
   */
  template <typename... Args>
  std::size_t try_send_n(std::size_t count, BOOST_ASIO_MOVE_ARG(Args)... args);

  /// Asynchronously send a message.
  template <typename... Args,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        CompletionToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  auto async_send(BOOST_ASIO_MOVE_ARG(Args)... args,
      BOOST_ASIO_MOVE_ARG(CompletionToken) token);

#endif // defined(GENERATING_DOCUMENTATION)

  /// Try to receive a message without blocking.
  /**
   * Fails if the buffer is full and there are no waiting receive operations.
   *
   * @returns @c true on success, @c false on failure.
   */
  template <typename Handler>
  bool try_receive(BOOST_ASIO_MOVE_ARG(Handler) handler)
  {
    return service_->try_receive(impl_, BOOST_ASIO_MOVE_CAST(Handler)(handler));
  }

  /// Asynchronously receive a message.
  template <typename CompletionToken
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  auto async_receive(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor))
#if !defined(GENERATING_DOCUMENTATION)
    -> decltype(
        this->do_async_receive(static_cast<payload_type*>(0),
          BOOST_ASIO_MOVE_CAST(CompletionToken)(token)))
#endif // !defined(GENERATING_DOCUMENTATION)
  {
    return this->do_async_receive(static_cast<payload_type*>(0),
        BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
  }

private:
  // Disallow copying and assignment.
  basic_concurrent_channel(
      const basic_concurrent_channel&) BOOST_ASIO_DELETED;
  basic_concurrent_channel& operator=(
      const basic_concurrent_channel&) BOOST_ASIO_DELETED;

  template <typename, typename, typename...>
  friend class detail::channel_send_functions;

  // Helper function to get an executor's context.
  template <typename T>
  static execution_context& get_context(const T& t,
      typename enable_if<execution::is_executor<T>::value>::type* = 0)
  {
    return boost::asio::query(t, execution::context);
  }

  // Helper function to get an executor's context.
  template <typename T>
  static execution_context& get_context(const T& t,
      typename enable_if<!execution::is_executor<T>::value>::type* = 0)
  {
    return t.context();
  }

  class initiate_async_send
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_send(basic_concurrent_channel* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename SendHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(SendHandler) handler,
        BOOST_ASIO_MOVE_ARG(payload_type) payload) const
    {
      boost::asio::detail::non_const_lvalue<SendHandler> handler2(handler);
      self_->service_->async_send(self_->impl_,
          BOOST_ASIO_MOVE_CAST(payload_type)(payload),
          handler2.value, self_->get_executor());
    }

  private:
    basic_concurrent_channel* self_;
  };

  class initiate_async_receive
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive(basic_concurrent_channel* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReceiveHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(ReceiveHandler) handler) const
    {
      boost::asio::detail::non_const_lvalue<ReceiveHandler> handler2(handler);
      self_->service_->async_receive(self_->impl_,
          handler2.value, self_->get_executor());
    }

  private:
    basic_concurrent_channel* self_;
  };

  // The service associated with the I/O object.
  service_type* service_;

  // The underlying implementation of the I/O object.
  typename service_type::template implementation_type<
      Traits, Signatures...> impl_;

  // The associated executor.
  Executor executor_;
};

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_BASIC_CONCURRENT_CHANNEL_HPP

/* basic_concurrent_channel.hpp
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
*/