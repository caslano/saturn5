//
// experimental/detail/channel_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SERVICE_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/cancellation_type.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/experimental/detail/channel_message.hpp>
#include <boost/asio/experimental/detail/channel_receive_op.hpp>
#include <boost/asio/experimental/detail/channel_send_op.hpp>
#include <boost/asio/experimental/detail/has_signature.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename Mutex>
class channel_service
  : public boost::asio::detail::execution_context_service_base<
      channel_service<Mutex> >
{
public:
  // Possible states for a channel end.
  enum state
  {
    buffer = 0,
    waiter = 1,
    block = 2,
    closed = 3
  };

  // The base implementation type of all channels.
  struct base_implementation_type
  {
    // Default constructor.
    base_implementation_type()
      : receive_state_(block),
        send_state_(block),
        max_buffer_size_(0),
        next_(0),
        prev_(0)
    {
    }

    // The current state of the channel.
    state receive_state_ : 16;
    state send_state_ : 16;

    // The maximum number of elements that may be buffered in the channel.
    std::size_t max_buffer_size_;

    // The operations that are waiting on the channel.
    boost::asio::detail::op_queue<channel_operation> waiters_;

    // Pointers to adjacent channel implementations in linked list.
    base_implementation_type* next_;
    base_implementation_type* prev_;

    // The mutex type to protect the internal implementation.
    mutable Mutex mutex_;
  };

  // The implementation for a specific value type.
  template <typename Traits, typename... Signatures>
  struct implementation_type;

  // Constructor.
  channel_service(execution_context& ctx);

  // Destroy all user-defined handler objects owned by the service.
  void shutdown();

  // Construct a new channel implementation.
  void construct(base_implementation_type& impl, std::size_t max_buffer_size);

  // Destroy a channel implementation.
  template <typename Traits, typename... Signatures>
  void destroy(implementation_type<Traits, Signatures...>& impl);

  // Move-construct a new channel implementation.
  template <typename Traits, typename... Signatures>
  void move_construct(implementation_type<Traits, Signatures...>& impl,
      implementation_type<Traits, Signatures...>& other_impl);

  // Move-assign from another channel implementation.
  template <typename Traits, typename... Signatures>
  void move_assign(implementation_type<Traits, Signatures...>& impl,
      channel_service& other_service,
      implementation_type<Traits, Signatures...>& other_impl);

  // Get the capacity of the channel.
  std::size_t capacity(
      const base_implementation_type& impl) const BOOST_ASIO_NOEXCEPT;

  // Determine whether the channel is open.
  bool is_open(const base_implementation_type& impl) const BOOST_ASIO_NOEXCEPT;

  // Reset the channel to its initial state.
  template <typename Traits, typename... Signatures>
  void reset(implementation_type<Traits, Signatures...>& impl);

  // Close the channel.
  template <typename Traits, typename... Signatures>
  void close(implementation_type<Traits, Signatures...>& impl);

  // Cancel all operations associated with the channel.
  template <typename Traits, typename... Signatures>
  void cancel(implementation_type<Traits, Signatures...>& impl);

  // Cancel the operation associated with the channel that has the given key.
  template <typename Traits, typename... Signatures>
  void cancel_by_key(implementation_type<Traits, Signatures...>& impl,
      void* cancellation_key);

  // Determine whether a value can be read from the channel without blocking.
  bool ready(const base_implementation_type& impl) const BOOST_ASIO_NOEXCEPT;

  // Synchronously send a new value into the channel.
  template <typename Message, typename Traits,
      typename... Signatures, typename... Args>
  bool try_send(implementation_type<Traits, Signatures...>& impl,
      BOOST_ASIO_MOVE_ARG(Args)... args);

  // Synchronously send a number of new values into the channel.
  template <typename Message, typename Traits,
      typename... Signatures, typename... Args>
  std::size_t try_send_n(implementation_type<Traits, Signatures...>& impl,
      std::size_t count, BOOST_ASIO_MOVE_ARG(Args)... args);

  // Asynchronously send a new value into the channel.
  template <typename Traits, typename... Signatures,
      typename Handler, typename IoExecutor>
  void async_send(implementation_type<Traits, Signatures...>& impl,
      BOOST_ASIO_MOVE_ARG2(typename implementation_type<
        Traits, Signatures...>::payload_type) payload,
      Handler& handler, const IoExecutor& io_ex)
  {
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef channel_send_op<
      typename implementation_type<Traits, Signatures...>::payload_type,
        Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST2(typename implementation_type<
          Traits, Signatures...>::payload_type)(payload), handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<op_cancellation<Traits, Signatures...> >(
            this, &impl);
    }

    BOOST_ASIO_HANDLER_CREATION((this->context(), *p.p,
          "channel", &impl, 0, "async_send"));

    start_send_op(impl, p.p);
    p.v = p.p = 0;
  }

  // Synchronously receive a value from the channel.
  template <typename Traits, typename... Signatures, typename Handler>
  bool try_receive(implementation_type<Traits, Signatures...>& impl,
      BOOST_ASIO_MOVE_ARG(Handler) handler);

  // Asynchronously send a new value into the channel.
  // Asynchronously receive a value from the channel.
  template <typename Traits, typename... Signatures,
      typename Handler, typename IoExecutor>
  void async_receive(implementation_type<Traits, Signatures...>& impl,
      Handler& handler, const IoExecutor& io_ex)
  {
    typename associated_cancellation_slot<Handler>::type slot
      = boost::asio::get_associated_cancellation_slot(handler);

    // Allocate and construct an operation to wrap the handler.
    typedef channel_receive_op<
      typename implementation_type<Traits, Signatures...>::payload_type,
        Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    // Optionally register for per-operation cancellation.
    if (slot.is_connected())
    {
      p.p->cancellation_key_ =
        &slot.template emplace<op_cancellation<Traits, Signatures...> >(
            this, &impl);
    }

    BOOST_ASIO_HANDLER_CREATION((this->context(), *p.p,
          "channel", &impl, 0, "async_receive"));

    start_receive_op(impl, p.p);
    p.v = p.p = 0;
  }

private:
  // Helper function object to handle a closed notification.
  template <typename Payload, typename Signature>
  struct complete_receive
  {
    explicit complete_receive(channel_receive<Payload>* op)
      : op_(op)
    {
    }

    template <typename... Args>
    void operator()(BOOST_ASIO_MOVE_ARG(Args)... args)
    {
      op_->complete(
          channel_message<Signature>(0,
            BOOST_ASIO_MOVE_CAST(Args)(args)...));
    }

    channel_receive<Payload>* op_;
  };

  // Destroy a base channel implementation.
  void base_destroy(base_implementation_type& impl);

  // Helper function to start an asynchronous put operation.
  template <typename Traits, typename... Signatures>
  void start_send_op(implementation_type<Traits, Signatures...>& impl,
      channel_send<typename implementation_type<
        Traits, Signatures...>::payload_type>* send_op);

  // Helper function to start an asynchronous get operation.
  template <typename Traits, typename... Signatures>
  void start_receive_op(implementation_type<Traits, Signatures...>& impl,
      channel_receive<typename implementation_type<
        Traits, Signatures...>::payload_type>* receive_op);

  // Helper class used to implement per-operation cancellation.
  template <typename Traits, typename... Signatures>
  class op_cancellation
  {
  public:
    op_cancellation(channel_service* s,
        implementation_type<Traits, Signatures...>* impl)
      : service_(s),
        impl_(impl)
    {
    }

    void operator()(cancellation_type_t type)
    {
      if (!!(type &
            (cancellation_type::terminal
              | cancellation_type::partial
              | cancellation_type::total)))
      {
        service_->cancel_by_key(*impl_, this);
      }
    }

  private:
    channel_service* service_;
    implementation_type<Traits, Signatures...>* impl_;
  };

  // Mutex to protect access to the linked list of implementations.
  boost::asio::detail::mutex mutex_;

  // The head of a linked list of all implementations.
  base_implementation_type* impl_list_;
};

// The implementation for a specific value type.
template <typename Mutex>
template <typename Traits, typename... Signatures>
struct channel_service<Mutex>::implementation_type : base_implementation_type
{
  // The traits type associated with the channel.
  typedef typename Traits::template rebind<Signatures...>::other traits_type;

  // Type of an element stored in the buffer.
  typedef typename conditional<
      has_signature<
        typename traits_type::receive_cancelled_signature,
        Signatures...
      >::value,
      typename conditional<
        has_signature<
          typename traits_type::receive_closed_signature,
          Signatures...
        >::value,
        channel_payload<Signatures...>,
        channel_payload<
          Signatures...,
          typename traits_type::receive_closed_signature
        >
      >::type,
      typename conditional<
        has_signature<
          typename traits_type::receive_closed_signature,
          Signatures...,
          typename traits_type::receive_cancelled_signature
        >::value,
        channel_payload<
          Signatures...,
          typename traits_type::receive_cancelled_signature
        >,
        channel_payload<
          Signatures...,
          typename traits_type::receive_cancelled_signature,
          typename traits_type::receive_closed_signature
        >
      >::type
    >::type payload_type;

  // Move from another buffer.
  void buffer_move_from(implementation_type& other)
  {
    buffer_ = BOOST_ASIO_MOVE_CAST(
        typename traits_type::template container<
          payload_type>::type)(other.buffer_);
    other.buffer_clear();
  }

  // Get number of buffered elements.
  std::size_t buffer_size() const
  {
    return buffer_.size();
  }

  // Push a new value to the back of the buffer.
  void buffer_push(payload_type payload)
  {
    buffer_.push_back(BOOST_ASIO_MOVE_CAST(payload_type)(payload));
  }

  // Push new values to the back of the buffer.
  std::size_t buffer_push_n(std::size_t count, payload_type payload)
  {
    std::size_t i = 0;
    for (; i < count && buffer_.size() < this->max_buffer_size_; ++i)
      buffer_.push_back(payload);
    return i;
  }

  // Get the element at the front of the buffer.
  payload_type buffer_front()
  {
    return BOOST_ASIO_MOVE_CAST(payload_type)(buffer_.front());
  }

  // Pop a value from the front of the buffer.
  void buffer_pop()
  {
    buffer_.pop_front();
  }

  // Clear all buffered values.
  void buffer_clear()
  {
    buffer_.clear();
  }

private:
  // Buffered values.
  typename traits_type::template container<payload_type>::type buffer_;
};

// The implementation for a void value type.
template <typename Mutex>
template <typename Traits, typename R>
struct channel_service<Mutex>::implementation_type<Traits, R()>
  : channel_service::base_implementation_type
{
  // The traits type associated with the channel.
  typedef typename Traits::template rebind<R()>::other traits_type;

  // Type of an element stored in the buffer.
  typedef typename conditional<
      has_signature<
        typename traits_type::receive_cancelled_signature,
        R()
      >::value,
      typename conditional<
        has_signature<
          typename traits_type::receive_closed_signature,
          R()
        >::value,
        channel_payload<R()>,
        channel_payload<
          R(),
          typename traits_type::receive_closed_signature
        >
      >::type,
      typename conditional<
        has_signature<
          typename traits_type::receive_closed_signature,
          R(),
          typename traits_type::receive_cancelled_signature
        >::value,
        channel_payload<
          R(),
          typename traits_type::receive_cancelled_signature
        >,
        channel_payload<
          R(),
          typename traits_type::receive_cancelled_signature,
          typename traits_type::receive_closed_signature
        >
      >::type
    >::type payload_type;

  // Construct with empty buffer.
  implementation_type()
    : buffer_(0)
  {
  }

  // Move from another buffer.
  void buffer_move_from(implementation_type& other)
  {
    buffer_ = other.buffer_;
    other.buffer_ = 0;
  }

  // Get number of buffered elements.
  std::size_t buffer_size() const
  {
    return buffer_;
  }

  // Push a new value to the back of the buffer.
  void buffer_push(payload_type)
  {
    ++buffer_;
  }

  // Push new values to the back of the buffer.
  std::size_t buffer_push_n(std::size_t count, payload_type)
  {
    std::size_t available = this->max_buffer_size_ - buffer_;
    count = (count < available) ? count : available;
    buffer_ += count;
    return count;
  }

  // Get the element at the front of the buffer.
  payload_type buffer_front()
  {
    return payload_type(channel_message<R()>(0));
  }

  // Pop a value from the front of the buffer.
  void buffer_pop()
  {
    --buffer_;
  }

  // Clear all values from the buffer.
  void buffer_clear()
  {
    buffer_ = 0;
  }

private:
  // Number of buffered "values".
  std::size_t buffer_;
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/experimental/detail/impl/channel_service.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SERVICE_HPP

/* channel_service.hpp
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
*/