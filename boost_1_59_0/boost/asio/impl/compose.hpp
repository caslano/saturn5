//
// impl/compose.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_COMPOSE_HPP
#define BOOST_ASIO_IMPL_COMPOSE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/base_from_cancellation_state.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/outstanding_work.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  template <typename Executor, typename = void>
  class composed_work_guard
  {
  public:
    typedef typename decay<
        typename prefer_result<Executor,
          execution::outstanding_work_t::tracked_t
        >::type
      >::type executor_type;

    composed_work_guard(const Executor& ex)
      : executor_(boost::asio::prefer(ex, execution::outstanding_work.tracked))
    {
    }

    void reset()
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return executor_;
    }

  private:
    executor_type executor_;
  };

  template <>
  struct composed_work_guard<system_executor>
  {
  public:
    typedef system_executor executor_type;

    composed_work_guard(const system_executor&)
    {
    }

    void reset()
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return system_executor();
    }
  };

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

  template <typename Executor>
  struct composed_work_guard<Executor,
      typename enable_if<
        !execution::is_executor<Executor>::value
      >::type> : executor_work_guard<Executor>
  {
    composed_work_guard(const Executor& ex)
      : executor_work_guard<Executor>(ex)
    {
    }
  };

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

  template <typename>
  struct composed_io_executors;

  template <>
  struct composed_io_executors<void()>
  {
    composed_io_executors() BOOST_ASIO_NOEXCEPT
      : head_(system_executor())
    {
    }

    typedef system_executor head_type;
    system_executor head_;
  };

  inline composed_io_executors<void()> make_composed_io_executors()
  {
    return composed_io_executors<void()>();
  }

  template <typename Head>
  struct composed_io_executors<void(Head)>
  {
    explicit composed_io_executors(const Head& ex) BOOST_ASIO_NOEXCEPT
      : head_(ex)
    {
    }

    typedef Head head_type;
    Head head_;
  };

  template <typename Head>
  inline composed_io_executors<void(Head)>
  make_composed_io_executors(const Head& head)
  {
    return composed_io_executors<void(Head)>(head);
  }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Head, typename... Tail>
  struct composed_io_executors<void(Head, Tail...)>
  {
    explicit composed_io_executors(const Head& head,
        const Tail&... tail) BOOST_ASIO_NOEXCEPT
      : head_(head),
        tail_(tail...)
    {
    }

    void reset()
    {
      head_.reset();
      tail_.reset();
    }

    typedef Head head_type;
    Head head_;
    composed_io_executors<void(Tail...)> tail_;
  };

  template <typename Head, typename... Tail>
  inline composed_io_executors<void(Head, Tail...)>
  make_composed_io_executors(const Head& head, const Tail&... tail)
  {
    return composed_io_executors<void(Head, Tail...)>(head, tail...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#define BOOST_ASIO_PRIVATE_COMPOSED_IO_EXECUTORS_DEF(n) \
  template <typename Head, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct composed_io_executors<void(Head, BOOST_ASIO_VARIADIC_TARGS(n))> \
  { \
    explicit composed_io_executors(const Head& head, \
        BOOST_ASIO_VARIADIC_CONSTREF_PARAMS(n)) BOOST_ASIO_NOEXCEPT \
      : head_(head), \
        tail_(BOOST_ASIO_VARIADIC_BYVAL_ARGS(n)) \
    { \
    } \
  \
    void reset() \
    { \
      head_.reset(); \
      tail_.reset(); \
    } \
  \
    typedef Head head_type; \
    Head head_; \
    composed_io_executors<void(BOOST_ASIO_VARIADIC_TARGS(n))> tail_; \
  }; \
  \
  template <typename Head, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  inline composed_io_executors<void(Head, BOOST_ASIO_VARIADIC_TARGS(n))> \
  make_composed_io_executors(const Head& head, \
      BOOST_ASIO_VARIADIC_CONSTREF_PARAMS(n)) \
  { \
    return composed_io_executors< \
      void(Head, BOOST_ASIO_VARIADIC_TARGS(n))>( \
        head, BOOST_ASIO_VARIADIC_BYVAL_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_COMPOSED_IO_EXECUTORS_DEF)
#undef BOOST_ASIO_PRIVATE_COMPOSED_IO_EXECUTORS_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename>
  struct composed_work;

  template <>
  struct composed_work<void()>
  {
    typedef composed_io_executors<void()> executors_type;

    composed_work(const executors_type&) BOOST_ASIO_NOEXCEPT
      : head_(system_executor())
    {
    }

    void reset()
    {
      head_.reset();
    }

    typedef system_executor head_type;
    composed_work_guard<system_executor> head_;
  };

  template <typename Head>
  struct composed_work<void(Head)>
  {
    typedef composed_io_executors<void(Head)> executors_type;

    explicit composed_work(const executors_type& ex) BOOST_ASIO_NOEXCEPT
      : head_(ex.head_)
    {
    }

    void reset()
    {
      head_.reset();
    }

    typedef Head head_type;
    composed_work_guard<Head> head_;
  };

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Head, typename... Tail>
  struct composed_work<void(Head, Tail...)>
  {
    typedef composed_io_executors<void(Head, Tail...)> executors_type;

    explicit composed_work(const executors_type& ex) BOOST_ASIO_NOEXCEPT
      : head_(ex.head_),
        tail_(ex.tail_)
    {
    }

    void reset()
    {
      head_.reset();
      tail_.reset();
    }

    typedef Head head_type;
    composed_work_guard<Head> head_;
    composed_work<void(Tail...)> tail_;
  };

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#define BOOST_ASIO_PRIVATE_COMPOSED_WORK_DEF(n) \
  template <typename Head, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct composed_work<void(Head, BOOST_ASIO_VARIADIC_TARGS(n))> \
  { \
    typedef composed_io_executors<void(Head, \
      BOOST_ASIO_VARIADIC_TARGS(n))> executors_type; \
  \
    explicit composed_work(const executors_type& ex) BOOST_ASIO_NOEXCEPT \
      : head_(ex.head_), \
        tail_(ex.tail_) \
    { \
    } \
  \
    void reset() \
    { \
      head_.reset(); \
      tail_.reset(); \
    } \
  \
    typedef Head head_type; \
    composed_work_guard<Head> head_; \
    composed_work<void(BOOST_ASIO_VARIADIC_TARGS(n))> tail_; \
  }; \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_COMPOSED_WORK_DEF)
#undef BOOST_ASIO_PRIVATE_COMPOSED_WORK_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
  template <typename Impl, typename Work, typename Handler, typename Signature>
  class composed_op;

  template <typename Impl, typename Work, typename Handler,
      typename R, typename... Args>
  class composed_op<Impl, Work, Handler, R(Args...)>
#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
  template <typename Impl, typename Work, typename Handler, typename Signature>
  class composed_op
#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
    : public base_from_cancellation_state<Handler>
  {
  public:
    template <typename I, typename W, typename H>
    composed_op(BOOST_ASIO_MOVE_ARG(I) impl,
        BOOST_ASIO_MOVE_ARG(W) work,
        BOOST_ASIO_MOVE_ARG(H) handler)
      : base_from_cancellation_state<Handler>(
          handler, enable_terminal_cancellation()),
        impl_(BOOST_ASIO_MOVE_CAST(I)(impl)),
        work_(BOOST_ASIO_MOVE_CAST(W)(work)),
        handler_(BOOST_ASIO_MOVE_CAST(H)(handler)),
        invocations_(0)
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    composed_op(composed_op&& other)
      : base_from_cancellation_state<Handler>(
          BOOST_ASIO_MOVE_CAST(base_from_cancellation_state<
            Handler>)(other)),
        impl_(BOOST_ASIO_MOVE_CAST(Impl)(other.impl_)),
        work_(BOOST_ASIO_MOVE_CAST(Work)(other.work_)),
        handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
        invocations_(other.invocations_)
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    typedef typename associated_executor<Handler,
        typename composed_work_guard<
          typename Work::head_type
        >::executor_type
      >::type executor_type;

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return (get_associated_executor)(handler_, work_.head_.get_executor());
    }

    typedef typename associated_allocator<Handler,
      std::allocator<void> >::type allocator_type;

    allocator_type get_allocator() const BOOST_ASIO_NOEXCEPT
    {
      return (get_associated_allocator)(handler_, std::allocator<void>());
    }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    template<typename... T>
    void operator()(BOOST_ASIO_MOVE_ARG(T)... t)
    {
      if (invocations_ < ~0u)
        ++invocations_;
      this->get_cancellation_state().slot().clear();
      impl_(*this, BOOST_ASIO_MOVE_CAST(T)(t)...);
    }

    void complete(Args... args)
    {
      this->work_.reset();
      BOOST_ASIO_MOVE_OR_LVALUE(Handler)(this->handler_)(
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    void operator()()
    {
      if (invocations_ < ~0u)
        ++invocations_;
      this->get_cancellation_state().slot().clear();
      impl_(*this);
    }

    void complete()
    {
      this->work_.reset();
      BOOST_ASIO_MOVE_OR_LVALUE(Handler)(this->handler_)();
    }

#define BOOST_ASIO_PRIVATE_COMPOSED_OP_DEF(n) \
    template<BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()(BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    { \
      if (invocations_ < ~0u) \
        ++invocations_; \
      this->get_cancellation_state().slot().clear(); \
      impl_(*this, BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    \
    template<BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void complete(BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    { \
      this->work_.reset(); \
      BOOST_ASIO_MOVE_OR_LVALUE(Handler)(this->handler_)( \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    /**/
    BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_COMPOSED_OP_DEF)
#undef BOOST_ASIO_PRIVATE_COMPOSED_OP_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    void reset_cancellation_state()
    {
      base_from_cancellation_state<Handler>::reset_cancellation_state(handler_);
    }

    template <typename Filter>
    void reset_cancellation_state(BOOST_ASIO_MOVE_ARG(Filter) filter)
    {
      base_from_cancellation_state<Handler>::reset_cancellation_state(handler_,
          BOOST_ASIO_MOVE_CAST(Filter)(filter));
    }

    template <typename InFilter, typename OutFilter>
    void reset_cancellation_state(BOOST_ASIO_MOVE_ARG(InFilter) in_filter,
        BOOST_ASIO_MOVE_ARG(OutFilter) out_filter)
    {
      base_from_cancellation_state<Handler>::reset_cancellation_state(handler_,
          BOOST_ASIO_MOVE_CAST(InFilter)(in_filter),
          BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter));
    }

  //private:
    Impl impl_;
    Work work_;
    Handler handler_;
    unsigned invocations_;
  };

  template <typename Impl, typename Work, typename Handler, typename Signature>
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Impl, typename Work, typename Handler, typename Signature>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Impl, typename Work, typename Handler, typename Signature>
  inline bool asio_handler_is_continuation(
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
    return this_handler->invocations_ > 1 ? true
      : boost_asio_handler_cont_helpers::is_continuation(
          this_handler->handler_);
  }

  template <typename Function, typename Impl,
      typename Work, typename Handler, typename Signature>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename Impl,
      typename Work, typename Handler, typename Signature>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Signature, typename Executors>
  class initiate_composed_op
  {
  public:
    typedef typename composed_io_executors<Executors>::head_type executor_type;

    template <typename T>
    explicit initiate_composed_op(int, BOOST_ASIO_MOVE_ARG(T) executors)
      : executors_(BOOST_ASIO_MOVE_CAST(T)(executors))
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return executors_.head_;
    }

    template <typename Handler, typename Impl>
    void operator()(BOOST_ASIO_MOVE_ARG(Handler) handler,
        BOOST_ASIO_MOVE_ARG(Impl) impl) const
    {
      composed_op<typename decay<Impl>::type, composed_work<Executors>,
        typename decay<Handler>::type, Signature>(
          BOOST_ASIO_MOVE_CAST(Impl)(impl),
          composed_work<Executors>(executors_),
          BOOST_ASIO_MOVE_CAST(Handler)(handler))();
    }

  private:
    composed_io_executors<Executors> executors_;
  };

  template <typename Signature, typename Executors>
  inline initiate_composed_op<Signature, Executors> make_initiate_composed_op(
      BOOST_ASIO_MOVE_ARG(composed_io_executors<Executors>) executors)
  {
    return initiate_composed_op<Signature, Executors>(0,
        BOOST_ASIO_MOVE_CAST(composed_io_executors<Executors>)(executors));
  }

  template <typename IoObject>
  inline typename IoObject::executor_type
  get_composed_io_executor(IoObject& io_object,
      typename enable_if<
        !is_executor<IoObject>::value
      >::type* = 0,
      typename enable_if<
        !execution::is_executor<IoObject>::value
      >::type* = 0)
  {
    return io_object.get_executor();
  }

  template <typename Executor>
  inline const Executor& get_composed_io_executor(const Executor& ex,
      typename enable_if<
        is_executor<Executor>::value
          || execution::is_executor<Executor>::value
      >::type* = 0)
  {
    return ex;
  }
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <template <typename, typename> class Associator,
    typename Impl, typename Work, typename Handler,
    typename Signature, typename DefaultCandidate>
struct associator<Associator,
    detail::composed_op<Impl, Work, Handler, Signature>,
    DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::composed_op<Impl, Work, Handler, Signature>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename CompletionToken, typename Signature,
    typename Implementation, typename... IoObjectsOrExecutors>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, Signature)
async_compose(BOOST_ASIO_MOVE_ARG(Implementation) implementation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token,
    BOOST_ASIO_MOVE_ARG(IoObjectsOrExecutors)... io_objects_or_executors)
{
  return async_initiate<CompletionToken, Signature>(
      detail::make_initiate_composed_op<Signature>(
        detail::make_composed_io_executors(
          detail::get_composed_io_executor(
            BOOST_ASIO_MOVE_CAST(IoObjectsOrExecutors)(
              io_objects_or_executors))...)),
      token, BOOST_ASIO_MOVE_CAST(Implementation)(implementation));
}

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename CompletionToken, typename Signature, typename Implementation>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, Signature)
async_compose(BOOST_ASIO_MOVE_ARG(Implementation) implementation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token)
{
  return async_initiate<CompletionToken, Signature>(
      detail::make_initiate_composed_op<Signature>(
        detail::make_composed_io_executors()),
      token, BOOST_ASIO_MOVE_CAST(Implementation)(implementation));
}

# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR(n) \
  BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_##n

# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_1 \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T1)(x1))
# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_2 \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T1)(x1)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T2)(x2))
# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_3 \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T1)(x1)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T2)(x2)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T3)(x3))
# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_4 \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T1)(x1)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T2)(x2)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T3)(x3)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T4)(x4))
# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_5 \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T1)(x1)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T2)(x2)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T3)(x3)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T4)(x4)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T5)(x5))
# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_6 \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T1)(x1)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T2)(x2)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T3)(x3)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T4)(x4)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T5)(x5)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T6)(x6))
# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_7 \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T1)(x1)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T2)(x2)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T3)(x3)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T4)(x4)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T5)(x5)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T6)(x6)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T7)(x7))
# define BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_8 \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T1)(x1)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T2)(x2)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T3)(x3)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T4)(x4)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T5)(x5)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T6)(x6)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T7)(x7)), \
  detail::get_composed_io_executor(BOOST_ASIO_MOVE_CAST(T8)(x8))

#define BOOST_ASIO_PRIVATE_ASYNC_COMPOSE_DEF(n) \
  template <typename CompletionToken, typename Signature, \
      typename Implementation, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, Signature) \
  async_compose(BOOST_ASIO_MOVE_ARG(Implementation) implementation, \
      BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return async_initiate<CompletionToken, Signature>( \
        detail::make_initiate_composed_op<Signature>( \
          detail::make_composed_io_executors( \
            BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR(n))), \
        token, BOOST_ASIO_MOVE_CAST(Implementation)(implementation)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_ASYNC_COMPOSE_DEF)
#undef BOOST_ASIO_PRIVATE_ASYNC_COMPOSE_DEF

#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR
#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_1
#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_2
#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_3
#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_4
#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_5
#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_6
#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_7
#undef BOOST_ASIO_PRIVATE_GET_COMPOSED_IO_EXECUTOR_8

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_COMPOSE_HPP

/* compose.hpp
LgVJiJwLKCwRFMcpvAVPzoUwXcH1/7oX0SQ0YlWnlkU7sqi87PUs+PdkA6MGXgJ56HpQv3nCtqkqdG+aGtuGZDfcNuQhUswK//0ly7A/OCCJS9fynK7DgoaO5eJZOpU0UoCVDTwQYPXFidgriIYVzNktEC6GVAAK1IdATgN7cACTpe18tkwtjSAJh7+7TzzdTCWyVHo6e3cX1NtMmw8Hv5FOq6Us4h7jczM0Yqj8CaNv/3RqzgfziETY0dHRVXX/yqnwe69WrV7Z8ecUHR4vylu9ICTAtIvxhOepL/FiKpmiOjxPFwY4+X3TMYJJzk63W00uk2VHBDCjQOqQ3PNzjLDVIpRthuF+eB5mRDkT79jISTL5KLZR7yx9EVxWGNAMMu0yl0AYSCfsDRJDCGDs4cpCxgf/KmoiEvRYgU525oPlEKmurYV1HXRHUNJ6i9LIQN5pAhro3PZAxuPtRFs4DKtvN7qBAhFFLkAVEgcdhw84ku8ieCjF0PcoxK4GJiGFndZUDvlZ9fHs8Xp+hm5BMQiRPsTI3Fh0GrXP3YgbjCmmgLdArNnQjmV1xtqefYsMGIQK9qk3jH3AqLz9MiLBBoxqzMko5SBUgVICnAoxtPr+YmV6wktSCq+RNwAABhYL027NQgO60ywqRIyczUVHjiUQpJD8NsW17R4GuuJ6M3uF0iAYyMEAovwHz/kiMe+cyn5/Qr4pMetCKlFvUjBEc8lj07HCFQagJBL3qzWmdMphm453NwdcmaiUtKOKfP9bRddxDQxsJmknOL0Gz3Jqarq5LM8WI4Qh8HCb8hLGYyNOk2cBm3xJn+3NwtXJMVBJZ2ijh0UnQHgzYjBClSN0wJhtsRsuw+zYUe7YDEUR22Lyi18CI1Uc6dYLkYJkE5QlZlggZ06c7ATT7dnc3plqkwW8ioYeN8T91ovZRGsRQYskQhbm9pJIUHMRi//3ggzDdykev5K3MiBRVCzq6Pj4vkntVXC2FDWT08kY/8uFTlMzkZjdkhQuKxyPFdpkIvMijWdH6JhQen7Qfe9zC0fdTp3lRA4IxcKYMhzqX1k9zQTWKjl6YxGM/14t3OkohV5Cz4Vw8cGVvLk6/98U3JmA9Th2y3ghoDlUmRorj+00vDjYGEl3Iw8rEHacTbKVIV0FDayEZOebFJMeKUPM7VrnO89rg987xymCAS01j35wCHH2XIbuJ2U4T7Q/8ZvGqpRlGh61RPMljPIjF529dt3f4QYTH5j8Bq6w5CLLErhOIfwZBAi4SV+rdTnlaT0dKt1NjcCip0xvrFfRJZXP1a0VlX8oBIMMVeatoDFA6aFlTTIsrDAXKZOC5ZER5HExz2dEt+WG4XgsoxUCWWED39gMqOsF/L6Vg/j9rIwH5sJ5S3jkACDsfEyr3iacZkKGY3fQxbTPybe4f8kVaI2aFYefKuwCur4eJpczSNwFvXh9x8nSh/hSMNM8TOGIaQUTeGBEAhRVChF7946+Yzl2Kk7J+mgrUNfYrV4vr65gXQ/hJKqTkoC/W4kiRYjZlpYuUmte2BUjGU4vc2Cd8GgWiqbrOxqyLVbp97cZkSXC/IPJsTg85bj/ubBfZ6l2EtaPp/+Bl4Yj4eLe1HH9/LNzX7lYJqQQeYCVHW6rGIEHYZ3ttFAMxLsOvtPVD3/bJpM5OGUPFBLJRBIUdJG129wFweQGAb32PMUyeyU07CmjV2IMO3hnFHW50fs7n0ioSZ72uBYcIMlI464KRPlMSBhxli2ZfaQ7wmHVVLile8Wr545SxiPLhDkKhqytirJRWt0Wa9KKAFTZySuJAF/9VAktidDMxTPKTns+k8Mu+/22CbM1AlvvubkagCozkAUx7+keSOHwtXXK30ZPaD0gzwccIYl48vIt4OKDEaAVVDxUs2WEwRo9PjG0IEGPWdPjuuxz5UkpV+JmgWsNGEwlZ4cPNB5ydgEZBoHAWYIrNtgU9Qo2f7XcA+4rpXrvm2zeCBWwHx0uBHCgdaTIOAp6Nbc1iNguR7PV1OBVtXMafH+3jRohUb5IZGek36VnyKTT1/TLXfPO/AyYpeulLZUV0FfcUpxzRTD0nCIlv+wC97/2PEzQtByOxE5isVmr0oOM+YSgEQeHV9LQ5xWzO9gouvPd0UNG7YDyTochGpaKGDudbYZ+x7AChybb12yJO+PMWKPCYMLOIA9Rh8s731HkAMujYGsnp5X0Opk+YifUi7DYIWZ2BT/g0krYC4ccIRoqOu9F+1MzMGhsv4zGVyoNDrpPajEmh3NZyfMABbXpZQMSuONsGZs/XD3AkF/PW0EbYKjWjQZ+qmBb8H2f5ql3PKlD06EjqZy+Tp53uUV9D0oqCdXL00hJdcNZ6I+lZui3CsrDdYbAhYAPJEWwFgPEtwQnIgQeF/aNnKWcFN2TweG3pRSqPFzSW+dyk0i42nnoryfY7SE4VbXLPi7r4tT+mMMzQYV/QSNktlp8lt3jnOLF871oprI0f3CluWqEiCpMdEgAoCbOw/0vDhQvpXoYHoZQFFTXUxOiwIZR2mAlQ/8ze0jXMSATxw4QwSCnSvR+bFIfKYKQEM2yiJVBQzcVRfLrt70EnynH6QC7uTxePN0snKiw4CG9BmJBzpKLI/xwfHWsJjiZ92u88wv3VYLK9J/SWONMvx6vh3EKmg7r0MJlEg1dp2G5hgPyw9VLgNEJprUvBKFWePphdkOj2mWdLG+BqVnpZZ7py9Q+J/LB32ibAsPTbOTQpJBHJHvafQVw7alNuwrLcSF/6jCsFPztFPy4I7aUlLhxXrD5vALDT0zDjOQOc+adKh7+GSZPSKV4XPkc0vGwLKGuECJftjCNL9096gd9yyN7jycoQcaljWCmPVdKRwx2RJv2qxGmItW44xiIpKIB2+fZ3fyCkViqUFIncmcv1+hkrj+wgdUEuOYNSC4iliVnBBCU5ATj0XCS/wVqTq7bnaMcFxRtHEHRRc3HQvQrW4yjQ0kfvpSiI0OK8FVcS2eu16rZWRUMP+uwOPTLUTsJlr/ECvvSWycaBr6pj3H0d1tsa48V8anijX6+wIjowNXasyJb56UGMxKEP9xghG5iJmjtXbQa2x+jKEtzRKEZyYJJllQD99Q9/fA8GkKcacfEAI6cABQ4QOc+qe+h+B3mODOlkBe1kK72P9YyHKqpMEEJUKvB/foru8wOcDKJaGsQTm2dTkCM1oWNxlQyqbBctkVIfI6nBFnAQqiJQu9AVeoP9x9L4u27M5aAetrV3YwXvQDRWQlO8ZQoKbN1FKVIUEhmir2eTQh7LrFYAp2wfXSKG/H/vAJROn/vIBfUqmQGefNR/5OeI6db6+YessOrFYBbhkKUtN1NORsZ2z8Fu11TW2GE6dSwvOwUz1JghmsDEDfJsKOg9zodbNLaO00iu3lC9ICKEdRnEq/neZz6G//TXfOBSkhLOxKyKvxlp9nr58sSpuNdEsR8ZIyZnfl+pbEl6bNHQHEYNW40kwNKGBhhriC6Hbjt1rSOyuppYS0/aw77bZuGvZ4Q/I+HdU615cyKtP08JyNPq3RAERoPczNqj1DS4y1lsMqmt1XQ91LmMVNWlqxLSMUjzM1WUkP7Mc5hWLYEIq/7HwKyKvyUhNvvW3VHejGFR5aE0sPjIws8712fMXICGlplf/uCDmipinJKzc3HpNTFgwOtal1Xq9qx2z0xBHtEvUApxI6SYCylDCwTFmjNmH85E1u/UXp3ZkEX+LaxSgBNxIJbSTU4ZrEiNQ+B43H9xF9+51JowkD74Y5/8ldG3ycfg8vnFHJR6zuyM9ODU1xvU27DOcXgDk0PYbPaLn0GA0n2dTM8GW0V/OmEU5CPicuYJPpjbBcYBj6JqdVt3iBhSI6QhkFTOVcuro8OcSrleYxabBJpAfM0heFFK92oXrTSKHQHXOAj4Gn4KCQIcPDm4MMcq+Cur1aC2I2z89cl4arwnJw5ziWh4GF5DK2CD23nq7D2I/DvVhTyrPdz4ELXshzUTOv2Rf8jeWvjih7pQfJKO4//j4SDMLAgOaRngXpYPksWceS7/avC8HMns24gVPg79qidQHqOQi47lh4lY4aZ98KYmplZ5heNX9HFKvF92fOqii4fQCwsetmulUCUQI6VaQi4+Ve8KrWqhwcEYlws9Ckc1HwZCjrBoMGko+GJr3uKv66rHZo4raDgz/nLEoFBlXjPMmvPyXsY6L+x5I2T4+BosSUJj8+8XK12Vt+uaqCaEX5IMlr1/YKH3OSbyeQZZNbKo/TvPrd4OBrjEZKH4jid9+WmyyxdQnqDI80vkVDZRXaDQHj4RtCsE9/zKJH696EOMWxfqkDzY6MaQVHg7QN4OXC2c19GO1F/MuYP085ysmci+RZLYBwr764akeSH4GGQnbssglQpww364stlR2665+a5SQjK+ObbfP77XK5ZgkVy26ftWXG4BC4xEe6tclmZDsQLFbEbLunRMk9IDNQsmXthLwvD0kLO46B6KFfzhoVw5r/XW4oDFLBjps0lcGbPwCjywKBbU3a+n7dDr3JcXpdrk9sZg7GXS5vlOoCRmd/T6dNtUZB7MGYugsCXY+kjEooc6AeMkWU8GOJH7us41cULjoKimQcIkoYLlqLkYXMGOHO28swJsdDBWY/msHBk7kOTU2mgFoVGk35tkqN+MvPMEAJzzdpdnPzmEBHesIIxJscHzvGHDO690T9yfj0XzgxCLn8hkZuwP0Yhhvsl2X17E6gU+2E3PvOx1XEUBAJS2+6PUu2h3Yz23syuOkiYS18eKNxL0g+w6n9v/J62PdtkPtf3Pwd2bgFGZH4+KiNtSvPh7RzOv9+vt0OrfhuhmOyCmOz4ki/5bKJ8Hv+ZXcC3ODBpbuI7JE50NYUxtpPDCXlWuy8hHywIGBOdDbGs5AjKNRyOkSYomnczlZOcF7le2W3sYfscW1KakwlnctgnbsP7ADFuVwkcZZhu5f4UGwA+SBgE5IldGcSPk/vhuhq+r6FQ5F69oONefAGKuRSUVYt/HyJvyveuH8LdSCl8sOoT39Nip81unCBFndnerUfoBQgIEuYhudfUDwzN729lZeXjjvdtjSGDUNEbjgI0XvWCyMSfpRp/TvRbutvyjTnGHEQvL9YgsVfbONV9eV6cznS2Sekwt9TJqYGzWoP26WzxK0dyPSMPjj8OfuCy+hwMiroCFLRkoSxToWCDSlNMgm3wfFAOq3hK3jZNILBu4mGtcpjKsVhqf/Hb30Vd57kWia0ktf0WDXhwcH3e/wfA3YzsjpO/mxhE6O7e5fiyO4nf3Zz9ZpdCoOYkvzAg7wckqVBJzfA+ThWSiMeMleJAmaEk37/jyuj5zcO6vvWTLLX5dYGOntjM/zGSDH2dOW4P5kc46grfWU8sf4xI1V/wo8T/4CeQ7KpMQIqN0hzqN/m3zzszE1wYnI9LHie1+pYYRx7lyY7wMu/yAV3Tgtc3J+Jt3g8PKqJMx0YMYOI5vApoVj0Zwu3bl4K4ccjxPlF9fv5dVzg+yZgNZZlmJHtfQKVLCpZYdQIuXkjERRB4WvHTKBQ0knrO9B5xXdXDkPLZ/uf6/3XuqZBltVRtP9U/P/s7kfe99ne+c/TwIDyzPbTIaq3eKNPMzEwLWVNwn2N41wEeJ6l6hts1iX/k7iNKmk9eXuFwK5iPWGpqB1GESdeiqg5nglU45YbvezAi8+4OQ4qlkhFAZOqiWh8RzOg6RDRhvJDAGjywGPuTlO6ZFkLaw4ujsjj61d439weuidvshWWKMQqAtB2jVrUvArN86+eSkYdhnuXN0xX5mbfViONoaCaNUF3fVsjft2rh5JL7B34n589tr8ZUB/dfO/qPIQ+DiXE+5l1N674wTWXK/6xIl//UhnBo21C31l7t4R86keZcfXRIdCnXyfcuzUmF949bF3Z8/F9WNlcAo60ii7q9jf3IMOJ0VU+jOtveZCed6zQmd30bqce/OrChv9mMFdMltZ1vENnjISaaQX1mnIfEvcrwYYWNgcK0lmBSRugMjsiBKA6009CYG9qmcUBZLaw8nfu4yk6hVXJs7DS+c3eFOgqqELM46E16JdM5ui39ztFLhJx333HcPeRCCndDeAhdXJ84DRtD8tUMVyDcQ8ahIZU3/iYrbTNce93uTrMr8Xm+L+t8mG6uezu7yETUUFRukSTmmEZl1yp/bz43nS5eIPgV/d971aqg3L9OjhzXxO7jC4GxS1B2HU+zfMVJ6E9mZpWwOtpnyB/KjDUniG4S9TcvFcqeqigh4jl8Q9358PMg3N9ETyGbbOolBd1IR+wnDNPaXC/iIDIV+ub70fgtKHBXTzJEwgAxed5ncJp/WqvgBivVYctf8vlQR8VeVFjKMnQkKDNNqBa1JD11FZtYSk4aXLtqp2eLnYR/aj71d1/zRCmRaGbzPuA4BTnPkV1nbVjsP6cCq6mBknB+P3d/Vw46r3KdYxEHAAos9dMREf0KhkCgDvU8XkyvduJUOH5MSv/9NsC19zTCmZjG1QAlwQYNGQE/RWG1szGzxAsyvVow+RVVTXpep+ybBBJvMHCHryES010hNvQPcGWMgPgXRGLN0DTzZGQtLNJuK3tlkOlyyZTeVhpbALsHlYGFw4annFbWGXBJ+F5VzP/buw/oFwSGzyqi4oKE5XWn022vh85fshxiYcj4AfbYx0pRLie4pEh8iUcTyNsNAAn5A6Kz3e3yUXyK9+CHJujMU2tfOcps8DnK/9JAhNibuE8YeUAR87sun/xyMEDrOq1xUjWbwyS1DWrVeFdqR42D4iaNKp3o4jPajZIUGtPf4GpO4sUWQMYHgZ0OAerYJQDDF66EBT40ssjoRBwQIU0bF8whJ60RKRjt6TgrieWVmMh2bbhAn+zgade3FTopxSFkXAI27WbZA5wLce71fLy4vF4uC9h2HG3IrjTFN4NmPNuHAA9XtTyFz5nY7na9XFEPKEYflZjp/DO+1FYKrwT10gRywx+hmEZBmjzz81XXle+CyzOQ8p58PRrxHSQikAF98A0Hy9NRUUF5mKIijxU17s3uzUT34zo7SrJcdj8cQ4o42uhlV/Nx2atejWGwXdjY5PjIcULnRRuDT4enHMqnww0olltjaWwEQgeAtTFzD75X4DY61Vix2+OSZrBm+YqwGaEzFSNLDhBV9Pyj4zIV5h7ZBRAzxwDXPM0tYIlbBQTk8RIL92FWGvX1R2+1m+xA52Znl/J7z6A+ny9SVH11DX2qAoVklJRaBoFw7DUbuncl3br2fesFHEa39fJ6+iKbKkbbc5Fn7ikZ3SeppWRfM+4BMnkdCDp58T+HJf4SRE0PGQAhjgZ7LkKPRVUCADDj/6sFiOO5aV+oVClHh5Z0CS5yJ2GRvB0DZS32UIb29yAQ7Pjud70YF9NhelIGpwQEgoO7OwOlufCWozC2Y+WZi7MrwJl0Q9/oIXWUOdKx07+cxJ7iijPKZF1d4KlsNaejRv5EUpaTRLtYXGFixruWE+TTLc6B2mtrJ4jPzCOdcjG7AH+zKlo+LFi+PQ44AgeLVMLMbEjkvjQ4VdUTchnWW/7tvHGRlLDgFDNUNCEqu3k/za8T8vsqOEnmTP2c1jHIUBz0GK8Y/uVk/9+mVfAJk1/yUdUsewffw7t+ZWhB8ifF
*/