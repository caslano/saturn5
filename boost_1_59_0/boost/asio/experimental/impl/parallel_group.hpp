//
// experimental/impl/parallel_group.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXPERIMENTAL_PARALLEL_GROUP_HPP
#define BOOST_ASIO_IMPL_EXPERIMENTAL_PARALLEL_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <atomic>
#include <memory>
#include <new>
#include <tuple>
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/dispatch.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

// Stores the result from an individual asynchronous operation.
template <typename T, typename = void>
struct parallel_group_op_result
{
public:
  parallel_group_op_result()
    : has_value_(false)
  {
  }

  parallel_group_op_result(parallel_group_op_result&& other)
    : has_value_(other.has_value_)
  {
    if (has_value_)
      new (&u_.value_) T(std::move(other.get()));
  }

  ~parallel_group_op_result()
  {
    if (has_value_)
      u_.value_.~T();
  }

  T& get() noexcept
  {
    return u_.value_;
  }

  template <typename... Args>
  void emplace(Args&&... args)
  {
    new (&u_.value_) T(std::forward<Args>(args)...);
    has_value_ = true;
  }

private:
  union u
  {
    u() {}
    ~u() {}
    char c_;
    T value_;
  } u_;
  bool has_value_;
};

// Proxy completion handler for the group of parallel operatations. Unpacks and
// concatenates the individual operations' results, and invokes the user's
// completion handler.
template <typename Handler, typename... Ops>
struct parallel_group_completion_handler
{
  typedef typename decay<
      typename prefer_result<
        typename associated_executor<Handler>::type,
        execution::outstanding_work_t::tracked_t
      >::type
    >::type executor_type;

  parallel_group_completion_handler(Handler&& h)
    : handler_(std::move(h)),
      executor_(
          boost::asio::prefer(
            boost::asio::get_associated_executor(handler_),
            execution::outstanding_work.tracked))
  {
  }

  executor_type get_executor() const noexcept
  {
    return executor_;
  }

  void operator()()
  {
    this->invoke(std::make_index_sequence<sizeof...(Ops)>());
  }

  template <std::size_t... I>
  void invoke(std::index_sequence<I...>)
  {
    this->invoke(std::tuple_cat(std::move(std::get<I>(args_).get())...));
  }

  template <typename... Args>
  void invoke(std::tuple<Args...>&& args)
  {
    this->invoke(std::move(args), std::make_index_sequence<sizeof...(Args)>());
  }

  template <typename... Args, std::size_t... I>
  void invoke(std::tuple<Args...>&& args, std::index_sequence<I...>)
  {
    std::move(handler_)(completion_order_, std::move(std::get<I>(args))...);
  }

  Handler handler_;
  executor_type executor_;
  std::array<std::size_t, sizeof...(Ops)> completion_order_{};
  std::tuple<
      parallel_group_op_result<
        typename parallel_op_signature_as_tuple<
          typename parallel_op_signature<Ops>::type
        >::type
      >...
    > args_{};
};

// Shared state for the parallel group.
template <typename Condition, typename Handler, typename... Ops>
struct parallel_group_state
{
  parallel_group_state(Condition&& c, Handler&& h)
    : cancellation_condition_(std::move(c)),
      handler_(std::move(h))
  {
  }

  // The number of operations that have completed so far. Used to determine the
  // order of completion.
  std::atomic<unsigned int> completed_{0};

  // The non-none cancellation type that resulted from a cancellation condition.
  // Stored here for use by the group's initiating function.
  std::atomic<cancellation_type_t> cancel_type_{cancellation_type::none};

  // The number of cancellations that have been requested, either on completion
  // of the operations within the group, or via the cancellation slot for the
  // group operation. Initially set to the number of operations to prevent
  // cancellation signals from being emitted until after all of the group's
  // operations' initiating functions have completed.
  std::atomic<unsigned int> cancellations_requested_{sizeof...(Ops)};

  // The number of operations that are yet to complete. Used to determine when
  // it is safe to invoke the user's completion handler.
  std::atomic<unsigned int> outstanding_{sizeof...(Ops)};

  // The cancellation signals for each operation in the group.
  boost::asio::cancellation_signal cancellation_signals_[sizeof...(Ops)];

  // The cancellation condition is used to determine whether the results from an
  // individual operation warrant a cancellation request for the whole group.
  Condition cancellation_condition_;

  // The proxy handler to be invoked once all operations in the group complete.
  parallel_group_completion_handler<Handler, Ops...> handler_;
};

// Handler for an individual operation within the parallel group.
template <std::size_t I, typename Condition, typename Handler, typename... Ops>
struct parallel_group_op_handler
{
  typedef boost::asio::cancellation_slot cancellation_slot_type;

  parallel_group_op_handler(
    std::shared_ptr<parallel_group_state<Condition, Handler, Ops...> > state)
    : state_(std::move(state))
  {
  }

  cancellation_slot_type get_cancellation_slot() const noexcept
  {
    return state_->cancellation_signals_[I].slot();
  }

  template <typename... Args>
  void operator()(Args... args)
  {
    // Capture this operation into the completion order.
    state_->handler_.completion_order_[state_->completed_++] = I;

    // Determine whether the results of this operation require cancellation of
    // the whole group.
    cancellation_type_t cancel_type = state_->cancellation_condition_(args...);

    // Capture the result of the operation into the proxy completion handler.
    std::get<I>(state_->handler_.args_).emplace(std::move(args)...);

    if (cancel_type != cancellation_type::none)
    {
      // Save the type for potential use by the group's initiating function.
      state_->cancel_type_ = cancel_type;

      // If we are the first operation to request cancellation, emit a signal
      // for each operation in the group.
      if (state_->cancellations_requested_++ == 0)
        for (std::size_t i = 0; i < sizeof...(Ops); ++i)
          if (i != I)
            state_->cancellation_signals_[i].emit(cancel_type);
    }

    // If this is the last outstanding operation, invoke the user's handler.
    if (--state_->outstanding_ == 0)
      boost::asio::dispatch(std::move(state_->handler_));
  }

  std::shared_ptr<parallel_group_state<Condition, Handler, Ops...> > state_;
};

// Handler for an individual operation within the parallel group that has an
// explicitly specified executor.
template <typename Executor, std::size_t I,
    typename Condition, typename Handler, typename... Ops>
struct parallel_group_op_handler_with_executor :
  parallel_group_op_handler<I, Condition, Handler, Ops...>
{
  typedef parallel_group_op_handler<I, Condition, Handler, Ops...> base_type;
  typedef boost::asio::cancellation_slot cancellation_slot_type;
  typedef Executor executor_type;

  parallel_group_op_handler_with_executor(
      std::shared_ptr<parallel_group_state<Condition, Handler, Ops...> > state,
      executor_type ex)
    : parallel_group_op_handler<I, Condition, Handler, Ops...>(std::move(state))
  {
    cancel_proxy_ =
      &this->state_->cancellation_signals_[I].slot().template
        emplace<cancel_proxy>(this->state_, std::move(ex));
  }

  cancellation_slot_type get_cancellation_slot() const noexcept
  {
    return cancel_proxy_->signal_.slot();
  }

  executor_type get_executor() const noexcept
  {
    return cancel_proxy_->executor_;
  }

  // Proxy handler that forwards the emitted signal to the correct executor.
  struct cancel_proxy
  {
    cancel_proxy(
        std::shared_ptr<parallel_group_state<
          Condition, Handler, Ops...> > state,
        executor_type ex)
      : state_(std::move(state)),
        executor_(std::move(ex))
    {
    }

    void operator()(cancellation_type_t type)
    {
      if (auto state = state_.lock())
      {
        boost::asio::cancellation_signal* sig = &signal_;
        boost::asio::dispatch(executor_,
            [state, sig, type]{ sig->emit(type); });
      }
    }

    std::weak_ptr<parallel_group_state<Condition, Handler, Ops...> > state_;
    boost::asio::cancellation_signal signal_;
    executor_type executor_;
  };

  cancel_proxy* cancel_proxy_;
};

// Helper to launch an operation using the correct executor, if any.
template <std::size_t I, typename Op, typename = void>
struct parallel_group_op_launcher
{
  template <typename Condition, typename Handler, typename... Ops>
  static void launch(Op& op,
    const std::shared_ptr<parallel_group_state<
      Condition, Handler, Ops...> >& state)
  {
    typedef typename associated_executor<Op>::type ex_type;
    ex_type ex = boost::asio::get_associated_executor(op);
    std::move(op)(
        parallel_group_op_handler_with_executor<ex_type, I,
          Condition, Handler, Ops...>(state, std::move(ex)));
  }
};

// Specialised launcher for operations that specify no executor.
template <std::size_t I, typename Op>
struct parallel_group_op_launcher<I, Op,
    typename enable_if<
      is_same<
        typename associated_executor<
          Op>::asio_associated_executor_is_unspecialised,
        void
      >::value
    >::type>
{
  template <typename Condition, typename Handler, typename... Ops>
  static void launch(Op& op,
    const std::shared_ptr<parallel_group_state<
      Condition, Handler, Ops...> >& state)
  {
    std::move(op)(
        parallel_group_op_handler<I, Condition, Handler, Ops...>(state));
  }
};

template <typename Condition, typename Handler, typename... Ops>
struct parallel_group_cancellation_handler
{
  parallel_group_cancellation_handler(
    std::shared_ptr<parallel_group_state<Condition, Handler, Ops...> > state)
    : state_(std::move(state))
  {
  }

  void operator()(cancellation_type_t cancel_type)
  {
    // If we are the first place to request cancellation, i.e. no operation has
    // yet completed and requested cancellation, emit a signal for each
    // operation in the group.
    if (cancel_type != cancellation_type::none)
      if (auto state = state_.lock())
        if (state->cancellations_requested_++ == 0)
          for (std::size_t i = 0; i < sizeof...(Ops); ++i)
            state->cancellation_signals_[i].emit(cancel_type);
  }

  std::weak_ptr<parallel_group_state<Condition, Handler, Ops...> > state_;
};

template <typename Condition, typename Handler,
    typename... Ops, std::size_t... I>
void parallel_group_launch(Condition cancellation_condition, Handler handler,
    std::tuple<Ops...>& ops, std::index_sequence<I...>)
{
  // Get the user's completion handler's cancellation slot, so that we can allow
  // cancellation of the entire group.
  typename associated_cancellation_slot<Handler>::type slot
    = boost::asio::get_associated_cancellation_slot(handler);

  // Create the shared state for the operation.
  typedef parallel_group_state<Condition, Handler, Ops...> state_type;
  std::shared_ptr<state_type> state = std::allocate_shared<state_type>(
      boost::asio::detail::recycling_allocator<state_type,
        boost::asio::detail::thread_info_base::parallel_group_tag>(),
      std::move(cancellation_condition), std::move(handler));

  // Initiate each individual operation in the group.
  int fold[] = { 0,
    ( parallel_group_op_launcher<I, Ops>::launch(std::get<I>(ops), state),
      0 )...
  };
  (void)fold;

  // Check if any of the operations has already requested cancellation, and if
  // so, emit a signal for each operation in the group.
  if ((state->cancellations_requested_ -= sizeof...(Ops)) > 0)
    for (auto& signal : state->cancellation_signals_)
      signal.emit(state->cancel_type_);

  // Register a handler with the user's completion handler's cancellation slot.
  if (slot.is_connected())
    slot.template emplace<
      parallel_group_cancellation_handler<
        Condition, Handler, Ops...> >(state);
}

} // namespace detail
} // namespace experimental

template <typename R, typename... Args>
class async_result<
    experimental::detail::parallel_op_signature_probe,
    R(Args...)>
{
public:
  typedef experimental::detail::parallel_op_signature_probe_result<
    void(Args...)> return_type;

  template <typename Initiation, typename... InitArgs>
  static return_type initiate(Initiation&&,
      experimental::detail::parallel_op_signature_probe, InitArgs&&...)
  {
    return return_type{};
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename... Ops, typename DefaultCandidate>
struct associator<Associator,
    experimental::detail::parallel_group_completion_handler<Handler, Ops...>,
    DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const experimental::detail::parallel_group_completion_handler<
        Handler, Ops...>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_EXPERIMENTAL_PARALLEL_GROUP_HPP

/* parallel_group.hpp
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
*/