//
// strand.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_STRAND_HPP
#define BOOST_ASIO_STRAND_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/strand_executor_service.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/blocking.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/is_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Provides serialised function invocation for any executor type.
template <typename Executor>
class strand
{
public:
  /// The type of the underlying executor.
  typedef Executor inner_executor_type;

  /// Default constructor.
  /**
   * This constructor is only valid if the underlying executor type is default
   * constructible.
   */
  strand()
    : executor_(),
      impl_(strand::create_implementation(executor_))
  {
  }

  /// Construct a strand for the specified executor.
  template <typename Executor1>
  explicit strand(const Executor1& e,
      typename constraint<
        conditional<
          !is_same<Executor1, strand>::value,
          is_convertible<Executor1, Executor>,
          false_type
        >::type::value
      >::type = 0)
    : executor_(e),
      impl_(strand::create_implementation(executor_))
  {
  }

  /// Copy constructor.
  strand(const strand& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      impl_(other.impl_)
  {
  }

  /// Converting constructor.
  /**
   * This constructor is only valid if the @c OtherExecutor type is convertible
   * to @c Executor.
   */
  template <class OtherExecutor>
  strand(
      const strand<OtherExecutor>& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      impl_(other.impl_)
  {
  }

  /// Assignment operator.
  strand& operator=(const strand& other) BOOST_ASIO_NOEXCEPT
  {
    executor_ = other.executor_;
    impl_ = other.impl_;
    return *this;
  }

  /// Converting assignment operator.
  /**
   * This assignment operator is only valid if the @c OtherExecutor type is
   * convertible to @c Executor.
   */
  template <class OtherExecutor>
  strand& operator=(
      const strand<OtherExecutor>& other) BOOST_ASIO_NOEXCEPT
  {
    executor_ = other.executor_;
    impl_ = other.impl_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  strand(strand&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      impl_(BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_))
  {
  }

  /// Converting move constructor.
  /**
   * This constructor is only valid if the @c OtherExecutor type is convertible
   * to @c Executor.
   */
  template <class OtherExecutor>
  strand(strand<OtherExecutor>&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(OtherExecutor)(other.executor_)),
      impl_(BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_))
  {
  }

  /// Move assignment operator.
  strand& operator=(strand&& other) BOOST_ASIO_NOEXCEPT
  {
    executor_ = BOOST_ASIO_MOVE_CAST(Executor)(other.executor_);
    impl_ = BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_);
    return *this;
  }

  /// Converting move assignment operator.
  /**
   * This assignment operator is only valid if the @c OtherExecutor type is
   * convertible to @c Executor.
   */
  template <class OtherExecutor>
  strand& operator=(strand<OtherExecutor>&& other) BOOST_ASIO_NOEXCEPT
  {
    executor_ = BOOST_ASIO_MOVE_CAST(OtherExecutor)(other.executor_);
    impl_ = BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  ~strand() BOOST_ASIO_NOEXCEPT
  {
  }

  /// Obtain the underlying executor.
  inner_executor_type get_inner_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  /// Forward a query to the underlying executor.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code boost::asio::strand<my_executor_type> ex = ...;
   * if (boost::asio::query(ex, boost::asio::execution::blocking)
   *       == boost::asio::execution::blocking.never)
   *   ... @endcode
   */
  template <typename Property>
  typename constraint<
    can_query<const Executor&, Property>::value,
    typename conditional<
      is_convertible<Property, execution::blocking_t>::value,
      execution::blocking_t,
      typename query_result<const Executor&, Property>::type
    >::type
  >::type query(const Property& p) const
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_query<const Executor&, Property>::value))
  {
    return this->query_helper(
        is_convertible<Property, execution::blocking_t>(), p);
  }

  /// Forward a requirement to the underlying executor.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code boost::asio::strand<my_executor_type> ex1 = ...;
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.never); @endcode
   */
  template <typename Property>
  typename constraint<
    can_require<const Executor&, Property>::value
      && !is_convertible<Property, execution::blocking_t::always_t>::value,
    strand<typename decay<
      typename require_result<const Executor&, Property>::type
    >::type>
  >::type require(const Property& p) const
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_require<const Executor&, Property>::value))
  {
    return strand<typename decay<
      typename require_result<const Executor&, Property>::type
        >::type>(boost::asio::require(executor_, p), impl_);
  }

  /// Forward a preference to the underlying executor.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::prefer customisation point.
   *
   * For example:
   * @code boost::asio::strand<my_executor_type> ex1 = ...;
   * auto ex2 = boost::asio::prefer(ex1,
   *     boost::asio::execution::blocking.never); @endcode
   */
  template <typename Property>
  typename constraint<
    can_prefer<const Executor&, Property>::value
      && !is_convertible<Property, execution::blocking_t::always_t>::value,
    strand<typename decay<
      typename prefer_result<const Executor&, Property>::type
    >::type>
  >::type prefer(const Property& p) const
    BOOST_ASIO_NOEXCEPT_IF((
      is_nothrow_prefer<const Executor&, Property>::value))
  {
    return strand<typename decay<
      typename prefer_result<const Executor&, Property>::type
        >::type>(boost::asio::prefer(executor_, p), impl_);
  }

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
  /// Obtain the underlying execution context.
  execution_context& context() const BOOST_ASIO_NOEXCEPT
  {
    return executor_.context();
  }

  /// Inform the strand that it has some outstanding work to do.
  /**
   * The strand delegates this call to its underlying executor.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
    executor_.on_work_started();
  }

  /// Inform the strand that some work is no longer outstanding.
  /**
   * The strand delegates this call to its underlying executor.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
    executor_.on_work_finished();
  }
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

  /// Request the strand to invoke the given function object.
  /**
   * Do not call this function directly. It is intended for use with the
   * execution::execute customisation point.
   *
   * For example:
   * @code boost::asio::strand<my_executor_type> ex = ...;
   * execution::execute(ex, my_function_object); @endcode
   *
   * This function is used to ask the strand to execute the given function
   * object on its underlying executor. The function object will be executed
   * according to the properties of the underlying executor.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   */
  template <typename Function>
  typename constraint<
    execution::can_execute<const Executor&, Function>::value,
    void
  >::type execute(BOOST_ASIO_MOVE_ARG(Function) f) const
  {
    detail::strand_executor_service::execute(impl_,
        executor_, BOOST_ASIO_MOVE_CAST(Function)(f));
  }

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the strand to execute the given function
   * object on its underlying executor. The function object will be executed
   * inside this function if the strand is not otherwise busy and if the
   * underlying executor's @c dispatch() function is also able to execute the
   * function before returning.
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
    detail::strand_executor_service::dispatch(impl_,
        executor_, BOOST_ASIO_MOVE_CAST(Function)(f), a);
  }

  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled by the underlying executor's defer function.
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
    detail::strand_executor_service::post(impl_,
        executor_, BOOST_ASIO_MOVE_CAST(Function)(f), a);
  }

  /// Request the strand to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled by the underlying executor's defer function.
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
    detail::strand_executor_service::defer(impl_,
        executor_, BOOST_ASIO_MOVE_CAST(Function)(f), a);
  }
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

  /// Determine whether the strand is running in the current thread.
  /**
   * @return @c true if the current thread is executing a function that was
   * submitted to the strand using post(), dispatch() or defer(). Otherwise
   * returns @c false.
   */
  bool running_in_this_thread() const BOOST_ASIO_NOEXCEPT
  {
    return detail::strand_executor_service::running_in_this_thread(impl_);
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

#if defined(GENERATING_DOCUMENTATION)
private:
#endif // defined(GENERATING_DOCUMENTATION)
  typedef detail::strand_executor_service::implementation_type
    implementation_type;

  template <typename InnerExecutor>
  static implementation_type create_implementation(const InnerExecutor& ex,
      typename constraint<
        can_query<InnerExecutor, execution::context_t>::value
      >::type = 0)
  {
    return use_service<detail::strand_executor_service>(
        boost::asio::query(ex, execution::context)).create_implementation();
  }

  template <typename InnerExecutor>
  static implementation_type create_implementation(const InnerExecutor& ex,
      typename constraint<
        !can_query<InnerExecutor, execution::context_t>::value
      >::type = 0)
  {
    return use_service<detail::strand_executor_service>(
        ex.context()).create_implementation();
  }

  strand(const Executor& ex, const implementation_type& impl)
    : executor_(ex),
      impl_(impl)
  {
  }

  template <typename Property>
  typename query_result<const Executor&, Property>::type query_helper(
      false_type, const Property& property) const
  {
    return boost::asio::query(executor_, property);
  }

  template <typename Property>
  execution::blocking_t query_helper(true_type, const Property& property) const
  {
    execution::blocking_t result = boost::asio::query(executor_, property);
    return result == execution::blocking.always
      ? execution::blocking.possibly : result;
  }

  Executor executor_;
  implementation_type impl_;
};

/** @defgroup make_strand boost::asio::make_strand
 *
 * @brief The boost::asio::make_strand function creates a @ref strand object for
 * an executor or execution context.
 */
/*@{*/

/// Create a @ref strand object for an executor.
/**
 * @param ex An executor.
 *
 * @returns A strand constructed with the specified executor.
 */
template <typename Executor>
inline strand<Executor> make_strand(const Executor& ex,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0)
{
  return strand<Executor>(ex);
}

/// Create a @ref strand object for an execution context.
/**
 * @param ctx An execution context, from which an executor will be obtained.
 *
 * @returns A strand constructed with the execution context's executor, obtained
 * by performing <tt>ctx.get_executor()</tt>.
 */
template <typename ExecutionContext>
inline strand<typename ExecutionContext::executor_type>
make_strand(ExecutionContext& ctx,
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type = 0)
{
  return strand<typename ExecutionContext::executor_type>(ctx.get_executor());
}

/*@}*/

#if !defined(GENERATING_DOCUMENTATION)

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename Executor>
struct equality_comparable<strand<Executor> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

template <typename Executor, typename Function>
struct execute_member<strand<Executor>, Function,
    typename enable_if<
      execution::can_execute<const Executor&, Function>::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

template <typename Executor, typename Property>
struct query_member<strand<Executor>, Property,
    typename enable_if<
      can_query<const Executor&, Property>::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_query<Executor, Property>::value));
  typedef typename conditional<
    is_convertible<Property, execution::blocking_t>::value,
      execution::blocking_t, typename query_result<Executor, Property>::type
        >::type result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

template <typename Executor, typename Property>
struct require_member<strand<Executor>, Property,
    typename enable_if<
      can_require<const Executor&, Property>::value
        && !is_convertible<Property, execution::blocking_t::always_t>::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_require<Executor, Property>::value));
  typedef strand<typename decay<
    typename require_result<Executor, Property>::type
      >::type> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)

template <typename Executor, typename Property>
struct prefer_member<strand<Executor>, Property,
    typename enable_if<
      can_prefer<const Executor&, Property>::value
        && !is_convertible<Property, execution::blocking_t::always_t>::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept =
      (is_nothrow_prefer<Executor, Property>::value));
  typedef strand<typename decay<
    typename prefer_result<Executor, Property>::type
      >::type> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)

} // namespace traits

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

// If both io_context.hpp and strand.hpp have been included, automatically
// include the header file needed for the io_context::strand class.
#if !defined(BOOST_ASIO_NO_EXTENSIONS)
# if defined(BOOST_ASIO_IO_CONTEXT_HPP)
#  include <boost/asio/io_context_strand.hpp>
# endif // defined(BOOST_ASIO_IO_CONTEXT_HPP)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

#endif // BOOST_ASIO_STRAND_HPP

/* strand.hpp
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
*/