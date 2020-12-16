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
HONZ4wtr9tFV/jsG6zZP/wl0uImyDu/GQp3/qXt9o3vneqv8WLTrDeeXOZcO/w7TdfiCm1yLDl+DhTpb3pX+ebM175ilFdYwJjhm+IRbfFaHT8dsHT4TC3V4Kmq6xoff6jeS4xR4XbTjh/+N1Tr8LDbr8NSfeR51+CLs0w1+DqsdM/yhlb5XdPg87NDhPuzVNb55lXut2zzhNvsYQ/gLaOvwZgx+93C2Vn/ue1Dn6t4/2BpzywN/YT+d409gg67wA1iv87d7x2K1LvIi7HOc8GoMGjucffYOx9fh6zBBt7ljtXHr8CyUdfgqLNThs39pPnX4E2jocAVbdfgr2K3bfMoa7xNd4sadnvH3GP9ac/hr4zO29nrv0rs8jzp8zm9ciw7Pwk6dfmudY7LO8RiM0wWeigm6xHMwRVf4WszXNV6D2brB2zBLt/h5TNep4fiYp3M8BjN0ga9Czphr3EbhRGPms37nO0iHv4Y+3eDs98Zv//BnsVmHb8ZO3eJRf/C+0gV+GJN0boPfqyjrNk/f6P7GMbn0R9/v7/Uc8Ts2eX50iVdgoW5w6R73wP7hB7BEh/+Fui7cay2j3/HDZ//JM2V7+BKM0g2+eovnwj7pz35P3ee3gS7wQU3Hj+YfoqBbPP8vjhtzwkfe71qMJ8+noqBbD1iDGBnH3NqVXkBeFx7035Wh7bPhL2yzNuwf3oFhuvRX318Yq6v8w7/5zaCLD7lurNY1Pv7v1o8u8gpk44a/6kfRq8MLdlgzOnw9pujw3ejT+YddC9Y7Tvg5bNXh1//Dd58u8rNI9s894jsC83WdN6JknybvQlG3eWDLPdUZj0CfzvNETNNFfuxRv5HG6ce60k+xWzf4ssfNj67xfgwa77M7fUdjn+1V/huS7W2e9YTrj+08ZpfnVJd49ZPWgK4+5b8H+5fnThf4Sozy2fBLmKTDh+5xLbrIdyPT6WnfWS9YA7r0orWM3Emu6yV/bbLfOG0vv6xfsb/tudSdJmBpHIe/jGU6fOMB3Wm1Dt+LHbr82u70mgH299k8b8Iy3eaTDrS/LvFKjHzf8Ff90dd1p0k6fDn6dOPg7vRvrLd/uDK4O23W4Y1o6/Cz6LF/ZUh3ug/zdXZId3oH5ukCT8X8OC/PwWxd4WuxWNd4DRbpBm/DPN3i5zFLp47udBim6ByPwQxd4KmYrks8B5N1ha/FBF3jNRinGzw/MycFa4xf19mdRuvwmZigwyswXYdfwFwdPqqrO1V1hX+HZa4xPKinOzV0+M3Yrqv8F+zR7H+vtp/Pht+JnK7xGiyKOedtWKpb/DwW63R4d7rkCMe0f3Zkd7oNG3SLn8dqnd5gfrBe53gcRr/fmuEHc86tC2/uTo9hgM7e0p1GYI/98zwR/brIM7FXl/l2VOwfvhtLdfhBrNXhu3u701Yd/tLRjqnDR4/oTukDw9nxMVSnt3b785WtAV06xn3GLF3l09/enYq6ke9O5Xd0p1G6xusxSTf5vne6vzH+d3X7s1h8Vhd5JsbpMi/ABF3lNZg/wTH5vBOs4Q+6d9w3pjvt1HW+6N3GaZ8a94w1Nl3kOVikK7weozT7+wyMR4efQUkXT7RmMEw3uPpe68fxmzxqnH+vi3zMeMfXJV6Pmm7xcSe5Ll3g9L7uVNd5vgLjdJUfxk7z0OZhBfdIh7+AAfYJX4GcrvEa7Ij55G1YrFv8PJbp9H5rBkt1jsdgsy7wVGzQJZ6D9brC12KlrvEabNUN3obVusVHf6A7DT7Zcfhj6NdlXoIBE805v/ODjml7ifdjs85PcE9Ptj50kU+eaAzmM3zTh2zX4fXYp0uTutNv0GP/Fn/uFP9Z3Ec+7VTjtL3CqzHYecM=
*/