//
// detail/null_tss_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP
#define BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
class null_tss_ptr
  : private noncopyable
{
public:
  // Constructor.
  null_tss_ptr()
    : value_(0)
  {
  }

  // Destructor.
  ~null_tss_ptr()
  {
  }

  // Get the value.
  operator T*() const
  {
    return value_;
  }

  // Set the value.
  void operator=(T* value)
  {
    value_ = value;
  }

private:
  T* value_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_TSS_PTR_HPP

/* null_tss_ptr.hpp
1zjwPVb4XmS4iR/G5AW16de4KIr1Sq3wE6w0XuzCGTBd9wi50iCsH7xjUMhpNkyOXi5BQpUECe3UIKE5GiT0O4KEfCokNEvs+rkKCK2HS9IpnKe2KBGR++C2RC0iDF5Os14IEMJWBQMDAkJorTRACPNvYVzYj63WAJe0WGMWxzjD/KFIz2nwT91CHf4hJcfckHEP4Z9EcomUlA0C/ySyj2NqVp6ZrGflGxIj8M/DMQPCP68OBv8gBQb4R+tOA/wzN0aFfwiQHhT+6UPeb5J08lr6wT97riP4R239LUZWXM/qUVkxADjRp57LIvXgWiiV5gdsfeCfmdQ3pjPfD/9oHGDwD4NI+sM/fah4cYROxdcG+CfGNiD8wwrtD//0KbR0RAT+eTS+L/zTR4aEW84hXVThn5Jrdfinr7CV/0gONw/X2zaMJlldav1B8A+ZkuZTOt/LOPdbBP/MoV7wrEGR3MFIaTfAP8eM8M/reTr889CQKPjnyaHR8M9HGvxzCJ8jgUfgB41oSZhcw3yn/Hkzoj+/GcnQn800w4cUVnCEiX0NFBJiXus+gigFutM+CBAWFUGAqJVf4/ZuZEO0mTlkv1QrObpfH3DuR4xgEJVx2Pw9YFBeXzDocls/MOhoFBh0SgeD4m0Gxn+DQA9RiJMWR9jx1lSmGRLe2p5MgjFW3GdZ4KMfbFQs+HIEIbrApgJC76kI0QTtwnoVIZol
*/