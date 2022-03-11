//
// io_object_impl.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_OBJECT_IMPL_HPP
#define BOOST_ASIO_DETAIL_IO_OBJECT_IMPL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <new>
#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/io_object_executor.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class executor;

namespace detail {

inline bool is_native_io_executor(const io_context::executor_type&)
{
  return true;
}

template <typename Executor>
inline bool is_native_io_executor(const Executor&,
    typename enable_if<!is_same<Executor, executor>::value>::type* = 0)
{
  return false;
}

template <typename Executor>
inline bool is_native_io_executor(const Executor& ex,
    typename enable_if<is_same<Executor, executor>::value>::type* = 0)
{
#if !defined (BOOST_ASIO_NO_TYPEID)
  return ex.target_type() == typeid(io_context::executor_type);
#else // !defined (BOOST_ASIO_NO_TYPEID)
  return false;
#endif // !defined (BOOST_ASIO_NO_TYPEID)
}

template <typename IoObjectService,
    typename Executor = io_context::executor_type>
class io_object_impl
{
public:
  // The type of the service that will be used to provide I/O operations.
  typedef IoObjectService service_type;

  // The underlying implementation type of I/O object.
  typedef typename service_type::implementation_type implementation_type;

  // The type of the executor associated with the object.
  typedef Executor executor_type;

  // The type of executor to be used when implementing asynchronous operations.
  typedef io_object_executor<Executor> implementation_executor_type;

  // Construct an I/O object using an executor.
  explicit io_object_impl(const executor_type& ex)
    : service_(&boost::asio::use_service<IoObjectService>(ex.context())),
      implementation_executor_(ex, (is_native_io_executor)(ex))
  {
    service_->construct(implementation_);
  }

  // Construct an I/O object using an execution context.
  template <typename ExecutionContext>
  explicit io_object_impl(ExecutionContext& context,
      typename enable_if<is_convertible<
        ExecutionContext&, execution_context&>::value>::type* = 0)
    : service_(&boost::asio::use_service<IoObjectService>(context)),
      implementation_executor_(context.get_executor(),
        is_same<ExecutionContext, io_context>::value)
  {
    service_->construct(implementation_);
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  // Move-construct an I/O object.
  io_object_impl(io_object_impl&& other)
    : service_(&other.get_service()),
      implementation_executor_(other.get_implementation_executor())
  {
    service_->move_construct(implementation_, other.implementation_);
  }

  // Perform a converting move-construction of an I/O object.
  template <typename IoObjectService1, typename Executor1>
  io_object_impl(io_object_impl<IoObjectService1, Executor1>&& other)
    : service_(&boost::asio::use_service<IoObjectService>(
            other.get_implementation_executor().context())),
      implementation_executor_(other.get_implementation_executor())
  {
    service_->converting_move_construct(implementation_,
        other.get_service(), other.get_implementation());
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  // Destructor.
  ~io_object_impl()
  {
    service_->destroy(implementation_);
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  // Move-assign an I/O object.
  io_object_impl& operator=(io_object_impl&& other)
  {
    if (this != &other)
    {
      service_->move_assign(implementation_,
          *other.service_, other.implementation_);
      implementation_executor_.~implementation_executor_type();
      new (&implementation_executor_) implementation_executor_type(
          std::move(other.implementation_executor_));
      service_ = other.service_;
    }
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  // Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return implementation_executor_.inner_executor();
  }

  // Get the executor to be used when implementing asynchronous operations.
  const implementation_executor_type& get_implementation_executor()
    BOOST_ASIO_NOEXCEPT
  {
    return implementation_executor_;
  }

  // Get the service associated with the I/O object.
  service_type& get_service()
  {
    return *service_;
  }

  // Get the service associated with the I/O object.
  const service_type& get_service() const
  {
    return *service_;
  }

  // Get the underlying implementation of the I/O object.
  implementation_type& get_implementation()
  {
    return implementation_;
  }

  // Get the underlying implementation of the I/O object.
  const implementation_type& get_implementation() const
  {
    return implementation_;
  }

private:
  // Disallow copying and copy assignment.
  io_object_impl(const io_object_impl&);
  io_object_impl& operator=(const io_object_impl&);

  // The service associated with the I/O object.
  service_type* service_;

  // The underlying implementation of the I/O object.
  implementation_type implementation_;

  // The associated executor.
  implementation_executor_type implementation_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IO_OBJECT_IMPL_HPP

/* io_object_impl.hpp
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
*/