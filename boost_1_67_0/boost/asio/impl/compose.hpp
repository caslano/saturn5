//
// impl/compose.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
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
    executor_work_guard<system_executor> head_;
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
    executor_work_guard<Head> head_;
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
    executor_work_guard<Head> head_;
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
    executor_work_guard<Head> head_; \
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
  {
  public:
    composed_op(BOOST_ASIO_MOVE_ARG(Impl) impl,
        BOOST_ASIO_MOVE_ARG(Work) work,
        BOOST_ASIO_MOVE_ARG(Handler) handler)
      : impl_(BOOST_ASIO_MOVE_CAST(Impl)(impl)),
        work_(BOOST_ASIO_MOVE_CAST(Work)(work)),
        handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
        invocations_(0)
    {
    }

#if defined(BOOST_ASIO_HAS_MOVE)
    composed_op(composed_op&& other)
      : impl_(BOOST_ASIO_MOVE_CAST(Impl)(other.impl_)),
        work_(BOOST_ASIO_MOVE_CAST(Work)(other.work_)),
        handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
        invocations_(other.invocations_)
    {
    }
#endif // defined(BOOST_ASIO_HAS_MOVE)

    typedef typename associated_executor<Handler,
        typename Work::head_type>::type executor_type;

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
      if (invocations_ < ~unsigned(0))
        ++invocations_;
      impl_(*this, BOOST_ASIO_MOVE_CAST(T)(t)...);
    }

    void complete(Args... args)
    {
      this->work_.reset();
      this->handler_(BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    void operator()()
    {
      if (invocations_ < ~unsigned(0))
        ++invocations_;
      impl_(*this);
    }

    void complete()
    {
      this->work_.reset();
      this->handler_();
    }

#define BOOST_ASIO_PRIVATE_COMPOSED_OP_DEF(n) \
    template<BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()(BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    { \
      if (invocations_ < ~unsigned(0)) \
        ++invocations_; \
      impl_(*this, BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    \
    template<BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void complete(BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    { \
      this->work_.reset(); \
      this->handler_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    /**/
    BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_COMPOSED_OP_DEF)
#undef BOOST_ASIO_PRIVATE_COMPOSED_OP_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  //private:
    Impl impl_;
    Work work_;
    Handler handler_;
    unsigned invocations_;
  };

  template <typename Impl, typename Work, typename Handler, typename Signature>
  inline void* asio_handler_allocate(std::size_t size,
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename Impl, typename Work, typename Handler, typename Signature>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
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
  inline void asio_handler_invoke(Function& function,
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename Impl,
      typename Work, typename Handler, typename Signature>
  inline void asio_handler_invoke(const Function& function,
      composed_op<Impl, Work, Handler, Signature>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Signature, typename Executors>
  class initiate_composed_op
  {
  public:
    typedef typename composed_io_executors<Executors>::head_type executor_type;

    template <typename T>
    explicit initiate_composed_op(BOOST_ASIO_MOVE_ARG(T) executors)
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
    return initiate_composed_op<Signature, Executors>(
        BOOST_ASIO_MOVE_CAST(composed_io_executors<Executors>)(executors));
  }

  template <typename IoObject>
  inline typename IoObject::executor_type
  get_composed_io_executor(IoObject& io_object,
      typename enable_if<!is_executor<IoObject>::value>::type* = 0)
  {
    return io_object.get_executor();
  }

  template <typename Executor>
  inline const Executor& get_composed_io_executor(const Executor& ex,
      typename enable_if<is_executor<Executor>::value>::type* = 0)
  {
    return ex;
  }
} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)
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

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_COMPOSE_HPP

/* compose.hpp
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
*/