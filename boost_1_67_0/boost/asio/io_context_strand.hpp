//
// io_context_strand.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#if !defined(BOOST_ASIO_NO_EXTENSIONS)

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

#endif // BOOST_ASIO_IO_CONTEXT_STRAND_HPP

/* io_context_strand.hpp
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
*/