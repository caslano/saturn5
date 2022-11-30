//
// io_context_strand.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IO_CONTEXT_STRAND_HPP
#define BOOST_ASIO_IO_CONTEXT_STRAND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_EXTENSIONS) \
  && !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/strand_service.hpp>
#include <boost/asio/detail/wrapped_handler.hpp>
#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Provides serialised handler execution.
/**
 * The io_context::strand class provides the ability to post and dispatch
 * handlers with the guarantee that none of those handlers will execute
 * concurrently.
 *
 * @par Order of handler invocation
 * Given:
 *
 * @li a strand object @c s
 *
 * @li an object @c a meeting completion handler requirements
 *
 * @li an object @c a1 which is an arbitrary copy of @c a made by the
 * implementation
 *
 * @li an object @c b meeting completion handler requirements
 *
 * @li an object @c b1 which is an arbitrary copy of @c b made by the
 * implementation
 *
 * if any of the following conditions are true:
 *
 * @li @c s.post(a) happens-before @c s.post(b)
 * 
 * @li @c s.post(a) happens-before @c s.dispatch(b), where the latter is
 * performed outside the strand
 * 
 * @li @c s.dispatch(a) happens-before @c s.post(b), where the former is
 * performed outside the strand
 * 
 * @li @c s.dispatch(a) happens-before @c s.dispatch(b), where both are
 * performed outside the strand
 *   
 * then @c asio_handler_invoke(a1, &a1) happens-before
 * @c asio_handler_invoke(b1, &b1).
 * 
 * Note that in the following case:
 * @code async_op_1(..., s.wrap(a));
 * async_op_2(..., s.wrap(b)); @endcode
 * the completion of the first async operation will perform @c s.dispatch(a),
 * and the second will perform @c s.dispatch(b), but the order in which those
 * are performed is unspecified. That is, you cannot state whether one
 * happens-before the other. Therefore none of the above conditions are met and
 * no ordering guarantee is made.
 *
 * @note The implementation makes no guarantee that handlers posted or
 * dispatched through different @c strand objects will be invoked concurrently.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Dispatcher.
 */
class io_context::strand
{
public:
  /// Constructor.
  /**
   * Constructs the strand.
   *
   * @param io_context The io_context object that the strand will use to
   * dispatch handlers that are ready to be run.
   */
  explicit strand(boost::asio::io_context& io_context)
    : service_(boost::asio::use_service<
        boost::asio::detail::strand_service>(io_context))
  {
    service_.construct(impl_);
  }

  /// Destructor.
  /**
   * Destroys a strand.
   *
   * Handlers posted through the strand that have not yet been invoked will
   * still be dispatched in a way that meets the guarantee of non-concurrency.
   */
  ~strand()
  {
  }

  /// Obtain the underlying execution context.
  boost::asio::io_context& context() const BOOST_ASIO_NOEXCEPT
  {
    return service_.get_io_context();
  }

  /// Inform the strand that it has some outstanding work to do.
  /**
   * The strand delegates this call to its underlying io_context.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
    context().get_executor().on_work_started();
  }

  /// Inform the strand that some work is no longer outstanding.
  /**
   * The strand delegates this call to its underlying io_context.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
    context().get_executor().on_work_finished();
  }

  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the strand to execute the given function
   * object on its underlying io_context. The function object will be executed
   * inside this function if the strand is not otherwise busy and if the
   * underlying io_context's executor's @c dispatch() function is also able to
   * execute the function before returning.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
  {
    typename decay<Function>::type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));
    service_.dispatch(impl_, tmp);
    (void)a;
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use boost::asio::dispatch().) Request the strand to invoke
  /// the given handler.
  /**
   * This function is used to ask the strand to execute the given handler.
   *
   * The strand object guarantees that handlers posted or dispatched through
   * the strand will not be executed concurrently. The handler may be executed
   * inside this function if the guarantee can be met. If this function is
   * called from within a handler that was posted or dispatched through the same
   * strand, then the new handler will be executed immediately.
   *
   * The strand's guarantee is in addition to the guarantee provided by the
   * underlying io_context. The io_context guarantees that the handler will only
   * be called in a thread in which the io_context's run member function is
   * currently being invoked.
   *
   * @param handler The handler to be called. The strand will make a copy of the
   * handler object as required. The function signature of the handler must be:
   * @code void handler(); @endcode
   */
  template <typename LegacyCompletionHandler>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(LegacyCompletionHandler, void ())
  dispatch(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler)
  {
    return async_initiate<LegacyCompletionHandler, void ()>(
        initiate_dispatch(), handler, this);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled to run by the underlying io_context.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
  {
    typename decay<Function>::type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));
    service_.post(impl_, tmp);
    (void)a;
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use boost::asio::post().) Request the strand to invoke the
  /// given handler and return immediately.
  /**
   * This function is used to ask the strand to execute the given handler, but
   * without allowing the strand to call the handler from inside this function.
   *
   * The strand object guarantees that handlers posted or dispatched through
   * the strand will not be executed concurrently. The strand's guarantee is in
   * addition to the guarantee provided by the underlying io_context. The
   * io_context guarantees that the handler will only be called in a thread in
   * which the io_context's run member function is currently being invoked.
   *
   * @param handler The handler to be called. The strand will make a copy of the
   * handler object as required. The function signature of the handler must be:
   * @code void handler(); @endcode
   */
  template <typename LegacyCompletionHandler>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(LegacyCompletionHandler, void ())
  post(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler)
  {
    return async_initiate<LegacyCompletionHandler, void ()>(
        initiate_post(), handler, this);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled to run by the underlying io_context.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
  {
    typename decay<Function>::type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));
    service_.post(impl_, tmp);
    (void)a;
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use boost::asio::bind_executor().) Create a new handler that
  /// automatically dispatches the wrapped handler on the strand.
  /**
   * This function is used to create a new handler function object that, when
   * invoked, will automatically pass the wrapped handler to the strand's
   * dispatch function.
   *
   * @param handler The handler to be wrapped. The strand will make a copy of
   * the handler object as required. The function signature of the handler must
   * be: @code void handler(A1 a1, ... An an); @endcode
   *
   * @return A function object that, when invoked, passes the wrapped handler to
   * the strand's dispatch function. Given a function object with the signature:
   * @code R f(A1 a1, ... An an); @endcode
   * If this function object is passed to the wrap function like so:
   * @code strand.wrap(f); @endcode
   * then the return value is a function object with the signature
   * @code void g(A1 a1, ... An an); @endcode
   * that, when invoked, executes code equivalent to:
   * @code strand.dispatch(boost::bind(f, a1, ... an)); @endcode
   */
  template <typename Handler>
#if defined(GENERATING_DOCUMENTATION)
  unspecified
#else
  detail::wrapped_handler<strand, Handler, detail::is_continuation_if_running>
#endif
  wrap(Handler handler)
  {
    return detail::wrapped_handler<io_context::strand, Handler,
        detail::is_continuation_if_running>(*this, handler);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Determine whether the strand is running in the current thread.
  /**
   * @return @c true if the current thread is executing a handler that was
   * submitted to the strand using post(), dispatch() or wrap(). Otherwise
   * returns @c false.
   */
  bool running_in_this_thread() const BOOST_ASIO_NOEXCEPT
  {
    return service_.running_in_this_thread(impl_);
  }

  /// Compare two strands for equality.
  /**
   * Two strands are equal if they refer to the same ordered, non-concurrent
   * state.
   */
  friend bool operator==(const strand& a, const strand& b) BOOST_ASIO_NOEXCEPT
  {
    return a.impl_ == b.impl_;
  }

  /// Compare two strands for inequality.
  /**
   * Two strands are equal if they refer to the same ordered, non-concurrent
   * state.
   */
  friend bool operator!=(const strand& a, const strand& b) BOOST_ASIO_NOEXCEPT
  {
    return a.impl_ != b.impl_;
  }

private:
#if !defined(BOOST_ASIO_NO_DEPRECATED)
  struct initiate_dispatch
  {
    template <typename LegacyCompletionHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler,
        strand* self) const
    {
      // If you get an error on the following line it means that your
      // handler does not meet the documented type requirements for a
      // LegacyCompletionHandler.
      BOOST_ASIO_LEGACY_COMPLETION_HANDLER_CHECK(
          LegacyCompletionHandler, handler) type_check;

      detail::non_const_lvalue<LegacyCompletionHandler> handler2(handler);
      self->service_.dispatch(self->impl_, handler2.value);
    }
  };

  struct initiate_post
  {
    template <typename LegacyCompletionHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(LegacyCompletionHandler) handler,
        strand* self) const
    {
      // If you get an error on the following line it means that your
      // handler does not meet the documented type requirements for a
      // LegacyCompletionHandler.
      BOOST_ASIO_LEGACY_COMPLETION_HANDLER_CHECK(
          LegacyCompletionHandler, handler) type_check;

      detail::non_const_lvalue<LegacyCompletionHandler> handler2(handler);
      self->service_.post(self->impl_, handler2.value);
    }
  };
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  boost::asio::detail::strand_service& service_;
  mutable boost::asio::detail::strand_service::implementation_type impl_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
       //   && !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#endif // BOOST_ASIO_IO_CONTEXT_STRAND_HPP

/* io_context_strand.hpp
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
*/