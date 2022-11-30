//
// executor.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTOR_HPP
#define BOOST_ASIO_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#include <typeinfo>
#include <boost/asio/detail/cstddef.hpp>
#include <boost/asio/detail/executor_function.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Exception thrown when trying to access an empty polymorphic executor.
class bad_executor
  : public std::exception
{
public:
  /// Constructor.
  BOOST_ASIO_DECL bad_executor() BOOST_ASIO_NOEXCEPT;

  /// Obtain message associated with exception.
  BOOST_ASIO_DECL virtual const char* what() const
    BOOST_ASIO_NOEXCEPT_OR_NOTHROW;
};

/// Polymorphic wrapper for executors.
class executor
{
public:
  /// Default constructor.
  executor() BOOST_ASIO_NOEXCEPT
    : impl_(0)
  {
  }

  /// Construct from nullptr.
  executor(nullptr_t) BOOST_ASIO_NOEXCEPT
    : impl_(0)
  {
  }

  /// Copy constructor.
  executor(const executor& other) BOOST_ASIO_NOEXCEPT
    : impl_(other.clone())
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  executor(executor&& other) BOOST_ASIO_NOEXCEPT
    : impl_(other.impl_)
  {
    other.impl_ = 0;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Construct a polymorphic wrapper for the specified executor.
  template <typename Executor>
  executor(Executor e);

  /// Allocator-aware constructor to create a polymorphic wrapper for the
  /// specified executor.
  template <typename Executor, typename Allocator>
  executor(allocator_arg_t, const Allocator& a, Executor e);

  /// Destructor.
  ~executor()
  {
    destroy();
  }

  /// Assignment operator.
  executor& operator=(const executor& other) BOOST_ASIO_NOEXCEPT
  {
    destroy();
    impl_ = other.clone();
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  // Move assignment operator.
  executor& operator=(executor&& other) BOOST_ASIO_NOEXCEPT
  {
    destroy();
    impl_ = other.impl_;
    other.impl_ = 0;
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Assignment operator for nullptr_t.
  executor& operator=(nullptr_t) BOOST_ASIO_NOEXCEPT
  {
    destroy();
    impl_ = 0;
    return *this;
  }

  /// Assignment operator to create a polymorphic wrapper for the specified
  /// executor.
  template <typename Executor>
  executor& operator=(BOOST_ASIO_MOVE_ARG(Executor) e) BOOST_ASIO_NOEXCEPT
  {
    executor tmp(BOOST_ASIO_MOVE_CAST(Executor)(e));
    destroy();
    impl_ = tmp.impl_;
    tmp.impl_ = 0;
    return *this;
  }

  /// Obtain the underlying execution context.
  execution_context& context() const BOOST_ASIO_NOEXCEPT
  {
    return get_impl()->context();
  }

  /// Inform the executor that it has some outstanding work to do.
  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
    get_impl()->on_work_started();
  }

  /// Inform the executor that some work is no longer outstanding.
  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
    get_impl()->on_work_finished();
  }

  /// Request the executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object is executed according to the rules of the
   * target executor object.
   *
   * @param f The function object to be called. The executor will make a copy
   * of the handler object as required. The function signature of the function
   * object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void dispatch(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Request the executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object is executed according to the rules of the
   * target executor object.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void post(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  /// Request the executor to invoke the given function object.
  /**
   * This function is used to ask the executor to execute the given function
   * object. The function object is executed according to the rules of the
   * target executor object.
   *
   * @param f The function object to be called. The executor will make
   * a copy of the handler object as required. The function signature of the
   * function object must be: @code void function(); @endcode
   *
   * @param a An allocator that may be used by the executor to allocate the
   * internal storage needed for function invocation.
   */
  template <typename Function, typename Allocator>
  void defer(BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const;

  struct unspecified_bool_type_t {};
  typedef void (*unspecified_bool_type)(unspecified_bool_type_t);
  static void unspecified_bool_true(unspecified_bool_type_t) {}

  /// Operator to test if the executor contains a valid target.
  operator unspecified_bool_type() const BOOST_ASIO_NOEXCEPT
  {
    return impl_ ? &executor::unspecified_bool_true : 0;
  }

  /// Obtain type information for the target executor object.
  /**
   * @returns If @c *this has a target type of type @c T, <tt>typeid(T)</tt>;
   * otherwise, <tt>typeid(void)</tt>.
   */
#if !defined(BOOST_ASIO_NO_TYPEID) || defined(GENERATING_DOCUMENTATION)
  const std::type_info& target_type() const BOOST_ASIO_NOEXCEPT
  {
    return impl_ ? impl_->target_type() : typeid(void);
  }
#else // !defined(BOOST_ASIO_NO_TYPEID) || defined(GENERATING_DOCUMENTATION)
  const void* target_type() const BOOST_ASIO_NOEXCEPT
  {
    return impl_ ? impl_->target_type() : 0;
  }
#endif // !defined(BOOST_ASIO_NO_TYPEID) || defined(GENERATING_DOCUMENTATION)

  /// Obtain a pointer to the target executor object.
  /**
   * @returns If <tt>target_type() == typeid(T)</tt>, a pointer to the stored
   * executor target; otherwise, a null pointer.
   */
  template <typename Executor>
  Executor* target() BOOST_ASIO_NOEXCEPT;

  /// Obtain a pointer to the target executor object.
  /**
   * @returns If <tt>target_type() == typeid(T)</tt>, a pointer to the stored
   * executor target; otherwise, a null pointer.
   */
  template <typename Executor>
  const Executor* target() const BOOST_ASIO_NOEXCEPT;

  /// Compare two executors for equality.
  friend bool operator==(const executor& a,
      const executor& b) BOOST_ASIO_NOEXCEPT
  {
    if (a.impl_ == b.impl_)
      return true;
    if (!a.impl_ || !b.impl_)
      return false;
    return a.impl_->equals(b.impl_);
  }

  /// Compare two executors for inequality.
  friend bool operator!=(const executor& a,
      const executor& b) BOOST_ASIO_NOEXCEPT
  {
    return !(a == b);
  }

private:
#if !defined(GENERATING_DOCUMENTATION)
  typedef detail::executor_function function;
  template <typename, typename> class impl;

#if !defined(BOOST_ASIO_NO_TYPEID)
  typedef const std::type_info& type_id_result_type;
#else // !defined(BOOST_ASIO_NO_TYPEID)
  typedef const void* type_id_result_type;
#endif // !defined(BOOST_ASIO_NO_TYPEID)

  template <typename T>
  static type_id_result_type type_id()
  {
#if !defined(BOOST_ASIO_NO_TYPEID)
    return typeid(T);
#else // !defined(BOOST_ASIO_NO_TYPEID)
    static int unique_id;
    return &unique_id;
#endif // !defined(BOOST_ASIO_NO_TYPEID)
  }

  // Base class for all polymorphic executor implementations.
  class impl_base
  {
  public:
    virtual impl_base* clone() const BOOST_ASIO_NOEXCEPT = 0;
    virtual void destroy() BOOST_ASIO_NOEXCEPT = 0;
    virtual execution_context& context() BOOST_ASIO_NOEXCEPT = 0;
    virtual void on_work_started() BOOST_ASIO_NOEXCEPT = 0;
    virtual void on_work_finished() BOOST_ASIO_NOEXCEPT = 0;
    virtual void dispatch(BOOST_ASIO_MOVE_ARG(function)) = 0;
    virtual void post(BOOST_ASIO_MOVE_ARG(function)) = 0;
    virtual void defer(BOOST_ASIO_MOVE_ARG(function)) = 0;
    virtual type_id_result_type target_type() const BOOST_ASIO_NOEXCEPT = 0;
    virtual void* target() BOOST_ASIO_NOEXCEPT = 0;
    virtual const void* target() const BOOST_ASIO_NOEXCEPT = 0;
    virtual bool equals(const impl_base* e) const BOOST_ASIO_NOEXCEPT = 0;

  protected:
    impl_base(bool fast_dispatch) : fast_dispatch_(fast_dispatch) {}
    virtual ~impl_base() {}

  private:
    friend class executor;
    const bool fast_dispatch_;
  };

  // Helper function to check and return the implementation pointer.
  impl_base* get_impl() const
  {
    if (!impl_)
    {
      bad_executor ex;
      boost::asio::detail::throw_exception(ex);
    }
    return impl_;
  }

  // Helper function to clone another implementation.
  impl_base* clone() const BOOST_ASIO_NOEXCEPT
  {
    return impl_ ? impl_->clone() : 0;
  }

  // Helper function to destroy an implementation.
  void destroy() BOOST_ASIO_NOEXCEPT
  {
    if (impl_)
      impl_->destroy();
  }

  impl_base* impl_;
#endif // !defined(GENERATING_DOCUMENTATION)
};

} // namespace asio
} // namespace boost

BOOST_ASIO_USES_ALLOCATOR(boost::asio::executor)

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/executor.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/executor.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#endif // BOOST_ASIO_EXECUTOR_HPP

/* executor.hpp
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
*/