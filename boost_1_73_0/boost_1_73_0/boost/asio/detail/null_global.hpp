//
// detail/null_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_NULL_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct null_global_impl
{
  null_global_impl()
    : ptr_(0)
  {
  }

  // Destructor automatically cleans up the global.
  ~null_global_impl()
  {
    delete ptr_;
  }

  static null_global_impl instance_;
  T* ptr_;
};

template <typename T>
null_global_impl<T> null_global_impl<T>::instance_;

template <typename T>
T& null_global()
{
  if (null_global_impl<T>::instance_.ptr_ == 0)
    null_global_impl<T>::instance_.ptr_ = new T;
  return *null_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NULL_GLOBAL_HPP

/* null_global.hpp
ek7h6EjukrwgjgLVIugSgIZoICUpKAx3vYCILTJVKpSaq3r5OfNW6ppE4lGnXOT9JP7sTM3VYu0AvHopnHJqyrVs5XzGrnD41JmQ0D2dRVxlD/TGmHvHjh4anOfF/It0W39qypnuevYlgQrXMy6Gs9F15m3zTMj8dFzdSZNyRL7OKggV6dwc8POhqsekLMJDcmemVbd062/U2UIltRHyJmArXz+zLw8PFVwKGHPQCarHmye///2Wox16SNVvYYRRm4bu4UdGm4m+IDxXhIvt1TG4d7/WcRrFP8OGKfqbWnITt5f8EI2pv1jz7dlkfid0XrZtQbam/nzvhV04HMGqysK5+SZ58QnA3KUls2qW5FWimtBnz2/U1DUnLUg+l7nIV/fK++UBphEfn5+vLk2o1sjwmqaHDFbPhApnVntsiEBqRBj4XH7KtkmdW0XGT7f91kbrxTjv39l1Rw33XnILnuB/jhAesZ01o2099T1ozeCvtf9WP0gwy7sqmZrLxx1CQSdvtICOKX9PE5xr4OkKgfFUY15MQEPl+S34kHBwMEJoiLLKnzOzQwRRGHiHMYMvfu9VeYG4sOuySGmgIkYZvQxHj5wLj9OYSts7IhfIFk6u7EsvfptX2bj8YjYf0DqjDhfwJRBx/HlwfiUG
*/