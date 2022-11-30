//
// experimental/impl/coro.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
#ifndef BOOST_ASIO_EXPERIMENTAL_IMPL_CORO_HPP
#define BOOST_ASIO_EXPERIMENTAL_IMPL_CORO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {

template <typename Yield, typename Return, typename Executor>
struct coro;

namespace detail {

struct coro_cancellation_source
{
  cancellation_slot slot;
  cancellation_state state;
  bool throw_if_cancelled_ = true;

  void reset_cancellation_state()
  {
    state = cancellation_state(slot);
  }

  template <typename Filter>
  void reset_cancellation_state(BOOST_ASIO_MOVE_ARG(Filter) filter)
  {
    state = cancellation_state(slot, BOOST_ASIO_MOVE_CAST(Filter)(filter));
  }

  template <typename InFilter, typename OutFilter>
  void reset_cancellation_state(BOOST_ASIO_MOVE_ARG(InFilter) in_filter,
      BOOST_ASIO_MOVE_ARG(OutFilter) out_filter)
  {
    state = cancellation_state(slot,
        BOOST_ASIO_MOVE_CAST(InFilter)(in_filter),
        BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter));
  }

  bool throw_if_cancelled() const
  {
    return throw_if_cancelled_;
  }

  void throw_if_cancelled(bool value)
  {
    throw_if_cancelled_ = value;
  }
};

template <typename Signature, typename Return, typename Executor>
struct coro_promise;

template <typename T>
struct is_noexcept : std::false_type
{
};

template <typename Return, typename... Args>
struct is_noexcept<Return(Args...)> : std::false_type
{
};

template <typename Return, typename... Args>
struct is_noexcept<Return(Args...) noexcept> : std::true_type
{
};

template <typename T>
constexpr bool is_noexcept_v = is_noexcept<T>::value;

template <typename T>
struct coro_error;

template <>
struct coro_error<boost::system::error_code>
{
  static boost::system::error_code invalid()
  {
    return boost::asio::error::fault;
  }

  static boost::system::error_code cancelled()
  {
    return boost::asio::error::operation_aborted;
  }

  static boost::system::error_code interrupted()
  {
    return boost::asio::error::interrupted;
  }

  static boost::system::error_code done()
  {
    return boost::asio::error::broken_pipe;
  }
};

template <>
struct coro_error<std::exception_ptr>
{
  static std::exception_ptr invalid()
  {
    return std::make_exception_ptr(
        boost::system::system_error(
          coro_error<boost::system::error_code>::invalid()));
  }

  static std::exception_ptr cancelled()
  {
    return std::make_exception_ptr(
        boost::system::system_error(
          coro_error<boost::system::error_code>::cancelled()));
  }

  static std::exception_ptr interrupted()
  {
    return std::make_exception_ptr(
        boost::system::system_error(
          coro_error<boost::system::error_code>::interrupted()));
  }

  static std::exception_ptr done()
  {
    return std::make_exception_ptr(
        boost::system::system_error(
          coro_error<boost::system::error_code>::done()));
  }
};

template <typename T, typename Coroutine >
struct coro_with_arg
{
  using coro_t = Coroutine;
  T value;
  coro_t& coro;

  struct awaitable_t
  {
    T value;
    coro_t& coro;

    constexpr static bool await_ready() { return false; }

    template <typename Y, typename R, typename E>
    auto await_suspend(coroutine_handle<coro_promise<Y, R, E>> h)
      -> coroutine_handle<>
    {
      auto& hp = h.promise();

      if constexpr (!coro_promise<Y, R, E>::is_noexcept)
      {
        if ((hp.cancel->state.cancelled() != cancellation_type::none)
            && hp.cancel->throw_if_cancelled_)
        {
          boost::asio::detail::throw_error(
              boost::asio::error::operation_aborted, "coro-cancelled");
        }
      }

      if (hp.get_executor() == coro.get_executor())
      {
        coro.coro_->awaited_from = h;
        coro.coro_->reset_error();
        coro.coro_->input_ = std::move(value);
        coro.coro_->cancel = hp.cancel;
        return coro.coro_->get_handle();
      }
      else
      {
        coro.coro_->awaited_from =
          dispatch_coroutine(
              boost::asio::prefer(hp.get_executor(),
                execution::outstanding_work.tracked),
                [h]() mutable { h.resume(); });

        coro.coro_->reset_error();
        coro.coro_->input_ = std::move(value);

        struct cancel_handler
        {
          using src = std::pair<cancellation_signal,
                detail::coro_cancellation_source>;

          std::shared_ptr<src> st = std::make_shared<src>();

          cancel_handler(E e, coro_t& coro) : e(e), coro_(coro.coro_)
          {
            st->second.state =
              cancellation_state(st->second.slot = st->first.slot());
          }

          E e;
          typename coro_t::promise_type* coro_;

          void operator()(cancellation_type ct)
          {
            boost::asio::dispatch(e, [ct, st = st]() mutable
            {
              auto & [sig, state] = *st;
              sig.emit(ct);
            });
          }
        };

        if (hp.cancel->state.slot().is_connected())
        {
          hp.cancel->state.slot().template emplace<cancel_handler>(
              coro.get_executor(), coro);
        }

        auto hh = detail::coroutine_handle<
          typename coro_t::promise_type>::from_promise(*coro.coro_);

        return dispatch_coroutine(
            coro.coro_->get_executor(), [hh]() mutable { hh.resume(); });
      }
    }

    auto await_resume() -> typename coro_t::result_type
    {
      coro.coro_->cancel = nullptr;
      coro.coro_->rethrow_if();
      return std::move(coro.coro_->result_);
    }
  };

  template <typename CompletionToken>
  auto async_resume(CompletionToken&& token) &&
  {
    return coro.async_resume(std::move(value),
        std::forward<CompletionToken>(token));
  }

  auto operator co_await() &&
  {
    return awaitable_t{std::move(value), coro};
  }
};

template <bool IsNoexcept>
struct coro_promise_error;

template <>
struct coro_promise_error<false>
{
  std::exception_ptr error_;

  void reset_error()
  {
    error_ = std::exception_ptr{};
  }

  void unhandled_exception()
  {
    error_ = std::current_exception();
  }

  void rethrow_if()
  {
    if (error_)
      std::rethrow_exception(error_);
  }
};

#if defined(__GNUC__)
# pragma GCC diagnostic push
# if defined(__clang__)
#  pragma GCC diagnostic ignored "-Wexceptions"
# else
#  pragma GCC diagnostic ignored "-Wterminate"
# endif
#elif defined(_MSC_VER)
# pragma warning(push)
# pragma warning (disable:4297)
#endif

template <>
struct coro_promise_error<true>
{
  void reset_error()
  {
  }

  void unhandled_exception() noexcept
  {
    throw;
  }

  void rethrow_if()
  {
  }
};

#if defined(__GNUC__)
# pragma GCC diagnostic pop
#elif defined(_MSC_VER)
# pragma warning(pop)
#endif

template <typename T = void>
struct yield_input
{
  T& value;
  coroutine_handle<> awaited_from{noop_coroutine()};

  bool await_ready() const noexcept
  {
    return false;
  }

  template <typename U>
  coroutine_handle<> await_suspend(coroutine_handle<U>) noexcept
  {
    return std::exchange(awaited_from, noop_coroutine());
  }

  T await_resume() const noexcept
  {
    return std::move(value);
  }
};

template <>
struct yield_input<void>
{
  coroutine_handle<> awaited_from{noop_coroutine()};

  bool await_ready() const noexcept
  {
    return false;
  }

  auto await_suspend(coroutine_handle<>) noexcept
  {
    return std::exchange(awaited_from, noop_coroutine());
  }

  constexpr void await_resume() const noexcept
  {
  }
};

struct coro_awaited_from
{
  coroutine_handle<> awaited_from{noop_coroutine()};

  auto final_suspend() noexcept
  {
    struct suspendor
    {
      coroutine_handle<> awaited_from;

      constexpr static bool await_ready() noexcept
      {
        return false;
      }

      auto await_suspend(coroutine_handle<>) noexcept
      {
        return std::exchange(awaited_from, noop_coroutine());
      }

      constexpr static void await_resume() noexcept
      {
      }
    };

    return suspendor{std::exchange(awaited_from, noop_coroutine())};
  }

  ~coro_awaited_from()
  {
    awaited_from.resume();
  }//must be on the right executor
};

template <typename Yield, typename Input, typename Return>
struct coro_promise_exchange : coro_awaited_from
{
  using result_type = coro_result_t<Yield, Return>;

  result_type result_;
  Input input_;

  auto yield_value(Yield&& y)
  {
    result_ = std::move(y);
    return yield_input<Input>{std::move(input_),
        std::exchange(awaited_from, noop_coroutine())};
  }

  auto yield_value(const Yield& y)
  {
    result_ = y;
    return yield_input<Input>{std::move(input_),
        std::exchange(awaited_from, noop_coroutine())};
  }

  void return_value(const Return& r)
  {
    result_ = r;
  }

  void return_value(Return&& r)
  {
    result_ = std::move(r);
  }
};

template <typename YieldReturn>
struct coro_promise_exchange<YieldReturn, void, YieldReturn> : coro_awaited_from
{
  using result_type = coro_result_t<YieldReturn, YieldReturn>;

  result_type result_;

  auto yield_value(const YieldReturn& y)
  {
    result_ = y;
    return yield_input<void>{std::exchange(awaited_from, noop_coroutine())};
  }

  auto yield_value(YieldReturn&& y)
  {
    result_ = std::move(y);
    return yield_input<void>{std::exchange(awaited_from, noop_coroutine())};
  }

  void return_value(const YieldReturn& r)
  {
    result_ = r;
  }

  void return_value(YieldReturn&& r)
  {
    result_ = std::move(r);
  }
};

template <typename Yield, typename Return>
struct coro_promise_exchange<Yield, void, Return> : coro_awaited_from
{
  using result_type = coro_result_t<Yield, Return>;

  result_type result_;

  auto yield_value(const Yield& y)
  {
    result_.template emplace<0>(y);
    return yield_input<void>{std::exchange(awaited_from, noop_coroutine())};
  }

  auto yield_value(Yield&& y)
  {
    result_.template emplace<0>(std::move(y));
    return yield_input<void>{std::exchange(awaited_from, noop_coroutine())};
  }

  void return_value(const Return& r)
  {
    result_.template emplace<1>(r);
  }

  void return_value(Return&& r)
  {
    result_.template emplace<1>(std::move(r));
  }
};

template <typename Yield, typename Input>
struct coro_promise_exchange<Yield, Input, void> : coro_awaited_from
{
  using result_type = coro_result_t<Yield, void>;

  result_type result_;
  Input input_;

  auto yield_value(Yield&& y)
  {
    result_ = std::move(y);
    return yield_input<Input>{input_,
                              std::exchange(awaited_from, noop_coroutine())};
  }

  auto yield_value(const Yield& y)
  {
    result_ = y;
    return yield_input<Input>{input_,
                              std::exchange(awaited_from, noop_coroutine())};
  }

  void return_void()
  {
    result_.reset();
  }
};

template <typename Return>
struct coro_promise_exchange<void, void, Return> : coro_awaited_from
{
  using result_type = coro_result_t<void, Return>;

  result_type result_;

  void yield_value();

  void return_value(const Return& r)
  {
    result_ = r;
  }

  void return_value(Return&& r)
  {
    result_ = std::move(r);
  }
};

template <>
struct coro_promise_exchange<void, void, void> : coro_awaited_from
{
  void return_void() {}

  void yield_value();
};

template <typename Yield>
struct coro_promise_exchange<Yield, void, void> : coro_awaited_from
{
  using result_type = coro_result_t<Yield, void>;

  result_type result_;

  auto yield_value(const Yield& y)
  {
    result_ = y;
    return yield_input<void>{std::exchange(awaited_from, noop_coroutine())};
  }

  auto yield_value(Yield&& y)
  {
    result_ = std::move(y);
    return yield_input<void>{std::exchange(awaited_from, noop_coroutine())};
  }

  void return_void()
  {
    result_.reset();
  }
};

template <typename Yield, typename Return, typename Executor>
struct coro_promise final :
  coro_promise_allocator<coro<Yield, Return, Executor>>,
  coro_promise_error<coro_traits<Yield, Return, Executor>::is_noexcept>,
  coro_promise_exchange<
      typename coro_traits<Yield, Return, Executor>::yield_type,
      typename coro_traits<Yield, Return, Executor>::input_type,
      typename coro_traits<Yield, Return, Executor>::return_type>
{
  using coro_type = coro<Yield, Return, Executor>;

  auto handle()
  {
    return coroutine_handle<coro_promise>::from_promise(this);
  }

  using executor_type = Executor;

  executor_type executor_;

  std::optional<coro_cancellation_source> cancel_source;
  coro_cancellation_source * cancel;

  using allocator_type =
    typename std::allocator_traits<associated_allocator_t<Executor>>::
      template rebind_alloc<std::byte>;
  using traits = coro_traits<Yield, Return, Executor>;

  using input_type = typename traits::input_type;
  using yield_type = typename traits::yield_type;
  using return_type = typename traits::return_type;
  using error_type = typename traits::error_type;
  using result_type = typename traits::result_type;
  constexpr static bool is_noexcept = traits::is_noexcept;

  auto get_executor() const -> Executor
  {
    return executor_;
  }

  auto get_handle()
  {
    return coroutine_handle<coro_promise>::from_promise(*this);
  }

  template <typename... Args>
  coro_promise(Executor executor, Args&&...) noexcept
    : executor_(std::move(executor))
  {
  }

  template <typename First, typename... Args>
  coro_promise(First&&, Executor executor, Args&&...) noexcept
    : executor_(std::move(executor))
  {
  }

  template <typename First, detail::execution_context Context, typename... Args>
  coro_promise(First&&, Context&& ctx, Args&&...) noexcept
    : executor_(ctx.get_executor())
  {
  }

  template <detail::execution_context Context, typename... Args>
  coro_promise(Context&& ctx, Args&&...) noexcept
    : executor_(ctx.get_executor())
  {
  }

  auto get_return_object()
  {
    return coro<Yield, Return, Executor>{this};
  }

  auto initial_suspend() noexcept
  {
    return suspend_always{};
  }

  using coro_promise_exchange<
      typename coro_traits<Yield, Return, Executor>::yield_type,
      typename coro_traits<Yield, Return, Executor>::input_type,
      typename coro_traits<Yield, Return, Executor>::return_type>::yield_value;

  auto await_transform(this_coro::executor_t) const
  {
    struct exec_helper
    {
      const executor_type& value;

      constexpr static bool await_ready() noexcept
      {
        return true;
      }

      constexpr static void await_suspend(coroutine_handle<>) noexcept
      {
      }

      executor_type await_resume() const noexcept
      {
        return value;
      }
    };

    return exec_helper{executor_};
  }

  auto await_transform(this_coro::cancellation_state_t) const
  {
    struct exec_helper
    {
      const boost::asio::cancellation_state& value;

      constexpr static bool await_ready() noexcept
      {
        return true;
      }

      constexpr static void await_suspend(coroutine_handle<>) noexcept
      {
      }

      boost::asio::cancellation_state await_resume() const noexcept
      {
        return value;
      }
    };
    assert(cancel);
    return exec_helper{cancel->state};
  }

  // This await transformation resets the associated cancellation state.
  auto await_transform(this_coro::reset_cancellation_state_0_t) noexcept
  {
    struct result
    {
      detail::coro_cancellation_source * src_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume() const
      {
        return src_->reset_cancellation_state();
      }
    };

    return result{cancel};
  }

  // This await transformation resets the associated cancellation state.
  template <typename Filter>
  auto await_transform(
      this_coro::reset_cancellation_state_1_t<Filter> reset) noexcept
  {
    struct result
    {
      detail::coro_cancellation_source* src_;
      Filter filter_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume()
      {
        return src_->reset_cancellation_state(
            BOOST_ASIO_MOVE_CAST(Filter)(filter_));
      }
    };

    return result{cancel, BOOST_ASIO_MOVE_CAST(Filter)(reset.filter)};
  }

  // This await transformation resets the associated cancellation state.
  template <typename InFilter, typename OutFilter>
  auto await_transform(
      this_coro::reset_cancellation_state_2_t<InFilter, OutFilter> reset)
  noexcept
  {
    struct result
    {
      detail::coro_cancellation_source* src_;
      InFilter in_filter_;
      OutFilter out_filter_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume()
      {
        return src_->reset_cancellation_state(
            BOOST_ASIO_MOVE_CAST(InFilter)(in_filter_),
            BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter_));
      }
    };

    return result{cancel,
        BOOST_ASIO_MOVE_CAST(InFilter)(reset.in_filter),
        BOOST_ASIO_MOVE_CAST(OutFilter)(reset.out_filter)};
  }

  // This await transformation determines whether cancellation is propagated as
  // an exception.
  auto await_transform(this_coro::throw_if_cancelled_0_t) noexcept
    requires (!is_noexcept)
  {
    struct result
    {
      detail::coro_cancellation_source* src_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume()
      {
        return src_->throw_if_cancelled();
      }
    };

    return result{cancel};
  }

  // This await transformation sets whether cancellation is propagated as an
  // exception.
  auto await_transform(
      this_coro::throw_if_cancelled_1_t throw_if_cancelled) noexcept
    requires (!is_noexcept)
  {
    struct result
    {
      detail::coro_cancellation_source* src_;
      bool value_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume()
      {
        src_->throw_if_cancelled(value_);
      }
    };

    return result{cancel, throw_if_cancelled.value};
  }

  template <typename Yield_, typename Return_, typename Executor_>
  auto await_transform(coro<Yield_, Return_, Executor_>& kr) -> decltype(auto)
  {
    return kr;
  }

  template <typename Yield_, typename Return_, typename Executor_>
  auto await_transform(coro<Yield_, Return_, Executor_>&& kr)
  {
    return std::move(kr);
  }

  template <typename T_, typename Coroutine >
  auto await_transform(coro_with_arg<T_, Coroutine>&& kr) -> decltype(auto)
  {
    return std::move(kr);
  }

  template <typename T_>
    requires requires(T_ t) {{ t.async_wait(use_coro) }; }
  auto await_transform(T_& t) -> decltype(auto)
  {
    return await_transform(t.async_wait(use_coro));
  }

  template <typename... Ts>
  auto await_transform(coro_init_handler<Executor, Ts...>&& kr) const
  {
    assert(cancel);
    if constexpr (is_noexcept)
      return std::move(kr).as_noexcept(cancel->state.slot());
    else
    {
      if ((cancel->state.cancelled() != cancellation_type::none)
          && cancel->throw_if_cancelled_)
      {
        boost::asio::detail::throw_error(
            boost::asio::error::operation_aborted, "coro-cancelled");
      }
      return std::move(kr).as_throwing(cancel->state.slot());
    }
  }
};

} // namespace detail

template <typename Yield, typename Return, typename Executor>
struct coro<Yield, Return, Executor>::awaitable_t
{
  coro& coro_;

  constexpr static bool await_ready() { return false; }

  template <typename Y, typename R, typename E>
  auto await_suspend(
      detail::coroutine_handle<detail::coro_promise<Y, R, E>> h)
    -> detail::coroutine_handle<>
  {
    auto& hp = h.promise();

    if constexpr (!detail::coro_promise<Y, R, E>::is_noexcept)
    {
      if ((hp.cancel->state.cancelled() != cancellation_type::none)
          && hp.cancel->throw_if_cancelled_)
      {
        boost::asio::detail::throw_error(
            boost::asio::error::operation_aborted, "coro-cancelled");
      }
    }

    if (hp.get_executor() == coro_.get_executor())
    {
      coro_.coro_->awaited_from  = h;
      coro_.coro_->cancel = hp.cancel;
      coro_.coro_->reset_error();

      return coro_.coro_->get_handle();
    }
    else
    {
      coro_.coro_->awaited_from = detail::dispatch_coroutine(
          boost::asio::prefer(hp.get_executor(),
            execution::outstanding_work.tracked),
          [h]() mutable
          {
            h.resume();
          });

      coro_.coro_->reset_error();

      struct cancel_handler
      {
        std::shared_ptr<std::pair<cancellation_signal,
          detail::coro_cancellation_source>> st = std::make_shared<
            std::pair<cancellation_signal, detail::coro_cancellation_source>>();

        cancel_handler(E e, coro& coro) : e(e), coro_(coro.coro_)
        {
          st->second.state = cancellation_state(
              st->second.slot = st->first.slot());
        }

        E e;
        typename coro::promise_type* coro_;

        void operator()(cancellation_type ct)
        {
          boost::asio::dispatch(e,
              [ct, st = st]() mutable
              {
                auto & [sig, state] = *st;
                sig.emit(ct);
              });
        }
      };

      if (hp.cancel->state.slot().is_connected())
      {
        hp.cancel->state.slot().template emplace<cancel_handler>(
            coro_.get_executor(), coro_);
      }

      auto hh = detail::coroutine_handle<
        detail::coro_promise<Yield, Return, Executor>>::from_promise(
            *coro_.coro_);

      return detail::dispatch_coroutine(
          coro_.coro_->get_executor(),
          [hh]() mutable { hh.resume(); });
    }
  }

  auto await_resume() -> result_type
  {
    coro_.coro_->cancel = nullptr;
    coro_.coro_->rethrow_if();
    if constexpr (!std::is_void_v<result_type>)
      return std::move(coro_.coro_->result_);
  }
};

template <typename Yield, typename Return, typename Executor>
struct coro<Yield, Return, Executor>::initiate_async_resume
{
  typedef Executor executor_type;

  explicit initiate_async_resume(coro* self)
    : coro_(self->coro_)
  {
  }

  executor_type get_executor() const noexcept
  {
    return coro_->get_executor();
  }

  template <typename E, typename WaitHandler>
  auto handle(E exec, WaitHandler&& handler,
      std::true_type /* error is noexcept */,
      std::true_type /* result is void */)  //noexcept
  {
    return [this, coro = coro_,
        h = std::forward<WaitHandler>(handler),
        exec = std::move(exec)]() mutable
    {
      assert(coro);

      auto ch = detail::coroutine_handle<promise_type>::from_promise(*coro);
      assert(ch && !ch.done());
      assert(coro->awaited_from == detail::noop_coroutine());

      coro->awaited_from = post_coroutine(std::move(exec), std::move(h));
      coro->reset_error();
      ch.resume();
    };
  }

  template <typename E, typename WaitHandler>
  requires (!std::is_void_v<result_type>)
  auto handle(E exec, WaitHandler&& handler,
      std::true_type /* error is noexcept */,
      std::false_type  /* result is void */)  //noexcept
  {
    return [coro = coro_,
        h = std::forward<WaitHandler>(handler),
        exec = std::move(exec)]() mutable
    {
      assert(coro);

      auto ch = detail::coroutine_handle<promise_type>::from_promise(*coro);
      assert(ch && !ch.done());
      assert(coro->awaited_from == detail::noop_coroutine());

      coro->awaited_from = detail::post_coroutine(exec,
          [coro, h = std::move(h)]() mutable
          {
            std::move(h)(std::move(coro->result_));
          });
      coro->reset_error();
      ch.resume();
    };
  }

  template <typename E, typename WaitHandler>
  auto handle(E exec, WaitHandler&& handler,
      std::false_type /* error is noexcept */,
      std::true_type /* result is void */)
  {
    return [coro = coro_,
        h = std::forward<WaitHandler>(handler),
        exec = std::move(exec)]() mutable
    {
      if (!coro)
      {
        boost::asio::post(exec,
            [h = std::move(h)]() mutable
            {
              h(detail::coro_error<error_type>::invalid());
            });
        return;
      }

      auto ch = detail::coroutine_handle<promise_type>::from_promise(*coro);
      if (!ch)
      {
        boost::asio::post(exec,
            [h = std::move(h)]() mutable
            {
              h(detail::coro_error<error_type>::invalid());
            });
      }
      else if (ch.done())
      {
        boost::asio::post(exec,
            [h = std::move(h)]() mutable
            {
              h(detail::coro_error<error_type>::done());
            });
      }
      else
      {
        assert(coro->awaited_from == detail::noop_coroutine());
        coro->awaited_from =
          detail::post_coroutine(exec,
              [coro, h = std::move(h)]() mutable
              {
                std::move(h)(std::move(coro->error_));
              });
        coro->reset_error();
        ch.resume();
      }
    };
  }

  template <typename E, typename WaitHandler>
  auto handle(E exec, WaitHandler&& handler,
      std::false_type /* error is noexcept */,
      std::false_type  /* result is void */)
  {
    return [coro = coro_,
        h = std::forward<WaitHandler>(handler),
        exec = std::move(exec)]() mutable
    {
      if (!coro)
      {
        boost::asio::post(exec,
            [h = std::move(h)]() mutable
            {
              h(detail::coro_error<error_type>::invalid(), result_type{});
            });
        return;
      }

      auto ch =
        detail::coroutine_handle<promise_type>::from_promise(*coro);
      if (!ch)
      {
        boost::asio::post(exec,
            [h = std::move(h)]() mutable
            {
              h(detail::coro_error<error_type>::invalid(), result_type{});
            });
      }
      else if (ch.done())
      {
        boost::asio::post(exec,
            [h = std::move(h)]() mutable
            {
              h(detail::coro_error<error_type>::done(), result_type{});
            });
      }
      else
      {
        assert(coro->awaited_from == detail::noop_coroutine());
        coro->awaited_from =
          detail::post_coroutine(exec,
              [h = std::move(h), coro]() mutable
              {
                std::move(h)(
                    std::move(coro->error_),
                    std::move(coro->result_));
              });
        coro->reset_error();
        ch.resume();
      }
    };
  }

  template <typename WaitHandler>
  void operator()(WaitHandler&& handler)
  {
    const auto exec = boost::asio::prefer(
        get_associated_executor(handler, get_executor()),
        execution::outstanding_work.tracked);

    coro_->cancel = &coro_->cancel_source.emplace();
    coro_->cancel->state = cancellation_state(
        coro_->cancel->slot = get_associated_cancellation_slot(handler));
    boost::asio::dispatch(get_executor(),
        handle(exec, std::forward<WaitHandler>(handler),
          std::integral_constant<bool, is_noexcept>{},
          std::is_void<result_type>{}));
  }

  template <typename WaitHandler, typename Input>
  void operator()(WaitHandler&& handler, Input&& input)
  {
    const auto exec = boost::asio::prefer(
        get_associated_executor(handler, get_executor()),
        execution::outstanding_work.tracked);

    coro_->cancel = &coro_->cancel_source.emplace();
    coro_->cancel->state = cancellation_state(
        coro_->cancel->slot = get_associated_cancellation_slot(handler));
    boost::asio::dispatch(get_executor(),
        [h = handle(exec, std::forward<WaitHandler>(handler),
            std::integral_constant<bool, is_noexcept>{},
            std::is_void<result_type>{}),
            in = std::forward<Input>(input), coro = coro_]() mutable
        {
          coro->input_ = std::move(in);
          std::move(h)();
        });
  }

private:
  typename coro::promise_type* coro_;
};

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_IMPL_CORO_HPP

/* coro.hpp
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
*/