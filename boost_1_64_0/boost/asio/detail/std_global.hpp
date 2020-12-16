//
// detail/std_global.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_STD_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_CALL_ONCE)

#include <exception>
#include <mutex>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct std_global_impl
{
  // Helper function to perform initialisation.
  static void do_init()
  {
    instance_.ptr_ = new T;
  }

  // Destructor automatically cleans up the global.
  ~std_global_impl()
  {
    delete ptr_;
  }

  static std::once_flag init_once_;
  static std_global_impl instance_;
  T* ptr_;
};

template <typename T>
std::once_flag std_global_impl<T>::init_once_;

template <typename T>
std_global_impl<T> std_global_impl<T>::instance_;

template <typename T>
T& std_global()
{
  std::call_once(std_global_impl<T>::init_once_, &std_global_impl<T>::do_init);
  return *std_global_impl<T>::instance_.ptr_;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_CALL_ONCE)

#endif // BOOST_ASIO_DETAIL_STD_GLOBAL_HPP

/* std_global.hpp
a1I3AXvP5XF8hV7XSN9b+tgs23qwvmOFkHuAY3IPBOxRJ+3ZNq9F9rrXa7ZfpesEPVN9S/vvEP9oWdP9A/H/Xvz1X/T614t/uPg3iP9m/Pb47hP/HZ0D90v4QRZkmoxrKGvCbyKOMS859jOZk/K8bfou7zoO9jWaJExLy6VvkfNpZr2aQvyqDwjcJ9N/jyxS5+V+zzLhm7n2EbXgfJGRPkPCNDb7rmzVftqb9JdYKk3JzdT7A5j7o0jLnB+694WksUGfrxIap7Thcymb2bS5aWHMcfLNK6U8VbvJM/NKQ9qXrK0U1L76O7Qve/0WV5XEyNdZwsM8R0pD6pd7nTqmYwt9lkh/U+9lFebfUt++ODqauV6nH8DPP+lr+Ys4/fUv8u3NmjK1dXxxHn3eH961frNMHG3NMyBFx1HDo88HXoPEMS3bF74OrIG86vukfUh8raW9BIZ/qrZ5Xph9NTa+7G0btSnlZjin9W3GaZn1ek6mMqpZG8/8A2ojKb5ryB5kPpn9RmZciEwjkfnBJxM9R2/3U3hXGfv9SJg06v9bjrHHxZ7geapn4o+XvrqB9Lnyt/gVw2/DwX1kR0g74BhFKPPbuzu015SAdkx9Be1fdkz2gFN6+FrCcWrvgwO2NmybQS2vRLZ2PE7dV2YdyWU63I2eJvw/lzqX9izx1bXt9VcwhWe9tF/f+cZmj6Y12n8pIaJ0mEOtpM/L97a3DBMmjbS971+rtX+Opy79RYEn1gp+b5J2KeFSdbhs/Cu0f77nNCsaG4hox3skRfrN/Vp2pKevJ9G2H7DEKfv28qwK2atK26t6r9eT6rG37SvNWmnjX/HOOw+eU54ifXpjff4/zDNqIseYaa+PfcUbyEEdrpquVV6abe82GVomUe8fs5c2+34ic5j0fOxUtVBW6D0hcslJPrn8pNga3BMflXFPSJh2hClRYaoV3hN8T8g+uHIveOcrfy/zlZV/tqa8axDm/pD1453vjzHm/vC2RdnvRfY91O3MvGscaiX9fr68azi8VxS69fsyr3dptdA1FVqpPUte9a2p0Ct9aN/Mi3sMHtnHvh5Qi7oh6ykQpvLrdBCf4zodBdVDr+9fyG5xuD7bElPybAm5Rgkna0zVcVynA5nKr9NBmqFrTNVxX6ejf43Q/LUjfyVO+dOv2W7lL2Hc17PgfOXXs2hRN/z1LI445Olz2upRyZOs08HLRJ+hFw1IHyrtSvrG0HwdPY52RXyO7Wpvcug1vo9s8mvO1yhl73KNEs697Dlf+bI/1Kr8sve1pxLZJ2+J5Okm3KNq7UxvvmbkTM3JnZmjHoLy9OPnMiYgYWab97YN2l8Tv/p+DXlvF/lp4jfy/mdQ0DdxlgkzSfwmjNvzDnnX73/bM0zk5BlGn2qTN3ttiDyyQfL0t6HfmRXY/yP4/aa/+YbzlledgDUhpExEdrRDHz7GoQ+vE7APmMlTZO2DX2Dtg07n6TUCjsxq+A/Pl1u3dtj9cLUOH66JrH0gax+4rnHgvCZC2WsfiH2l/r5ZTj5P4+9vbX8z9iN/e9/39vP3Rep+sP29RNYI2KLiwR21ZMxQxlHVuQb8/amk1c/yzvFIh63gMNgbDofp8CJ4ORwJ8+HF8DuZs+khrtGwLrwUngUvhy1kDuUVMBNOhmPgTDgRLoP5cDUsgDvgLPgKvBa+BWfDw/B6mds/V+byz4PJ5GM+rA8XwGbwRtgKLjJzuGXcA052mPO2H7nG8ABsD1+FfeFrUM8LgcPh6xJfMa5U4uspcyjUp/E2iS8VOcWGsIX4O8LT4ACYBsfB02EOPAPOgU1gEWxqyRxnuBmeBZ+AzeAeeDY8AM+Bn8AW8AhsCf8J28Aoruk=
*/