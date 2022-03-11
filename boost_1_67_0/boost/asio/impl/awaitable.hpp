//
// impl/awaitable.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <utility>
#include <boost/asio/detail/thread_context.hpp>
#include <boost/asio/detail/thread_info_base.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/post.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/this_coro.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

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
        boost::asio::detail::thread_context::thread_call_stack::top(),
        size);
  }

  void operator delete(void* pointer, std::size_t size)
  {
    boost::asio::detail::thread_info_base::deallocate(
        boost::asio::detail::thread_info_base::awaitable_frame_tag(),
        boost::asio::detail::thread_context::thread_call_stack::top(),
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
        this_->pop_frame();
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

  template <typename T>
  auto await_transform(awaitable<T, Executor> a) const
  {
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
      >::type* = 0)
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

  void attach_thread(awaitable_thread<Executor>* handler) noexcept
  {
    attached_thread_ = handler;
  }

  awaitable_thread<Executor>* detach_thread() noexcept
  {
    return std::exchange(attached_thread_, nullptr);
  }

  void push_frame(awaitable_frame_base<Executor>* caller) noexcept
  {
    caller_ = caller;
    attached_thread_ = caller_->attached_thread_;
    attached_thread_->top_of_stack_ = this;
    caller_->attached_thread_ = nullptr;
  }

  void pop_frame() noexcept
  {
    if (caller_)
      caller_->attached_thread_ = attached_thread_;
    attached_thread_->top_of_stack_ = caller_;
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

template <typename Executor>
class awaitable_thread
{
public:
  typedef Executor executor_type;

  // Construct from the entry point of a new thread of execution.
  awaitable_thread(awaitable<void, Executor> p, const Executor& ex)
    : bottom_of_stack_(std::move(p)),
      top_of_stack_(bottom_of_stack_.frame_),
      executor_(ex)
  {
  }

  // Transfer ownership from another awaitable_thread.
  awaitable_thread(awaitable_thread&& other) noexcept
    : bottom_of_stack_(std::move(other.bottom_of_stack_)),
      top_of_stack_(std::exchange(other.top_of_stack_, nullptr)),
      executor_(std::move(other.executor_))
  {
  }

  // Clean up with a last ditch effort to ensure the thread is unwound within
  // the context of the executor.
  ~awaitable_thread()
  {
    if (bottom_of_stack_.valid())
    {
      // Coroutine "stack unwinding" must be performed through the executor.
      (post)(executor_,
          [a = std::move(bottom_of_stack_)]() mutable
          {
            awaitable<void, Executor>(std::move(a));
          });
    }
  }

  executor_type get_executor() const noexcept
  {
    return executor_;
  }

  // Launch a new thread of execution.
  void launch()
  {
    top_of_stack_->attach_thread(this);
    pump();
  }

protected:
  template <typename> friend class awaitable_frame_base;

  // Repeatedly resume the top stack frame until the stack is empty or until it
  // has been transferred to another resumable_thread object.
  void pump()
  {
    do top_of_stack_->resume(); while (top_of_stack_);
    if (bottom_of_stack_.valid())
    {
      awaitable<void, Executor> a(std::move(bottom_of_stack_));
      a.frame_->rethrow_exception();
    }
  }

  awaitable<void, Executor> bottom_of_stack_;
  awaitable_frame_base<Executor>* top_of_stack_;
  executor_type executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#if !defined(GENERATING_DOCUMENTATION)

namespace std { namespace experimental {

template <typename T, typename Executor, typename... Args>
struct coroutine_traits<boost::asio::awaitable<T, Executor>, Args...>
{
  typedef boost::asio::detail::awaitable_frame<T, Executor> promise_type;
};

}} // namespace std::experimental

#endif // !defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_AWAITABLE_HPP

/* awaitable.hpp
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
*/