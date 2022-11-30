//
// experimental/detail/impl/channel_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_IMPL_CHANNEL_SERVICE_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_IMPL_CHANNEL_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename Mutex>
inline channel_service<Mutex>::channel_service(execution_context& ctx)
  : boost::asio::detail::execution_context_service_base<channel_service>(ctx),
    mutex_(),
    impl_list_(0)
{
}

template <typename Mutex>
inline void channel_service<Mutex>::shutdown()
{
  // Abandon all pending operations.
  boost::asio::detail::op_queue<channel_operation> ops;
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
  base_implementation_type* impl = impl_list_;
  while (impl)
  {
    ops.push(impl->waiters_);
    impl = impl->next_;
  }
}

template <typename Mutex>
inline void channel_service<Mutex>::construct(
    channel_service<Mutex>::base_implementation_type& impl,
    std::size_t max_buffer_size)
{
  impl.max_buffer_size_ = max_buffer_size;
  impl.receive_state_ = block;
  impl.send_state_ = max_buffer_size ? buffer : block;

  // Insert implementation into linked list of all implementations.
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
  impl.next_ = impl_list_;
  impl.prev_ = 0;
  if (impl_list_)
    impl_list_->prev_ = &impl;
  impl_list_ = &impl;
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::destroy(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl)
{
  cancel(impl);
  base_destroy(impl);
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::move_construct(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl,
    channel_service<Mutex>::implementation_type<
      Traits, Signatures...>& other_impl)
{
  impl.max_buffer_size_ = other_impl.max_buffer_size_;
  impl.receive_state_ = other_impl.receive_state_;
  other_impl.receive_state_ = block;
  impl.send_state_ = other_impl.send_state_;
  other_impl.send_state_ = other_impl.max_buffer_size_ ? buffer : block;
  impl.buffer_move_from(other_impl);

  // Insert implementation into linked list of all implementations.
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
  impl.next_ = impl_list_;
  impl.prev_ = 0;
  if (impl_list_)
    impl_list_->prev_ = &impl;
  impl_list_ = &impl;
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::move_assign(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl,
    channel_service& other_service,
    channel_service<Mutex>::implementation_type<
      Traits, Signatures...>& other_impl)
{
  cancel(impl);

  if (this != &other_service)
  {
    // Remove implementation from linked list of all implementations.
    boost::asio::detail::mutex::scoped_lock lock(mutex_);
    if (impl_list_ == &impl)
      impl_list_ = impl.next_;
    if (impl.prev_)
      impl.prev_->next_ = impl.next_;
    if (impl.next_)
      impl.next_->prev_= impl.prev_;
    impl.next_ = 0;
    impl.prev_ = 0;
  }

  impl.max_buffer_size_ = other_impl.max_buffer_size_;
  impl.receive_state_ = other_impl.receive_state_;
  other_impl.receive_state_ = block;
  impl.send_state_ = other_impl.send_state_;
  other_impl.send_state_ = other_impl.max_buffer_size_ ? buffer : block;
  impl.buffer_move_from(other_impl);

  if (this != &other_service)
  {
    // Insert implementation into linked list of all implementations.
    boost::asio::detail::mutex::scoped_lock lock(other_service.mutex_);
    impl.next_ = other_service.impl_list_;
    impl.prev_ = 0;
    if (other_service.impl_list_)
      other_service.impl_list_->prev_ = &impl;
    other_service.impl_list_ = &impl;
  }
}

template <typename Mutex>
inline void channel_service<Mutex>::base_destroy(
    channel_service<Mutex>::base_implementation_type& impl)
{
  // Remove implementation from linked list of all implementations.
  boost::asio::detail::mutex::scoped_lock lock(mutex_);
  if (impl_list_ == &impl)
    impl_list_ = impl.next_;
  if (impl.prev_)
    impl.prev_->next_ = impl.next_;
  if (impl.next_)
    impl.next_->prev_= impl.prev_;
  impl.next_ = 0;
  impl.prev_ = 0;
}

template <typename Mutex>
inline std::size_t channel_service<Mutex>::capacity(
    const channel_service<Mutex>::base_implementation_type& impl)
  const BOOST_ASIO_NOEXCEPT
{
  typename Mutex::scoped_lock lock(impl.mutex_);

  return impl.max_buffer_size_;
}

template <typename Mutex>
inline bool channel_service<Mutex>::is_open(
    const channel_service<Mutex>::base_implementation_type& impl)
  const BOOST_ASIO_NOEXCEPT
{
  typename Mutex::scoped_lock lock(impl.mutex_);

  return impl.send_state_ != closed;
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::reset(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl)
{
  cancel(impl);

  typename Mutex::scoped_lock lock(impl.mutex_);

  impl.receive_state_ = block;
  impl.send_state_ = impl.max_buffer_size_ ? buffer : block;
  impl.buffer_clear();
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::close(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl)
{
  typedef typename implementation_type<Traits,
      Signatures...>::traits_type traits_type;
  typedef typename implementation_type<Traits,
      Signatures...>::payload_type payload_type;

  typename Mutex::scoped_lock lock(impl.mutex_);

  if (impl.receive_state_ == block)
  {
    while (channel_operation* op = impl.waiters_.front())
    {
      impl.waiters_.pop();
      traits_type::invoke_receive_closed(
          complete_receive<payload_type,
            typename traits_type::receive_closed_signature>(
              static_cast<channel_receive<payload_type>*>(op)));
    }
  }

  impl.send_state_ = closed;
  impl.receive_state_ = closed;
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::cancel(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl)
{
  typedef typename implementation_type<Traits,
      Signatures...>::traits_type traits_type;
  typedef typename implementation_type<Traits,
      Signatures...>::payload_type payload_type;

  typename Mutex::scoped_lock lock(impl.mutex_);

  while (channel_operation* op = impl.waiters_.front())
  {
    if (impl.send_state_ == block)
    {
      impl.waiters_.pop();
      static_cast<channel_send<payload_type>*>(op)->cancel();
    }
    else
    {
      impl.waiters_.pop();
      traits_type::invoke_receive_cancelled(
          complete_receive<payload_type,
            typename traits_type::receive_cancelled_signature>(
              static_cast<channel_receive<payload_type>*>(op)));
    }
  }

  if (impl.receive_state_ == waiter)
    impl.receive_state_ = block;
  if (impl.send_state_ == waiter)
    impl.send_state_ = block;
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::cancel_by_key(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl,
    void* cancellation_key)
{
  typedef typename implementation_type<Traits,
      Signatures...>::traits_type traits_type;
  typedef typename implementation_type<Traits,
      Signatures...>::payload_type payload_type;

  typename Mutex::scoped_lock lock(impl.mutex_);

  boost::asio::detail::op_queue<channel_operation> other_ops;
  while (channel_operation* op = impl.waiters_.front())
  {
    if (op->cancellation_key_ == cancellation_key)
    {
      if (impl.send_state_ == block)
      {
        impl.waiters_.pop();
        static_cast<channel_send<payload_type>*>(op)->cancel();
      }
      else
      {
        impl.waiters_.pop();
        traits_type::invoke_receive_cancelled(
            complete_receive<payload_type,
              typename traits_type::receive_cancelled_signature>(
                static_cast<channel_receive<payload_type>*>(op)));
      }
    }
    else
    {
      impl.waiters_.pop();
      other_ops.push(op);
    }
  }
  impl.waiters_.push(other_ops);

  if (impl.waiters_.empty())
  {
    if (impl.receive_state_ == waiter)
      impl.receive_state_ = block;
    if (impl.send_state_ == waiter)
      impl.send_state_ = block;
  }
}

template <typename Mutex>
inline bool channel_service<Mutex>::ready(
    const channel_service<Mutex>::base_implementation_type& impl)
  const BOOST_ASIO_NOEXCEPT
{
  typename Mutex::scoped_lock lock(impl.mutex_);

  return impl.receive_state_ != block;
}

template <typename Mutex>
template <typename Message, typename Traits,
    typename... Signatures, typename... Args>
bool channel_service<Mutex>::try_send(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl,
    BOOST_ASIO_MOVE_ARG(Args)... args)
{
  typedef typename implementation_type<Traits,
      Signatures...>::payload_type payload_type;

  typename Mutex::scoped_lock lock(impl.mutex_);

  switch (impl.send_state_)
  {
  case block:
    {
      return false;
    }
  case buffer:
    {
      impl.buffer_push(Message(0, BOOST_ASIO_MOVE_CAST(Args)(args)...));
      impl.receive_state_ = buffer;
      if (impl.buffer_size() == impl.max_buffer_size_)
        impl.send_state_ = block;
      return true;
    }
  case waiter:
    {
      payload_type payload(Message(0, BOOST_ASIO_MOVE_CAST(Args)(args)...));
      channel_receive<payload_type>* receive_op =
        static_cast<channel_receive<payload_type>*>(impl.waiters_.front());
      impl.waiters_.pop();
      receive_op->complete(BOOST_ASIO_MOVE_CAST(payload_type)(payload));
      if (impl.waiters_.empty())
        impl.send_state_ = impl.max_buffer_size_ ? buffer : block;
      return true;
    }
  case closed:
  default:
    {
      return false;
    }
  }
}

template <typename Mutex>
template <typename Message, typename Traits,
    typename... Signatures, typename... Args>
std::size_t channel_service<Mutex>::try_send_n(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl,
		std::size_t count, BOOST_ASIO_MOVE_ARG(Args)... args)
{
  typedef typename implementation_type<Traits,
      Signatures...>::payload_type payload_type;

  typename Mutex::scoped_lock lock(impl.mutex_);

  if (count == 0)
    return 0;

  switch (impl.send_state_)
  {
  case block:
    return 0;
  case buffer:
  case waiter:
    break;
  case closed:
  default:
    return 0;
  }

  payload_type payload(Message(0, BOOST_ASIO_MOVE_CAST(Args)(args)...));

  for (std::size_t i = 0; i < count; ++i)
  {
    switch (impl.send_state_)
    {
    case block:
      {
        return i;
      }
    case buffer:
      {
        i += impl.buffer_push_n(count - i,
            BOOST_ASIO_MOVE_CAST(payload_type)(payload));
        impl.receive_state_ = buffer;
        if (impl.buffer_size() == impl.max_buffer_size_)
          impl.send_state_ = block;
        return i;
      }
    case waiter:
      {
        channel_receive<payload_type>* receive_op =
          static_cast<channel_receive<payload_type>*>(impl.waiters_.front());
        impl.waiters_.pop();
        receive_op->complete(payload);
        if (impl.waiters_.empty())
          impl.send_state_ = impl.max_buffer_size_ ? buffer : block;
        break;
      }
    case closed:
    default:
      {
        return i;
      }
    }
  }

  return count;
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::start_send_op(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl,
		channel_send<typename implementation_type<
			Traits, Signatures...>::payload_type>* send_op)
{
  typedef typename implementation_type<Traits,
      Signatures...>::payload_type payload_type;

  typename Mutex::scoped_lock lock(impl.mutex_);

  switch (impl.send_state_)
  {
  case block:
    {
      impl.waiters_.push(send_op);
      if (impl.receive_state_ == block)
        impl.receive_state_ = waiter;
      return;
    }
  case buffer:
    {
      impl.buffer_push(send_op->get_payload());
      impl.receive_state_ = buffer;
      if (impl.buffer_size() == impl.max_buffer_size_)
        impl.send_state_ = block;
      send_op->complete();
      break;
    }
  case waiter:
    {
      channel_receive<payload_type>* receive_op =
        static_cast<channel_receive<payload_type>*>(impl.waiters_.front());
      impl.waiters_.pop();
      receive_op->complete(send_op->get_payload());
      if (impl.waiters_.empty())
        impl.send_state_ = impl.max_buffer_size_ ? buffer : block;
      send_op->complete();
      break;
    }
  case closed:
  default:
    {
      send_op->close();
      break;
    }
  }
}

template <typename Mutex>
template <typename Traits, typename... Signatures, typename Handler>
bool channel_service<Mutex>::try_receive(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl,
		BOOST_ASIO_MOVE_ARG(Handler) handler)
{
  typedef typename implementation_type<Traits,
      Signatures...>::payload_type payload_type;

  typename Mutex::scoped_lock lock(impl.mutex_);

  switch (impl.receive_state_)
  {
  case block:
    {
      return false;
    }
  case buffer:
    {
      payload_type payload(impl.buffer_front());
      if (channel_send<payload_type>* send_op =
          static_cast<channel_send<payload_type>*>(impl.waiters_.front()))
      {
        impl.buffer_pop();
        impl.buffer_push(send_op->get_payload());
        impl.waiters_.pop();
        send_op->complete();
      }
      else
      {
        impl.buffer_pop();
        if (impl.buffer_size() == 0)
          impl.receive_state_ = (impl.send_state_ == closed) ? closed : block;
        impl.send_state_ = (impl.send_state_ == closed) ? closed : buffer;
      }
      lock.unlock();
      boost::asio::detail::non_const_lvalue<Handler> handler2(handler);
      channel_handler<payload_type, typename decay<Handler>::type>(
          BOOST_ASIO_MOVE_CAST(payload_type)(payload), handler2.value)();
      return true;
    }
  case waiter:
    {
      channel_send<payload_type>* send_op =
        static_cast<channel_send<payload_type>*>(impl.waiters_.front());
      payload_type payload = send_op->get_payload();
      impl.waiters_.pop();
      send_op->complete();
      if (impl.waiters_.front() == 0)
        impl.receive_state_ = (impl.send_state_ == closed) ? closed : block;
      lock.unlock();
      boost::asio::detail::non_const_lvalue<Handler> handler2(handler);
      channel_handler<payload_type, typename decay<Handler>::type>(
          BOOST_ASIO_MOVE_CAST(payload_type)(payload), handler2.value)();
      return true;
    }
  case closed:
  default:
    {
      return false;
    }
  }
}

template <typename Mutex>
template <typename Traits, typename... Signatures>
void channel_service<Mutex>::start_receive_op(
    channel_service<Mutex>::implementation_type<Traits, Signatures...>& impl,
		channel_receive<typename implementation_type<
			Traits, Signatures...>::payload_type>* receive_op)
{
  typedef typename implementation_type<Traits,
      Signatures...>::traits_type traits_type;
  typedef typename implementation_type<Traits,
      Signatures...>::payload_type payload_type;

  typename Mutex::scoped_lock lock(impl.mutex_);

  switch (impl.receive_state_)
  {
  case block:
    {
      impl.waiters_.push(receive_op);
      if (impl.send_state_ != closed)
        impl.send_state_ = waiter;
      return;
    }
  case buffer:
    {
      receive_op->complete(impl.buffer_front());
      if (channel_send<payload_type>* send_op =
          static_cast<channel_send<payload_type>*>(impl.waiters_.front()))
      {
        impl.buffer_pop();
        impl.buffer_push(send_op->get_payload());
        impl.waiters_.pop();
        send_op->complete();
      }
      else
      {
        impl.buffer_pop();
        if (impl.buffer_size() == 0)
          impl.receive_state_ = (impl.send_state_ == closed) ? closed : block;
        impl.send_state_ = (impl.send_state_ == closed) ? closed : buffer;
      }
      break;
    }
  case waiter:
    {
      channel_send<payload_type>* send_op =
        static_cast<channel_send<payload_type>*>(impl.waiters_.front());
      payload_type payload = send_op->get_payload();
      impl.waiters_.pop();
      send_op->complete();
      receive_op->complete(BOOST_ASIO_MOVE_CAST(payload_type)(payload));
      if (impl.waiters_.front() == 0)
        impl.receive_state_ = (impl.send_state_ == closed) ? closed : block;
      break;
    }
  case closed:
  default:
    {
      traits_type::invoke_receive_closed(
          complete_receive<payload_type,
            typename traits_type::receive_closed_signature>(receive_op));
      break;
    }
  }
}

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_IMPL_CHANNEL_SERVICE_HPP

/* channel_service.hpp
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
*/