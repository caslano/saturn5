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
LqTO1LJBZyrrCt+Hgq7zW1ih04adqT8m6hzf39KZSrq7tTP9ED06fBbm6vAFqOke3rytMw0YYw38Mlp1rr0z7YWlsQaeh3FxXd65ozNVdJFnY7qu8tRMZxozRvNajNL1zs50/kadqVvX+JCvdKbxOtunMx2/cWeapNMmnWkrzNDd/Cv0O7Sr169jiA5fumlnyuvw7zFRh29HRYdfxlzd+FpnSv060wKd4+Mx0/zhxzBXh9/FYh0+bvPO1NDhmUjOzX+9M12PhbrG4/p3piW6zH/FCl3lsd/oTCvjOG/8zc60Ps7l8QPcy/e857xZV2capIu8/xadabgucybnfN3NczFF1/nULTvTHN3D39yqM03QeV6Bis5u3Zm2w4I4l7+LhbrAJ2KJLvHfsTTm5AMHeV7fd5xz23Smoi7wZ2jV3YNdF3N0+F9YoMOvY2mM2da1hnjG5qxwHX0cb/C+23Wm1brIl2zvPYzjPHYHz0uXeRbWxH3x4qGdqel4bsfO9DdUdJ2H7mTfdPgMDNDhP2OYDj+KMTq7c2eajPWxHr4BK3WVF2GFrvPXd/H+FNw7P45xOtyxq33Q4UMwRYdLqOgq37SbZ6Ob/MmwzjRf53fvTE982z7r0vDOtByrdXjLPb0/P+jq9e57+T51eCSG6/CPMUZn9/btYF3sFX+MnHnSCN8mhusc74HuuC4fjiG6yAuR1Q2+Y6T1mzPcvo9nrcOP7et3QFfyrrW/+9XpgM60N2q6wLeM8jx0Y7T3AQN+6LoHd6b3xthPx6uH+k4L3mnHa/z8Ed7nGDO+M236E9c6zJzHdKZrJ9hnx7PHd6ZzTnY9XTzF8zrNnkSXOtOOk81vfO4Mvw+Y63gPd51pPTrPG/zKs9OFs1wfyfjs2b5lzHK8wX88z3ocb5Y7/WsZe6XTNPuGJTE/nzDD+6zLv+tMV2K97uEDLnN8bFevp+NOHT76D95zHb4ITR2+Bq0/cu7lnelurDVPjQddaXw07zjLszO+wg9dZbzOXt2ZzkNeh/+BsTq8CpN0+LprOtO0OPfaznTKn/3mu1b4VczS4QnXdaaqDp+IJTp8Lho6f731/9Xz1d03+H1Dfx3+7Vzfjg7fiTG6+DdzYK1u8lY32Z84l3+J1sOth0+52Teuq/w+BujwrvO8kzq8P0br8EKM1+GlmKxzt/jGMV3X+R306HRrZ/op5urwPNR0eCmW6+xt3iOs0T38DNbqBn+zas26m69H6489C34T/XS63W8UBujsHZ3pS3Tr/N8701MYrcO73WPfdPggTNWF+Z3pNFR0mfve61nobj4Y82IMP447dfjm++ypDj+F1TH+fmvHeh3+ywLPZVwXG4NunX/A+4xROrzjg/ZQh4/AFN3DW//Dn5W6wOdhrq7w3ajqGr+H+Tpb60zb/tM7eYTfKD7lIe+hrvKRD7t3XeGpC11L1/jyR7xnOvwWpujwHovsgw4fjLk6vAYLdHifRz0v3fgfR/Yfb/dcB3D8I2vm3ntuR62M5nZodGM4fsRNw5G1RsORYWnqlGGYHBotNh2ZWRodDKPRwZrR6MSwNBzMDMOR0Y3RoZnR6MhoadHzvT9ej9fL1/d8v5/v5/v5fs/Zxh9inU7LrSus13m+HRt1kzd73P06zjj5F+jSdd76CfdL5/lQDNdFvgtjdZPfwnjd5u4njVnn+ABM0kU+HZN1hV/FVJ1WWDOYrnNcfdp86vwzW6bD0TBvJV6E5brJn/2zZyfGxnOf816yvcVv/sU16na/7+K/mnP7hF9HQ4f/hX5deNHaf8ma1y2+e5V3iw7f/LJ5+G4PW9sYqouvWAt/8/sg7hH/tGWd6MKr3pmYcryx8Y6v+a7SBb4=
*/