//
// Copyright 2019 Olzhas Zhumabek <anonymous.from.applecity@gmail.com>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_IMAGE_PROCESSING_DETAIL_MATH_HPP
#define BOOST_GIL_IMAGE_PROCESSING_DETAIL_MATH_HPP

#include <array>
#include <boost/gil/extension/numeric/kernel.hpp>

namespace boost { namespace gil { namespace detail {

static constexpr double pi = 3.14159265358979323846;

static constexpr std::array<float, 9> dx_sobel = {{-1, 0, 1, -2, 0, 2, -1, 0, 1}};
static constexpr std::array<float, 9> dx_scharr = {{-1, 0, 1, -1, 0, 1, -1, 0, 1}};
static constexpr std::array<float, 9> dy_sobel = {{1, 2, 1, 0, 0, 0, -1, -2, -1}};
static constexpr std::array<float, 9> dy_scharr = {{1, 1, 1, 0, 0, 0, -1, -1, -1}};

template <typename T, typename Allocator>
inline detail::kernel_2d<T, Allocator> get_identity_kernel()
{
    detail::kernel_2d<T, Allocator> kernel(1, 0, 0);
    kernel[0] = 1;
    return kernel;
}

}}} // namespace boost::gil::detail

#endif

/* math.hpp
w16JMLvrov4LCzGuxfj9UpgKhtVhmIRQBNTtFBFXA/Wj5FAgmoIF2PbwVH4pMH1CK8MOv+X+o4SVATZikSGxPwAza/a5xYiUAoSZAdkvUNaePLbB+pX7P+7udTvn/d7Rhz7zCDNjmP32NoVleH7RyBGenxP0orHruSXuZEHwNQStWaJN+aIlIx4RZt3OohhUnAE/9DLDDDBCCqrOPIZRWrBmCLkFVYS+TPTQEZUr+ckIop0pGq3z4DEnKU/hW9THCsk7Xx/XrT6GiK8UGSI5vQZmIzSvgVp3g761MAlA7Kgp74juSixhkwi4JTYVya7UqDEm5XW884o4iNgUZ+enl6dnl8jD4M/x6ckFmNGHK01A84R9XLF2ENKStWAuc6QPvfdvTs8/9I8GxydnV5cHJbxW8ph9RZmxLuC7ni31MzjCsMP704+Dq4v+uWdCntKUhFeB9FLJTj4U6kbHw0EQcdtWDylPGNsPTk4vB9Rd/0hrku6cjeNAJScKktDZ1F2P2qOmrmeE1kuhHml610A1VTUyvtRoOXXlqcfqYUL7Vv4SCE1Cnp6BKTADud3x+kk8X50cX172Ly4dAeOgMeZJVslAJ3a/snBjF36QDzTp24RdHIYZqCeOQIG5Ber9LGkD2EWs/ffMxkyKnvJY
*/