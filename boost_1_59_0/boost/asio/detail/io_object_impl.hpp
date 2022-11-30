//
// io_object_impl.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/context.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

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

  // Construct an I/O object using an executor.
  explicit io_object_impl(int, const executor_type& ex)
    : service_(&boost::asio::use_service<IoObjectService>(
          io_object_impl::get_context(ex))),
      executor_(ex)
  {
    service_->construct(implementation_);
  }

  // Construct an I/O object using an execution context.
  template <typename ExecutionContext>
  explicit io_object_impl(int, int, ExecutionContext& context)
    : service_(&boost::asio::use_service<IoObjectService>(context)),
      executor_(context.get_executor())
  {
    service_->construct(implementation_);
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  // Move-construct an I/O object.
  io_object_impl(io_object_impl&& other)
    : service_(&other.get_service()),
      executor_(other.get_executor())
  {
    service_->move_construct(implementation_, other.implementation_);
  }

  // Perform a converting move-construction of an I/O object.
  template <typename IoObjectService1, typename Executor1>
  io_object_impl(io_object_impl<IoObjectService1, Executor1>&& other)
    : service_(&boost::asio::use_service<IoObjectService>(
            io_object_impl::get_context(other.get_executor()))),
      executor_(other.get_executor())
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
      executor_.~executor_type();
      new (&executor_) executor_type(other.executor_);
      service_ = other.service_;
    }
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  // Get the executor associated with the object.
  const executor_type& get_executor() BOOST_ASIO_NOEXCEPT
  {
    return executor_;
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
  // Helper function to get an executor's context.
  template <typename T>
  static execution_context& get_context(const T& t,
      typename enable_if<execution::is_executor<T>::value>::type* = 0)
  {
    return boost::asio::query(t, execution::context);
  }

  // Helper function to get an executor's context.
  template <typename T>
  static execution_context& get_context(const T& t,
      typename enable_if<!execution::is_executor<T>::value>::type* = 0)
  {
    return t.context();
  }

  // Disallow copying and copy assignment.
  io_object_impl(const io_object_impl&);
  io_object_impl& operator=(const io_object_impl&);

  // The service associated with the I/O object.
  service_type* service_;

  // The underlying implementation of the I/O object.
  implementation_type implementation_;

  // The associated executor.
  executor_type executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IO_OBJECT_IMPL_HPP

/* io_object_impl.hpp
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
*/