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
zL+MHwQGwGCjLwyQTCZ91TyEAZBtFRJdMsAA5HgbkEcNBAP81aJm/ZW9DAZ4TrvQ0YXxrJW/nHUcxCYIBoTBsPb60YLqDf1jF5oKhq6jPQ/+umtAvAZL0QEBZFoEEPBc2R8QiK1+DqMaTM/5TQOAAljcfwAK4Gs/FBRgNqVqDnTZtYQNkATfjFvrIwKgCplA22lEEIBo93l8rNFKTOc894LIRz9ywPBIVfdGvgSyf76wgZSbMv/wRv58TcQh88dK5zPjEMn8VwQhmzYtKooqeXQMS/uDcf0qLRmLyTeVqdWNyTcWSsk3fTEm38oOJlPeMdnzmRwxfx3cQgn4XXiOHQMlonX1ERul4fgCpuFmm0FHVoU0A0J+vSwUScFJ6LQUPC+EntubErw6pMer/SGZqVqH4Dwr206zkhbd5JvGRPjcB/y4DviDyanDzNh9owhq9VMyjY5VanLaSl2xWjiPYI6D6D09LNanKP/ZRquPfgc+tSq3SJQGqHk93i+UN+NcoEY2JqbkUdm5L6hlk3dmgxf0IvdswBZohUSffvnojnzXZjXXZ0MIq3QPQLl+I6MmaZ/aqyz5YCRh3ouc4a+O5khhSoQjQRsU10d+PrBQ30VaGZ3rH3aZliXVnWoxVkXZPrLydVVys5CVLM//V4Xa3G0qK5OJlVup8ZjIBFqtyuXs66218cpF9Fban5iTLw/QuJqtSF5TaSLMlkAI
*/