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
VLqptKpK7Ael3FC3Bn8aZeqa9F255sc19DVck74m17bh2inhkz4j1+qNZ42oe1QKn9SX4bzIXZHK9zRGSbR90KjB6Cd71BiFr1yWLp9bODu/QB31wO86wYdvDGq2KVtVTW6Q+q77cgnvEHvNvaj8TNwvDnXm6ZPviejnaIcpNlwfgvL6hW6HCX2QR02fybFz5N54zzWR3xwyz7k9TWfhM8+ttnkWM2drfmmvGnmH4Rx8pGE8B38Y4vXn4I8e0TnbUl2eDPV2uqf1/Oa5aIA5d9jlQQ5sX19aVeNUb5Dr3NnNSi/TOS/1PJ+fIO/XbxmLegyiV1lx+WaXc5uibFSXddPON0nrZdVtHsqsKIhutVVVpTgrAQOvs35FF6jfQu2MHLN+rFN/x/qVV1fXYqRw1tF/gTpq9Vtk4yvgCuhY76yjGEYHq9/6C2x7rF+8sLWW33zo1hBUN6lepOWsX8MFlp2mX6ONfguycd1RPzpCKqxxGIN4ftVF0i/HY6pb9t0mZ/1qN8sxQqUlweq36QLrV2t7ZzxGn1pp1O+ok37jOh5b2mQT1HPokZEdf6vCsdlRz529reW4MBv/fN5BTxmag44xkL04ZZhmc+7/IujmddatrHT91aKck27eC9RNa39HbXTLzYbOHegmg19JkDnJRdLvH6xdCXhURRJ+byaTawaYTMKQBAghF4EECIcQEDVcyiWE08hhDhIgEJJIwqWoiSLgii4qiogiKggoKiIKKiiKCK6sBkUXV3bFcz1Q44W4srr/q6nX885JBPN9LzXdXdWvuru6uru6XndRKzN/l4K/nND8cSe25y/nHPlTx48wrzV/eU3wh9VJ1fTi2vKqSnse886RR3F+mtegA5nHfDsemzHnzL/rT9J/Mdbjb5Etbzz8Uv8NMT84R/54zof5P/PFROF4OgG32pY/LDOq5tnxxXQRZ82XWm+LfNZ81YXmi48DDTEvOEf+VJmbwGf1t1fPTMEzWpkX2PO3qLC0uLbYnjemjbP7ZpTT24txZULrsxtXbL4ZFX3+dKx13e8LUbZq5dDaWlZLocbGP6n+V8eZ9dIYFKrBjkc8PBza8tZwjvpIld3erc285YO3EyF54+l2CP5O/En8HbXgbyz4a7Tjjy9HIZVUY89f45/EX63frDPH5SrOYU3wh+atsa8/0J+bzhRnxrax7h9eW/5wKoFmWmvDH+j/nL6xvY31mJ1sxx9/TRtC9kB7bm2r8jYq3szbePCW0wRvhdNL7Oc658ibasOp4HPttzrIl5a+TewI3DxL3sory83jszhHcArR1DsucbiZT86Hba+tiaamtmpeGdvR1fQsYTedQ+FrHAMdMtF8RHbxRWCD7eKCZo9M9w6QrZuWJ2zr1qeLu1OYzxjA1LVKem/UQrtAHEJdKe5BWKCX0Hu/8NOIrLsrooJwWnAYtUPhONt7kMooPULqhrErGuGrsgL3r7TGo0A/njZ44vFMaa3YP8muRW2aE6JNW8IG+iblLaVhBsDn9pnHu2GArSmO6lzchYA6RRzVqbgLAfWIOKpHnXx42vI3Bjzmj8TTAXluuMdCPvhyHpYP/BEvov5eIZp0UX9fUdgVvKenmTZgrV4axmfEf8vzkn/iKQCxd50Vf3ymsrjozLbvM303cU7nhRR+XnNmPO60LjSdBc10ncR5nX0pvNf2/OhZ4l39gIMw6mUThSfDDBNreZZxHMLnEc5zFC4XeaSbZDGRZXE4pV8FzsKknmjJiXibX72fi3mOxB5MAh6Wf3FfsY/b72rC6wJqP+U7TPA6lHjNAG1fPEloz3CJ5Jvas41G1g9kNS3fVvKcyPLM587r6t6vuztbxLNsm85pFuuAuCQ=
*/