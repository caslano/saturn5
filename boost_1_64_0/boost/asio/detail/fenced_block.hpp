//
// detail/fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) \
  || defined(BOOST_ASIO_DISABLE_FENCED_BLOCK)
# include <boost/asio/detail/null_fenced_block.hpp>
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
# include <boost/asio/detail/std_fenced_block.hpp>
#elif defined(__MACH__) && defined(__APPLE__)
# include <boost/asio/detail/macos_fenced_block.hpp>
#elif defined(__sun)
# include <boost/asio/detail/solaris_fenced_block.hpp>
#elif defined(__GNUC__) && defined(__arm__) \
  && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
# include <boost/asio/detail/gcc_arm_fenced_block.hpp>
#elif defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))
# include <boost/asio/detail/gcc_hppa_fenced_block.hpp>
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
# include <boost/asio/detail/gcc_x86_fenced_block.hpp>
#elif defined(__GNUC__) \
  && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)) \
  && !defined(__INTEL_COMPILER) && !defined(__ICL) \
  && !defined(__ICC) && !defined(__ECC) && !defined(__PATHSCALE__)
# include <boost/asio/detail/gcc_sync_fenced_block.hpp>
#elif defined(BOOST_ASIO_WINDOWS) && !defined(UNDER_CE)
# include <boost/asio/detail/win_fenced_block.hpp>
#else
# include <boost/asio/detail/null_fenced_block.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS) \
  || defined(BOOST_ASIO_DISABLE_FENCED_BLOCK)
typedef null_fenced_block fenced_block;
#elif defined(BOOST_ASIO_HAS_STD_ATOMIC)
typedef std_fenced_block fenced_block;
#elif defined(__MACH__) && defined(__APPLE__)
typedef macos_fenced_block fenced_block;
#elif defined(__sun)
typedef solaris_fenced_block fenced_block;
#elif defined(__GNUC__) && defined(__arm__) \
  && !defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4)
typedef gcc_arm_fenced_block fenced_block;
#elif defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))
typedef gcc_hppa_fenced_block fenced_block;
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
typedef gcc_x86_fenced_block fenced_block;
#elif defined(__GNUC__) \
  && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)) \
  && !defined(__INTEL_COMPILER) && !defined(__ICL) \
  && !defined(__ICC) && !defined(__ECC) && !defined(__PATHSCALE__)
typedef gcc_sync_fenced_block fenced_block;
#elif defined(BOOST_ASIO_WINDOWS) && !defined(UNDER_CE)
typedef win_fenced_block fenced_block;
#else
typedef null_fenced_block fenced_block;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_FENCED_BLOCK_HPP

/* fenced_block.hpp
5dr+DM+L/PQaryjtz/CNy4v+tVz1N3yf1hfDp2v9PcT0XUH6e8M7C17b8G9afwxfuqToa3ixpaT+1PJlJf8N37is6Gv4vuUl/w1/u4y0v1q+rPR3ht8V/FvCnevc/9N9eqarvwH/17p9+k9LSLif8dvgV/pF8IHKz/+q8sw91xL+t/8Y/p8d9PhTwr37G35n+Hf5PV1/17TfP8rxH6j8ffr729/s3Q2cFGUdB/DZC+FQtK2oLoPazOwyq63QrrLa0uwqtC2trrLaipcFDhiOtwUOHRBpUcRVEVfD3ERtU7StqK5C3Yz0KsxNya7S2srsKqqtzK6i7PfM7/efCc5Kzd6dz+f/+f+/8zw788wzs7Mv3B1hxvp71F+58ZuHNr7mvdruPjkzou39Vvv/nTz6/eoLw9vspXa/pANzji6bfbpqDui6uUQP0aOW6Z4XtrfUPkNu30LPkjvlmXLXln/sfpnacshfO35+W3Zd9P4jdNKcZXvKXGJ7msYyPnSGRgPbs+YKnTf73F7BHNDFqD9djsZD18w1ejAytz8UbZ8ejsY7LvSIuc7Ht19vr0d0h7nJ/p3mGp0x1+ls9Hg6Z67QvjngeIJo+zo+c4uuRttn/4GoPz0Y7Y9u0li4v5Y5CYfbiT5P8HyaW3TKnKbTsN6/8njNWbonatfxRdvX8ZmTdCl6PPtXzTl6gB614PtPHq/az5KH5FU0PrjT0+WU3C93yTPlbnmO3COvkQP5dLksr5Xr8kobj/x+uSWvkMfcQBflpLxB7pRX2/jkeXJePtvGJ5fkmrzAxiMHNh55oc3XF+jFcoe8xOZLXmfzIy+VffkMuSSfKVflc2y+5ILclNfb+ORz5fYd9DKbH/k0OSOfYvMjL5eLO/6x++P/4hLw+f6o8Gl3tz1/x4bOy5j50EVzlu1Vc44eNPt00xzQI+YS3f6j6P4VusOc4XjS5gr7Z8xJ9s/Cut9z/LDuNxx/1M7tFcwBHZhb7F821+mquUEPmtP0cDReesScpZPDNj90p9mnu82Bxmsu0YE5OZ7jg3V/5PjMDR5/3Vxn+5A5S49E/emOH9v8a74jj+X4YL1+cn7NvubPXKLLNBaNz5ykt5lTdN1coRtRO4+3GW2PbpnT7O/95K++PnD+1T5dTsl9cpe8RM7KM+S8PFMuhsZ6uSzPkmvyPHlIni235IVy+0+j+yfPhzxf7pTn2HjlXhuvvEjOyYtlX/blkrxArspz5fpP/3/uj+17xaj3u+PC83loh65vum7O0kOHdjyg+Xqf5z03vP+sZ/+PyiW5Ig/I0+Qhebo8Is+QU2fRM+WsnJfz8pW2f3mWXJavkmvybLkhz7H9y722/w30XLlbnmf7l+fb/mVfLsoLbDxyn82HvFAelhfReONDL5Y75ZrNh7zE9i8vtfkPjfVyVV5m8y9vteOXL5WTJXqL3CVfJvfIl8u+vNz2L6+w/cuftOOX++18yB+z+ZBX2vjkU+z8nEOfKqflq0PH/94XyBm1r7Lxy6vtfMrX2OPl0+x8ymvkinyFXJc/LDflj9v45dPl9nPptXY8ctWOR36/XX9y0cYvf8TGJ6+z+ZbPsPHJZ9r8yuvtejuPPkvukDfYeOSz7fqTS3JOPkcO5HNtvuTzbDzyRpsv+XybL3mTjWcjfYE9H+SyjUe+0M6f/Am7HuWLbP/yB2z/8ubQ8b8HXmzn63y2b7PxyB+0+ZEvsfHQo5f0WM6X2vH9Oscbme2BOcv2iozvl0MPRu3sP2zO0e2bZJ9OmQM6Yy7RWXOF9s01umyu0zVzg26Ym3TT3KJbMt4/wVgukJN00pzj8abNKbZnaTTQvjlDl81Zuh5tj25G++P2R8y+9l8=
*/