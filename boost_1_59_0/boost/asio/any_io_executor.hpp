//
// any_io_executor.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_ANY_IO_EXECUTOR_HPP
#define BOOST_ASIO_ANY_IO_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#if defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)
# include <boost/asio/executor.hpp>
#else // defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)
# include <boost/asio/execution.hpp>
# include <boost/asio/execution_context.hpp>
#endif // defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

typedef executor any_io_executor;

#else // defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

/// Polymorphic executor type for use with I/O objects.
/**
 * The @c any_io_executor type is a polymorphic executor that supports the set
 * of properties required by I/O objects. It is defined as the
 * execution::any_executor class template parameterised as follows:
 * @code execution::any_executor<
 *   execution::context_as_t<execution_context&>,
 *   execution::blocking_t::never_t,
 *   execution::prefer_only<execution::blocking_t::possibly_t>,
 *   execution::prefer_only<execution::outstanding_work_t::tracked_t>,
 *   execution::prefer_only<execution::outstanding_work_t::untracked_t>,
 *   execution::prefer_only<execution::relationship_t::fork_t>,
 *   execution::prefer_only<execution::relationship_t::continuation_t>
 * > @endcode
 */
class any_io_executor :
#if defined(GENERATING_DOCUMENTATION)
  public execution::any_executor<...>
#else // defined(GENERATING_DOCUMENTATION)
  public execution::any_executor<
      execution::context_as_t<execution_context&>,
      execution::blocking_t::never_t,
      execution::prefer_only<execution::blocking_t::possibly_t>,
      execution::prefer_only<execution::outstanding_work_t::tracked_t>,
      execution::prefer_only<execution::outstanding_work_t::untracked_t>,
      execution::prefer_only<execution::relationship_t::fork_t>,
      execution::prefer_only<execution::relationship_t::continuation_t>
    >
#endif // defined(GENERATING_DOCUMENTATION)
{
public:
#if !defined(GENERATING_DOCUMENTATION)
  typedef execution::any_executor<
      execution::context_as_t<execution_context&>,
      execution::blocking_t::never_t,
      execution::prefer_only<execution::blocking_t::possibly_t>,
      execution::prefer_only<execution::outstanding_work_t::tracked_t>,
      execution::prefer_only<execution::outstanding_work_t::untracked_t>,
      execution::prefer_only<execution::relationship_t::fork_t>,
      execution::prefer_only<execution::relationship_t::continuation_t>
    > base_type;

  typedef void supportable_properties_type(
      execution::context_as_t<execution_context&>,
      execution::blocking_t::never_t,
      execution::prefer_only<execution::blocking_t::possibly_t>,
      execution::prefer_only<execution::outstanding_work_t::tracked_t>,
      execution::prefer_only<execution::outstanding_work_t::untracked_t>,
      execution::prefer_only<execution::relationship_t::fork_t>,
      execution::prefer_only<execution::relationship_t::continuation_t>
    );
#endif // !defined(GENERATING_DOCUMENTATION)

  /// Default constructor.
  BOOST_ASIO_DECL any_io_executor() BOOST_ASIO_NOEXCEPT;

  /// Construct in an empty state. Equivalent effects to default constructor.
  BOOST_ASIO_DECL any_io_executor(nullptr_t) BOOST_ASIO_NOEXCEPT;

  /// Copy constructor.
  BOOST_ASIO_DECL any_io_executor(const any_io_executor& e) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  BOOST_ASIO_DECL any_io_executor(any_io_executor&& e) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Construct to point to the same target as another any_executor.
#if defined(GENERATING_DOCUMENTATION)
  template <class... OtherSupportableProperties>
    any_io_executor(execution::any_executor<OtherSupportableProperties...> e);
#else // defined(GENERATING_DOCUMENTATION)
  template <typename OtherAnyExecutor>
  any_io_executor(OtherAnyExecutor e,
      typename constraint<
        conditional<
          !is_same<OtherAnyExecutor, any_io_executor>::value
            && is_base_of<execution::detail::any_executor_base,
              OtherAnyExecutor>::value,
          typename execution::detail::supportable_properties<
            0, supportable_properties_type>::template
              is_valid_target<OtherAnyExecutor>,
          false_type
        >::type::value
      >::type = 0)
    : base_type(BOOST_ASIO_MOVE_CAST(OtherAnyExecutor)(e))
  {
  }
#endif // defined(GENERATING_DOCUMENTATION)

  /// Construct a polymorphic wrapper for the specified executor.
#if defined(GENERATING_DOCUMENTATION)
  template <BOOST_ASIO_EXECUTION_EXECUTOR Executor>
  any_io_executor(Executor e);
#else // defined(GENERATING_DOCUMENTATION)
  template <BOOST_ASIO_EXECUTION_EXECUTOR Executor>
  any_io_executor(Executor e,
      typename constraint<
        conditional<
          !is_same<Executor, any_io_executor>::value
            && !is_base_of<execution::detail::any_executor_base,
              Executor>::value,
          execution::detail::is_valid_target_executor<
            Executor, supportable_properties_type>,
          false_type
        >::type::value
      >::type = 0)
    : base_type(BOOST_ASIO_MOVE_CAST(Executor)(e))
  {
  }
#endif // defined(GENERATING_DOCUMENTATION)

  /// Assignment operator.
  BOOST_ASIO_DECL any_io_executor& operator=(
      const any_io_executor& e) BOOST_ASIO_NOEXCEPT;

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move assignment operator.
  BOOST_ASIO_DECL any_io_executor& operator=(
      any_io_executor&& e) BOOST_ASIO_NOEXCEPT;
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Assignment operator that sets the polymorphic wrapper to the empty state.
  BOOST_ASIO_DECL any_io_executor& operator=(nullptr_t);

  /// Destructor.
  BOOST_ASIO_DECL ~any_io_executor();

  /// Swap targets with another polymorphic wrapper.
  BOOST_ASIO_DECL void swap(any_io_executor& other) BOOST_ASIO_NOEXCEPT;

  /// Obtain a polymorphic wrapper with the specified property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::require and boost::asio::prefer customisation points.
   *
   * For example:
   * @code any_io_executor ex = ...;
   * auto ex2 = boost::asio::require(ex, execution::blocking.possibly); @endcode
   */
  template <typename Property>
  any_io_executor require(const Property& p,
      typename constraint<
        traits::require_member<const base_type&, const Property&>::is_valid
      >::type = 0) const
  {
    return static_cast<const base_type&>(*this).require(p);
  }

  /// Obtain a polymorphic wrapper with the specified property.
  /**
   * Do not call this function directly. It is intended for use with the
   * boost::asio::prefer customisation point.
   *
   * For example:
   * @code any_io_executor ex = ...;
   * auto ex2 = boost::asio::prefer(ex, execution::blocking.possibly); @endcode
   */
  template <typename Property>
  any_io_executor prefer(const Property& p,
      typename constraint<
        traits::prefer_member<const base_type&, const Property&>::is_valid
      >::type = 0) const
  {
    return static_cast<const base_type&>(*this).prefer(p);
  }
};

#if !defined(GENERATING_DOCUMENTATION)

template <>
BOOST_ASIO_DECL any_io_executor any_io_executor::require(
    const execution::blocking_t::never_t&, int) const;

template <>
BOOST_ASIO_DECL any_io_executor any_io_executor::prefer(
    const execution::blocking_t::possibly_t&, int) const;

template <>
BOOST_ASIO_DECL any_io_executor any_io_executor::prefer(
    const execution::outstanding_work_t::tracked_t&, int) const;

template <>
BOOST_ASIO_DECL any_io_executor any_io_executor::prefer(
    const execution::outstanding_work_t::untracked_t&, int) const;

template <>
BOOST_ASIO_DECL any_io_executor any_io_executor::prefer(
    const execution::relationship_t::fork_t&, int) const;

template <>
BOOST_ASIO_DECL any_io_executor any_io_executor::prefer(
    const execution::relationship_t::continuation_t&, int) const;

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <>
struct equality_comparable<any_io_executor>
{
  static const bool is_valid = true;
  static const bool is_noexcept = true;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

template <typename F>
struct execute_member<any_io_executor, F>
{
  static const bool is_valid = true;
  static const bool is_noexcept = false;
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

template <typename Prop>
struct query_member<any_io_executor, Prop> :
  query_member<any_io_executor::base_type, Prop>
{
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

template <typename Prop>
struct require_member<any_io_executor, Prop> :
  require_member<any_io_executor::base_type, Prop>
{
  typedef any_io_executor result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)

template <typename Prop>
struct prefer_member<any_io_executor, Prop> :
  prefer_member<any_io_executor::base_type, Prop>
{
  typedef any_io_executor result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_PREFER_MEMBER_TRAIT)

} // namespace traits

#endif // !defined(GENERATING_DOCUMENTATION)

#endif // defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY) \
  && !defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)
# include <boost/asio/impl/any_io_executor.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)
       //   && !defined(BOOST_ASIO_USE_TS_EXECUTOR_AS_DEFAULT)

#endif // BOOST_ASIO_ANY_IO_EXECUTOR_HPP

/* any_io_executor.hpp
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
*/