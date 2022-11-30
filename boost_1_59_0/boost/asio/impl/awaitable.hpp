//
// impl/awaitable.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_AWAITABLE_HPP
#define BOOST_ASIO_IMPL_AWAITABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <exception>
#include <new>
#include <tuple>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/cancellation_state.hpp>
#include <boost/asio/detail/thread_context.hpp>
#include <boost/asio/detail/thread_info_base.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/post.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/this_coro.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct awaitable_thread_has_context_switched {};

// An awaitable_thread represents a thread-of-execution that is composed of one
// or more "stack frames", with each frame represented by an awaitable_frame.
// All execution occurs in the context of the awaitable_thread's executor. An
// awaitable_thread continues to "pump" the stack frames by repeatedly resuming
// the top stack frame until the stack is empty, or until ownership of the
// stack is transferred to another awaitable_thread object.
//
//                +------------------------------------+
//                | top_of_stack_                      |
//                |                                    V
// +--------------+---+                            +-----------------+
// |                  |                            |                 |
// | awaitable_thread |<---------------------------+ awaitable_frame |
// |                  |           attached_thread_ |                 |
// +--------------+---+           (Set only when   +---+-------------+
//                |               frames are being     |
//                |               actively pumped      | caller_
//                |               by a thread, and     |
//                |               then only for        V
//                |               the top frame.)  +-----------------+
//                |                                |                 |
//                |                                | awaitable_frame |
//                |                                |                 |
//                |                                +---+-------------+
//                |                                    |
//                |                                    | caller_
//                |                                    :
//                |                                    :
//                |                                    |
//                |                                    V
//                |                                +-----------------+
//                | bottom_of_stack_               |                 |
//                +------------------------------->| awaitable_frame |
//                                                 |                 |
//                                                 +-----------------+

template <typename Executor>
class awaitable_frame_base
{
public:
#if !defined(BOOST_ASIO_DISABLE_AWAITABLE_FRAME_RECYCLING)
  void* operator new(std::size_t size)
  {
    return boost::asio::detail::thread_info_base::allocate(
        boost::asio::detail::thread_info_base::awaitable_frame_tag(),
        boost::asio::detail::thread_context::top_of_thread_call_stack(),
        size);
  }

  void operator delete(void* pointer, std::size_t size)
  {
    boost::asio::detail::thread_info_base::deallocate(
        boost::asio::detail::thread_info_base::awaitable_frame_tag(),
        boost::asio::detail::thread_context::top_of_thread_call_stack(),
        pointer, size);
  }
#endif // !defined(BOOST_ASIO_DISABLE_AWAITABLE_FRAME_RECYCLING)

  // The frame starts in a suspended state until the awaitable_thread object
  // pumps the stack.
  auto initial_suspend() noexcept
  {
    return suspend_always();
  }

  // On final suspension the frame is popped from the top of the stack.
  auto final_suspend() noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;

      bool await_ready() const noexcept
      {
        return false;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
        this->this_->pop_frame();
      }

      void await_resume() const noexcept
      {
      }
    };

    return result{this};
  }

  void set_except(std::exception_ptr e) noexcept
  {
    pending_exception_ = e;
  }

  void set_error(const boost::system::error_code& ec)
  {
    this->set_except(std::make_exception_ptr(boost::system::system_error(ec)));
  }

  void unhandled_exception()
  {
    set_except(std::current_exception());
  }

  void rethrow_exception()
  {
    if (pending_exception_)
    {
      std::exception_ptr ex = std::exchange(pending_exception_, nullptr);
      std::rethrow_exception(ex);
    }
  }

  void clear_cancellation_slot()
  {
    this->attached_thread_->entry_point()->cancellation_state_.slot().clear();
  }

  template <typename T>
  auto await_transform(awaitable<T, Executor> a) const
  {
    if (attached_thread_->entry_point()->throw_if_cancelled_)
      if (!!attached_thread_->get_cancellation_state().cancelled())
        do_throw_error(boost::asio::error::operation_aborted, "co_await");
    return a;
  }

  // This await transformation obtains the associated executor of the thread of
  // execution.
  auto await_transform(this_coro::executor_t) noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume() const noexcept
      {
        return this_->attached_thread_->get_executor();
      }
    };

    return result{this};
  }

  // This await transformation obtains the associated cancellation state of the
  // thread of execution.
  auto await_transform(this_coro::cancellation_state_t) noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume() const noexcept
      {
        return this_->attached_thread_->get_cancellation_state();
      }
    };

    return result{this};
  }

  // This await transformation resets the associated cancellation state.
  auto await_transform(this_coro::reset_cancellation_state_0_t) noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume() const
      {
        return this_->attached_thread_->reset_cancellation_state();
      }
    };

    return result{this};
  }

  // This await transformation resets the associated cancellation state.
  template <typename Filter>
  auto await_transform(
      this_coro::reset_cancellation_state_1_t<Filter> reset) noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;
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
        return this_->attached_thread_->reset_cancellation_state(
            BOOST_ASIO_MOVE_CAST(Filter)(filter_));
      }
    };

    return result{this, BOOST_ASIO_MOVE_CAST(Filter)(reset.filter)};
  }

  // This await transformation resets the associated cancellation state.
  template <typename InFilter, typename OutFilter>
  auto await_transform(
      this_coro::reset_cancellation_state_2_t<InFilter, OutFilter> reset)
    noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;
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
        return this_->attached_thread_->reset_cancellation_state(
            BOOST_ASIO_MOVE_CAST(InFilter)(in_filter_),
            BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter_));
      }
    };

    return result{this,
        BOOST_ASIO_MOVE_CAST(InFilter)(reset.in_filter),
        BOOST_ASIO_MOVE_CAST(OutFilter)(reset.out_filter)};
  }

  // This await transformation determines whether cancellation is propagated as
  // an exception.
  auto await_transform(this_coro::throw_if_cancelled_0_t)
    noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      auto await_resume()
      {
        return this_->attached_thread_->throw_if_cancelled();
      }
    };

    return result{this};
  }

  // This await transformation sets whether cancellation is propagated as an
  // exception.
  auto await_transform(this_coro::throw_if_cancelled_1_t throw_if_cancelled)
    noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;
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
        this_->attached_thread_->throw_if_cancelled(value_);
      }
    };

    return result{this, throw_if_cancelled.value};
  }

  // This await transformation is used to run an async operation's initiation
  // function object after the coroutine has been suspended. This ensures that
  // immediate resumption of the coroutine in another thread does not cause a
  // race condition.
  template <typename Function>
  auto await_transform(Function f,
      typename enable_if<
        is_convertible<
          typename result_of<Function(awaitable_frame_base*)>::type,
          awaitable_thread<Executor>*
        >::value
      >::type* = nullptr)
  {
    struct result
    {
      Function function_;
      awaitable_frame_base* this_;

      bool await_ready() const noexcept
      {
        return false;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
        function_(this_);
      }

      void await_resume() const noexcept
      {
      }
    };

    return result{std::move(f), this};
  }

  // Access the awaitable thread's has_context_switched_ flag.
  auto await_transform(detail::awaitable_thread_has_context_switched) noexcept
  {
    struct result
    {
      awaitable_frame_base* this_;

      bool await_ready() const noexcept
      {
        return true;
      }

      void await_suspend(coroutine_handle<void>) noexcept
      {
      }

      bool& await_resume() const noexcept
      {
        return this_->attached_thread_->entry_point()->has_context_switched_;
      }
    };

    return result{this};
  }

  void attach_thread(awaitable_thread<Executor>* handler) noexcept
  {
    attached_thread_ = handler;
  }

  awaitable_thread<Executor>* detach_thread() noexcept
  {
    attached_thread_->entry_point()->has_context_switched_ = true;
    return std::exchange(attached_thread_, nullptr);
  }

  void push_frame(awaitable_frame_base<Executor>* caller) noexcept
  {
    caller_ = caller;
    attached_thread_ = caller_->attached_thread_;
    attached_thread_->entry_point()->top_of_stack_ = this;
    caller_->attached_thread_ = nullptr;
  }

  void pop_frame() noexcept
  {
    if (caller_)
      caller_->attached_thread_ = attached_thread_;
    attached_thread_->entry_point()->top_of_stack_ = caller_;
    attached_thread_ = nullptr;
    caller_ = nullptr;
  }

  void resume()
  {
    coro_.resume();
  }

  void destroy()
  {
    coro_.destroy();
  }

protected:
  coroutine_handle<void> coro_ = nullptr;
  awaitable_thread<Executor>* attached_thread_ = nullptr;
  awaitable_frame_base<Executor>* caller_ = nullptr;
  std::exception_ptr pending_exception_ = nullptr;
};

template <typename T, typename Executor>
class awaitable_frame
  : public awaitable_frame_base<Executor>
{
public:
  awaitable_frame() noexcept
  {
  }

  awaitable_frame(awaitable_frame&& other) noexcept
    : awaitable_frame_base<Executor>(std::move(other))
  {
  }

  ~awaitable_frame()
  {
    if (has_result_)
      static_cast<T*>(static_cast<void*>(result_))->~T();
  }

  awaitable<T, Executor> get_return_object() noexcept
  {
    this->coro_ = coroutine_handle<awaitable_frame>::from_promise(*this);
    return awaitable<T, Executor>(this);
  };

  template <typename U>
  void return_value(U&& u)
  {
    new (&result_) T(std::forward<U>(u));
    has_result_ = true;
  }

  template <typename... Us>
  void return_values(Us&&... us)
  {
    this->return_value(std::forward_as_tuple(std::forward<Us>(us)...));
  }

  T get()
  {
    this->caller_ = nullptr;
    this->rethrow_exception();
    return std::move(*static_cast<T*>(static_cast<void*>(result_)));
  }

private:
  alignas(T) unsigned char result_[sizeof(T)];
  bool has_result_ = false;
};

template <typename Executor>
class awaitable_frame<void, Executor>
  : public awaitable_frame_base<Executor>
{
public:
  awaitable<void, Executor> get_return_object()
  {
    this->coro_ = coroutine_handle<awaitable_frame>::from_promise(*this);
    return awaitable<void, Executor>(this);
  };

  void return_void()
  {
  }

  void get()
  {
    this->caller_ = nullptr;
    this->rethrow_exception();
  }
};

struct awaitable_thread_entry_point {};

template <typename Executor>
class awaitable_frame<awaitable_thread_entry_point, Executor>
  : public awaitable_frame_base<Executor>
{
public:
  awaitable_frame()
    : top_of_stack_(0),
      has_executor_(false),
      has_context_switched_(false),
      throw_if_cancelled_(true)
  {
  }

  ~awaitable_frame()
  {
    if (has_executor_)
      u_.executor_.~Executor();
  }

  awaitable<awaitable_thread_entry_point, Executor> get_return_object()
  {
    this->coro_ = coroutine_handle<awaitable_frame>::from_promise(*this);
    return awaitable<awaitable_thread_entry_point, Executor>(this);
  };

  void return_void()
  {
  }

  void get()
  {
    this->caller_ = nullptr;
    this->rethrow_exception();
  }

private:
  template <typename> friend class awaitable_frame_base;
  template <typename, typename> friend class awaitable_handler_base;
  template <typename> friend class awaitable_thread;

  union u
  {
    u() {}
    ~u() {}
    char c_;
    Executor executor_;
  } u_;

  awaitable_frame_base<Executor>* top_of_stack_;
  boost::asio::cancellation_slot parent_cancellation_slot_;
  boost::asio::cancellation_state cancellation_state_;
  bool has_executor_;
  bool has_context_switched_;
  bool throw_if_cancelled_;
};

template <typename Executor>
class awaitable_thread
{
public:
  typedef Executor executor_type;
  typedef cancellation_slot cancellation_slot_type;

  // Construct from the entry point of a new thread of execution.
  awaitable_thread(awaitable<awaitable_thread_entry_point, Executor> p,
      const Executor& ex, cancellation_slot parent_cancel_slot,
      cancellation_state cancel_state)
    : bottom_of_stack_(std::move(p))
  {
    bottom_of_stack_.frame_->top_of_stack_ = bottom_of_stack_.frame_;
    new (&bottom_of_stack_.frame_->u_.executor_) Executor(ex);
    bottom_of_stack_.frame_->has_executor_ = true;
    bottom_of_stack_.frame_->parent_cancellation_slot_ = parent_cancel_slot;
    bottom_of_stack_.frame_->cancellation_state_ = cancel_state;
  }

  // Transfer ownership from another awaitable_thread.
  awaitable_thread(awaitable_thread&& other) noexcept
    : bottom_of_stack_(std::move(other.bottom_of_stack_))
  {
  }

  // Clean up with a last ditch effort to ensure the thread is unwound within
  // the context of the executor.
  ~awaitable_thread()
  {
    if (bottom_of_stack_.valid())
    {
      // Coroutine "stack unwinding" must be performed through the executor.
      auto* bottom_frame = bottom_of_stack_.frame_;
      (post)(bottom_frame->u_.executor_,
          [a = std::move(bottom_of_stack_)]() mutable
          {
            (void)awaitable<awaitable_thread_entry_point, Executor>(
                std::move(a));
          });
    }
  }

  awaitable_frame<awaitable_thread_entry_point, Executor>* entry_point()
  {
    return bottom_of_stack_.frame_;
  }

  executor_type get_executor() const noexcept
  {
    return bottom_of_stack_.frame_->u_.executor_;
  }

  cancellation_state get_cancellation_state() const noexcept
  {
    return bottom_of_stack_.frame_->cancellation_state_;
  }

  void reset_cancellation_state()
  {
    bottom_of_stack_.frame_->cancellation_state_ =
      cancellation_state(bottom_of_stack_.frame_->parent_cancellation_slot_);
  }

  template <typename Filter>
  void reset_cancellation_state(BOOST_ASIO_MOVE_ARG(Filter) filter)
  {
    bottom_of_stack_.frame_->cancellation_state_ =
      cancellation_state(bottom_of_stack_.frame_->parent_cancellation_slot_,
        BOOST_ASIO_MOVE_CAST(Filter)(filter));
  }

  template <typename InFilter, typename OutFilter>
  void reset_cancellation_state(BOOST_ASIO_MOVE_ARG(InFilter) in_filter,
      BOOST_ASIO_MOVE_ARG(OutFilter) out_filter)
  {
    bottom_of_stack_.frame_->cancellation_state_ =
      cancellation_state(bottom_of_stack_.frame_->parent_cancellation_slot_,
        BOOST_ASIO_MOVE_CAST(InFilter)(in_filter),
        BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter));
  }

  bool throw_if_cancelled() const
  {
    return bottom_of_stack_.frame_->throw_if_cancelled_;
  }

  void throw_if_cancelled(bool value)
  {
    bottom_of_stack_.frame_->throw_if_cancelled_ = value;
  }

  cancellation_slot_type get_cancellation_slot() const noexcept
  {
    return bottom_of_stack_.frame_->cancellation_state_.slot();
  }

  // Launch a new thread of execution.
  void launch()
  {
    bottom_of_stack_.frame_->top_of_stack_->attach_thread(this);
    pump();
  }

protected:
  template <typename> friend class awaitable_frame_base;

  // Repeatedly resume the top stack frame until the stack is empty or until it
  // has been transferred to another resumable_thread object.
  void pump()
  {
    do
      bottom_of_stack_.frame_->top_of_stack_->resume();
    while (bottom_of_stack_.frame_ && bottom_of_stack_.frame_->top_of_stack_);

    if (bottom_of_stack_.frame_)
    {
      awaitable<awaitable_thread_entry_point, Executor> a(
          std::move(bottom_of_stack_));
      a.frame_->rethrow_exception();
    }
  }

  awaitable<awaitable_thread_entry_point, Executor> bottom_of_stack_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#if !defined(GENERATING_DOCUMENTATION)
# if defined(BOOST_ASIO_HAS_STD_COROUTINE)

namespace std {

template <typename T, typename Executor, typename... Args>
struct coroutine_traits<boost::asio::awaitable<T, Executor>, Args...>
{
  typedef boost::asio::detail::awaitable_frame<T, Executor> promise_type;
};

} // namespace std

# else // defined(BOOST_ASIO_HAS_STD_COROUTINE)

namespace std { namespace experimental {

template <typename T, typename Executor, typename... Args>
struct coroutine_traits<boost::asio::awaitable<T, Executor>, Args...>
{
  typedef boost::asio::detail::awaitable_frame<T, Executor> promise_type;
};

}} // namespace std::experimental

# endif // defined(BOOST_ASIO_HAS_STD_COROUTINE)
#endif // !defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_AWAITABLE_HPP

/* awaitable.hpp
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
*/