//
// executor.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <typeinfo>
#include <boost/asio/detail/cstddef.hpp>
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
  class function;
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

#endif // BOOST_ASIO_EXECUTOR_HPP

/* executor.hpp
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
*/