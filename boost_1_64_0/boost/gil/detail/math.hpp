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
RjwAWI8/Fphl0o+4sV5AmuckITxKS9bVTKt4FD8wCVeeidR43R7LW3kkJKIx4YOaz8VaOTaZ0IrkPoEkIbby2VxZPwr3LYwhf0Jc8wWow30OtoLfaqV/0Pa8T0sjSzEH4uKVTtydBbQlkY71zhTZi0gWP3gZni4oCYs8vK8DmGQlgBSYYSWxAO8kbVrhiiE+0pVDdfae56CamGLKzlTtBDS5QNvbNUAECh4PitEVKnqzWSFKWczQVNpF5OmZhkSjEP+LD9xpV+i0pphsWEOzKKyfuqzCF1CWr3ygrpJ4gnOmKKC6SKbrIld0bY3lKfugcmJ06kR3s+ry2RDRCSuXy2nwzLE0/oyjDo1l936YQhS67rfi9vBje8RTjQO/cW0qV4aeMIULnR24YH+poDwheKK616mSyUckLmGofHgOXUfVuARH9r5g0EHrN3M9r3QUBnUhGQCQzoEqHEstTOlKwmg3VmsEQ5Is1iZf+AkbnCZXHjhgNzmgqF92DKYAyJQjyuPkeGGzoqn1orRx3OaW/wA8Bbo8eH/2E+ahdezkxKPCX1P4j/Qkrd+0yg==
*/