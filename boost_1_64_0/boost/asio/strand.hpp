//
// strand.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
      impl_(use_service<detail::strand_executor_service>(
            executor_.context()).create_implementation())
  {
  }

  /// Construct a strand for the specified executor.
  explicit strand(const Executor& e)
    : executor_(e),
      impl_(use_service<detail::strand_executor_service>(
            executor_.context()).create_implementation())
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
  ~strand()
  {
  }

  /// Obtain the underlying executor.
  inner_executor_type get_inner_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

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
  Executor executor_;
  typedef detail::strand_executor_service::implementation_type
    implementation_type;
  implementation_type impl_;
};

/** @defgroup make_strand boost::asio::make_strand
 *
 * @brief The boost::asio::make_strand function creates a @ref strand object for
 * an executor or execution context.
 */
/*@{*/

/// Create a @ref strand object for an executor.
template <typename Executor>
inline strand<Executor> make_strand(const Executor& ex,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return strand<Executor>(ex);
}

/// Create a @ref strand object for an execution context.
template <typename ExecutionContext>
inline strand<typename ExecutionContext::executor_type>
make_strand(ExecutionContext& ctx,
    typename enable_if<
      is_convertible<ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return strand<typename ExecutionContext::executor_type>(ctx.get_executor());
}

/*@}*/

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
Yt1JWNj5oOTTqi0YJmSAIMtD8o9W+x4pOwdUcxR25IeH6G+g/NM672ixsM6eEG3T8YkmC/sZ6DZVJ1eMpwfGyuJ+dWKavCvXFujEjwvRe0GN/1T5KMyH3FytLztRBuZP50DF3rJf+YaCrTzW07GlITpiWYhuVnVgmOtdQm3vCfn/xBDN6wtRSeXBMKEXHDVtBKQ9t+QrUfCVmOUnavtRIXoCtGi/dvaHcEI4sfCq97tQ9j7Q1v36PI5Z2H9A10sc5IKx9B786TDINMMtWPObrTv5aF3Nf4uweUXfdKJvOnt0m1d5bzbtem+W79Hcz3F92ncI2VTYTnAbLe6fTp1zmfsD0Pi/VJswzGUvCX0izj3jOW19vSdO92DduCsbR18JOYv7eJS/u+K0C3HvZnE9dVfedjye9+a3nxmib4A+/G+nzSDHjSOidATKOwzlLcwKPan0h9EtxhO+NX9GiL4DesJOJ8Y01uPJoOmX0Qr7DWhKhoPcMJ4P31Pw8cdlGdf25Lq514OPnod5/R/t2xku2tq+O5TFb6/SZ1V8VZ0ToujrQlSs5EMO7ID03TP87Ut+YXPDfc7O4izJ7RxD3rlE/O1vCNFe0ATNU3I2woiFqb2Qj3OZmXi9HNcvjtKLwTdacnOoZaewT5c2IuMN2O/UU+miEJ3yphBtMWTdyIGxdvDhj4jFNeWnK2BPVADHUvKybRv/1hC9FFSWZb80Si+FLPCCCVNHir0jjyPzR1tzP5elS0O06rIQ9QXmiTKCtn6Xhem68auAfQG0WeIghnmdrfA7Bd3qbkKaRkZC9ABoXOWrY9XX6vlhmg9bufn7NNujjhqsG41k/yVlUPiMfA9kKtCaGjNf6Z+m3vRTYuFl0HoRJvwmuuDE8/Ee66bfYcgJi4Y0eXxZjJbtmFvOlFqKTYU5+YbB+n5zf30g56+ZhaavY+dd1w3ApSyX2Yv1u+i0hxt0yHKtRJ8K0UbQcUGtv6dqLewLoLMkDnLBWHoxX5GeWN6u8eU3POj8hs16Hacgb94RoiPvDNGkyodhor98xs0siVAjtAGiVLVPRpgut5bvCtFHxkK0IVTJi2GiXBZX3UU1/U3Po73AOz4XoltVPgxzzzuzAvIh/Ey271MWK+LeipP/WfPaUOvT/AjNv8I8E9d3m3LPAX3YV0K0+16M3/A8x11LE/sbqF/iIBeMpZdrqpj/o/BmJm9ySp8Jk3PQnpAzvxai+V/HnoyVa2L3gcZVGQwT7ewzblX5nftZNOVdnEvFhW+Hzt2Y76ANEVXGdCxsn2EjDflMI+z0pA8oxZNNOfZbIboMVBRx5f7QxMZAkzqO7zGxPaD9qjxXjKcH5ijLjw1N/ntID9ocVXkwTPBLHlfK0SnI0fhlcrQKr0N4LbfNc97D4muLvE+GtlP3yYScOB7HGYZ91tv9M+wxQZ2xSt0ZJvoSaax7ZdPSeNt7DT4Yos+BrolpbTAdlz5sS13LamnZFNb/Cch+4+adihjuvtVi3KWsM/q+H4ToNNBuVVeGifVuSNi76Lbkw6btYYS6fxKit4Ia47r8hO9jYWqM4e+fhuhM0LpKGnLFeHqjKURNa4X3Munv8eQonQybzhPQL/Fc0hqrpR8hDcrZbqcTvpqDyubTNQ45MN/3c6a9L8FsAI11ytZZs5cgh57wZCo8HKKLHgHfS6j6KIzzPfj93AG+V9Dur5t2/+APbRPwLYC9fBQ288Vfh+iEvRhbKk+GsTN5Phch4438KkQPg6ZUHgwT49BnXF/2KdN9LvrTkzjmdorPbZW/aa+xSZ4QyLMS27/W4B+g/wQ9njTrK3xOYw61S9tlFoeNE8f7FqIEsZdMwfdF0vbh9WSI3gE=
*/