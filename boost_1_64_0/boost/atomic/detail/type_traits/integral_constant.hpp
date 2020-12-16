/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/integral_constant.hpp
 *
 * This header defines \c integral_constant wrapper
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <boost/type_traits/integral_constant.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS)
using std::integral_constant;
using std::true_type;
using std::false_type;
#else
using boost::integral_constant;
using boost::true_type;
using boost::false_type;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_INCLUDED_

/* integral_constant.hpp
PfwF/FTXaf+h67QpnPNK2BZeZdbH9flKnxULXevjW3UJ9mMYhp8Y/ejzADzHRz9vq37eUf28q/p5X/WzCU4Uv9GP3ttS733083fi9YXfwJFwFyyC38EK+D28Au6Gv1H/Heq/D/4An4D2QPcnEAff0/Q7YBj/l7A5/Bq2gMaeSOVM9dHPG2o/8CZsDTc47bTeDE53j6a7T9Pda9LJfU1gus803eeabofTDuHtunTLXfYF95h4uAbiZYW5tp+wPsjAejduHe4jXMKnrFd+GrdHa+E1c5zr4bgS8iqpvy6+HH9lSd36+Ioq1t5uirc2lPivle/ieNLN8QFr5rhzWYvE5eMi6+fL+Hslbgp/r4HDOJ5JHn7r6ZvOrVtTT55bf139aPwjcLNwS+0w3A6ce729U2n9Nfch+HM4n3PtfQ1yPg9XldauwW+Au3DOtfjkMtZ5ce41+awy4sI86FybHzFH1ufplP3X6CvLvOv0u8oIuzle1uuTy8kHZ6/ZZ9kkXh6MrN1Xltet31fzdw0uso6fNg+d4iLr+Tnz6tb0l83zruuvR/4qO4xzO9f3q4m7DbcDf9p5dWv9med51/sLOZZ0BOE2B7P2Dnvhr4J+a//bzqu//r+FMqy/Ob5BO4CviNd3Pue16wxcjHPaBqzCn4s/+dmw9dH8OhuBXXYa2Ov8PbMVyD0/2F5gyEN1NgMLzm/YbmDd+XW2Ax/xd9It6P0C0uD6ciwHOu0Jej0bNjYF8y/wtyvIIg+3bUEex6xTCCP9CtIt5VgV7MSxCsK28fex/J10IWXGRWwPhvH3CjgLum0QKjm2i7/XwU34d8DkBRzj70zotEsYhj8LlsC2w9AVjNgorOHvgcPIAzptFZIuqrNXWIp/CP4cyl+GW4arxFXjanDJz2EvgMvBleGW4VbjNj23f31//++/85eAK97H6/8yITRvxvliAGBZe20DMKK7nUdyvfXCbvG19y8d4SUZ5L1W5jBGDx6XPfWsaaVF06fOK5hbNMN8H+LQw2UuttQxd6FpBoh/PP6Wz9v+p+Ls+F1TZF6qYG5ZqYQPN/E7m3X+L8Qfjrfjt/tJ7fyU2bPexB9Xb8+DQy3Zr23WtJmlZo73XxLvrTiz/iT+DEvLwW964bSiYjOfX/WCHX4Pc7R99RizLi9yjLdf0mSta5DsW9BR5Hlb5On8E8nHzLNNJJ/OEv57wiPzxnMLbHbWueMMCV8bxwhgzcRickBcqjUWXysJj5wzVeY7P5CrM998X2SYhCU756RlLbAtf6VI+XdjkzmI55JT9XjIOkWOXxcaRLrzmUNPMfKXF5fNLS8tK8i3Oug8e3Mp261xf0fiLFJcG9pmpUpYJJ97JZ8BoUMd30AptV/8xK92BZJHP/UbeTivKXNxEa/BFpRSZl0TOUPyPtXqxnl7MJu1hmN3UwdHyfx416T4TokHJY5MPLlZs6Rw12Ytk+IWHWbWS0Z3r3UpRl+lRTOLqeR6TXIoUw8p071xMp+u+beg0Wbb+bdYeGRSfKKZSxvTvbZObU93zMupfnZJPmmBOpF5eM1/IPlPbk/+8QsHJIVbJMX3TAqHOe43x5+iafJIk2ynSVw4OVKeXFecxcQ53Y7TcmG2aw3AyLYqEid+0WyWFSwTz5VXdaSMLRYVaBxPmb4iTq7E+UXrSJyslPpx0sLo347TetG7kTgTNJ9R+FPwX0D4DTSAn3fjOZ+wC/Hbdjhju3OMv8fBi/VYBXwX5nBsPI5j4ha2r53nzG5gHeOiF+vWMVLwL3yh1j9jKkc0zp2ROMX5Zk8Suz8bHZL+zOxJQlvhmPRZZk8S+iWZs47EW2KnlTlU6YPq7aGzTteMD44T+3+ZC70=
*/