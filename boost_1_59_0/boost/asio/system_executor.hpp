//
// system_executor.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SYSTEM_EXECUTOR_HPP
#define BOOST_ASIO_SYSTEM_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/execution.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class system_context;

/// An executor that uses arbitrary threads.
/**
 * The system executor represents an execution context where functions are
 * permitted to run on arbitrary threads. When the blocking.never property is
 * established, the system executor will schedule the function to run on an
 * unspecified system thread pool. When either blocking.possibly or
 * blocking.always is established, the executor invokes the function
 * immediately.
 */
template <typename Blocking, typename Relationship, typename Allocator>
class basic_system_executor
{
public:
  /// Default constructor.
  basic_system_executor() BOOST_ASIO_NOEXCEPT
    : allocator_(Allocator())
  {
  }

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_require_fn::impl;
  friend struct boost_asio_prefer_fn::impl;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Obtain an executor with the @c blocking.possibly property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex1;
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.possibly); @endcode
   */
  basic_system_executor<execution::blocking_t::possibly_t,
      Relationship, Allocator>
  require(execution::blocking_t::possibly_t) const
  {
    return basic_system_executor<execution::blocking_t::possibly_t,
        Relationship, Allocator>(allocator_);
  }

  /// Obtain an executor with the @c blocking.always property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex1;
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.always); @endcode
   */
  basic_system_executor<execution::blocking_t::always_t,
      Relationship, Allocator>
  require(execution::blocking_t::always_t) const
  {
    return basic_system_executor<execution::blocking_t::always_t,
        Relationship, Allocator>(allocator_);
  }

  /// Obtain an executor with the @c blocking.never property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex1;
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::blocking.never); @endcode
   */
  basic_system_executor<execution::blocking_t::never_t,
      Relationship, Allocator>
  require(execution::blocking_t::never_t) const
  {
    return basic_system_executor<execution::blocking_t::never_t,
        Relationship, Allocator>(allocator_);
  }

  /// Obtain an executor with the @c relationship.continuation property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex1;
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::relationship.continuation); @endcode
   */
  basic_system_executor<Blocking,
      execution::relationship_t::continuation_t, Allocator>
  require(execution::relationship_t::continuation_t) const
  {
    return basic_system_executor<Blocking,
        execution::relationship_t::continuation_t, Allocator>(allocator_);
  }

  /// Obtain an executor with the @c relationship.fork property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex1;
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::relationship.fork); @endcode
   */
  basic_system_executor<Blocking,
      execution::relationship_t::fork_t, Allocator>
  require(execution::relationship_t::fork_t) const
  {
    return basic_system_executor<Blocking,
        execution::relationship_t::fork_t, Allocator>(allocator_);
  }

  /// Obtain an executor with the specified @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex1;
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::allocator(my_allocator)); @endcode
   */
  template <typename OtherAllocator>
  basic_system_executor<Blocking, Relationship, OtherAllocator>
  require(execution::allocator_t<OtherAllocator> a) const
  {
    return basic_system_executor<Blocking,
        Relationship, OtherAllocator>(a.value());
  }

  /// Obtain an executor with the default @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex1;
   * auto ex2 = boost::asio::require(ex1,
   *     boost::asio::execution::allocator); @endcode
   */
  basic_system_executor<Blocking, Relationship, std::allocator<void> >
  require(execution::allocator_t<void>) const
  {
    return basic_system_executor<Blocking,
        Relationship, std::allocator<void> >();
  }

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_query_fn::impl;
  friend struct boost::asio::execution::detail::blocking_t<0>;
  friend struct boost::asio::execution::detail::mapping_t<0>;
  friend struct boost::asio::execution::detail::outstanding_work_t<0>;
  friend struct boost::asio::execution::detail::relationship_t<0>;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Query the current value of the @c mapping property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex;
   * if (boost::asio::query(ex, boost::asio::execution::mapping)
   *       == boost::asio::execution::mapping.thread)
   *   ... @endcode
   */
  static BOOST_ASIO_CONSTEXPR execution::mapping_t query(
      execution::mapping_t) BOOST_ASIO_NOEXCEPT
  {
    return execution::mapping.thread;
  }

  /// Query the current value of the @c context property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex;
   * boost::asio::system_context& pool = boost::asio::query(
   *     ex, boost::asio::execution::context); @endcode
   */
  static system_context& query(execution::context_t) BOOST_ASIO_NOEXCEPT;

  /// Query the current value of the @c blocking property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex;
   * if (boost::asio::query(ex, boost::asio::execution::blocking)
   *       == boost::asio::execution::blocking.always)
   *   ... @endcode
   */
  static BOOST_ASIO_CONSTEXPR execution::blocking_t query(
      execution::blocking_t) BOOST_ASIO_NOEXCEPT
  {
    return Blocking();
  }

  /// Query the current value of the @c relationship property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex;
   * if (boost::asio::query(ex, boost::asio::execution::relationship)
   *       == boost::asio::execution::relationship.continuation)
   *   ... @endcode
   */
  static BOOST_ASIO_CONSTEXPR execution::relationship_t query(
      execution::relationship_t) BOOST_ASIO_NOEXCEPT
  {
    return Relationship();
  }

  /// Query the current value of the @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex;
   * auto alloc = boost::asio::query(ex,
   *     boost::asio::execution::allocator); @endcode
   */
  template <typename OtherAllocator>
  BOOST_ASIO_CONSTEXPR Allocator query(
      execution::allocator_t<OtherAllocator>) const BOOST_ASIO_NOEXCEPT
  {
    return allocator_;
  }

  /// Query the current value of the @c allocator property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex;
   * auto alloc = boost::asio::query(ex,
   *     boost::asio::execution::allocator); @endcode
   */
  BOOST_ASIO_CONSTEXPR Allocator query(
      execution::allocator_t<void>) const BOOST_ASIO_NOEXCEPT
  {
    return allocator_;
  }

  /// Query the occupancy (recommended number of work items) for the system
  /// context.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::query customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex;
   * std::size_t occupancy = boost::asio::query(
   *     ex, boost::asio::execution::occupancy); @endcode
   */
  std::size_t query(execution::occupancy_t) const BOOST_ASIO_NOEXCEPT;

public:
  /// Compare two executors for equality.
  /**
   * Two executors are equal if they refer to the same underlying io_context.
   */
  friend bool operator==(const basic_system_executor&,
      const basic_system_executor&) BOOST_ASIO_NOEXCEPT
  {
    return true;
  }

  /// Compare two executors for inequality.
  /**
   * Two executors are equal if they refer to the same underlying io_context.
   */
  friend bool operator!=(const basic_system_executor&,
      const basic_system_executor&) BOOST_ASIO_NOEXCEPT
  {
    return false;
  }

#if !defined(GENERATING_DOCUMENTATION)
private:
  friend struct boost_asio_execution_execute_fn::impl;
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Execution function.
  /**
   * Do not call this function directly. It is intended for use with the
   * execution::execute customisation point.
   *
   * For example:
   * @code boost::asio::system_executor ex;
   * execution::execute(ex, my_function_object); @endcode
   */
  template <typename Function>
  void execute(BOOST_ASIO_MOVE_ARG(Function) f) const
  {
    this->do_execute(BOOST_ASIO_MOVE_CAST(Function)(f), Blocking());
  }

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
public:
  /// Obtain the underlying execution context.
  system_context& context() const BOOST_ASIO_NOEXCEPT;

  /// Inform the executor that it has some outstanding work to do.
  /**
   * For the system executor, this is a no-op.
   */
  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
  }

  /// Inform the executor that some work is no longer outstanding.
  /**
   * For the system executor, this is a no-op.
   */
  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
  }

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will always be executed inside this function.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const;

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled to run on an unspecified system thread pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const;

  /// Request the system executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object will never be executed inside this function.
   * Instead, it will be scheduled to run on an unspecified system thread pool.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename OtherAllocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f, const OtherAllocator& a) const;
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

private:
  template <typename, typename, typename> friend class basic_system_executor;

  // Constructor used by require().
  basic_system_executor(const Allocator& a)
    : allocator_(a)
  {
  }

  /// Execution helper implementation for the possibly blocking property.
  template <typename Function>
  void do_execute(BOOST_ASIO_MOVE_ARG(Function) f,
      execution::blocking_t::possibly_t) const;

  /// Execution helper implementation for the always blocking property.
  template <typename Function>
  void do_execute(BOOST_ASIO_MOVE_ARG(Function) f,
      execution::blocking_t::always_t) const;

  /// Execution helper implementation for the never blocking property.
  template <typename Function>
  void do_execute(BOOST_ASIO_MOVE_ARG(Function) f,
      execution::blocking_t::never_t) const;

  // The allocator used for execution functions.
  Allocator allocator_;
};

/// An executor that uses arbitrary threads.
/**
 * The system executor represents an execution context where functions are
 * permitted to run on arbitrary threads. When the blocking.never property is
 * established, the system executor will schedule the function to run on an
 * unspecified system thread pool. When either blocking.possibly or
 * blocking.always is established, the executor invokes the function
 * immediately.
 */
typedef basic_system_executor<execution::blocking_t::possibly_t,
    execution::relationship_t::fork_t, std::allocator<void> >
  system_executor;

#if !defined(GENERATING_DOCUMENTATION)

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename Blocking, typename Relationship, typename Allocator>
struct equality_comparable<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

template <typename Blocking, typename Relationship,
    typename Allocator, typename Function>
struct execute_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    Function
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

template <typename Blocking, typename Relationship, typename Allocator>
struct require_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::blocking_t::possibly_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::basic_system_executor<
      boost::asio::execution::blocking_t::possibly_t,
      Relationship, Allocator> result_type;
};

template <typename Blocking, typename Relationship, typename Allocator>
struct require_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::blocking_t::always_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::basic_system_executor<
      boost::asio::execution::blocking_t::always_t,
      Relationship, Allocator> result_type;
};

template <typename Blocking, typename Relationship, typename Allocator>
struct require_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::blocking_t::never_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::basic_system_executor<
      boost::asio::execution::blocking_t::never_t,
      Relationship, Allocator> result_type;
};

template <typename Blocking, typename Relationship, typename Allocator>
struct require_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::relationship_t::fork_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::basic_system_executor<Blocking,
      boost::asio::execution::relationship_t::fork_t,
      Allocator> result_type;
};

template <typename Blocking, typename Relationship, typename Allocator>
struct require_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::relationship_t::continuation_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::basic_system_executor<Blocking,
      boost::asio::execution::relationship_t::continuation_t,
      Allocator> result_type;
};

template <typename Blocking, typename Relationship, typename Allocator>
struct require_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::allocator_t<void>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::basic_system_executor<Blocking,
      Relationship, std::allocator<void> > result_type;
};

template <typename Blocking, typename Relationship,
    typename Allocator, typename OtherAllocator>
struct require_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::allocator_t<OtherAllocator>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef boost::asio::basic_system_executor<Blocking,
      Relationship, OtherAllocator> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

template <typename Blocking, typename Relationship,
    typename Allocator, typename Property>
struct query_static_constexpr_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::mapping_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::mapping_t::thread_t result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return result_type();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

template <typename Blocking, typename Relationship,
    typename Allocator, typename Property>
struct query_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::blocking_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::blocking_t result_type;
};

template <typename Blocking, typename Relationship,
    typename Allocator, typename Property>
struct query_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::relationship_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::execution::relationship_t result_type;
};

template <typename Blocking, typename Relationship, typename Allocator>
struct query_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::context_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::system_context& result_type;
};

template <typename Blocking, typename Relationship, typename Allocator>
struct query_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::allocator_t<void>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef Allocator result_type;
};

template <typename Blocking, typename Relationship, typename Allocator>
struct query_member<
    boost::asio::basic_system_executor<Blocking, Relationship, Allocator>,
    boost::asio::execution::allocator_t<Allocator>
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef Allocator result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

} // namespace traits

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/system_executor.hpp>

#endif // BOOST_ASIO_SYSTEM_EXECUTOR_HPP

/* system_executor.hpp
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
*/