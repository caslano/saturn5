//
// experimental/basic_channel.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_BASIC_CHANNEL_HPP
#define BOOST_ASIO_EXPERIMENTAL_BASIC_CHANNEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/null_mutex.hpp>
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
 * The basic_channel class template is used for sending messages between
 * different parts of the same application. A <em>message</em> is defined as a
 * collection of arguments to be passed to a completion handler, and the set of
 * messages supported by a channel is specified by its @c Traits and
 * <tt>Signatures...</tt> template parameters. Messages may be sent and received
 * using asynchronous or non-blocking synchronous operations.
 *
 * Unless customising the traits, applications will typically use the @c
 * experimental::channel alias template. For example:
 * @code void send_loop(int i, steady_timer& timer,
 *     channel<void(error_code, int)>& ch)
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
 * void receive_loop(channel<void(error_code, int)>& ch)
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
 * @e Shared @e objects: Unsafe.
 *
 * The basic_channel class template is not thread-safe, and would typically be
 * used for passing messages between application code that runs on the same
 * thread or in the same strand. Consider using @ref basic_concurrent_channel,
 * and its alias template @c experimental::concurrent_channel, to pass messages
 * between code running in different threads.
 */
template <typename Executor, typename Traits, typename... Signatures>
class basic_channel
#if !defined(GENERATING_DOCUMENTATION)
  : public detail::channel_send_functions<
      basic_channel<Executor, Traits, Signatures...>,
      Executor, Signatures...>
#endif // !defined(GENERATING_DOCUMENTATION)
{
private:
  class initiate_async_send;
  class initiate_async_receive;
  typedef detail::channel_service<boost::asio::detail::null_mutex> service_type;
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
    typedef basic_channel<Executor1, Traits, Signatures...> other;
  };

  /// The traits type associated with the channel.
  typedef typename Traits::template rebind<Signatures...>::other traits_type;

  /// Construct a basic_channel.
  /**
   * This constructor creates and channel.
   *
   * @param ex The I/O executor that the channel will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the channel.
   *
   * @param max_buffer_size The maximum number of messages that may be buffered
   * in the channel.
   */
  basic_channel(const executor_type& ex, std::size_t max_buffer_size = 0)
    : service_(&boost::asio::use_service<service_type>(
            basic_channel::get_context(ex))),
      impl_(),
      executor_(ex)
  {
    service_->construct(impl_, max_buffer_size);
  }

  /// Construct and open a basic_channel.
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
  basic_channel(ExecutionContext& context, std::size_t max_buffer_size = 0,
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
  /// Move-construct a basic_channel from another.
  /**
   * This constructor moves a channel from one object to another.
   *
   * @param other The other basic_channel object from which the move will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_channel(const executor_type&) constructor.
   */
  basic_channel(basic_channel&& other)
    : service_(other.service_),
      executor_(other.executor_)
  {
    service_->move_construct(impl_, other.impl_);
  }

  /// Move-assign a basic_channel from another.
  /**
   * This assignment operator moves a channel from one object to another.
   * Cancels any outstanding asynchronous operations associated with the target
   * object.
   *
   * @param other The other basic_channel object from which the move will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_channel(const executor_type&)
   * constructor.
   */
  basic_channel& operator=(basic_channel&& other)
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
  friend class basic_channel;

  /// Move-construct a basic_channel from another.
  /**
   * This constructor moves a channel from one object to another.
   *
   * @param other The other basic_channel object from which the move will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_channel(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  basic_channel(
      basic_channel<Executor1, Traits, Signatures...>&& other,
      typename constraint<
          is_convertible<Executor1, Executor>::value
      >::type = 0)
    : service_(other.service_),
      executor_(other.executor_)
  {
    service_->move_construct(impl_, *other.service_, other.impl_);
  }

  /// Move-assign a basic_channel from another.
  /**
   * This assignment operator moves a channel from one object to another.
   * Cancels any outstanding asynchronous operations associated with the target
   * object.
   *
   * @param other The other basic_channel object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_channel(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  typename constraint<
    is_convertible<Executor1, Executor>::value,
    basic_channel&
  >::type operator=(basic_channel<Executor1, Traits, Signatures...>&& other)
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
  ~basic_channel()
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
  /**
   * @par Completion Signature
   * @code void(boost::system::error_code) @endcode
   */
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
  /**
   * @par Completion Signature
   * As determined by the <tt>Signatures...</tt> template parameter and the
   * channel traits.
   */
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
  basic_channel(const basic_channel&) BOOST_ASIO_DELETED;
  basic_channel& operator=(const basic_channel&) BOOST_ASIO_DELETED;

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

    explicit initiate_async_send(basic_channel* self)
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
    basic_channel* self_;
  };

  class initiate_async_receive
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive(basic_channel* self)
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
    basic_channel* self_;
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

#endif // BOOST_ASIO_EXPERIMENTAL_BASIC_CHANNEL_HPP

/* basic_channel.hpp
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
*/